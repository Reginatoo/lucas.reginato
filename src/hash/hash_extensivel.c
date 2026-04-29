#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_extensivel.h"

#define MAX_CHAVE 20
#define MAX_DADOS 512 
#define HEADER_SIZE ((long)(2 * sizeof(int)))

typedef struct {
    char chave[MAX_CHAVE];
    char dados[MAX_DADOS];
    int ativo;
} RegistroInterno;

typedef struct {
    int profundidade_local;
    int qtd_registro;
    RegistroInterno registros[10]; 
} Bucket;

struct TabelaEspalhamento {
    FILE* arquivo_dados;     
    FILE* arquivo_cabecalho;  
    char nome_base[256];
    int profundidade_global;
    int cap_bucket;
};

static unsigned int calcular_hash(const char *chave, int profundidade) {
    unsigned long h = 5381;
    int c;
    while ((c = *chave++)) h = ((h << 5) + h) + c;
    return (unsigned int)(h & ((1u << profundidade) - 1));
}

static int ler_offset_dir(TabelaEspalhamento *T, int indice) {
    int offset;
    fseek(T->arquivo_cabecalho, HEADER_SIZE + (indice * (int)sizeof(int)), SEEK_SET);
    if (fread(&offset, sizeof(int), 1, T->arquivo_cabecalho) != 1) return -1;
    return offset;
}

static void gravar_offset_dir(TabelaEspalhamento *T, int indice, int offset) {
    fseek(T->arquivo_cabecalho, HEADER_SIZE + (indice * (int)sizeof(int)), SEEK_SET);
    fwrite(&offset, sizeof(int), 1, T->arquivo_cabecalho);
}

static void ler_bucket(TabelaEspalhamento *T, int offset, Bucket* b) {
    fseek(T->arquivo_dados, offset, SEEK_SET);
    fread(b, sizeof(Bucket), 1, T->arquivo_dados);
}

static void gravar_bucket(TabelaEspalhamento *T, int offset, const Bucket *b) {
    fseek(T->arquivo_dados, offset, SEEK_SET);
    fwrite(b, sizeof(Bucket), 1, T->arquivo_dados);
    fflush(T->arquivo_dados);
}

TabelaEspalhamento* criaTabela(const char* nome_arq, int n) {
    TabelaEspalhamento* T = (TabelaEspalhamento*) malloc(sizeof(TabelaEspalhamento));
    char nome_hf[256], nome_hfc[256];
    snprintf(nome_hf, sizeof(nome_hf), "%s.hf", nome_arq);
    snprintf(nome_hfc, sizeof(nome_hfc), "%s.hfc", nome_arq);

    T->arquivo_dados = fopen(nome_hf, "rb+");
    T->arquivo_cabecalho = fopen(nome_hfc, "rb+");

    if (!T->arquivo_dados) { 
        T->arquivo_dados = fopen(nome_hf, "wb+");
        T->arquivo_cabecalho = fopen(nome_hfc, "wb+");
        T->profundidade_global = 1;
        T->cap_bucket = n;

        fwrite(&T->profundidade_global, sizeof(int), 1, T->arquivo_cabecalho);
        fwrite(&T->cap_bucket, sizeof(int), 1, T->arquivo_cabecalho);

        Bucket b_inicial;
        memset(&b_inicial, 0, sizeof(Bucket));
        b_inicial.profundidade_local = 1;

        gravar_offset_dir(T, 0, 0);
        gravar_offset_dir(T, 1, 0);
        gravar_bucket(T, 0, &b_inicial);
    } else {
        fseek(T->arquivo_cabecalho, 0, SEEK_SET);
        fread(&T->profundidade_global, sizeof(int), 1, T->arquivo_cabecalho);
        fread(&T->cap_bucket, sizeof(int), 1, T->arquivo_cabecalho);
    }
    strncpy(T->nome_base, nome_arq, 255);
    return T;
}

void insereRegistro(TabelaEspalhamento* T, const char* ch, void* r) {
    int indice = (int)calcular_hash(ch, T->profundidade_global);
    int offset = ler_offset_dir(T, indice);
    Bucket b;
    ler_bucket(T, offset, &b);

    if (b.qtd_registro < T->cap_bucket) {
        for (int i = 0; i < T->cap_bucket; i++) {
            if (!b.registros[i].ativo) {
                strncpy(b.registros[i].chave, ch, MAX_CHAVE - 1);
                b.registros[i].chave[MAX_CHAVE - 1] = '\0';
                memcpy(b.registros[i].dados, r, MAX_DADOS);
                b.registros[i].ativo = 1;
                b.qtd_registro++;
                break;
            }
        }
        gravar_bucket(T, offset, &b);
        return;
    }

    if (b.profundidade_local == T->profundidade_global) {
        int tam_antigo = 1 << T->profundidade_global;
        for (int i = 0; i < tam_antigo; i++) {
            int off = ler_offset_dir(T, i);
            gravar_offset_dir(T, i + tam_antigo, off);
        }
        T->profundidade_global++;
        fseek(T->arquivo_cabecalho, 0, SEEK_SET);
        fwrite(&T->profundidade_global, sizeof(int), 1, T->arquivo_cabecalho);
    }

    Bucket b_nova;
    memset(&b_nova, 0, sizeof(Bucket));
    b.profundidade_local++;
    b_nova.profundidade_local = b.profundidade_local;

    fseek(T->arquivo_dados, 0, SEEK_END);
    int novo_offset = (int)ftell(T->arquivo_dados);

    Bucket temp = b;
    b.qtd_registro = 0;
    for (int i = 0; i < T->cap_bucket; i++) b.registros[i].ativo = 0;

    for (int i = 0; i < T->cap_bucket; i++) {
        if (temp.registros[i].ativo) {
            unsigned int h = calcular_hash(temp.registros[i].chave, b.profundidade_local);
            if (h & (1u << (b.profundidade_local - 1))) {
                b_nova.registros[b_nova.qtd_registro++] = temp.registros[i];
            } else {
                b.registros[b.qtd_registro++] = temp.registros[i];
            }
        }
    }

    gravar_bucket(T, offset, &b);
    gravar_bucket(T, novo_offset, &b_nova);

    int tam_dir = 1 << T->profundidade_global;
    int bit_comparacao = 1 << (b.profundidade_local - 1);
    for (int i = 0; i < tam_dir; i++) {
        if (ler_offset_dir(T, i) == offset) {
            if (i & bit_comparacao) {
                gravar_offset_dir(T, i, novo_offset);
            }
        }
    }
    insereRegistro(T, ch, r);
}

void* buscaRegistro(TabelaEspalhamento* T, const char* ch) {
    int indice = (int)calcular_hash(ch, T->profundidade_global);
    int offset = ler_offset_dir(T, indice);
    Bucket b;
    ler_bucket(T, offset, &b);

    for (int i = 0; i < T->cap_bucket; i++) {
        if (b.registros[i].ativo && strcmp(b.registros[i].chave, ch) == 0) {
            void* res = malloc(MAX_DADOS);
            if (res) memcpy(res, b.registros[i].dados, MAX_DADOS);
            return res;
        }
    }
    return NULL;
}

int removeChave(TabelaEspalhamento* T, const char* ch) {
    int indice = (int)calcular_hash(ch, T->profundidade_global);
    int offset = ler_offset_dir(T, indice);
    Bucket b;
    ler_bucket(T, offset, &b);

    for (int i = 0; i < T->cap_bucket; i++) {
        if (b.registros[i].ativo && strcmp(b.registros[i].chave, ch) == 0) {
            b.registros[i].ativo = 0;
            b.qtd_registro--;
            gravar_bucket(T, offset, &b);
            return 1;
        }
    }
    return 0;
}

void imprimeTabela(TabelaEspalhamento* T, const char* nome_arq_saida) {
    FILE* f = fopen(nome_arq_saida, "w");
    if (!f) return;
    fprintf(f, "PG: %d\n", T->profundidade_global);
    int tam_dir = 1 << T->profundidade_global;
    for (int i = 0; i < tam_dir; i++) {
        int off = ler_offset_dir(T, i);
        Bucket b;
        ler_bucket(T, off, &b);
        fprintf(f, "D[%d]->O(%d) [PL:%d, Q:%d]\n", i, off, b.profundidade_local, b.qtd_registro);
    }
    fclose(f);
}

void killTabela(TabelaEspalhamento* T) {
    if (T) {
        if (T->arquivo_dados) fclose(T->arquivo_dados);
        if (T->arquivo_cabecalho) fclose(T->arquivo_cabecalho);
        free(T);
    }
}
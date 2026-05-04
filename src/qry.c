#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "qry.h"
#include "quadra.h"
#include "pessoa.h"
#include "svg.h"

extern void insereRegistro(void* T, const char* ch, void* r);
extern void* buscaRegistro(void* T, const char* ch);
extern int removeChave(void* T, const char* ch);
extern void percorreTabela(void* T, void (*cb)(void*, void*), void *aux);

struct censo_aux {
    int hab, mor, st;
    int hom, mul;
    int mor_h, mor_m;
    int st_h, st_m;
};

struct pq_aux {
    char cep[50];
    int total, n, s, l, o;
};

struct rq_aux {
    char cep[50];
    char cpfs[500][20];
    int qtd;
};

void cb_censo(void *dados, void *aux) {
    Pessoa p = (Pessoa)dados;
    struct censo_aux *c = (struct censo_aux *)aux;
    
    c->hab++;
    bool is_masc = (strcmp(getPessoaSexo(p), "M") == 0);
    
    if (is_masc) c->hom++;
    else c->mul++;
    
    if (isPessoaMorador(p)) {
        c->mor++;
        if (is_masc) c->mor_h++;
        else c->mor_m++;
    } else {
        c->st++;
        if (is_masc) c->st_h++;
        else c->st_m++;
    }
}

void cb_pq(void *dados, void *aux) {
    Pessoa p = (Pessoa)dados;
    struct pq_aux *pq = (struct pq_aux *)aux;
    
    if (isPessoaMorador(p) && strcmp(getPessoaCep(p), pq->cep) == 0) {
        pq->total++;
        char *face = getPessoaFace(p);
        if (strcmp(face, "N") == 0) pq->n++;
        else if (strcmp(face, "S") == 0) pq->s++;
        else if (strcmp(face, "L") == 0) pq->l++;
        else if (strcmp(face, "O") == 0) pq->o++;
    }
}

void cb_rq(void *dados, void *aux) {
    Pessoa p = (Pessoa)dados;
    struct rq_aux *rq = (struct rq_aux *)aux;
    
    if (isPessoaMorador(p) && strcmp(getPessoaCep(p), rq->cep) == 0) {
        if (rq->qtd < 500) {
            strcpy(rq->cpfs[rq->qtd], getPessoaCpf(p));
            rq->qtd++;
        }
    }
}

void lerArquivoQry(char *path_qry, char *path_txt, char *path_svg, void *hash_quadras, void *hash_pessoas) {
    FILE *f_qry = fopen(path_qry, "r");
    FILE *f_txt = fopen(path_txt, "w");
    FILE *f_svg = fopen(path_svg, "a");

    if (!f_qry || !f_txt || !f_svg) {
        if (f_qry) fclose(f_qry);
        if (f_txt) fclose(f_txt);
        if (f_svg) fclose(f_svg);
        return;
    }

    char linha[256], comando[10];
    char cep[50], cpf[20], nome[50], sobrenome[50], sexo[5], nasc[20], face[5], compl[50];
    int num;

    while (fgets(linha, sizeof(linha), f_qry)) {
        sscanf(linha, "%s", comando);

       if (strcmp(comando, "rq") == 0) {
            sscanf(linha, "%*s %s", cep);
            fprintf(f_txt, "Comando: %s", linha);
            
            Quadra q = buscaRegistro(hash_quadras, cep);
            if (q) {
                struct rq_aux aux;
                strcpy(aux.cep, cep);
                aux.qtd = 0; 
                percorreTabela(hash_pessoas, cb_rq, &aux);
                
                for (int i = 0; i < aux.qtd; i++) {
                    Pessoa p = buscaRegistro(hash_pessoas, aux.cpfs[i]);
                    if (p) {
                        fprintf(f_txt, "Despejado: %s - %s %s\n", getPessoaCpf(p), getPessoaNome(p), getPessoaSobrenome(p));
                        
                        removePessoaEndereco(p); 
                        removeChave(hash_pessoas, aux.cpfs[i]); 
                        insereRegistro(hash_pessoas, aux.cpfs[i], p); 
                        
                        destroiPessoa(p);
                    }
                }
                
                desenhaX(f_svg, getQuadraX(q), getQuadraY(q), "red");
                removeChave(hash_quadras, cep);
                destroiQuadra(q);
            }
        }
        else if (strcmp(comando, "Pq") == 0) {
            sscanf(linha, "%*s %s", cep);
            fprintf(f_txt, "Comando: %s", linha);
            
            Quadra q = buscaRegistro(hash_quadras, cep);
            if (q) {
                struct pq_aux aux = {"", 0, 0, 0, 0, 0};
                strcpy(aux.cep, cep);
                percorreTabela(hash_pessoas, cb_pq, &aux);
                
                double cx = getQuadraX(q) + (getQuadraW(q) / 2);
                double cy = getQuadraY(q) + (getQuadraH(q) / 2);
                
                char txt[10];
                sprintf(txt, "%d", aux.total);
                desenhaTexto(f_svg, cx, cy, txt);
                
                sprintf(txt, "%d", aux.n); desenhaTexto(f_svg, cx, getQuadraY(q) + getQuadraH(q) - 2, txt);
                sprintf(txt, "%d", aux.s); desenhaTexto(f_svg, cx, getQuadraY(q) + 5, txt);
                sprintf(txt, "%d", aux.l); desenhaTexto(f_svg, getQuadraX(q) + 2, cy, txt);
                sprintf(txt, "%d", aux.o); desenhaTexto(f_svg, getQuadraX(q) + getQuadraW(q) - 5, cy, txt);
                
                fprintf(f_txt, "Moradores na quadra %s: %d (N:%d, S:%d, L:%d, O:%d)\n", cep, aux.total, aux.n, aux.s, aux.l, aux.o);
                destroiQuadra(q);
            }
        }
        else if (strcmp(comando, "censo") == 0) {
            fprintf(f_txt, "Comando: %s", linha);
            
            struct censo_aux aux = {0, 0, 0, 0, 0, 0, 0, 0, 0};
            percorreTabela(hash_pessoas, cb_censo, &aux);
            
            fprintf(f_txt, "Total Habitantes: %d\n", aux.hab);
            fprintf(f_txt, "Total Moradores: %d (%.2f%% da populacao)\n", aux.mor, aux.hab > 0 ? (float)aux.mor / aux.hab * 100 : 0);
            fprintf(f_txt, "Habitantes Homens: %d (%.2f%%)\n", aux.hom, aux.hab > 0 ? (float)aux.hom / aux.hab * 100 : 0);
            fprintf(f_txt, "Habitantes Mulheres: %d (%.2f%%)\n", aux.mul, aux.hab > 0 ? (float)aux.mul / aux.hab * 100 : 0);
            fprintf(f_txt, "Moradores Homens: %d (%.2f%% dos moradores)\n", aux.mor_h, aux.mor > 0 ? (float)aux.mor_h / aux.mor * 100 : 0);
            fprintf(f_txt, "Moradores Mulheres: %d (%.2f%% dos moradores)\n", aux.mor_m, aux.mor > 0 ? (float)aux.mor_m / aux.mor * 100 : 0);
            fprintf(f_txt, "Total Sem-tetos: %d\n", aux.st);
            fprintf(f_txt, "Sem-tetos Homens: %d (%.2f%% dos sem-tetos)\n", aux.st_h, aux.st > 0 ? (float)aux.st_h / aux.st * 100 : 0);
            fprintf(f_txt, "Sem-tetos Mulheres: %d (%.2f%% dos sem-tetos)\n", aux.st_m, aux.st > 0 ? (float)aux.st_m / aux.st * 100 : 0);
        }
        else if (strcmp(comando, "dspj") == 0) {
            sscanf(linha, "%*s %s", cpf);
            fprintf(f_txt, "Comando: %s", linha);
            
            Pessoa p = buscaRegistro(hash_pessoas, cpf);
            if (p && isPessoaMorador(p)) {
                fprintf(f_txt, "Despejado: %s %s de CEP: %s\n", getPessoaNome(p), getPessoaSobrenome(p), getPessoaCep(p));
                
                Quadra q = buscaRegistro(hash_quadras, getPessoaCep(p));
                if (q) {
                    double exato_x, exato_y;
                    getQuadraEnderecoCoordenadas(q, getPessoaFace(p), getPessoaNum(p), &exato_x, &exato_y);
                 
                    desenhaCirculo(f_svg, exato_x, exato_y, 3, "black", "black");
                    destroiQuadra(q);
                }
                
                removePessoaEndereco(p);
                removeChave(hash_pessoas, cpf);
                insereRegistro(hash_pessoas, cpf, p);
                destroiPessoa(p);
            }
        }
    }

    fclose(f_qry);
    fclose(f_txt);
    fclose(f_svg);
}
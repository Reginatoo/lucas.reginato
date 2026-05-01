#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pm.h"
#include "pessoa.h"

extern void insereRegistro(void* T, const char* ch, void* r);
extern void* buscaRegistro(void* T, const char* ch);
extern int removeChave(void* T, const char* ch);

void lerArquivoPm(char *path_pm, void *hash_pessoas) {
    FILE *f = fopen(path_pm, "r");
    if (!f) return;

    char linha[256], comando[10];
    char cpf[20], nome[50], sobrenome[50], sexo[5], nasc[20];
    char cep[50], face[5], compl[50];
    int num;

    while (fgets(linha, sizeof(linha), f)) {
        sscanf(linha, "%s", comando);

        if (strcmp(comando, "p") == 0) {
            sscanf(linha, "%*s %s %s %s %s %s", cpf, nome, sobrenome, sexo, nasc);
            Pessoa p = criaPessoa(cpf, nome, sobrenome, sexo, nasc);
            
            insereRegistro(hash_pessoas, cpf, p);
            destroiPessoa(p);
        } 
        else if (strcmp(comando, "m") == 0) {
            compl[0] = '\0';
            int lidos = sscanf(linha, "%*s %s %s %s %d %[^\n]", cpf, cep, face, &num, compl);
            Pessoa p = buscaRegistro(hash_pessoas, cpf);
            
            if (p) {
                setPessoaEndereco(p, cep, face, num, lidos == 5 ? compl : NULL);
                removeChave(hash_pessoas, cpf);
                insereRegistro(hash_pessoas, cpf, p);
                
                destroiPessoa(p);
            }
        }
    }

    fclose(f);
}
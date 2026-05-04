#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pm.h"
#include "pessoa.h"
#include "hash_extensivel.h"

void lerArquivoPm(char *path_pm, void *hash_pessoas) {
    FILE *f = fopen(path_pm, "r");
    if (!f) return;

    char linha[512], comando[10];
    char cpf[20], nome[50], sobrenome[50], sexo[5], nasc[20];
    char cep[50], face[5], compl[50];
    int num;

    while (fgets(linha, sizeof(linha), f)) {
        if (sscanf(linha, "%s", comando) <= 0) continue;

        if (strcmp(comando, "p") == 0) {
            sscanf(linha, "%*s %s %s %s %s %s", cpf, nome, sobrenome, sexo, nasc);
            Pessoa p = criaPessoa(cpf, nome, sobrenome, sexo, nasc);
            if (p) {
                insereRegistro(hash_pessoas, cpf, p);
                destroiPessoa(p);
            }
        } 
        else if (strcmp(comando, "m") == 0) {
            memset(compl, 0, sizeof(compl));
            int lidos = sscanf(linha, "%*s %s %s %s %d %[^\n]", cpf, cep, face, &num, compl);
            Pessoa p = buscaRegistro(hash_pessoas, cpf);
            
            if (p) {
                char *complemento = (lidos == 5) ? compl : NULL;
                setPessoaEndereco(p, cep, face, num, complemento);
                removeChave(hash_pessoas, cpf);
                insereRegistro(hash_pessoas, cpf, p);
                destroiPessoa(p);
            }
        }
    }

    fclose(f);
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "pessoa.h"

struct pessoa {
    char cpf[20], nome[50], sobrenome[50], sexo[5], nasc[20];
    char cep[50], face[5], compl[50];
    int num;
    bool is_morador;
};

Pessoa criaPessoa(char *cpf, char *nome, char *sobrenome, char *sexo, char *nasc) {
    struct pessoa *p = malloc(sizeof(struct pessoa));
    
    if (!p) return NULL;
    
    strncpy(p->cpf, cpf, 19); p->cpf[19] = '\0';
    strncpy(p->nome, nome, 49); p->nome[49] = '\0';
    strncpy(p->sobrenome, sobrenome, 49); p->sobrenome[49] = '\0';
    strncpy(p->sexo, sexo, 4); p->sexo[4] = '\0';
    strncpy(p->nasc, nasc, 19); p->nasc[19] = '\0';
    
    p->is_morador = false;
    p->cep[0] = '\0';
    p->face[0] = '\0';
    p->compl[0] = '\0';
    p->num = -1;
    
    return p;
}

void destroiPessoa(Pessoa p) {
    if (p) free(p);
}

void setPessoaEndereco(Pessoa p, char *cep, char *face, int num, char *compl) {
    struct pessoa *pes = (struct pessoa *) p;
    if (!pes) return;
    
    strncpy(pes->cep, cep, 49); pes->cep[49] = '\0';
    strncpy(pes->face, face, 4); pes->face[4] = '\0';
    pes->num = num;
    
    if (compl) {
        strncpy(pes->compl, compl, 49); pes->compl[49] = '\0';
    } else {
        pes->compl[0] = '\0';
    }
    
    pes->is_morador = true;
}

void removePessoaEndereco(Pessoa p) {
    struct pessoa *pes = (struct pessoa *) p;
    if (!pes) return;
    
    pes->cep[0] = '\0';
    pes->face[0] = '\0';
    pes->compl[0] = '\0';
    pes->num = -1;
    pes->is_morador = false;
}

bool isPessoaMorador(Pessoa p) {
    return ((struct pessoa *)p)->is_morador;
}

char *getPessoaCpf(Pessoa p) {
    return ((struct pessoa *)p)->cpf;
}

char *getPessoaNome(Pessoa p) {
    return ((struct pessoa *)p)->nome;
}

char *getPessoaSobrenome(Pessoa p) {
    return ((struct pessoa *)p)->sobrenome;
}

char *getPessoaSexo(Pessoa p) {
    return ((struct pessoa *)p)->sexo;
}

char *getPessoaNasc(Pessoa p) {
    return ((struct pessoa *)p)->nasc;
}

char *getPessoaCep(Pessoa p) {
    return ((struct pessoa *)p)->cep;
}

char *getPessoaFace(Pessoa p) {
    return ((struct pessoa *)p)->face;
}

int getPessoaNum(Pessoa p) {
    return ((struct pessoa *)p)->num;
}

char *getPessoaCompl(Pessoa p) {
    return ((struct pessoa *)p)->compl;
}
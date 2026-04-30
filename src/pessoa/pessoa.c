#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "pessoa.h"

                struct pessoa {
                    char *cpf, *nome, *sobrenome, *sexo, *nasc;
                    char *cep, *face, *compl;
                    int num;
                    bool is_morador;
                };

              Pessoa criaPessoa(char *cpf, char *nome, char *sobrenome, char *sexo, char *nasc) {
               struct pessoa *p = malloc(sizeof(struct pessoa));
                
                if (!p) return NULL;
                
                p->cpf = malloc(strlen(cpf) + 1);
                strcpy(p->cpf, cpf);
                
                p->nome = malloc(strlen(nome) + 1);
                strcpy(p->nome, nome);
                
                p->sobrenome = malloc(strlen(sobrenome) + 1);
                strcpy(p->sobrenome, sobrenome);
                
                p->sexo = malloc(strlen(sexo) + 1);
                strcpy(p->sexo, sexo);
                
                p->nasc = malloc(strlen(nasc) + 1);
                strcpy(p->nasc, nasc);
                
                p->is_morador = false;
                p->cep = NULL;
                p->face = NULL;
                p->compl = NULL;
                p->num = -1;
                
                return p;
            }

            void destroiPessoa(Pessoa p) {
                struct pessoa *pes = (struct pessoa *) p;
                
                if (pes) {
                    if (pes->cpf) free(pes->cpf);
                    if (pes->nome) free(pes->nome);
                    if (pes->sobrenome) free(pes->sobrenome);
                    if (pes->sexo) free(pes->sexo);
                    if (pes->nasc) free(pes->nasc);
                    if (pes->cep) free(pes->cep);
                    if (pes->face) free(pes->face);
                    if (pes->compl) free(pes->compl);
                    
                    free(pes);
                }
            }

            void setPessoaEndereco(Pessoa p, char *cep, char *face, int num, char *compl) {
                struct pessoa *pes = (struct pessoa *) p;
                if (!pes) return;
                
                if (pes->cep) free(pes->cep);
                if (pes->face) free(pes->face);
                if (pes->compl) free(pes->compl);
                
                pes->cep = malloc(strlen(cep) + 1);
                strcpy(pes->cep, cep);
                
                pes->face = malloc(strlen(face) + 1);
                strcpy(pes->face, face);
                
                pes->num = num;
                
                if (compl) {
                    pes->compl = malloc(strlen(compl) + 1);
                    strcpy(pes->compl, compl);
                } else {
                    pes->compl = NULL;
                }
                
                pes->is_morador = true;
            }

            void removePessoaEndereco(Pessoa p) {
                struct pessoa *pes = (struct pessoa *) p;
                if (!pes) return;
                
                if (pes->cep) free(pes->cep);
                if (pes->face) free(pes->face);
                if (pes->compl) free(pes->compl);
                
                pes->cep = NULL;
                pes->face = NULL;
                pes->compl = NULL;
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
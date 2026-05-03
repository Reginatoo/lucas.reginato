#ifndef PESSOA_H
#define PESSOA_H

#include <stdbool.h>

/**
 * @brief tipo opaco que representa uma pessoa na cidade
 */
typedef void *Pessoa;

/**
 * @brief cria um habitante sem endereco 
 * @param cpf cpf do habitante
 * @param nome nome do habitante
 * @param sobrenome sobrenome do habitante
 * @param sexo sexo do habitante 
 * @param nasc data de nascimento 
 * @return ponteiro para a pessoa criada
 */
Pessoa criaPessoa(char *cpf, char *nome, char *sobrenome, char *sexo, char *nasc);

/**
 * @brief libera a memoria alocada para a pessoa
 * @param p ponteiro para a pessoa
 */
void destroiPessoa(Pessoa p);

/**
 * @brief define ou atualiza o endereco da pessoa, tornando-a moradora
 * @param p ponteiro para a pessoa
 * @param cep cep da quadra onde mora
 * @param face face da quadra 
 * @param num numero do endereco
 * @param compl complemento do endereco
 */
void setPessoaEndereco(Pessoa p, char *cep, char *face, int num, char *compl);

/**
 * @brief remove o endereco da pessoa tornando-a sem-teto
 * @param p ponteiro para a pessoa
 */
void removePessoaEndereco(Pessoa p);

/**
 * @brief verifica se a pessoa tem endereco
 * @param p ponteiro para a pessoa
 * @return true se for morador, false se for sem-teto
 */
bool isPessoaMorador(Pessoa p);

/**
 * @brief retorna o cpf da pessoa
 * @param p ponteiro para a pessoa
 * @return  o cpf
 */
char *getPessoaCpf(Pessoa p);

/**
 * @brief retorna o nome da pessoa
 * @param p ponteiro para a pessoa
 * @return  o nome
 */
char *getPessoaNome(Pessoa p);

/**
 * @brief retorna o sobrenome da pessoa
 * @param p ponteiro para a pessoa
 * @return  o sobrenome
 */
char *getPessoaSobrenome(Pessoa p);

/**
 * @brief retorna o sexo da pessoa
 * @param p ponteiro para a pessoa
 * @return  o sexo
 */
char *getPessoaSexo(Pessoa p);

/**
 * @brief retorna a data de nascimento da pessoa
 * @param p ponteiro para a pessoa
 * @return  a data de nascimento
 */
char *getPessoaNasc(Pessoa p);

/**
 * @brief retorna o cep do endereco da pessoa 
 * @param p ponteiro para a pessoa
 * @return  o cep ou null se for sem-teto
 */
char *getPessoaCep(Pessoa p);

/**
 * @brief retorna a face do endereco da pessoa
 * @param p ponteiro para a pessoa
 * @return  a face ou null
 */
char *getPessoaFace(Pessoa p);

/**
 * @brief retorna o numero do endereco da pessoa
 * @param p ponteiro para a pessoa
 * @return inteiro com o numero ou -1 se sem-teto
 */
int getPessoaNum(Pessoa p);

/**
 * @brief retorna o complemento do endereco da pessoa
 * @param p ponteiro para a pessoa
 * @return complemento ou null
 */
char *getPessoaCompl(Pessoa p);

#endif
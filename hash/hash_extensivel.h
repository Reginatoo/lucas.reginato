#ifndef HASH_EXTENSIVEL_H
#define HASH_EXTENSIVEL_H

typedef void* Registro;

typedef struct TabelaEspalhamento TabelaEspalhamento;

/**
 * @brief Cria uma tabela hash
 * @param n número de posições da tabela
 * @return ponteiro para a tabela
 */
TabelaEspalhamento* criaTabela(int n);

/**
 * @brief insere um novo registro
 * @param T tabela hash
 * @param ch chave do registro
 * @param r registro a ser armazenado
 */
void insereRegistro(TabelaEspalhamento* T, const char* ch, Registro r);

/**
 * @brief retorna o registro
 * @param T tabela hash
 * @param ch chave do registro
 * @return registro associado à chave 
 */
Registro getRegistro(TabelaEspalhamento* T, const char* ch);

/**
 * @brief busca um registro
 * @param T tabela hash
 * @param ch chave do registro
 * @return registro se encontrado, ou NULL se não existir
 */
Registro buscaRegistro(TabelaEspalhamento* T, const char* ch);

/**
 * @brief atualiza o registro de uma chave
 * @param T tabela hash
 * @param ch chave do registro
 * @param r novo valor para a chave
 */
void atualizaRegistro(TabelaEspalhamento* T, const char* ch, Registro r);

/**
 * @brief remove uma chave da tabela
 * @param T tabela hash
 * @param ch chave a ser removida
 */
void removeChave(TabelaEspalhamento* T, const char* ch);

/**
 * @brief retorna a quantidade de elementos na tabela
 * @param T tabela hash
 * @return número total de registros
 */
int tamanhoTabela(TabelaEspalhamento* T);

/**
 * @brief imprime o conteúdo da tabela
 * @param T tabela hash
 */
void imprimeTabela(TabelaEspalhamento* T);

/**
 * @brief libera toda a memória da tabela
 * @param T tabela hash
 */
void killTabela(TabelaEspalhamento* T);

#endif
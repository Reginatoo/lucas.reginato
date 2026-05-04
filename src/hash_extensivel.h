#ifndef HASH_EXTENSIVEL_H
#define HASH_EXTENSIVEL_H

typedef void* Registro;
#define MAX_CHAVE 20

typedef struct TabelaEspalhamento TabelaEspalhamento;

/**
 * @brief cria uma tabela hash
 * @param nome_arq nome base para os arquivos no disco
 * @param n capacidade do bucket
 * @param tam_registro tamanho em bytes da struct a ser salva
 * @return ponteiro para a tabela
 */
TabelaEspalhamento* criaTabela(const char* nome_arq, int n, int tam_registro);

/**
 * @brief insere um registro na hash em disco
 * @param T tabela hash
 * @param ch chave identificadora
 * @param r ponteiro para os dados
 */
void insereRegistro(TabelaEspalhamento* T, const char* ch, void* r);

/**
 * @brief busca um registro no arquivo binario
 * @param T tabela hash
 * @param ch chave de busca
 * @return ponteiro para o registro lido do disco ou null
 */
void* buscaRegistro(TabelaEspalhamento* T, const char* ch);

/**
 * @brief remove uma chave da tabela e do disco
 * @param T tabela hash
 * @param ch chave a ser removida
 * @return 1 se removeu com sucesso, 0 caso contrario
 */
int removeChave(TabelaEspalhamento* T, const char* ch);

/**
 * @brief imprime o conteudo da tabela para conferencia
 * @param T tabela hash
 * @param nome_arq_saida nome do arquivo de texto para o dump
 */
void imprimeTabela(TabelaEspalhamento* T, const char* nome_arq_saida);

/**
 * @brief percorre todos os registros da tabela executando uma funcao
 * @param T tabela hash
 * @param callback funcao a ser executada para cada registro
 * @param info_extra ponteiro para dados adicionais
 */
void percorreTabela(TabelaEspalhamento* T, void (*callback)(void* registro, void* info_extra), void* info_extra);

/**
 * @brief libera a memoria da tabela e fecha os arquivos hf
 * @param T tabela hash
 */
void killTabela(TabelaEspalhamento* T);

#endif
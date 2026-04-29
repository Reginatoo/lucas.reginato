#ifndef HASH_EXTENSIVEL_H
#define HASH_EXTENSIVEL_H

typedef void* Registro;
#define MAX_CHAVE 20

typedef struct TabelaEspalhamento TabelaEspalhamento;

/**
 * @brief Cria uma tabela hash
 * @param nome_arq Nome base para os arquivos no disco
 * @param n número de posições iniciais ou capacidade do bucket 
 * @return ponteiro para a tabela
 */
TabelaEspalhamento* criaTabela(const char* nome_arq, int n);

/**
 * @brief Insere um registro. Como é em disco, passamos o tamanho do dado.
 * @param T tabela hash
 * @param ch chave (ex: CPF ou CEP)
 * @param r ponteiro para a struct de dados (Quadra ou Pessoa)
 * @param tamRegistro tamanho em bytes da struct
 */
void insereRegistro(TabelaEspalhamento* T, const char* ch, void* r, size_t tamRegistro);

/**
 * @brief busca um registro
 * @param T tabela hash
 * @param ch chave do registro
 * @return registro se encontrado, ou NULL se não existir
 */
void* buscaRegistro(TabelaEspalhamento* T, const char* ch);

/**
 * @brief remove uma chave da tabela
 * @param T tabela hash
 * @param ch chave a ser removida
 * @return 1 se removeu com sucesso, 0 caso contrário
 */
int removeChave(TabelaEspalhamento* T, const char* ch);

/**
 * @brief imprime o conteúdo da tabela 
 * @param T tabela hash
 * @param nome_arq_saida Nome do arquivo de texto para o dump
 */
void imprimeTabela(TabelaEspalhamento* T, const char* nome_arq_saida);

/**
 * @brief libera toda a memória da tabela e fecha os arquivos
 * @param T tabela hash
 */
void killTabela(TabelaEspalhamento* T);

#endif
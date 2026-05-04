#include "unity.h"
#include "hash_extensivel.h"
#include <string.h>
#include <stdio.h>

void *tabela;

void setUp(void) {
    tabela = criaTabela("teste_unidade", 10);
}

void tearDown(void) {
    killTabela(tabela);
    remove("teste_unidade.hf");
}

void inserir_e_buscar_registro_com_sucesso(void) {
    char* meu_dado = "Dados do Aluno";
    
    insereTabela(tabela, "chave123", (void*)meu_dado);
    
    void* recuperado = buscaTabela(tabela, "chave123");
    TEST_ASSERT_NOT_NULL(recuperado);
    TEST_ASSERT_EQUAL_STRING(meu_dado, (char*)recuperado);
}

void remover_chave_da_tabela(void) {
    insereTabela(tabela, "temp", (void*)"dado");
    
    removeTabela(tabela, "temp"); 
    TEST_ASSERT_NULL(buscaTabela(tabela, "temp"));
}

void retornar_null_para_chave_inexistente(void) {
    void* resultado = buscaTabela(tabela, "chave_que_nao_existe");
    TEST_ASSERT_NULL(resultado);
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(inserir_e_buscar_registro_com_sucesso);
    RUN_TEST(remover_chave_da_tabela);
    RUN_TEST(retornar_null_para_chave_inexistente);

    return UNITY_END();
}
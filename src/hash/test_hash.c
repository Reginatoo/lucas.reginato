#include "unity.h"
#include "hash_extensivel.h"
#include <string.h>

TabelaEspalhamento* tabela;

void setUp(void) {
    tabela = criaTabela(10);
}

void tearDown(void) {
    killTabela(tabela);
}

void inserir_e_buscar_registro_com_sucesso(void) {
    char* meu_dado = "Dados do Aluno";
    
    insereRegistro(tabela, "chave123", (Registro)meu_dado);
    
    Registro recuperado = buscaRegistro(tabela, "chave123");
    TEST_ASSERT_NOT_NULL(recuperado);
    TEST_ASSERT_EQUAL_STRING(meu_dado, (char*)recuperado);
    
    TEST_ASSERT_EQUAL_INT(1, tamanhoTabela(tabela));
}

void atualizar_registro_existente(void) {
    insereRegistro(tabela, "A1", (Registro)"Versao Antiga");
    
    atualizaRegistro(tabela, "A1", (Registro)"Versao Nova");
    
    char* recuperado = (char*)getRegistro(tabela, "A1");
    TEST_ASSERT_EQUAL_STRING("Versao Nova", recuperado);
}

void remover_chave_da_tabela(void) {
    insereRegistro(tabela, "temp", (Registro)"dado");
    TEST_ASSERT_EQUAL_INT(1, tamanhoTabela(tabela));
    
    removeChave(tabela, "temp");
    TEST_ASSERT_NULL(buscaRegistro(tabela, "temp"));
    TEST_ASSERT_EQUAL_INT(0, tamanhoTabela(tabela));
}

void retornar_null_para_chave_inexistente(void) {
    Registro resultado = buscaRegistro(tabela, "chave_que_nao_existe");
    TEST_ASSERT_NULL(resultado);
}

void gerenciar_multiplas_insercoes(void) {
    insereRegistro(tabela, "id1", (Registro)"Data1");
    insereRegistro(tabela, "id2", (Registro)"Data2");
    insereRegistro(tabela, "id3", (Registro)"Data3");
    
    TEST_ASSERT_EQUAL_INT(3, tamanhoTabela(tabela));
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(inserir_e_buscar_registro_com_sucesso);
    RUN_TEST(atualizar_registro_existente);
    RUN_TEST(remover_chave_da_tabela);
    RUN_TEST(retornar_null_para_chave_inexistente);
    RUN_TEST(gerenciar_multiplas_insercoes);

    return UNITY_END();
}
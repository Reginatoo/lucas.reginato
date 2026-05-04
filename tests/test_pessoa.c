#include "unity.h"
#include "../src/pessoa/pessoa.h"
#include <string.h>
#include <stdbool.h>

void setUp(void) {}
void tearDown(void) {}

void test_cria_pessoa(void) {
    Pessoa p = criaPessoa("111.222.333-44", "Joao", "Silva", "M", "01/01/2000");
    
    TEST_ASSERT_NOT_NULL(p);
    TEST_ASSERT_EQUAL_STRING("111.222.333-44", getPessoaCpf(p));
    TEST_ASSERT_EQUAL_STRING("Joao", getPessoaNome(p));
    TEST_ASSERT_EQUAL_STRING("Silva", getPessoaSobrenome(p));
    TEST_ASSERT_EQUAL_STRING("M", getPessoaSexo(p));
    TEST_ASSERT_EQUAL_STRING("01/01/2000", getPessoaNasc(p));
    
    TEST_ASSERT_FALSE(isPessoaMorador(p));
    
    destroiPessoa(p);
}

void test_endereco_pessoa(void) {
    Pessoa p = criaPessoa("123", "Maria", "Souza", "F", "15/05/1990");
    
    setPessoaEndereco(p, "86010-000", "L", 50, "Apt 101");

    TEST_ASSERT_TRUE(isPessoaMorador(p));
    TEST_ASSERT_EQUAL_STRING("86010-000", getPessoaCep(p));
    TEST_ASSERT_EQUAL_STRING("L", getPessoaFace(p));
    TEST_ASSERT_EQUAL_INT(50, getPessoaNum(p));
    TEST_ASSERT_EQUAL_STRING("Apt 101", getPessoaCompl(p));

    removePessoaEndereco(p);
    
    TEST_ASSERT_FALSE(isPessoaMorador(p));
    TEST_ASSERT_EQUAL_STRING("", getPessoaCep(p));
    TEST_ASSERT_EQUAL_STRING("", getPessoaFace(p));
    TEST_ASSERT_EQUAL_INT(-1, getPessoaNum(p));

    destroiPessoa(p);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_cria_pessoa);
    RUN_TEST(test_endereco_pessoa);
    return UNITY_END();
}
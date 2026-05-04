#include "unity.h"
#include "../src/quadra/quadra.h"
#include <string.h>

void setUp(void) {}
void tearDown(void) {}

void test_cria_quadra(void) {
    Quadra q = criaQuadra("86010-000", 10.0, 20.0, 100.0, 50.0, "red", "black", 1.5);
    
    TEST_ASSERT_NOT_NULL(q);
    TEST_ASSERT_EQUAL_STRING("86010-000", getQuadraCep(q));
    TEST_ASSERT_EQUAL_DOUBLE(10.0, getQuadraX(q));
    TEST_ASSERT_EQUAL_DOUBLE(20.0, getQuadraY(q));
    TEST_ASSERT_EQUAL_DOUBLE(100.0, getQuadraW(q));
    TEST_ASSERT_EQUAL_DOUBLE(50.0, getQuadraH(q));
    TEST_ASSERT_EQUAL_STRING("red", getQuadraFill(q));
    TEST_ASSERT_EQUAL_STRING("black", getQuadraStroke(q));
    TEST_ASSERT_EQUAL_DOUBLE(1.5, getQuadraSw(q));
    
    destroiQuadra(q);
}

void test_coordenadas_face(void) {
    Quadra q = criaQuadra("123", 10.0, 10.0, 100.0, 100.0, "white", "black", 1.0);
    double out_x, out_y;

    getQuadraEnderecoCoordenadas(q, "S", 25, &out_x, &out_y);
    TEST_ASSERT_EQUAL_DOUBLE(35.0, out_x);
    TEST_ASSERT_EQUAL_DOUBLE(10.0, out_y);

    getQuadraEnderecoCoordenadas(q, "N", 25, &out_x, &out_y);
    TEST_ASSERT_EQUAL_DOUBLE(35.0, out_x);
    TEST_ASSERT_EQUAL_DOUBLE(110.0, out_y);

    destroiQuadra(q);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_cria_quadra);
    RUN_TEST(test_coordenadas_face);
    return UNITY_END();
}
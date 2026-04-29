#ifndef QUADRA_H
#define QUADRA_H

typedef void *Quadra;

/**
 * @brief cria uma instancia de quadra com os parametros do comando q
 * @param cep identificador unico da quadra
 * @param x coordenada x do ponto de ancoragem
 * @param y coordenada y do ponto de ancoragem
 * @param w largura da quadra
 * @param h altura da quadra
 * @param fill cor de preenchimento
 * @param stroke cor da borda
 * @param sw espessura da borda
 * @return ponteiro para a quadra criada
 */
Quadra criaQuadra(char *cep, double x, double y, double w, double h, char *fill, char *stroke, double sw);

/**
 * @brief libera a memoria ocupada pela quadra
 * @param q ponteiro para a quadra a ser removida
 */
void destroiQuadra(Quadra q);

/**
 * @brief retorna o cep da quadra
 * @param q ponteiro para a quadra
 * @return o cep
 */
char *getQuadraCep(Quadra q);

/**
 * @brief retorna a coordenada x da quadra
 * @param q ponteiro para a quadra
 * @return valor x
 */
double getQuadraX(Quadra q);

/**
 * @brief retorna a coordenada y da quadra
 * @param q ponteiro para a quadra
 * @return valor y
 */
double getQuadraY(Quadra q);

/**
 * @brief retorna a largura da quadra
 * @param q ponteiro para a quadra
 * @return largura w
 */
double getQuadraW(Quadra q);

/**
 * @brief retorna a altura da quadra
 * @param q ponteiro para a quadra
 * @return altura h
 */
double getQuadraH(Quadra q);

/**
 * @brief retorna a cor de preenchimento da quadra
 * @param q ponteiro para a quadra
 * @return  cor de preenchimento
 */
char *getQuadraFill(Quadra q);

/**
 * @brief retorna a cor da borda da quadra
 * @param q ponteiro para a quadra
 * @return  cor da borda
 */
char *getQuadraStroke(Quadra q);

/**
 * @brief retorna a espessura da borda da quadra
 * @param q ponteiro para a quadra
 * @return valor da espessura sw
 */
double getQuadraSw(Quadra q);

#endif
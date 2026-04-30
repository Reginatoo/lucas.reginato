#ifndef SVG_H
#define SVG_H

#include <stdio.h>

/**
 * @brief inicia o arquivo svg 
 * @param f ponteiro para o arquivo
 */
void iniciaSvg(FILE *f);

/**
 * @brief fecha a tag do arquivo svg
 * @param f ponteiro para o arquivo
 */
void fechaSvg(FILE *f);

/**
 * @brief desenha um retangulo 
 * @param f ponteiro para o arquivo
 * @param x coordenada x
 * @param y coordenada y
 * @param w largura
 * @param h altura
 * @param fill cor de preenchimento
 * @param stroke cor da borda
 * @param sw espessura da borda
 */
void desenhaRetangulo(FILE *f, double x, double y, double w, double h, char *fill, char *stroke, double sw);

/**
 * @brief escreve um texto no svg 
 * @param f ponteiro para o arquivo
 * @param x coordenada x
 * @param y coordenada y
 * @param texto conteudo a ser escrito
 */
void desenhaTexto(FILE *f, double x, double y, char *texto);

/**
 * @brief desenha uma marca de x 
 * @param f ponteiro para o arquivo
 * @param x coordenada x
 * @param y coordenada y
 * @param cor cor do x
 */
void desenhaX(FILE *f, double x, double y, char *cor);

/**
 * @brief desenha uma cruz 
 * @param f ponteiro para o arquivo
 * @param x coordenada x
 * @param y coordenada y
 * @param cor cor da cruz
 */
void desenhaCruz(FILE *f, double x, double y, char *cor);

/**
 * @brief desenha um circulo 
 * @param f ponteiro para o arquivo
 * @param x coordenada x do centro
 * @param y coordenada y do centro
 * @param r raio
 * @param fill cor de preenchimento
 * @param stroke cor da borda
 */
void desenhaCirculo(FILE *f, double x, double y, double r, char *fill, char *stroke);

#endif
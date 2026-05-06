#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "quadra.h"

struct quadra {
    char cep[50], fill[50], stroke[50];
    double x_nw, y_nw;
    double w, h, sw;
    double x_ancora, y_ancora;
};

Quadra criaQuadra(char *cep, double x, double y, double w, double h, char *fill, char *stroke, double sw) {
    struct quadra *q = calloc(1, sizeof(struct quadra));
    if (!q) return NULL;

    strncpy(q->cep, cep, 49); q->cep[49] = '\0';
    strncpy(q->fill, fill, 49); q->fill[49] = '\0';
    strncpy(q->stroke, stroke, 49); q->stroke[49] = '\0';

    q->x_ancora = x;
    q->y_ancora = y;
    q->w = w;
    q->h = h;
    q->sw = sw;

    q->x_nw = x - w;
    q->y_nw = y - h;

    return q;
}

double getQuadraX(Quadra q) {
     return ((struct quadra *)q)->x_nw;
 }
double getQuadraY(Quadra q){
     return ((struct quadra *)q)->y_nw;
     }
char *getQuadraCep(Quadra q){
     return ((struct quadra *)q)->cep;
 }
double getQuadraW(Quadra q) {
     return ((struct quadra *)q)->w;
     }
double getQuadraH(Quadra q) {
     return ((struct quadra *)q)->h;
     }
char *getQuadraFill(Quadra q) {
     return ((struct quadra *)q)->fill; 
    }
char *getQuadraStroke(Quadra q) {
     return ((struct quadra *)q)->stroke; 
    }
double getQuadraSw(Quadra q) { 
    return ((struct quadra *)q)->sw;
 }

void destroiQuadra(Quadra q) {
    if (q) free(q);
}

void getQuadraEnderecoCoordenadas(Quadra q, char *face, int num, double *out_x, double *out_y) {
    struct quadra *qd = (struct quadra *) q;
    
    if (strcmp(face, "N") == 0) {
        *out_x = qd->x_ancora - num; 
        *out_y = qd->y_nw;
    } else if (strcmp(face, "S") == 0) {
        *out_x = qd->x_ancora - num;
        *out_y = qd->y_ancora;
    } else if (strcmp(face, "L") == 0) {
        *out_x = qd->x_nw;
        *out_y = qd->y_ancora - num;
    } else if (strcmp(face, "O") == 0) {
        *out_x = qd->x_ancora;
        *out_y = qd->y_ancora - num;
    }
}
size_t getTamanhoQuadra() {
    return sizeof(struct quadra);
}
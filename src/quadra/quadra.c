#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "quadra.h"

struct quadra {
    char cep[50], fill[50], stroke[50];
    double x, y, w, h, sw;
};

Quadra criaQuadra(char *cep, double x, double y, double w, double h, char *fill, char *stroke, double sw) {
    struct quadra *q = malloc(sizeof(struct quadra));
    
    if (!q) return NULL;
    
    strncpy(q->cep, cep, 49); q->cep[49] = '\0';
    strncpy(q->fill, fill, 49); q->fill[49] = '\0';
    strncpy(q->stroke, stroke, 49); q->stroke[49] = '\0';
    
    q->x = x;
    q->y = y;
    q->w = w;
    q->h = h;
    q->sw = sw;
    
    return q;
}

void destroiQuadra(Quadra q) {
    if (q) free(q);
}

char *getQuadraCep(Quadra q) {
    return ((struct quadra *)q)->cep;
}

double getQuadraX(Quadra q) {
    return ((struct quadra *)q)->x;
}

double getQuadraY(Quadra q) {
    return ((struct quadra *)q)->y;
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
void getQuadraEnderecoCoordenadas(Quadra q, char *face, int num, double *out_x, double *out_y) {
    struct quadra *qd = (struct quadra *) q;
    
    if (strcmp(face, "S") == 0) {
        *out_x = qd->x + num;
        *out_y = qd->y;
    } else if (strcmp(face, "N") == 0) {
        *out_x = qd->x + num;
        *out_y = qd->y + qd->h;
    } else if (strcmp(face, "L") == 0) {
        *out_x = qd->x;
        *out_y = qd->y + num;
    } else if (strcmp(face, "O") == 0) {
        *out_x = qd->x + qd->w;
        *out_y = qd->y + num;
    }
}

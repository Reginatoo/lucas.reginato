        #include <stdio.h>
        #include <stdlib.h>
        #include <string.h>
        #include "quadra.h"

        struct quadra {
            char *cep, *fill, *stroke;
            double x, y, w, h, sw;
        };

        Quadra criaQuadra(char *cep, double x, double y, double w, double h, char *fill, char *stroke, double sw) {
            struct quadra *q = malloc(sizeof(struct quadra));
            
            if (!q) return NULL;
            
            q->cep = malloc(strlen(cep) + 1);
            strcpy(q->cep, cep);
            
            q->fill = malloc(strlen(fill) + 1);
            strcpy(q->fill, fill);
            
            q->stroke = malloc(strlen(stroke) + 1);
            strcpy(q->stroke, stroke);
            
            q->x = x;
            q->y = y;
            q->w = w;
            q->h = h;
            q->sw = sw;
            
            return q;
        }

        void destroiQuadra(Quadra q) {
            struct quadra *qd = (struct quadra *) q;
            
            if (qd) {
                if (qd->cep) free(qd->cep);
                if (qd->fill) free(qd->fill);
                if (qd->stroke) free(qd->stroke);
                free(qd);
            }
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
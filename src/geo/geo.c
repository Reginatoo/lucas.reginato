#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "quadra.h"

extern void insereRegistro(void* T, const char* ch, void* r);

void lerArquivoGeo(char *path_geo, void *hash_quadras) {
    FILE *f = fopen(path_geo, "r");
    if (!f) return;

    char linha[256], comando[10];
    char cfill[50] = "white", cstrk[50] = "black";
    double sw = 1.0;
    
    char cep[50];
    double x, y, w, h;

    while (fgets(linha, sizeof(linha), f)) {
        sscanf(linha, "%s", comando);

        if (strcmp(comando, "cq") == 0) {
            sscanf(linha, "%*s %lf %s %s", &sw, cfill, cstrk);
        } 
        else if (strcmp(comando, "q") == 0) {
            sscanf(linha, "%*s %s %lf %lf %lf %lf", cep, &x, &y, &w, &h);
            Quadra q = criaQuadra(cep, x, y, w, h, cfill, cstrk, sw);
            
            insereRegistro(hash_quadras, cep, q);
            
            destroiQuadra(q);
        }
    }

    fclose(f);
}
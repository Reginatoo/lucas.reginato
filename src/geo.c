#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "geo.h"
#include "quadra.h"
#include "hash_extensivel.h"
#include "svg.h"

void lerArquivoGeo(char *path_geo, char *path_svg_base, void *hash_quadras) {
    FILE *f_geo = fopen(path_geo, "r");
    if (!f_geo) return;

    FILE *f_svg = fopen(path_svg_base, "a");
    if (!f_svg) {
        fclose(f_geo);
        return;
    }

    char tipo[32];
    char cor_preenchimento[32] = "white"; 
    char cor_contorno[32] = "black";      
    double espessura_borda = 1.0;

    while (fscanf(f_geo, "%s", tipo) != EOF) {
        if (strcmp(tipo, "q") == 0) {
            char cep[50];
            double x, y, w, h;
            fscanf(f_geo, "%s %lf %lf %lf %lf", cep, &x, &y, &w, &h);

            Quadra q = criaQuadra(cep, x, y, w, h, cor_preenchimento, cor_contorno, espessura_borda);
            insereRegistro(hash_quadras, cep, q);
            destroiQuadra(q);

            double x_desenho = x - w;
            double y_desenho = y - h;
            desenhaRetangulo(f_svg, x_desenho, y_desenho, w, h, cor_preenchimento, cor_contorno, espessura_borda);
            desenhaTexto(f_svg, x_desenho + 2, y_desenho + 12, cep);
        }
        else if (strcmp(tipo, "cq") == 0) {
            fscanf(f_geo, "%lf %s %s", &espessura_borda, cor_contorno, cor_preenchimento);
        }
    }

    fclose(f_geo);
    fclose(f_svg);
}
#include "svg.h"

void iniciaSvg(FILE *f) {
    fprintf(f, "<svg xmlns=\"http://www.w3.org/2000/svg\">\n");
}

void fechaSvg(FILE *f) {
    fprintf(f, "</svg>\n");
}

void desenhaRetangulo(FILE *f, double x, double y, double w, double h, char *fill, char *stroke, double sw) {
    fprintf(f, "<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" fill=\"%s\" stroke=\"%s\" stroke-width=\"%f\" />\n", x, y, w, h, fill, stroke, sw);
}

void desenhaTexto(FILE *f, double x, double y, char *texto) {
    fprintf(f, "<text x=\"%f\" y=\"%f\" font-family=\"Verdana\" font-size=\"5\">%s</text>\n", x, y, texto);
}

void desenhaX(FILE *f, double x, double y, char *cor) {
    fprintf(f, "<text x=\"%f\" y=\"%f\" fill=\"%s\" font-family=\"Verdana\" font-size=\"10\">X</text>\n", x, y, cor);
}

void desenhaCruz(FILE *f, double x, double y, char *cor) {
    fprintf(f, "<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" stroke=\"%s\" stroke-width=\"1\" />\n", x - 2, y, x + 2, y, cor);
    fprintf(f, "<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" stroke=\"%s\" stroke-width=\"1\" />\n", x, y - 2, x, y + 2, cor);
}

void desenhaCirculo(FILE *f, double x, double y, double r, char *fill, char *stroke) {
    fprintf(f, "<circle cx=\"%f\" cy=\"%f\" r=\"%f\" fill=\"%s\" stroke=\"%s\" />\n", x, y, r, fill, stroke);
}
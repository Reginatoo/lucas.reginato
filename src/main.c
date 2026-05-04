#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "geo.h"
#include "pm.h"
#include "qry.h"
#include "hash_extensivel.h"

void extraiNomeBase(char *caminho, char *nomeBase) {
    char temp[256];
    strcpy(temp, caminho);
    
    char *barra = strrchr(temp, '/');
    char *ficheiro = barra ? barra + 1 : temp;
    
    char *ponto = strrchr(ficheiro, '.');
    if (ponto) *ponto = '\0';
    
    strcpy(nomeBase, ficheiro);
}

void juntaCaminho(char *dir, char *ficheiro, char *destino) {
    if (dir == NULL || strlen(dir) == 0) {
        strcpy(destino, ficheiro);
    } else {
        strcpy(destino, dir);
        if (dir[strlen(dir) - 1] != '/') {
            strcat(destino, "/");
        }
        strcat(destino, ficheiro);
    }
}

int main(int argc, char *argv[]) {
    char *dir_e = NULL;
    char *dir_o = NULL;
    char *arq_f = NULL;
    char *arq_q = NULL;
    char *arq_pm = NULL;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-e") == 0) dir_e = argv[++i];
        else if (strcmp(argv[i], "-f") == 0) arq_f = argv[++i];
        else if (strcmp(argv[i], "-o") == 0) dir_o = argv[++i];
        else if (strcmp(argv[i], "-q") == 0) arq_q = argv[++i];
        else if (strcmp(argv[i], "-pm") == 0) arq_pm = argv[++i];
    }

    if (!arq_f || !dir_o) {
        printf("Erro: Os parametros -f e -o sao obrigatorios!\n");
        return 1;
    }

    char path_geo[512] = "", path_pm[512] = "", path_qry[512] = "";
    juntaCaminho(dir_e, arq_f, path_geo);
    if (arq_pm) juntaCaminho(dir_e, arq_pm, path_pm);
    if (arq_q) juntaCaminho(dir_e, arq_q, path_qry);

    char base_geo[128], base_qry[128];
    extraiNomeBase(arq_f, base_geo);
    if (arq_q) extraiNomeBase(arq_q, base_qry);

    char path_base_saida[512];
    juntaCaminho(dir_o, base_geo, path_base_saida);

    char path_svg_geo[512];
    sprintf(path_svg_geo, "%s.svg", path_base_saida);

    char nome_hf_quadras[512], nome_hf_pessoas[512];
    sprintf(nome_hf_quadras, "%s_quadras", path_base_saida);
    sprintf(nome_hf_pessoas, "%s_pessoas", path_base_saida);

    void *hash_quadras = criaTabela(nome_hf_quadras, 10);
    void *hash_pessoas = criaTabela(nome_hf_pessoas, 10);

    FILE *f_svg_base = fopen(path_svg_geo, "w");
    if (f_svg_base) {
        fprintf(f_svg_base, "<svg xmlns=\"http://www.w3.org/2000/svg\">\n");
        fclose(f_svg_base);
    }
    
    lerArquivoGeo(path_geo, path_svg_geo, hash_quadras);

    if (arq_pm) {
        lerArquivoPm(path_pm, hash_pessoas);
    }

    if (arq_q) {
        char path_txt[512], path_svg_qry[512];
        sprintf(path_txt, "%s/%s-%s.txt", dir_o, base_geo, base_qry);
        sprintf(path_svg_qry, "%s/%s-%s.svg", dir_o, base_geo, base_qry);
        
        char comando_cp[1024];
        #ifdef _WIN32
            sprintf(comando_cp, "copy \"%s\" \"%s\"", path_svg_geo, path_svg_qry);
        #else
            sprintf(comando_cp, "cp \"%s\" \"%s\"", path_svg_geo, path_svg_qry);
        #endif
        system(comando_cp);

        lerArquivoQry(path_qry, path_txt, path_svg_qry, hash_quadras, hash_pessoas);
        
        FILE *f_qry_svg = fopen(path_svg_qry, "a");
        if (f_qry_svg) {
            fprintf(f_qry_svg, "</svg>\n");
            fclose(f_qry_svg);
        }
    }

    FILE *f_geo_close = fopen(path_svg_geo, "a");
    if (f_geo_close) {
        fprintf(f_geo_close, "</svg>\n");
        fclose(f_geo_close);
    }

    char path_hfd_quadras[512], path_hfd_pessoas[512];
    sprintf(path_hfd_quadras, "%s_quadras.hfd", path_base_saida);
    sprintf(path_hfd_pessoas, "%s_pessoas.hfd", path_base_saida);
    
    imprimeTabela(hash_quadras, path_hfd_quadras);
    imprimeTabela(hash_pessoas, path_hfd_pessoas);

    killTabela(hash_quadras);
    killTabela(hash_pessoas);

    return 0;
}
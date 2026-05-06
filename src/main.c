#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "geo.h"
#include "pm.h"
#include "qry.h"
#include "hash_extensivel.h"
#include "svg.h" 
#include "quadra.h"
#include "pessoa.h"

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

    char path_geo[2048] = "", path_pm[2048] = "", path_qry[2048] = "";
    juntaCaminho(dir_e, arq_f, path_geo);
    if (arq_pm) juntaCaminho(dir_e, arq_pm, path_pm);
    if (arq_q) juntaCaminho(dir_e, arq_q, path_qry);

    char base_geo[128], base_qry[128];
    extraiNomeBase(arq_f, base_geo);
    if (arq_q) extraiNomeBase(arq_q, base_qry);

    char path_base_saida[2048];
    juntaCaminho(dir_o, base_geo, path_base_saida);

    char path_svg_geo[2048];
    snprintf(path_svg_geo, sizeof(path_svg_geo), "%s.svg", path_base_saida);

    char nome_hf_quadras[2048], nome_hf_pessoas[2048];
    snprintf(nome_hf_quadras, sizeof(nome_hf_quadras), "%s_quadras", path_base_saida);
    snprintf(nome_hf_pessoas, sizeof(nome_hf_pessoas), "%s_pessoas", path_base_saida);

    void *hash_quadras = criaTabela(nome_hf_quadras, 10, getTamanhoQuadra());
    void *hash_pessoas = criaTabela(nome_hf_pessoas, 10, getTamanhoPessoa());
    
    FILE *f_svg_base = fopen(path_svg_geo, "w");
    if (f_svg_base) {
        iniciaSvg(f_svg_base); 
        fclose(f_svg_base);
    }
    
    lerArquivoGeo(path_geo, path_svg_geo, hash_quadras);

    if (arq_pm) {
        lerArquivoPm(path_pm, hash_pessoas, hash_quadras);
    }

    if (arq_q) {
        char path_txt[2048], path_svg_qry[2048];
        sprintf(path_txt, "%s/%s-%s.txt", dir_o, base_geo, base_qry);
        sprintf(path_svg_qry, "%s/%s-%s.svg", dir_o, base_geo, base_qry);
        
        char comando_cp[4096];
        #ifdef _WIN32
            sprintf(comando_cp, "copy \"%s\" \"%s\"", path_svg_geo, path_svg_qry);
        #else
            snprintf(comando_cp, sizeof(comando_cp), "cp \"%s\" \"%s\"", path_svg_geo, path_svg_qry);
        #endif
        system(comando_cp);

        lerArquivoQry(path_qry, path_txt, path_svg_qry, hash_quadras, hash_pessoas);
        
        FILE *f_qry_svg = fopen(path_svg_qry, "a");
        if (f_qry_svg) {
            fechaSvg(f_qry_svg); 
            fclose(f_qry_svg);
        }
    }

    FILE *f_geo_close = fopen(path_svg_geo, "a");
    if (f_geo_close) {
        fechaSvg(f_geo_close); 
        fclose(f_geo_close);
    }

    char path_hfd_quadras[2048], path_hfd_pessoas[2048];
    snprintf(path_hfd_quadras, sizeof(path_hfd_quadras), "%s_quadras.hfd", path_base_saida);
    snprintf(path_hfd_pessoas, sizeof(path_hfd_pessoas), "%s_pessoas.hfd", path_base_saida);
    
    imprimeTabela(hash_quadras, path_hfd_quadras);
    imprimeTabela(hash_pessoas, path_hfd_pessoas);

    killTabela(hash_quadras);
    killTabela(hash_pessoas);

    return 0;
}
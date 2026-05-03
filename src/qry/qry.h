#ifndef QRY_H
#define QRY_H

/**
 * @brief le o arquivo qry
 * @param path_qry caminho do arquivo .qry
 * @param path_txt caminho do arquivo .txt 
 * @param path_svg caminho do arquivo .svg  
 * @param hash_quadras ponteiro para o hash de quadras
 * @param hash_pessoas ponteiro para o hash de pessoas
 */
void lerArquivoQry(char *path_qry, char *path_txt, char *path_svg, void *hash_quadras, void *hash_pessoas);

#endif
#ifndef PM_H
#define PM_H

/**
 * @brief processa o arquivo .pm 
 * @param path_pm caminho completo do arquivo .pm 
 * @param hash_pessoas ponteiro para onde as pessoas serao salvas
 * @param hash_quadras ponteiro para a hash de quadras
 */
void lerArquivoPm(char *path_pm, void *hash_pessoas, void *hash_quadras);

#endif
#ifndef PM_H
#define PM_H

/**
 * @brief processa o arquivo .pm 
 * @param path_pm caminho completo do arquivo .pm 
 * @param hash_pessoas ponteiro para onde as pessoas serao salvas
 */
void lerArquivoPm(char *path_pm, void *hash_pessoas);

#endif
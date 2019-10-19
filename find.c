// Feito por: Luiz Gustavo Nunes e Luis Gabriel Kingeski
// Data: 15/10/2019

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h> 

int tamanho = 0;

int busca[10000][10000];
char arquivos[10000][10000];

int comparar(char *padrao, char *texto) {

    if (*padrao == '\0' && *texto == '\0')
        return 1; 

    if (*padrao == '*' && *(padrao + 1) != '\0' && *texto == '\0')
        return 0; 
  
    if (*padrao == '?' || *padrao == *texto)
        return comparar(padrao + 1, texto + 1);

    if (*padrao == '*')
        return comparar(padrao + 1, texto) || comparar(padrao, texto + 1);

    return 0;
}

void buscar(char *caminho, char *padrao) {
    char novo_caminho[10000];
    struct dirent *entrada;
    DIR *dir = opendir(caminho);

    while ((entrada = readdir(dir)) != NULL) {
        strcpy(novo_caminho, caminho);
        strcat(novo_caminho, "/");
        strcat(novo_caminho, entrada -> d_name);

        if (strcmp(entrada -> d_name, ".") == 0 || strcmp(entrada -> d_name, "..") == 0)
            continue;

        if (entrada -> d_type == DT_DIR) {
            buscar(novo_caminho, padrao);
        } else {
            if (comparar(padrao, entrada -> d_name))
                strcpy(arquivos[tamanho++], novo_caminho);
        }
    }

    closedir(dir);
}

int main(int numParametros, char *parametros[]) {

    int i;

    // 1º parâmetro = caminho
    // 2º parâmetro = arquivo

    // Sempre passar o segundo parâmetro entre aspas duplas!

switch (numParametros) {

    case 1: 
        printf("Você precisa passar o(s) parâmetro(s)!\nExemplo: ./find <caminho_do_arquivo> <nome_do_arquivo>\n");
        exit(0);
    break;
    
    case 2:
        if (strcmp(parametros[1], ".") == 0) {
            buscar(parametros[1], "*");
        } else {
          buscar(".", parametros[1]);  
        }

        if (strcmp(parametros[1], ".") != 0) {
            printf("Não foram encontrados arquivos com esse nome.\n");
        }
    break;

    case 3:
        buscar(parametros[1], parametros[2]);
    break;

    default:
        printf("O número máximo de parâmetros é de 2.\n");
    break;
}

    if (tamanho == 0) {
    //   printf("Não foram encontrados arquivos com esse nome.\n");
    } else {
        printf("Arquivos Encontrados:\n--------------------------------------------------------------------------------------------------\n");
      for (i = 0; i < tamanho; i++) {
        printf("---> %s\n", arquivos[i]);
      }
      printf("--------------------------------------------------------------------------------------------------\nTotal de Arquivos Encontrados: %d\n", i);
    }

    return 0;
}
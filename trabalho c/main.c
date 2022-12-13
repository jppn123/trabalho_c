#include "funcoes.h"

int main(int argc, char *argv[]) {
  FILE *txt;
  DIR *d, *d_mean;
  clock_t begin, end;
  struct pgm img, img_mean;
  struct dirent *dir=NULL, *dir_mean=NULL;
  int cont = 0, k, *scm=NULL, quantizacao = atoi(argv[1]);
  double time_per_img, time_total = 0;
  char id[50], nome_arquivo[50], mean[10]="mean",itsmean , nome_arquivo_mean[50], type, outname[50] = "SCM-Qtz ";

  if(argc != 2){
    printf("\nUse:\n\t %s <quantizacao>\n\n", argv[0]);
    exit(4);
  }
  d = opendir("./images");
  d_mean = opendir("./images");
  rewinddir(d);
  rewinddir(d_mean);
  strcat(outname, argv[1]);
  strcat(outname, ".txt");
  txt = fopen(outname, "w");
  if(!(txt)){
    puts("Erro ao abrir o arquivo txt.");
    exit(5);
  }
  if (d) {
    for (int i = 0; (dir = readdir(d)) != NULL; i += 2) {

      begin = clock(); 
      cont += 1;

      if (i >= 3) {
        type = dir->d_name[0];
        strncpy(id, dir->d_name + 2, 5);
        strcpy(nome_arquivo, dir->d_name);
        itsmean = verificarMean(nome_arquivo);
        if (itsmean == 'n'){
          for(int x=0;(dir_mean=readdir(d_mean))!=NULL;x++){
            if (x>=2){
              if ((strstr(dir_mean->d_name, id)!=NULL) && (strstr(dir_mean->d_name, mean)!=NULL)){
                strcpy(nome_arquivo_mean, dir_mean->d_name);
              }
            }  
          }
          rewinddir(d_mean);
        } else {
          continue;
        }
        puts("\n-------------------------------------------");
        readPGMImage(&img, nome_arquivo);
        readPGMImage(&img_mean, nome_arquivo_mean);
        printf("Lendo imagens PGM (dados em binário)");
        calculaSCM(scm,&img, &img_mean, quantizacao, txt, type);
      }
      
      end = clock();
      time_per_img = (double)(end - begin) / CLOCKS_PER_SEC;
      time_total += time_per_img;

    }
    puts("\n-------------------------------------------");
    closedir(d);
    fclose(txt);
  }
  cont -= 2; // cont fica com o total de arquivos armazenado
  printf("Tempo médio: %lf\n",time_total / cont); // tempo total/total de arquivos(cont)
  printf("Tempo Total: %lf\n", time_total);
  return 0;
}

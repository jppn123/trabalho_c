/**********************************************************************/
/* Aluno: JOÃO PEDRO BARROS DE MOURA, LEVY STEVAM, ARTHUR QUEIROZ     */
/* Matricula:   N/A                                                   */
/* Avaliacao 04: Trabalho Final                                       */
/* 04.505.23 − 2022.2 − Prof. Daniel Ferreira                         */
/* Compilador: MinGW  GCC-6.3.0-1                                     */
/**********************************************************************/

#include "funcoes.h"

int main(int argc, char *argv[]) {
  //inclusão das variáveis utilizadas dentro da main
  FILE *txt;
  DIR *d, *d_mean;
  clock_t begin, end;
  struct pgm img, img_mean;
  struct dirent *dir=NULL, *dir_mean=NULL;
  int cont = 0, k, *scm=NULL, quantizacao = atoi(argv[1]);
  double time_per_img, time_total = 0;
  char id[50], nome_arquivo[50], mean[10]="mean",itsmean , nome_arquivo_mean[50], type, outname[50] = "SCM-Qtz ";

  //verificação de argc
  if(argc != 2){
    printf("\nUse:\n\t %s <quantizacao>\n\n", argv[0]);
    exit(4);
  }

  //abrindo os diretórios e setando seu ponteiro para a primeira posição
  d = opendir("./images");
  d_mean = opendir("./images");
  rewinddir(d);
  rewinddir(d_mean);

  //setando o nome do arquivo para conter a quantização
  strcat(outname, argv[1]);
  strcat(outname, ".txt");
  txt = fopen(outname, "w");
  if(!(txt)){
    puts("Erro ao abrir o arquivo txt.");
    exit(5);
  }

  if (d) {
    //abrindo dir enquanto houver arquivos
    for (int i = 0; (dir = readdir(d)) != NULL; i += 2) {
      begin = clock(); 
      cont += 1;
      
      //pula as primeiras detecções de dir (. e ..)
      if (i >= 3) {
        //pega o primeiro char da palavra para conter o tipo do arquivo (0 ou 1)
        type = dir->d_name[0];
        
        //coleta o nome do arquivo e id e verifica se dentro do nome do arquivo possui a palavra "mean"
        strncpy(id, dir->d_name + 2, 5);
        strcpy(nome_arquivo, dir->d_name);
        itsmean = verificarMean(nome_arquivo);
        //verificarMean retorna 's' caso houver "mean" dentro do nome do arquivo, e 'n' caso não tenha
        if (itsmean == 'n'){
          for(int x=0;(dir_mean=readdir(d_mean))!=NULL;x++){
            if (x>=2){
              //caso dentro do nome do arquivo contenha o id coletado e tenha "mean" contido, nome_arquivo_mean vai receber esse nome
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
        //lê as duas imagens utilizando os nomes adquiridos anteriormente, imagem e imagem_mean
        readPGMImage(&img, nome_arquivo);
        readPGMImage(&img_mean, nome_arquivo_mean);
        printf("Lendo imagens PGM (dados em binário)");
        //realiza o calculo de scm e insere cada scm dentro do arquivo .txt aberto anteriormente
        calculaSCM(scm,&img, &img_mean, quantizacao, txt, type);
        if(txt == NULL){
          puts("acabou o alloc");
        }
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
  printf("Tempo médio: %lf\n",time_total / cont); 
  printf("Tempo Total: %lf\n", time_total);
  return 0;
}

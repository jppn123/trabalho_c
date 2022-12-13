/**********************************************************************/
/* Aluno: JOÃO PEDRO BARROS DE MOURA, LEVY STEVAM, ARTHUR QUEIROZ     */
/* Matricula:   N/A                                                   */
/* Avaliacao 04: Trabalho Final                                       */
/* 04.505.23 − 2022.2 − Prof. Daniel Ferreira                         */
/* Compilador: MinGW  GCC-6.3.0-1                                     */
/**********************************************************************/
#include "funcoes.h"

void readPGMImage(struct pgm *pio, char *filename) {
  FILE *fp;
  char ch;
  char diretorio[100] = "images/";
  //verificações do arquivo
  if (!(fp = fopen(strcat(diretorio, filename), "r"))) {
    perror("Erro.");
    exit(1);
  }
  if ((ch = getc(fp)) != 'P') {
    puts("A imagem fornecida não está no formato pgm");
    exit(2);
  }
  //aqui, o ponteiro fp vai estar na segunda posição e pegar char = 5(53 em ascii), retira-se 48 para pegar o int 5 depois move o ponteiro novamente
  pio->tipo = getc(fp) - 48;
  fseek(fp, 1, SEEK_CUR);
  //caso encontre '#', vai pular todos as letras seguintes até a quebra de linha e pular a linha
  while ((ch = getc(fp)) == '#') {
    while ((ch = getc(fp)) != '\n'){
      fseek(fp, 1, SEEK_CUR);
    }
  }
  //a terceira linha é onde ficam as dimensões das imagens, então coletar os dados para pio->c e pio->r, coluna e linha
  fseek(fp, -2, SEEK_CUR);
  fscanf(fp, "%d %d", &pio->c, &pio->r);
  if (ferror(fp)) {
    perror(NULL);
    exit(3);
  }
  //a quarta linha é onde fica o maximo valor da variação de pdata
  fscanf(fp, "%d", &pio->mv);
  fseek(fp, 0, SEEK_CUR);
  //aloca espaço e coleta todos os dados da quinta linha pra pdata, esses serão os valores tratados posteriormente
  pio->pData = (unsigned char *)malloc(pio->r * pio->c * sizeof(unsigned char));
  switch (pio->tipo) {
  case 2:
    puts("Lendo imagem PGM (dados em texto)");
    for (int k = 0; k < (pio->r * pio->c); k++) {
      fscanf(fp, "%hhu", pio->pData + k);
    }
    break;
  case 5:
    //puts("Lendo imagem PGM (dados em binário)");
    fread(pio->pData, sizeof(unsigned char), pio->r * pio->c, fp);
    break;
  default:
    puts("Não está implementado");
  }

  fclose(fp);
}

char verificarMean(char *nome_arquivo){
  char mean[50] = "mean";
  //caso mean esteja contido em nome_arquivo, retorna 's', caso não retorna 'n'
  if (strstr(nome_arquivo, mean) != NULL) {
      return 's';
  } else {
      return 'n';
  }
}

void calculaSCM(int *scm, struct pgm *pioA, struct pgm *pioB, int quant){
  //setando os valores que serão utilizados e alocando as matrizes
  int linha = pioA->r, coluna = pioA->c;
  unsigned char *pdataA = pioA->pData, *pdataB = pioB->pData;
  int *matrizA = NULL, *matrizB = NULL;
  
  
  matrizA = malloc(sizeof(int)*linha*coluna);
  matrizB = malloc(sizeof(int)*linha*coluna);
  int divisao = 256/quant;
  //preenche as matrizes com os valores de pdata % quantização, para tratar cada dado de pdata conforme a quantização indicada
  for(int i = 0; i < linha; i++){
    for(int x = 0; x < coluna; x++){
      *(matrizA + i * coluna + x) = (int) (*(pdataA + i * coluna + x) / divisao);
      *(matrizB + i * coluna + x) = (int) (*(pdataB + i * coluna + x) / divisao);
    }
  }
  //seta todas as posições de scm para 0
  for(int i = 0; i< quant; i++){
    for(int x = 0; x < quant; x++){
      *(scm + i * quant + x) = 0;
    }
  } 
  /*
    nesse caso, o valor de matrizA e o valor de matrizB serão, respectivamente, linha e coluna da matriz coocorrencia
    e onde cada valor desse irá se juntar numa coordenada, (valor(matrizA), valor(matrizB)) = (y, x), y = linha, x = coluna,
    e somar 1
  */
  for(int i = 0; i< linha; i++){
    for(int x = 0; x < coluna; x++){
      *(scm + *(matrizA + i * coluna + x) * quant + *(matrizB + i * coluna + x)) += 1;
    }
  } 
  //fazendo a verificação, a soma de todos os valores de soma, deve ser a quantidade de elementos
  int soma = 0;
  for(int i = 0; i< quant; i++){
    for(int x = 0; x < quant; x++){
      soma += *(scm + i * quant + x);
    }
  }
  //if(soma == (linha*coluna)){
    //printf("\nMatriz SCM computada corretamente!");
  //}
 
}
//insere os valores de scm no arquivo .txt e no final da linha insere a classe (0 ou 1)
void outmatriz(int *scm, FILE *pf, int quant, char tipo){
  for(int i=0;i<quant;i++){
    for(int x = 0; x < quant; x++){
      fprintf(pf, "%d, ", *(scm + i * quant + x));
    }
  }
  fprintf(pf, "%c \n", tipo);
}
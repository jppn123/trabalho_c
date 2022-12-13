#include "funcoes.h"

void readPGMImage(struct pgm *pio, char *filename) {
  FILE *fp;
  char ch;
  char diretorio[100] = "images/";

  if (!(fp = fopen(strcat(diretorio, filename), "r"))) {
    perror("Erro.");
    exit(1);
  }

  if ((ch = getc(fp)) != 'P') {
    puts("A imagem fornecida não está no formato pgm");
    exit(2);
  }

  pio->tipo = getc(fp) - 48;

  fseek(fp, 1, SEEK_CUR);

  while ((ch = getc(fp)) == '#') {
    while ((ch = getc(fp)) != '\n'){
      fseek(fp, 1, SEEK_CUR);
    }
  }

  fseek(fp, -1, SEEK_CUR);

  fscanf(fp, "%d %d", &pio->c, &pio->r);

  if (ferror(fp)) {
    perror(NULL);
    exit(3);
  }
  fscanf(fp, "%d", &pio->mv);
  fseek(fp, 1, SEEK_CUR);

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

void writePGMImage(struct pgm *pio, char *filename) {
  FILE *fp;
  char ch;

  if (!(fp = fopen(filename, "wb"))) {
    perror("Erro.");
    exit(1);
  }

  fprintf(fp, "%s\n", "P5");
  fprintf(fp, "%d %d\n", pio->c, pio->r);
  fprintf(fp, "%d\n", 255);

  fwrite(pio->pData, sizeof(unsigned char), pio->c * pio->r, fp);

  fclose(fp);
}

void viewPGMImage(struct pgm *pio) {
  printf("Tipo: %d\n", pio->tipo);
  printf("Dimensões: [%d %d]\n", pio->c, pio->r);
  printf("Max: %d\n", pio->mv);
}

char verificarMean(char *nome_arquivo){
  char mean[50] = "mean";
  if (strstr(nome_arquivo, mean) != NULL) {
      return 's';
  } else {
      return 'n';
  }
}

void calculaSCM(int *scm, struct pgm *pioA, struct pgm *pioB, int quant, FILE *pf, char tipo){
  unsigned char *output = NULL;
  int linha = pioA->r, coluna = pioA->c;
  unsigned char *pdataA = pioA->pData, *pdataB = pioB->pData;
  int *matrizA = NULL, *matrizB = NULL;
  
  scm = malloc(sizeof(int) * linha * coluna);
  matrizA = malloc(sizeof(int)*linha*coluna);
  matrizB = malloc(sizeof(int)*linha*coluna);
  output = malloc(sizeof(unsigned char)*quant*quant);
  
  for(int i = 0; i < linha; i++){
    for(int x = 0; x < coluna; x++){
      *(matrizA + i * coluna + x) = *(pdataA + i * coluna + x) % quant;
      *(matrizB + i * coluna + x) = *(pdataB + i * coluna + x) % quant;
    }
  }

  for(int i = 0; i< quant; i++){
    for(int x = 0; x < quant; x++){
      *(scm + i * quant + x) = 0;
    }
  } 
  for(int i = 0; i< linha; i++){
    for(int x = 0; x < coluna; x++){
      *(scm + *(matrizA + i * coluna + x) * quant + *(matrizB + i * coluna + x)) += 1;
    }
  } 

  int soma = 0;
  for(int i = 0; i< quant; i++){
    for(int x = 0; x < quant; x++){
      soma += *(scm + i * quant + x);
    }
  }
  
  for(int i=0;i<quant;i++){
    for(int x = 0; x < quant; x++){
      fprintf(pf, "%d, ", *(scm + i * quant + x));
    }
  }
  fprintf(pf, "%c \n", tipo);
}


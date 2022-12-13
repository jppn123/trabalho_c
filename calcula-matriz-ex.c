#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define tam 480 //tamanho de m1 e m2
#define tam1 480

void preenchematriz(int *, int, int, int);
void printamatriz(int *, int, int);
void mat(int *, int, int, int, int *, int *);

int main(){
    //necessário transformar em ponteiros todas as matrizes
    srand(time(NULL));
    int *m1 = NULL, *m2 = NULL, *msc = NULL, quantizacao;
    
    puts("digite a quantização: ");
    scanf("%d", &quantizacao); //muda o tamanho de msc e a faixa de valores randomizados de m1 e m2

    //ler as imagens aqui e coletar os dados

    m1 = malloc(tam * tam1 * sizeof(int)); //m1 == imagem 1
    m2 = malloc(tam * tam1 * sizeof(int)); //m2 == imagem 1(suavizada)
    msc = malloc(quantizacao * quantizacao * sizeof(int)); //matriz computada scm

    preenchematriz(m1, tam, tam1, quantizacao); //retirar
    preenchematriz(m2, tam, tam1, quantizacao); //retirar
    
    puts("m1: linha"); //retirar
    //printamatriz(m1, tam, tam1);  //retirar
    
    puts("m2: coluna"); //retirar
    //printamatriz(m2, tam, tam1); //retirar

    puts("msc: ");
    mat(msc, quantizacao, tam, tam1, m1, m2);

    //printar msc
    /*
    for(int i = 0; i < quantizacao; i++){
        for(int x = 0; x < quantizacao; x++){
            printf("%d ", *(msc + i * quantizacao + x));
        }   
        puts("");
    }
    */
    puts("");
    return 0;
}
//preenche a matriz com valores randomizados
void preenchematriz(int *ma, int lin, int col, int faixa){
    for(int i = 0; i < lin; i++){
        for(int x = 0; x < col; x++){
            *(ma + i * col + x) = rand() % faixa;           //retirar
        }
    }
}
//printa as matrizes m1 e m2
void printamatriz(int *ma, int lin, int col){
    for(int i = 0; i < lin; i++){
        for(int x = 0; x < col; x++){
            printf("%3d ", *(ma + i * col + x));             //retirar
        }
        puts("");
    }
    puts("");
}

void mat(int *ma, int t, int lin, int coluna, int *mat1, int *mat2){
    //primeiro realiza a alocação onde todos os elementos são 0
    for(int i = 0; i < t; i++){
        for(int x = 0; x < t; x++){
            *(ma + i * t + x) = 0;
        }//i == linha, x == coluna
    }
    //de acordo com os valores de m1 e m2, msc recebe o valor de m1 como linha e o valor de m2 como coluna
    /**/
    for(int i = 0; i < lin; i++){
        for(int x = 0; x < coluna; x++){
            *(ma + *(mat1 + i * coluna + x) * t + *(mat2 + i * coluna + x)) += 1;
        }
    }
    int soma = 0;
    for(int i = 0; i < t; i++){
        for(int x = 0; x < t; x++){
            soma += *(ma + i * t + x);
        }
    }
    printf("%d \n", soma);
}



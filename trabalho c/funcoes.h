/**********************************************************************/
/* Aluno: JOÃO PEDRO BARROS DE MOURA, LEVY STEVAM, ARTHUR QUEIROZ     */
/* Matricula:   N/A                                                   */
/* Avaliacao 04: Trabalho Final                                       */
/* 04.505.23 − 2022.2 − Prof. Daniel Ferreira                         */
/* Compilador: MinGW  GCC-6.3.0-1                                     */
/**********************************************************************/
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct pgm {
  int tipo;
  int c;
  int r;
  int mv;
  unsigned char *pData;
};

void readPGMImage(struct pgm *, char *);
char verificarMean(char *);
void calculaSCM(int *, struct pgm *, struct pgm *, int, FILE *, char);
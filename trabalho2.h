/*============================================================================*/
/* CSF13 - 2022-2 - TRABALHO 2                                                */
/*----------------------------------------------------------------------------*/
/* Bogdan T. Nassu - btnassu@utfpr.edu.br                                     */
/* Leyza E. B. Dorini - leyza@utfpr.edu.br                                    */
/*============================================================================*/
/** Funções pedidas para o 2o trabalho da disciplina Fundamentos de Programação
 * 1, 2o semestre de 2022, prof. Bogdan T. Nassu e Leyza E. B. Dorini,
 * Universidade Tecnológica Federal do Paraná. */
/*============================================================================*/

#ifndef __TRABALHO2_H
#define __TRABALHO2_H

/*============================================================================*/

void mudaGanho (double* dados, int n_amostras, double ganho);
void meiaVelocidade (double* dados, int n_amostras, double* saida);
void dobraVelocidade (double* dados, int n_amostras, double* saida);
void fade (double* dados, int n_amostras, int inicio, int fim, int in_out);
int buscaPadrao (double* dados, int n_amostras, double* padrao, int n_amostras_padrao, double* score);

/*============================================================================*/
#endif /* __TRABALHO2_H */

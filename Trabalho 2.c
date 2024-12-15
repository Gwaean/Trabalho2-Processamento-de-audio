#define WINDOWS
#include <stdio.h>
#include <stdlib.h>
#include "trabalho2.h"

#ifdef WINDOWS
#include <windows.h>
#endif

void mudaGanho (double* dados, int n_amostras, double ganho){
    int i;

    for(i=0;i<n_amostras;i++){
        dados[i]=dados[i]*ganho;
    }
}

void meiaVelocidade (double* dados, int n_amostras, double* saida){
    int i,j=0, k;
    for(i=0;i<n_amostras;i++){
        for(k=0; k<2; k++){
        saida[j]=dados[i];
        j++;
        }
    }


}
void dobraVelocidade (double* dados, int n_amostras, double* saida){
    int i, j=0;
    for(i=0;i<n_amostras;i+=2){
        saida[j]=dados[i];
        j++;
    }
}


void fade (double* dados, int n_amostras, int inicio, int fim, int in_out){
    double taxa_fade, fade;
    int i;

    taxa_fade=1.0/(fim-inicio);

    if(fim>n_amostras)
        fim=n_amostras;

    if(in_out>0)
        fade=0.0;
    else if(in_out<0)
        fade=1.0;

    for(i=inicio;i<fim;i++){
        if(in_out<0){
            dados[i]=dados[i]*fade;
            fade=fade-taxa_fade;
        }
        else if(in_out>0){
            dados[i]=dados[i]*fade;
            fade=fade+taxa_fade;
        }
    }
}

int buscaPadrao (double* dados, int n_amostras, double* padrao,int n_amostras_padrao, double* score){
    int i, j, posicao_padrao;
    double numerador, denominador=0.0, score_aux=0.0;

    for(j=0;j<n_amostras_padrao;j++){
                denominador=denominador+(padrao[j]*padrao[j]);
        }

    for(i=0;i<(n_amostras-n_amostras_padrao);i++){
            numerador=0.0;
        for(j=0;j<n_amostras_padrao;j++){
                numerador=numerador+(dados[i+j]*padrao[j]);
        }
        if(numerador/denominador>0.5){
            score_aux=numerador/denominador;
            if((*score)<score_aux){
                (*score)=score_aux;
                posicao_padrao=i;
            }
        }
    }
    if((*score)<0.5)
        return(-1);
    else
        return(posicao_padrao);
}

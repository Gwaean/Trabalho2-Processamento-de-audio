/*============================================================================*/
/* Exemplo: brincadeira "jogando" o som para a esquerda e para a direita. */

#include <stdlib.h>
#include "wavfile.h"
#include "trabalho2.h"

/*============================================================================*/

#define INPUT_FILE "data/sonic1.wav"
#define OUTPUT_FILE "data/teste4_fade.wav"

#define N_TRANSICOES 20

/*============================================================================*/

int main ()
{
	WavHeader header; /* Cabeçalho para as informações sobre o arquivo. */
	double* dados_l; /* Dados do canal esquerdo. Alocado na readWavFile. */
	double* dados_r; /* Dados do canal direito. Alocado na readWavFile, se necessário. */
	int n_amostras; /* Número de amostras nos buffers. */
	int step, i, in_out;

    /* Lê um arquivo. */
    n_amostras = readWavFile (INPUT_FILE, &header, &dados_l, &dados_r);
    if (!n_amostras)
    {
        printf ("Erro lendo %s.\n", INPUT_FILE);
        return (1);
    }

	/* Confirma que o arquivo é stereo. */
    if (!dados_r)
    {
        printf ("%s nao eh um arquivo stereo.\n", INPUT_FILE);
        return (1);
    }

    /* Faz agora uma sequência de fades in/out. Começa usando metade do tempo, jogando da esquerda para a direita. */
    step = n_amostras/N_TRANSICOES;
    in_out = 1;
    for (i = 0; i < N_TRANSICOES; i++)
    {
        fade (dados_l+i*step, step, 0, step, in_out);
        fade (dados_r+i*step, step, 0, step, -in_out);
        in_out *= -1;
    }

     /* Salva. */
    if (!writeWavFile (OUTPUT_FILE, &header, dados_l, dados_r))
    {
        printf ("Erro salvando %s.\n", OUTPUT_FILE);
        return (1);
    }

    /* Desaloca os vetores. */
	free (dados_l);
    free (dados_r);

	return (0);
}

/*============================================================================*/

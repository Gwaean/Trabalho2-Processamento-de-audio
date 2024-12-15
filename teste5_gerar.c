/*============================================================================*/
/* Exemplo (gerador): gera um arquivo contendo ru�do, e "cola" sobre ele uma
 * trilha de �udio. */

#include <stdlib.h>
#include "wavfile.h"

#include "trabalho2.h"

/*============================================================================*/

#define INPUT_FILE "data/teste.wav"
#define OUTPUT_FILE "data/teste5.wav"

#define TAMANHO_TOTAL 44100*5 /* Tamanho do sinal. */
#define ATENUACAO_RUIDO 0.2 /* Fator de atenua��o para o ru�do. Quanto menor, menos ru�do. */
#define POSICAO_INICIAL 44100*2 /* Posi��o inicial para os dados do arquivo. */

/*============================================================================*/

void misturaDados (double* dados1, double* dados2, double* saida, int n_amostras);

int main ()
{
	WavHeader header; /* Cabe�alho para as informa��es sobre o arquivo. */
	double* dados; /* Vetor de dados. Alocado na generateSignal. */
	int n_amostras; /* N�mero de amostras nos buffers. */

    WavHeader header_in; /* Cabe�alho para as informa��es sobre o arquivo. */
    double* dados_in_l; /* Dados do canal esquerdo. Alocado na readWavFile. */
    double* dados_in_r; /* Dados do canal direito. Alocado na readWavFile. */
	int n_amostras_in; /* N�mero de amostras nos buffers. */

    /* Gera um sinal */
    n_amostras = TAMANHO_TOTAL;
    header = generateSignal (&n_amostras, 1, 44100, &dados, NULL);

    /* L� o arquivo. */
    n_amostras_in = readWavFile (INPUT_FILE, &header_in, &dados_in_l, &dados_in_r);
    if (!n_amostras_in)
    {
        printf ("Erro lendo %s.\n", INPUT_FILE);
        return (1);
    }

    if (n_amostras_in + POSICAO_INICIAL > n_amostras)
    {
        printf ("Os dados do arquivo nao cabem no sinal a partir da posicao %d.\n", POSICAO_INICIAL);
        return (1);
    }

    /* Preenche o sinal com ru�do, e "cola" os dados do arquivo no sinal. */
    generateRandomData (dados, n_amostras);
    mudaGanho (dados, n_amostras, ATENUACAO_RUIDO);
    misturaDados (&(dados [POSICAO_INICIAL]), dados_in_l, &(dados [POSICAO_INICIAL]), n_amostras_in);

    /* Escreve em outro arquivo. */
    if (!writeWavFile (OUTPUT_FILE, &header, dados, NULL))
    {
        printf ("Erro salvando %s.\n", OUTPUT_FILE);
        return (1);
    }

    /* Desaloca os vetores. O direito s� vai ter sido alocado se o arquivo for est�reo. */
	free (dados);
	free (dados_in_l);
	if (dados_in_r)
        free (dados_in_r);

	return (0);
}

/*----------------------------------------------------------------------------*/
/** Mistura duas trilhas. Simplesmente soma os dados posi��o-a-posi��o. Os dois
 * vetores de entrada devem ter o mesmo tamanho.
 *
 * Par�metros: double* dados1: vetor de dados 1.
 *             double* dados1: vetor de dados 2.
 *             double* saida: vetor de sa�da.
 *             int n_amostras: n�mero de amostras nos vetores.
 *
 * Valor de Retorno: nenhum. */

void misturaDados (double* dados1, double* dados2, double* saida, int n_amostras)
{
	while (n_amostras--)
	{
		*saida = *dados1+ *dados2;
		saida++;
		dados1++;
		dados2++;
	}
}

/*============================================================================*/

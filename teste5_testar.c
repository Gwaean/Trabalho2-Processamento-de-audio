/*============================================================================*/
/* Exemplo (testador): abre um arquivo contendo um padrão, e outro arquivo
  contendo o mesmo padrão, mas no meio de um sinal com ruído. Mostra a posição
  do padrão no segundo arquivo. */

#include <stdlib.h>
#include "wavfile.h"

#include "trabalho2.h"

/*============================================================================*/

#define ARQUIVO_PADRAO "data/teste.wav"
#define ARQUIVO_RUIDO "data/teste5.wav"

/*============================================================================*/

int main ()
{
	WavHeader header_padrao; /* Cabeçalho para as informações sobre o arquivo. */
	WavHeader header_ruido; /* Cabeçalho para as informações sobre o arquivo. */
    double* dados_l_padrao; /* Dados do canal esquerdo. Alocado na readWavFile. */
    double* dados_r_padrao; /* Dados do canal direito. Alocado na readWavFile. */
    double* dados_l_ruido; /* Dados do canal esquerdo. Alocado na readWavFile. */
    double* dados_r_ruido; /* Dados do canal direito. Alocado na readWavFile. */
	int n_amostras_padrao; /* Número de amostras nos buffers. */
	int n_amostras_ruido; /* Número de amostras nos buffers. */

    double score;

    /* Lê o arquivo do padrão. */
    n_amostras_padrao = readWavFile (ARQUIVO_PADRAO, &header_padrao, &dados_l_padrao, &dados_r_padrao);
    if (!n_amostras_padrao)
    {
        printf ("Erro lendo %s.\n", ARQUIVO_PADRAO);
        return (1);
    }

    /* Lê o arquivo contendo ruído. */
    n_amostras_ruido = readWavFile (ARQUIVO_RUIDO, &header_ruido, &dados_l_ruido, &dados_r_ruido);
    if (!n_amostras_ruido)
    {
        printf ("Erro lendo %s.\n", ARQUIVO_RUIDO);
        return (1);
    }

    /* Procura pelo padrão (usa somente os dados do lado esquerdo). */
    score = -1;
    printf ("Posicao encontrada: %d\n", buscaPadrao (dados_l_ruido, n_amostras_ruido, dados_l_padrao, n_amostras_padrao, &score));
    if (score >= 0)
        printf ("Score: %f\n", score);

    /* Desaloca os vetores. O direito só vai ter sido alocado se o arquivo for estéreo. */
	free (dados_l_padrao);
	free (dados_l_ruido);
	if (dados_r_padrao)
        free (dados_r_padrao);
    if (dados_r_ruido)
        free (dados_r_ruido);

	return (0);
}

/*============================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define TAMANHO 100

void end()
{
  system("cls");
  printf("BURRO !");
  getchar();
  getchar();
  exit(0);
}

void trim(char *str)
{
  int j = 0;
  char aux[TAMANHO];

  for (int i = 0; i < strlen(str); i++)
  {
    if (isspace(str[i]))
    {
      continue;
    }

    aux[j] = str[i];
    j++;
  }

  aux[j] = '\0';
  strcpy(str, aux);
}

int isInArray(char val, char arr[])
{
  for (int i = 0; i < strlen(arr); i++)
  {
    if (arr[i] == val)
    {
      return 1;
    }
  }

  return 0;
}

void clearString(char *str)
{
  char operators[7] = {'+', '-', '*', '/', '^', '(', ')'};

  for (int i = 0; i < strlen(str); i++)
  {
    if (!isdigit(str[i]) && !isInArray(str[i], operators))
    {
      end();
    }
  }
}

int main()
{
  char input[TAMANHO];

  system("cls");
  printf("Digite uma string de ate %d caracteres: ", TAMANHO - 1);
  fflush(stdin);
  gets(input);

  trim(input);
  clearString(input);

  char deitado[TAMANHO][TAMANHO], emPe[TAMANHO][TAMANHO], pedaco[TAMANHO];
  int ultimoIndice = 0, pegarOperador = 0, posicaoDeitado = -1, posicaoEmPe = -1;

  if (!isdigit(input[0]))
  {
    end();
  }

  while (ultimoIndice != -1)
  {
    printf("\n ULTIMO INDICE %d e %d \n ", ultimoIndice, strlen(input));
    for (ultimoIndice; ultimoIndice < strlen(input); ultimoIndice++)
    {
      if (input[ultimoIndice] == '\0')
      {
        ultimoIndice = -1;
        break;
      }

      if (isdigit(input[ultimoIndice]))
      {
        continue;
      }

      if (pegarOperador)
      {
        pedaco[0] = input[ultimoIndice];
      }
      else
      {
        for (int j = 0; j < ultimoIndice; j++)
        {
          pedaco[j] = input[j];
        }
      }
    }

    if (!pegarOperador)
    {
      posicaoDeitado++;
      strcpy(deitado[posicaoDeitado], pedaco);
      pegarOperador = 1;
      printf("\n %s", deitado[posicaoDeitado]);
    }
    else
    {
      if (posicaoEmPe > -1)
      {
      }

      posicaoEmPe++;
      strcpy(emPe[posicaoEmPe], pedaco);
      pegarOperador = 0;
      printf("\n %s", emPe[posicaoEmPe]);
    }
  }

  getchar();
  getchar();
  return (0);
}
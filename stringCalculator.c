#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define TAMANHO 100

void end()
{
  system("clear");
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

  system("clear");
  printf("Digite uma string de ate %d caracteres: ", TAMANHO - 1);
  fflush(stdin);
  gets(input);

  trim(input);
  clearString(input);

  char deitado[TAMANHO][TAMANHO], emPe[TAMANHO][TAMANHO], pedaco[TAMANHO];
  int leitor = 0, pegarOperador = 0, posicaoDeitado = -1, posicaoEmPe = -1, loop = 1, ultimaPos = 0;

  if (!isdigit(input[0]))
  {
    end();
  }

  while (loop < 5)
  {
    for (leitor; leitor < strlen(input); leitor++)
    {
      printf("\n\n------Entrei no for, meu leitor é %d e o tamanho do input é %d.", leitor, strlen(input));
      if(isdigit(input[leitor]) && (leitor + 1) < strlen(input))
      {
        continue;
      }

      if (pegarOperador == 1)
      {
        printf("\n\nPeguei operador: %c.", input[leitor]);
        pedaco[0] = input[leitor];
        leitor++;
        ultimaPos = leitor;
      }
      else
      {
        printf("\n\nPeguei número: %c.", input[0]);
        for (int j = 0; j < leitor; j++)
        {
          pedaco[j] = input[ultimaPos];
          ultimaPos++;
        }
      }
      break;
    }

    if (pegarOperador == 0)
    {
      posicaoDeitado++;
      printf("\n\nPeguei um pedaço <%s> e coloquei na posição: %d", pedaco, posicaoDeitado);
      strcpy(deitado[posicaoDeitado], pedaco);
      pegarOperador = 1;
      printf("\nDeitado: %s", deitado[posicaoDeitado]);
    }
    else
    {
      // if (posicaoEmPe > -1)
      // {
      // }

      posicaoEmPe++;
      strcpy(emPe[posicaoEmPe], pedaco);
      pegarOperador = 0;
      printf("\nEm pé: %s", emPe[posicaoEmPe]);
    }
    memset(pedaco, 0, strlen(pedaco));
    loop++;
  }

  getchar();
  getchar();
  return (0);
}
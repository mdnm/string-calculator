#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define TAMANHO 100

void endProgram()
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
      endProgram();
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

  char vetorDeitado[TAMANHO], vetorEmPe[TAMANHO], pedaco[TAMANHO];
  int posicaoDeitado = -1, posicaoEmPe = -1, j = 0;

  for (int i = 0; i < strlen(input); i++)
  {
    while (isdigit(input[j]))
    {
      pedaco[j] = input[j];
      j++;
    }
  }

  printf("\n%s", input);

  getchar();
  getchar();
  return (0);
}
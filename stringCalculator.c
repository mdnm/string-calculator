#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define TAMANHO 100

char operadores[7] = {'(', '^', '*', '/', '+', '-', ')'};

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

int isInRangeOfArray(char val, char arr[], int startIndex, int endIndex)
{
  for (int i = startIndex; i <= endIndex; i++)
  {
    if (arr[i] == val)
    {
      return 1;
    }
  }

  return 0;
}

void isValid(char *str)
{
  for (int i = 0; i < strlen(str); i++)
  {
    if (!isdigit(str[i]) && !isInArray(str[i], operadores))
    {
      end();
    }
  }
}

int isTrueInMatrix(char emPe, char pedaco)
{
  switch (pedaco)
  {
  case '(':
  case '^':
    return 0;
    break;
  case '*':
  case '/':
    return isInRangeOfArray(emPe, operadores, 1, 3);
    break;
  case '+':
  case '-':
    return isInRangeOfArray(emPe, operadores, 1, 6);
    break;
  case ')':
    return isInRangeOfArray(emPe, operadores, 0, 6);
    break;
  default:
    return 0;
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
  isValid(input);

  char deitado[TAMANHO][TAMANHO], emPe[TAMANHO][TAMANHO], pedaco[TAMANHO];
  int leitor = 0, pegarOperador = 0, posicaoDeitado = -1, posicaoEmPe = -1, loop = 1, ultimaPos = 0;

  if (input[0] != '(' && !isdigit(input[0]))
  {
    end();
  }

  while (loop < strlen(input))
  {
    for (leitor; leitor < strlen(input); leitor++)
    {
      printf("\n\n------Entrei no for, meu leitor e %d e o tamanho do input e %d.", leitor, strlen(input));
      if (isdigit(input[leitor]) && (leitor + 1) < strlen(input))
      {
        continue;
      }

      //printf("\n\n ULTIMA POS %d.", ultimaPos);
      if (pegarOperador == 1)
      {
        //printf("\n\nPeguei operador: %c.", input[leitor]);
        pedaco[0] = input[leitor];
        leitor++;
        ultimaPos = leitor;
      }
      else
      {
        int tamanhoDigito = leitor - ultimaPos;
        for (int j = 0; j < tamanhoDigito; j++)
        {
          //printf("\n\ninput[%d]: %c.", j, input[ultimaPos]);
          pedaco[j] = input[ultimaPos];
          ultimaPos++;
        }
      }
      break;
    }

    if (pegarOperador == 0)
    {
      posicaoDeitado++;
      printf("\n\nPeguei um pedaco <%s> e coloquei na posicao: %d", pedaco, posicaoDeitado);
      strcpy(deitado[posicaoDeitado], pedaco);
      pegarOperador = 1;
      printf("\nDeitado: %s", deitado[posicaoDeitado]);
    }
    else
    {
      printf("\n\n posicao EM PE %d", posicaoEmPe);
      if (posicaoEmPe > -1)
      {
        for (int i = 0; i < posicaoEmPe + 1; i++)
        {
          if (isTrueInMatrix(emPe[i][0], pedaco[0]) == 0)
          {
            printf("\n tabela deu false emPe[%d][0]: %c | pedaco[0]: %c", i, emPe[i][0], pedaco[0]);
            break;
          }

          printf("\n tabela deu true emPe[%d][0]: %c | pedaco[0]: %c", i, emPe[i][0], pedaco[0]);

          posicaoDeitado++;
          strcpy(deitado[posicaoDeitado], emPe[i]);

          printf("\nDeitado: %s", deitado[posicaoDeitado]);
          memset(emPe[i], 0, strlen(emPe[i]));
          posicaoEmPe--;
        }
      }

      posicaoEmPe++;
      strcpy(emPe[posicaoEmPe], pedaco);

      printf("\nEm pe: %s", emPe[posicaoEmPe]);

      if (isdigit(input[leitor + 1]))
      {
        pegarOperador = 0;
      }
    }

    memset(pedaco, 0, strlen(pedaco));
    loop++;
  }

  getchar();
  getchar();
  return (0);
}
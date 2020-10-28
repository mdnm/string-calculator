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

  system("clear");
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
      // printf("\n\n------Entrei no for, meu leitor e %d e o tamanho do input e %d.", leitor, strlen(input));
      // printf("\n\n\tPegar Operador = %d.", pegarOperador);
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
        // printf("\n\n\tO tamanho do número é: %d.", tamanhoDigito);
        // printf("\n\n\tO leitor está em: %d.", leitor);
        // printf("\n\tA última posição é: %d.", ultimaPos);
        if(leitor + 1 == strlen(input))//Prestar atenção para ver se não da pau mais para frente.
        {
          tamanhoDigito++;
        }
        for (int j = 0; j < tamanhoDigito; j++)
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
      printf("\n\nPeguei o pedaco <%s> e coloquei em deitado[%d].", pedaco, posicaoDeitado);
      strcpy(deitado[posicaoDeitado], pedaco);
      pegarOperador = 1;
    }
    else
    {
      if (posicaoEmPe > -1)
      {
        for (int i = 0; i < posicaoEmPe + 1; i++)
        {
          if (isTrueInMatrix(emPe[i][0], pedaco[0]) == 0)
          {
            printf("\n\n----Tabela deu False emPe[%d][0]: %c | Pedaco[0]: %c", i, emPe[i][0], pedaco[0]);
            break;
          }

          printf("\n\n----Tabela deu True emPe[%d][0]: %c | Pedaco[0]: %c", i, emPe[i][0], pedaco[0]);

          posicaoDeitado++;
          strcpy(deitado[posicaoDeitado], emPe[i]);

          printf("\n\n----Tirei <%s> do emPe[%d] e coloquei em deitado[%d].", deitado[posicaoDeitado], i, posicaoDeitado);
          memset(emPe[i], 0, strlen(emPe[i]));
          posicaoEmPe--;
          printf("\n\n----Agora posicaoEmPe é: %d.", posicaoEmPe);
        }
      }

      posicaoEmPe++;
      strcpy(emPe[posicaoEmPe], pedaco);

      printf("\n\nPeguei o pedaço <%s> e coloquei em emPe[%d].", emPe[posicaoEmPe], posicaoEmPe);

      // printf("\n\tAntes de entrar no if o input[leitor] é: %c.", input[leitor]);
      if (isdigit(input[leitor]))
      {
        pegarOperador = 0;
      }
    }

    if(leitor + 1 == strlen(input))
      break;

    memset(pedaco, 0, strlen(pedaco));
    loop++;
  }

  getchar();getchar();// Pausa o programa.
  return (0);
}
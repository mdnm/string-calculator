#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TAMANHO 100

char operadores[7] = {'(', '^', '*', '/', '+', '-', ')'};

int isFloat(char input)
{
  if(isdigit(input) || input == '.' || input == ',')
  {
    return 1;
  }
  return 0;
}

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
    if (!isFloat(str[i]) && !isInArray(str[i], operadores))
    {
      end();
    }

    if(str[i] == '.' || str[i] == ',')
    {
      if(i == 0 || !isdigit(str[i - 1]) || i + 1 == strlen(str) || !isdigit(str[i + 1]))
      {
        end();
      }
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

void expression(int posicaoDeitado, char deitado[TAMANHO][TAMANHO])
{
  char emPe[TAMANHO][TAMANHO];

  int posicaoEmPe = -1;
  int atual;
  float num1, num2;
  char oper;

    for(atual = 0; atual <= posicaoDeitado; atual++)
    {
        if(isFloat(deitado[atual][0]))
        {
            posicaoEmPe++;
            strcpy(emPe[posicaoEmPe], deitado[atual]);
        }
        else
        {
            if(posicaoEmPe < 1)
            {
                printf("\n\n\nERRO!!");
            }
            oper = deitado[atual][0];
            num2 = atof(emPe[posicaoEmPe]);
            posicaoEmPe--;
            num1 = atof(emPe[posicaoEmPe]);

            switch(oper)
            {
            case '+':
                sprintf(emPe[posicaoEmPe], "%f", num1+num2);
                break;
            case '-':
                sprintf(emPe[posicaoEmPe], "%f", num1-num2);
                break;
            case '*':
                sprintf(emPe[posicaoEmPe], "%f", num1*num2);
                break;
            case '/':
                sprintf(emPe[posicaoEmPe], "%f", num1/num2);
                break;
            case '^':
                sprintf(emPe[posicaoEmPe], "%f", pow(num1, num2));
                break;
            }
        }
    }

    printf("\n\n\nRESULTADO: %s\n", emPe[0]);
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
  int leitor = 0, pegarOperador = 0, posicaoDeitado = -1, posicaoEmPe = -1, loop = 1, ultimaPos = 0, fechouParenteses = 0, ultimoNumero = 0;

  if (input[0] != '(' && !isFloat(input[0]))
  {
    end();
  }

  while (loop < strlen(input))
  {
    printf("\n\nDei um loop e o leitor atual é: %d", leitor);
    for (leitor; leitor <= strlen(input); leitor++)
    {
      // printf("\n\n------Entrei no for, meu leitor e %d e o tamanho do input e %d.", leitor, strlen(input));
      // printf("\n\n\tPegar Operador = %d.", pegarOperador);
      if (isFloat(input[leitor]) && (leitor + 1) < strlen(input))
      {
        continue;
      }

      // printf("\n\n ULTIMA POS %d.", ultimaPos);
      if (pegarOperador == 1)
      {
        // printf("\n\nPeguei operador: %c.", input[leitor]);
        pedaco[0] = input[leitor];
        leitor++;
        ultimaPos = leitor;
      }
      else
      {
        int tamanhoDigito = leitor - ultimaPos;
        printf("\n\n\tO tamanho do número é: %d.", tamanhoDigito);
        printf("\n\n\tO leitor está em: %d.", leitor);
        printf("\n\tA última posição é: %d.", ultimaPos);
        if (leitor + 1 == strlen(input) && isFloat(input[leitor + 1]))
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
        for (int i = posicaoEmPe; i >= 0; i--)
        {
          if (isTrueInMatrix(emPe[i][0], pedaco[0]) == 0)
          {
            printf("\n\n----Tabela deu False emPe[%d][0]: %c | Pedaco[0]: %c", i, emPe[i][0], pedaco[0]);
            break;
          }

          printf("\n\n----Tabela deu True emPe[%d][0]: %c | Pedaco[0]: %c", i, emPe[i][0], pedaco[0]);
          if (emPe[i][0] == '(' && pedaco[0] == ')')
          {
            fechouParenteses = 1;
            printf("\n\n----Os parenteses sucumbiram MuaHaHaHa");
            memset(emPe[i], 0, strlen(emPe[i]));
            posicaoEmPe--;
            printf("\n\n----Agora posicaoEmPe é: %d.", posicaoEmPe);
            break;
          }

          posicaoDeitado++;
          strcpy(deitado[posicaoDeitado], emPe[i]);

          printf("\n\n----Tirei <%s> do emPe[%d] e coloquei em deitado[%d].", deitado[posicaoDeitado], i, posicaoDeitado);
          memset(emPe[i], 0, strlen(emPe[i]));
          posicaoEmPe--;
          printf("\n\n----Agora posicaoEmPe é: %d.", posicaoEmPe);
        }
      }

      //printf("\n\n FECHOU PARENTESES %d", fechouParenteses);
      if (fechouParenteses != 1)
      {
        posicaoEmPe++;
        strcpy(emPe[posicaoEmPe], pedaco);
        printf("\n\nPeguei o pedaço <%s> e coloquei em emPe[%d].", emPe[posicaoEmPe], posicaoEmPe);
      }

      // printf("\n\tAntes de entrar no if o input[leitor] é: %c.", input[leitor]);
      if (isFloat(input[leitor]))
      {
        pegarOperador = 0;
      }
    }

    //Filtra quando o último número tem mais de um dígito.
    if ((input[leitor] != ')' && fechouParenteses == 1) && leitor + 1 == strlen(input))
    {
      printf("\n\nSai do While no if");
      //Se o último número tiver mais de um dígito, não executa o primeiro if após o while.
      if(strlen(pedaco) == 1)
      {
        ultimoNumero = 1;
      }
      fechouParenteses = 0;

      break;
    }

    memset(pedaco, 0, strlen(pedaco));
    loop++;
  }

  //Se o último número só tiver um dígito, ele executa esse if.
  if(ultimoNumero == 1)
  {
    leitor++;
    int tamanhoDigito = leitor - ultimaPos;
    // printf("\n\n\tO tamanho do número é: %d.", tamanhoDigito);
    // printf("\n\n\tO leitor está em: %d.", leitor);
    // printf("\n\tA última posição é: %d.", ultimaPos);

    if (leitor + 1 == strlen(input) && isFloat(input[ultimaPos + 1]))
    {
      tamanhoDigito++;
    }

    for (int j = 0; j < tamanhoDigito; j++)
    {
      pedaco[j] = input[ultimaPos];
      ultimaPos++;
    }

    posicaoDeitado++;
      printf("\n\nPeguei o pedaco <%s> e coloquei em deitado[%d].", pedaco, posicaoDeitado);
      strcpy(deitado[posicaoDeitado], pedaco);
      pegarOperador = 1;
  }

  for(int i = posicaoEmPe; i >= 0; i--)
  {
    posicaoDeitado++;
    strcpy(deitado[posicaoDeitado], emPe[i]);

    printf("\n\n----Tirei <%s> do emPe[%d] e coloquei em deitado[%d].", deitado[posicaoDeitado], i, posicaoDeitado);
    memset(emPe[i], 0, strlen(emPe[i]));
  }

  for(int i = 0; i <= posicaoDeitado; i++)
  {
    if(i == 0)
    {
      printf("\n\nAssim ficou o vetor de string Deitado: ");
    }

    printf("%s", deitado[i]);
  }

  printf("\n\nPosição deitado final: %d", posicaoDeitado);

  expression(posicaoDeitado, deitado);

  //Pausa o programa.
  getchar();
  getchar();
  return (0);
}

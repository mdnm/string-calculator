#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include <math.h>

#define MAX 100

char opr[7] = {'(', '^', '*', '/', '+', '-', ')'};

int esta_no_vetor(char val, char arr[]);
int tabela_maligna(char em_pe, char pedaco);

int main()
{
  float numero_um, numero_dois;
  char expressao[MAX], deitado[MAX][MAX], em_pe[MAX], pedaco[MAX], resultado[MAX][MAX], opr_atual;
  int leitor = 0, pos_deitado = -1, pos_em_pe = -1, pos_resultado = -1, tipo_pedaco[MAX],
      pegar_opr = 0, fechou_parenteses = 0, prox_leitura_digito = 0;

  setlocale(LC_ALL, "portuguese");

  system("cls");
  printf("Digite uma expressão com no máximo %d caracteres: ", MAX - 1);
  fflush(stdin);
  gets(expressao);

  int j = 0;
  char expressao_sem_espacos[MAX];
  for (int i = 0; i < strlen(expressao); i++)
  {
    if (isspace(expressao[i]) == 0)
    {
      expressao_sem_espacos[j] = expressao[i];
      j++;
    }
  }
  expressao_sem_espacos[j] = '\0';
  strcpy(expressao, expressao_sem_espacos);

  for (int i = 0; i < strlen(expressao); i++)
  {
    if (!isdigit(expressao[i]) && expressao[i] != '.' && expressao[i] != ',' && !esta_no_vetor(expressao[i], opr))
    {
      system("cls");
      printf("Expressão inválida!");
      return 0;
    }

    if (expressao[i] == '.' || expressao[i] == ',')
    {
      if (i == 0 || !isdigit(expressao[i - 1]) || i + 1 == strlen(expressao) || !isdigit(expressao[i + 1]))
      {
        system("cls");
        printf("Expressão inválida!");
        return 0;
      }
    }
  }

  if (expressao[0] != '(')
  {
    if (!isdigit(expressao[0]) && expressao[0] != '.' && expressao[0] != ',')
    {
      system("cls");
      printf("Ocorreu um erro!");
      return 0;
    }
  }

  for (leitor; leitor < strlen(expressao); leitor++)
  {
    if ((isdigit(expressao[leitor]) || expressao[leitor] == '.' || expressao[leitor] == ','))
    {
      tipo_pedaco[leitor] = 0;
    }
    else
    {
      tipo_pedaco[leitor] = 1;
    }

    pedaco[leitor] = expressao[leitor];
  }

  for (int i = 0; i < leitor; i++)
  {
    if (tipo_pedaco[i] == 1)
    {
      if (pos_em_pe > -1)
      {
        for (int j = pos_em_pe; j >= 0; j--)
        {
          if (tabela_maligna(em_pe[j], pedaco[i]) == 1)
          {
            if (em_pe[j] == '(' && pedaco[i] == ')')
            {
              fechou_parenteses = 1;
              em_pe[j] = ' ';
              pos_em_pe--;
              break;
            }

            pos_deitado++;
            deitado[pos_deitado][0] = em_pe[j];

            em_pe[j] = ' ';
            pos_em_pe--;
          }
        }
      }

      if (fechou_parenteses == 0)
      {
        pos_em_pe++;
        em_pe[pos_em_pe] = pedaco[i];
      }
      else
      {
        fechou_parenteses = 0;
      }

      prox_leitura_digito = i + 1;
    }
    else
    {
      int posicao_digito = i - prox_leitura_digito;
      if (pos_deitado == -1 || (pos_deitado > -1 && tipo_pedaco[i - 1] == 1))
      {
        pos_deitado++;
      }
      deitado[pos_deitado][posicao_digito] = pedaco[i];
    }
  }

  for (int i = pos_em_pe; i >= 0; i--)
  {
    pos_deitado++;
    deitado[pos_deitado][0] = em_pe[i];
    deitado[pos_deitado][1] = '\0';
  }

  for (int i = 0; i <= pos_deitado; i++)
  {
    if (isdigit(deitado[i][0]) || deitado[i][0] == '.' || deitado[i][0] == ',')
    {
      pos_resultado++;
      strcpy(resultado[pos_resultado], deitado[i]);
    }
    else
    {
      if (pos_resultado < 1)
      {
        printf("\nAlgo deu errado!\n");
      }

      opr_atual = deitado[i][0];
      numero_dois = atof(resultado[pos_resultado]);
      pos_resultado--;
      numero_um = atof(resultado[pos_resultado]);

      if (opr_atual == '+')
      {
        sprintf(resultado[pos_resultado], "%.2f", numero_um + numero_dois);
      }
      else if (opr_atual == '-')
      {
        sprintf(resultado[pos_resultado], "%.2f", numero_um - numero_dois);
      }
      else if (opr_atual == '*')
      {
        sprintf(resultado[pos_resultado], "%.2f", numero_um * numero_dois);
      }
      else if (opr_atual == '/')
      {
        sprintf(resultado[pos_resultado], "%.2f", numero_um / numero_dois);
      }
      else if (opr_atual == '^')
      {
        sprintf(resultado[pos_resultado], "%.2f", pow(numero_um, numero_dois));
      }
    }
  }

  printf("\n\n\nO resultado é: %s\n", resultado[0]);

  //Pausa o programa.
  getchar();
  getchar();
  return 0;
}

int esta_no_vetor(char val, char arr[])
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

int tabela_maligna(char em_pe, char pedaco)
{
  if (pedaco == '(' || pedaco == '^')
  {
    return 0;
  }
  else if (pedaco == '*' || pedaco == '/')
  {
    for (int i = 1; i <= 3; i++)
    {
      if (opr[i] == em_pe)
      {
        return 1;
      }
    }

    return 0;
  }
  else if (pedaco == '+' || pedaco == '-')
  {
    for (int i = 1; i <= 6; i++)
    {
      if (opr[i] == em_pe)
      {
        return 1;
      }
    }

    return 0;
  }
  else if (pedaco == ')')
  {
    for (int i = 0; i <= 6; i++)
    {
      if (opr[i] == em_pe)
      {
        return 1;
      }
    }

    return 0;
  }
}
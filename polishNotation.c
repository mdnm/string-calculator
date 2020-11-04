#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#define TAMANHO 100

void end()
{
  system("cls");
  printf("BURRO !");
  getchar();
  getchar();
  exit(0);
}

void expression()
{
    char deitado[TAMANHO][TAMANHO] = {
        {'1','0'},{'2'},{'3'},{'*'},{'4'},{'-'},{'2'},
        {'^'},{'4'},{'/'},{'+'},{'6'},{'2'},{'*'},{'+'}
    };

    char emPe[TAMANHO][TAMANHO];

    int posicaoDeitado = 14; // ja existia
    int posicaoEmPe = -1;
    int atual;
    float num1, num2;
    char oper;

    for(atual = 0; atual <= posicaoDeitado; atual++)
    {
        if(isdigit(deitado[atual][0]))
        {
            posicaoEmPe++;
            strcpy(emPe[posicaoEmPe], deitado[atual]);
        }
        else
        {
            if(posicaoEmPe < 1)
            {
                end();
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

    printf("RESULTADO: %s\n", emPe[0]);
}

int main()
{
    expression();

    return(0);
}


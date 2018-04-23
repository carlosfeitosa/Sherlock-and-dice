//
//  main.cpp
//  Sherlock and dice
//
//  Created by Carlos Feitosa on 7/14/14.
//  Copyright (c) 2014 Carlos Feitosa. All rights reserved.
//

/*
 Explicação sobre o algoritmo:
 
 Sherlock (provavelmente de Sherlock Holmes) rola um dado de N lados M vezes. Ele soma todos os números que aparecem a cada arremesso. Qual a probabilidade dele (Sherlock) advinhar a soma K dos valores de cada arremesso?
 
Um dado de N faces tem todos os números entre 1 e N impressos nele e qualquer número tem a mesma probabilidade (de aparecer) que os demais quando o dado é lançado.

Entrada de dados:
A primeira linha possui um inteiro T que contem o número de testes que aparecerem nas linhas abaixo. Cada linha, após a primeira, deverá ter os elementos M, N e K.
 
Saída de dados:
Para cada teste, imprima a probabilidade (K) em notação científica como definida abaixo:
 A saída deve ser na forma de "x y" onde x é um número decimal (float) menor que 10 e maior ou igual a 1 e y é um inteiro. Esta notação é equivalente a X * 10-y. x deve ser arredondado e a saída dele deve possuir até 3 casas decimais.
 Entretanto, se a probabilidade for o, a saída deve ser "0.000 0".
 
 Exemplos: se a saída deveria ser 0,0034567 então a o resultado deveria ser "3.457 3".
 Se a saída deveria ser 0.3034567 então o resultado deveria ser "3.034 1".
 
 Restrições:
 1 ≤ T ≤ 10
 1 ≤ N, M ≤ 50
 1 ≤ K ≤ 10000
 
 <source: http://www.hackerearth.com/problem/algorithm/sherlock-and-dice/ available in 08/25/2014>
 
*/

// inclusão das bibliotecas necessárias para a execução deste programa
// biblioteca de entrada e saida (io)
#include <iostream>
// biblioteca matemática
#include <math.h>
// biblioteca de assertivas
#include <assert.h>
// ajustando namespace
using namespace std;

/*
*   Função returnProbabilities(int m, int n, int k)
*
*   Retorna a probabilidade das somas (k) dos arremessos de um dado de n lados, arremessado m vezes ser o número k
*
*   @param
*   m = número de arremessos
*   n = número de lados do dado
*   k = número que Sherlock está "apostando" que a soma dos arremessos
*
*   @return
*   Número decimal (float/double) com a probabilidade
*/
double calculateProbabilities(int m, int n, int k)
{
    // declarando array bidimensional dice (dado) que possui n+1 elementos na primeira dimensão e k+10 elementos na segunda posição
    double dice[n+1][k+10];

    // iniciando array bidimensional com o valor 0 (cada elemento)
    // loop para percorrer a primeira dimensão
    for (int x = 0; x < n; x++) {
        // loop para percorrer a segunda dimensão
        for (int y = 0; y < k+9; y++) {
            // atribuindo o valor 0 ao elemento (x/y - linha/coluna)
            dice[x][y] = 0;
        }
    }

    // verificando probabilidades de dar zero, para evitar calculos desnecessários
    // se k (soma dos arremessos) for maior que a multiplicação de m (arremessos) por n (lados) ou se k for menor que a quantidade de lados (n), já é sabido, sem calculos além destas condições, que a probabilidade é zero
    if ((k > (m * n)) or (k < n)) {
        // retornando 0
        return 0;
    }

    // loop na segunda linha (elemento 1) do array bidimensional, até o incremento ser maior ou igual ao número de arremessos e o incremento for menor que a soma dos arremessos - elementos fora deste escopo já podem ser considerados como zero probabilidades e a inicialização zerou todos os elementos.
    for (int x = 1; ((x <= m) and (x <= k)); x++) {
        // setando o valor da coluna x para a probabilidade padrão em cada arremesso de um determinado número do dado aparecer, ou seja 1/quantidade de arremessos.
        dice[1][x] = (double) 1/m;
    }

    // loop para os demais arremessos, na dimensão linha
    for (int x = 2; x <= n; x++) {
        // loop para a dimensão coluna
        for (int y = 1; y <= k; y++) {
            // loop para a quantidade de arremessos
            for (int w = 1; ((w <= m) and (w < y)); w++) {
                // setando o valor da probabilidade x/y como sendo a probabilidade dele próprio + a probabilidade do arremesso anterior
                dice[x][y] = (dice[x][y] + dice[x-1][y-w]);
            }

            // setando o valor da probabilidade para a quantidade de probabilidades dividido pela quantidade de arremessos
            dice[x][y] /= m;
        }
    }

    // retornando probabilidade
    return dice[n][k];
}

// função principal do programa
int main()
{
    // declaração de variáveis
	int loops, m, n, k;
    double probability;

    // lendo (e salvando na variável loops) a quantidade de testes a serem realizados, já que a primeira linha do arquivo (ou número inteiro digitado pelo usuário seguido de quebra de linha "enter") é a quantidade de testes
    fscanf(stdin, "%i\n", &loops);

    // verificando restrições
    assert(loops > 0 and loops <= 10);

    // loop para a quantidade de testes declaradas na primeira linha do arquivo ou digitação do usuário
    for (int i = 1; i <= loops; i++) {
        // recuperando do arquivo (ou, novamente, da digitação sequencial do usuário) m, n e k
        fscanf(stdin, "%i %i %i\n", &m, &n, &k);

        // verificando restrições
        assert((m > 0 and m < 51) or (n > 0 and n < 51) or (k > 1 and k <= 10000));

        // recuperando probabilidade
        probability = calculateProbabilities(n, m, k);

        // verificando se a probabilidade é zero
        if (0 == probability) {
            // imprimindo a probabilidade zero no formato solicitado
            cout << "0.000 0" << endl;
            // saindo da estrutura de loop (for) a qual este bloco está condicionado
            continue;
        }

        // declarando variáveis
        int decimalPositions = 0;
        // convertendo o número (probabilidade) em string (vetor de caracteres)
        string stringValue = to_string(probability);
        // declarando, inicializando variável e verificando se na string convertida do número foi encontrado a string "e" (de exponencial, da notação científica mesmo!
        int eSNPosition = (int) stringValue.find("e");

        // caso haja "e" na probabilidade
        if (eSNPosition > 0) {
            // recuperando da string todos os elementos antes da posição do "e"
            probability = stod(stringValue.substr(0, eSNPosition));
            // setando a quantidade de posições decimais este número já possui, por possuir um "e" da notação científica padrão
            decimalPositions = stod(stringValue.substr(eSNPosition+2, stringValue.length()));
        }

        // loop para reduzir o resultado para o formato esperado (entre 1 e 10)
        while (probability < 1) {
            // incrementando a quantidade de casas decimais
            decimalPositions++;

            // multiplicando o resultado por 10, para avançar uma casa decimal no número obtido
            probability *= 10;
        }

        // setando a precisão da impressão de um número do tipo decimal no cout
        cout.precision(3);

        // imprimindo o resultado conforme formato especificado
        cout << fixed << probability << " " << decimalPositions << endl;
    }

    // saindo do programa com o estados de sucesso
    exit(0);
}

#include <iostream>
#include <algorithm>
#include <random>
#include <vector>
#include <array>
#include <math.h>

using namespace std;

int qtd_trocam(){ //decide quantas coordenadas vao ser trocadas

    vector<double> weights = {7, 21/sqrt(2), 35/sqrt(3), 35/sqrt(4), 21/sqrt(5), 7/sqrt(6), 1/sqrt(7)};

    random_device rd;
    mt19937 generator(rd());

    discrete_distribution<int> distribution(weights.begin(), weights.end());

    return distribution(generator) + 1; //senao comecaria do 0
}

array<int, 7> realizar_trocas(array<int, 7> estado, int qtd_trocas){ //realizar as trocas de forma aleatoria
    //escolher qtd_trocas elementos num conjunto de 0 a N-1
    //embaralha o vetor de 0 a N-1 e escolhe os qtd_trocas primeiros elementos
    vector<int> vetor = {0,1,2,3,4,5,6};
    random_shuffle ( vetor.begin(), vetor.end() );

    for(int i = 0; i < qtd_trocas; i++){
        estado[vetor[i]] = 1 - estado[vetor[i]];
    }

    return estado;
}

int main(){
    int N = 10000;
    
    int passos; 
    array<int, 7> estado;
    array<int, 7> prox_estado;
    array<int, 7> pontoA {0,0,0,0,0,0,0}; 
    array<int, 7> pontoG {1,1,1,1,1,1,1}; 
    int passos_acumulados = 0; // = soma dos passos de todos os episodios
    int qtd_trocas;

    for(int i = 0; i < N; i++){
        estado = pontoA; // estado inicial no ponto A
        passos = 0;

        while(!(estado == pontoG)){ // enquanto nao chegar no ponto G
            qtd_trocas = qtd_trocam(); //decide quantas corrdenadas vao ser invertidas
            prox_estado = realizar_trocas(estado, qtd_trocas); //realiza a inversao das coordenadas  
            passos++;
            estado = prox_estado;
        }
        passos_acumulados += passos;
    }

    cout << (float)passos_acumulados/N << endl;
    return 0;
}
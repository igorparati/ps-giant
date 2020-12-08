#include <iostream>
#include <random>
#include <vector>
#include <array>
#include <math.h>

using namespace std;

int next(vector<double> weights){

    random_device rd;
    mt19937 generator(rd());

    discrete_distribution<int> distribution(weights.begin(), weights.end());

    return distribution(generator);
}

int main(){
    int N = 100000;

    //A = 0, B = 1, C = 2, D = 3, E = 4, F = 5, G = 6, H = 7

    vector<double> weightsA = {0,sqrt(6),sqrt(3),sqrt(6),sqrt(6),sqrt(3),sqrt(2),sqrt(3)};
    vector<double> weightsB = {sqrt(6),0,sqrt(6),sqrt(3),sqrt(3),sqrt(6),sqrt(3),sqrt(2)};
    vector<double> weightsC = {sqrt(3),sqrt(6),0,sqrt(6),sqrt(2),sqrt(3),sqrt(6),sqrt(3)};
    vector<double> weightsD = {sqrt(6),sqrt(3),sqrt(6),0,sqrt(3),sqrt(2),sqrt(3),sqrt(6)};
    vector<double> weightsE = {sqrt(6),sqrt(3),sqrt(2),sqrt(3),0,sqrt(6),sqrt(3),sqrt(6)};
    vector<double> weightsF = {sqrt(3),sqrt(6),sqrt(3),sqrt(2),sqrt(6),0,sqrt(6),sqrt(3)};
    vector<double> weightsG = {sqrt(2),sqrt(3),sqrt(6),sqrt(3),sqrt(3),sqrt(6),0,sqrt(6)};
    vector<double> weightsH = {sqrt(3),sqrt(2),sqrt(3),sqrt(6),sqrt(6),sqrt(3),sqrt(6),0};
    
    int passos, estado, prox_estado;
    int passos_acumulados = 0; // = soma dos passos de todos os episodios

    bool passou_pelo_C; // true se o caminho eh tal que passou pelo C na ultima etapa
    int qtd_passou_pelo_C = 0; // conta em quantos caminhos passou pelo C na ultima etapa

    for(int i = 0; i < N; i++){
        estado = 0; // estado inicial no ponto A
        passos = 0;
        passou_pelo_C = false;

        while(estado != 6){ // enquanto nao chegar no ponto G
            //cout << "passo " << passos << " - estado " << estado << endl;
            switch (estado){
            case 0:
                prox_estado = next(weightsA);
                break;
            case 1:
                prox_estado = next(weightsB);
                break;
            case 2:
                prox_estado = next(weightsC);
                break;
            case 3:
                prox_estado = next(weightsD);
                break;
            case 4:
                prox_estado = next(weightsE);
                break;
            case 5:
                prox_estado = next(weightsF);
                break;
            case 6:
                prox_estado = next(weightsG);
                break;
            case 7:
                prox_estado = next(weightsH);
                break;
            default:
                break;
            }
            passos++;
            if(estado == 2 && prox_estado == 6)
                passou_pelo_C = true;
            estado = prox_estado;
        }
        if(passou_pelo_C == true){
            passos_acumulados += passos;
            qtd_passou_pelo_C++;
        }
    }

    cout << (float)passos_acumulados/qtd_passou_pelo_C << endl;
    return 0;
}
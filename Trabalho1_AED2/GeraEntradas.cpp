#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>
#include <random>
#include <iomanip>

using namespace std;
namespace fs = filesystem;

fs::path Entradas = fs::current_path() / "Entradas";

int main(){
    vector<int> tamanho = {1000, 5000, 10000, 50000, 100000};
    vector<float> Sequencia;
    for(int i=0; i<tamanho.size(); i++){
        //Gera números inteiros e reais no intervalo [-tamanho[i], tamaho[i]]
        for(int j=0; j<tamanho[i]/2; j++){
            Sequencia.push_back(rand()%(2*tamanho[i]+1) - tamanho[i]);
            Sequencia.push_back(2*tamanho[i]*((float)rand()/RAND_MAX) - tamanho[i]);
        }
        //Embaralha Sequencia
        int k;
        for(int j=0;j<tamanho[i];j++){
            k = rand()%tamanho[i];
            swap(Sequencia[j], Sequencia[k]); 
        }
        
        //Cria e adiciona Sequencia ao arquivo .csv
        ofstream ArqCSV(Entradas / ("Sequencia"+ to_string(i+1) +".csv"));
        for(int j=0; j<tamanho[i]; j++){
            ArqCSV << fixed << setprecision(3) << Sequencia[j] << endl;
        }
        ArqCSV.close();
        //Limpa Sequencia para a próxima iteração de tamanho
        Sequencia.clear();
    }

    return 0;
}

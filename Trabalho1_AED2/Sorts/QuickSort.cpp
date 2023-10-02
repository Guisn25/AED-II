#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;
namespace fs = filesystem;

fs::path TrabalhoDir = fs::current_path().parent_path();
fs::path Entradas = TrabalhoDir / "Entradas";
fs::path Saida = TrabalhoDir / "Saidas" / "Quick";

int k;
int Separa(vector<float>& Sequencia, int p, int r){
    k = p-1;
    for(int j=p; j<r;j++){
        if(Sequencia[j] < Sequencia[r]){
            swap(Sequencia[++k], Sequencia[j]);
        }
    }
    swap(Sequencia[k+1], Sequencia[r]);
    return k+1;
}
int j; //pivô escolhido com base no último elemento de Sequencia
void QuickSort(vector<float>& Sequencia, int p, int r){
    if(p<r){
        j = Separa(Sequencia, p, r);
        QuickSort(Sequencia, p, j-1);
        QuickSort(Sequencia, j+1, r);
    }
}

int main(){
    ofstream ArqCSVTempos(Saida / "TemposQ.csv");
    ArqCSVTempos << "Unidade(\u03BCs),Tempo1,Tempo2,Tempo3,Media" << endl;
    chrono::microseconds media;

    vector<float> Sequencia;
    float aux;
    int Seq=1;
    for(fs::path Entrada : fs::directory_iterator(Entradas)){
        //Repete a ordenação para cada Entrada 3 vezes
        Saida.assign(Saida / ("Seq" + to_string(Seq)));
        ArqCSVTempos << "Seq" + to_string(Seq) + ",";
        media = (chrono::microseconds) 0;
        for(int i=0;i<3;i++){
            //Lê Entrada
            ifstream ArqCSVIn(Entrada);
            while(ArqCSVIn >> aux){
                Sequencia.push_back(aux);
            }
            ArqCSVIn.close();
            
            //Ordena e armazena tempo de execução
            auto inicio = chrono::high_resolution_clock::now();
            QuickSort(Sequencia, 0, Sequencia.size());
            auto fim = chrono::high_resolution_clock::now();
            
            auto tempo = chrono::duration_cast<chrono::microseconds>(fim - inicio);
            ArqCSVTempos << tempo.count() << ",";

            media = media + tempo;
        
            //Escreve Saída
            ofstream ArqCSVOut(Saida / ("Sequencia" + to_string(Seq) + "_Ordenada" + to_string(i+1) + ".csv"));
            for(float x : Sequencia){
                ArqCSVOut << fixed << setprecision(3) << x << endl;
            }
            ArqCSVOut.close();
            //Limpa Sequencia para proxima iteração
            Sequencia.clear();
        }
        
        ArqCSVTempos << media.count()/3 << endl;
        Saida.assign(Saida.parent_path());
        Seq++;
    }
    
    return 0;
}
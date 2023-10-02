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
fs::path Saida = TrabalhoDir / "Saidas" / "Selection";

void SelectionSort(vector<float>& Sequencia){
    int Menor;
    for(int i=0; i<Sequencia.size()-1;i++){
        Menor = i;
        for(int j=i+1;j<Sequencia.size();j++){
            if (Sequencia[j] < Sequencia[Menor]){
                Menor = j ;
            }
            swap(Sequencia[i], Sequencia[Menor]);   
        }
    }
}

int main(){
    ofstream ArqCSVTempos(Saida / "TemposS.csv");
    ArqCSVTempos << "Unidade(ms),Tempo1,Tempo2,Tempo3,Media" << endl;
    chrono::milliseconds media;
    
    vector<float> Sequencia;
    float aux;
    int Seq=1;
    for(fs::path Entrada : fs::directory_iterator(Entradas)){
        //Repete a ordenação para cada Entrada 3 vezes
        Saida.assign(Saida / ("Seq" + to_string(Seq)));
        ArqCSVTempos << "Seq" + to_string(Seq) + ",";
        media = (chrono::milliseconds) 0;
        for(int i=0;i<3;i++){
            //Lê Entrada
            ifstream ArqCSVIn(Entrada);
            while(ArqCSVIn >> aux){
                Sequencia.push_back(aux);
            }
            ArqCSVIn.close();
            
            //Ordena e armazena tempo de execução
            auto inicio = chrono::high_resolution_clock::now();
            SelectionSort(Sequencia);
            auto fim = chrono::high_resolution_clock::now();
            
            auto tempo = chrono::duration_cast<chrono::milliseconds>(fim - inicio);
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
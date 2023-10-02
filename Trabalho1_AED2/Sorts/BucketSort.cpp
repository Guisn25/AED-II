#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>

using namespace std;
namespace fs = filesystem;

fs::path TrabalhoDir = fs::current_path().parent_path();
fs::path Entradas = TrabalhoDir / "Entradas";
fs::path Saida = TrabalhoDir / "Saidas" / "Bucket";

#define N 10

void InsertionSort(vector<float>& Balde){
    int j;
    float x;
    for(int i=1;i<Balde.size();i++){
        x = Balde[i];
        j=i-1;
        while(x<Balde[j]){
            Balde[j+1] = Balde[j];
            j--;
        }
        Balde[j+1] = x;
    }
}

void BucketSort(vector<float>& Sequencia){
    vector<float> Baldes[N+1];
    auto Min = *min_element(Sequencia.begin(), Sequencia.end());
    auto Max = *max_element(Sequencia.begin(), Sequencia.end());
    float TamanhoBalde = (Max-Min)/N;
    int Baldekey;
    //Inseri valor em uma "hashtable"
    for(float valor : Sequencia){
        Baldekey = int((valor-Min)/TamanhoBalde);
        Baldes[Baldekey].push_back(valor);
    }

    //Ordena as listas de colisão de cada "hashkey" por InsertionSort
    for(int i=0;i<N;i++){
        InsertionSort(Baldes[i]);
    }

    //Limpa Sequencia para adicionar valores ordenados
    Sequencia.clear();
    for(int i=0;i<N;i++){
        for(float Ordenado : Baldes[i]){
            Sequencia.push_back(Ordenado);
        }
    }
}

int main(){
    ofstream ArqCSVTempos(Saida / "TemposB.csv");
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
            BucketSort(Sequencia);
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
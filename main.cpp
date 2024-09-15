#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

std::vector <int> processos;
int frame_length;

void readFile(){
    std::ifstream inputFile("processos.txt");

    if (!inputFile.is_open()){
        std::cerr << "Não foi possível abrir o arquivo!" << std::endl;
        return;
    }

    std::string linha;

    while(std::getline(inputFile, linha)){
        frame_length = atoi(&linha[0]);
        for(size_t i = 1; i < linha.size(); i++){
            if(linha[i] != ' '){
                int num = atoi(&linha[i]);
                processos.push_back(num);
            }
        }
    }

    return;
}

int main(){
    readFile();
}
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>

std::vector <int> processos;
int frame_length;

void readFile(){
    std::ifstream inputFile("processos.txt");

    if (!inputFile){
        std::cerr << "Não foi possível abrir o arquivo!" << std::endl;
        return;
    }

    inputFile >> frame_length;

    int processo;

    while(inputFile >> processo){
        processos.push_back(processo);
    };

    inputFile.close();
}

bool find_in_queue(std::queue<int> q, int n){
    while (!q.empty())
    {
        if (n == q.front()){
            return true;
        }
        q.pop();
    }
    return false;
}

void FIFO(){
    std::queue<int> aux;
    int page_faults = 0;
    
    for(int i : processos){
        if(aux.size() == frame_length){
            if(!find_in_queue(aux, i)){
                aux.pop();
                aux.push(i);
                page_faults++;
            }
        }else{
            aux.push(i);
            page_faults++;
        }
    }

    std::cout << page_faults << std::endl;
}

int main(){
    readFile();

    FIFO();
}
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>


std::vector <int> pages;
std::queue <int> aux;
int frame_length;
int page_faults;

void readFile(){
    std::ifstream inputFile("pages.txt");

    if (!inputFile){
        std::cerr << "Não foi possível abrir o arquivo!" << std::endl;
        return;
    }

    inputFile >> frame_length;

    int processo;

    while(inputFile >> processo){
        pages.push_back(processo);
    };

    inputFile.close();
}

void print_queue(std::queue<int> q)
{
  while (!q.empty())
  {
    std::cout << q.front() << " ";
    q.pop();
  }
  std::cout << std::endl;
}


bool find_in_queue(std::queue<int> q, int n){
    while (!q.empty()){
        if (n == q.front()){
            return true;
        }
        q.pop();
    }
    return false;
}

void clear_queue(std::queue<int> &q){
    std::queue<int> empty;
    std::swap(q, empty);
}

void FIFO(){
    clear_queue(aux);
    page_faults = 0;
    
    for(int i : pages){
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

void LRU(){
    std::vector<int> aux;
    std::unordered_map<int, int> frame_index;
    page_faults = 0;

    for(size_t i = 0; i < pages.size(); i++){
        int page = pages[i];

        if(frame_index.find(page) == frame_index.end()){

            page_faults++;

            if(aux.size() == frame_length){
                int lru = *aux.begin();

                for (int k : aux){
                    if(frame_index[k] < frame_index[lru]){
                        lru = k;
                    }
                }

                aux.erase(std::remove(aux.begin(), aux.end(), lru), aux.end());
                frame_index.erase(lru);
            }

            aux.push_back(page);
        }

        frame_index[page] = i;
    }

    std::cout << page_faults << std::endl;
}

int main(){
    readFile();

    FIFO();

    LRU();
}
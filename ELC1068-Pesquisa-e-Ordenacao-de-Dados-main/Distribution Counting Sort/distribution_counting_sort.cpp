#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

void vector_print(vector<int> const &input){
    for (int i = 0; i < input.size(); i++) {
        cout << input.at(i) << ' ';
    }
    cout << endl << endl;
}


void distribution_counting_sort(vector<int> &vec, vector<int> &vec_final, int maximum_number){
    int x = 0;
    int y = 0;
    vector<int> vec_aux(maximum_number, 0);

    //Conta a repeticao de cada numero e armazena no vec_aux
    for (int i = 0; i < vec.size(); i++){
        x = vec[i];
        vec_aux[x-1] = vec_aux[x-1] + 1;
    }
    cout << "Vetor com as repeticoes: " << endl;
    vector_print(vec_aux);

    //Acumula as repeticoes no vec_aux
    for (int i = 1; i < maximum_number; i++){
        vec_aux[i] = vec_aux[i] + vec_aux[i-1];
    }
    cout << "Vetor com as repeticoes acumuladas: " << endl;
    vector_print(vec_aux);
    
    //Reposicionando os elementos de vec no vec_final de acordo com sua frequencia no vec_aux
    for (int i = vec.size() - 1; i > -1; i--){
        x = vec[i];
        y = vec_aux[x-1];
        vec_final[y-1] = x;
        vec_aux[x-1] = vec_aux[x-1] - 1; 
    }
    cout << "Vetor final: " << endl;
    vector_print(vec_final);
}

int main() {
   
    //Ordena os valores de vec (que vão de 1 até maximum_number) no vec_final
    int maximum_number = 10;

    vector<int> vec{3, 2, 5, 3, 5, 7, 1, 2, 1};

    vector<int> vec_final(vec.size(), 0);

    distribution_counting_sort(vec, vec_final, 10);

    
    return 0;
}

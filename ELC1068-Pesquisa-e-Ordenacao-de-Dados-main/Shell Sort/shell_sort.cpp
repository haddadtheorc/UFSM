#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

void vector_print(vector<int> const &input)
{
    for (int i = 0; i < input.size(); i++)
    {
        cout << input.at(i) << ' ';
    }
    cout << endl;
}

void shell_sort(vector<int> &vec, vector<int> &vec_aux)
{
    int aux = 0;
    int j = 0;
    int y = 0;
    int gap = vec.size() / 2;
    while (gap > 0)
    {
        for (int i = 0; i < gap; ++i)
        {
            //formando o vetor auxiliar com o grupo
            for (int j = i; j < vec.size(); j += gap)
            {
                vec_aux.push_back(vec[j]);
            }
            //insertion_sort no grupo (vector_aux)
            for (int x = 1; x < vec_aux.size(); x++)
            {
                aux = vec_aux[x];
                y = x - 1;
                while (y >= 0 && vec_aux[y] > aux)
                {
                    vec_aux[y + 1] = vec_aux[y];
                    y--;
                }
                vec_aux[y + 1] = aux;
            }
            //colocando no vetor original os grupos nas posicoes ordenadas
            for (j = i; j < vec.size(); j += gap)
            {
                vec[j] = vec_aux[0];
                vec_aux.erase(vec_aux.begin());
            }
            vec_aux.clear();
        }
        gap = gap / 2;
    }
    cout << "Vetor final ordenado" << endl;
    vector_print(vec);
}

int main()
{

    vector<int> vec(17);
    iota(vec.begin(), vec.end(), 1);
    random_shuffle(vec.begin(), vec.end());
    cout << "Vetor original nao ordenado" << endl;
    vector_print(vec);

    vector<int> vec_aux;
    shell_sort(vec, vec_aux);

    return 0;
}

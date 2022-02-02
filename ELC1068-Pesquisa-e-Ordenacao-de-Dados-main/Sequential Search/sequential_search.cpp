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

void sequential_sort(vector<int> &vec, int target)
{

    for (int i = 0; i < vec.size(); i++)
    {
        if (vec[i] == target)
        {
            cout << "Valor " << target << " encontrado na posicao " << i << endl;
            return;
        }
    }
    cout << "Valor " << target << " nao encontrado" << endl;
}

int main()
{
    vector<int> vec(10);
    iota(vec.begin(), vec.end(), 1);
    random_shuffle(vec.begin(), vec.end());
    vector_print(vec);

    sequential_sort(vec, 3);
    sequential_sort(vec, 15);
}
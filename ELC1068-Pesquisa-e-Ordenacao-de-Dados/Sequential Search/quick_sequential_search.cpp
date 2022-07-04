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

void quick_sequential_sort(vector<int> &vec, int target)
{

    int size = vec.size();

    vec.push_back(target);

    int i = 0;
    while (vec[i] != target)
    {
        i++;
    }

    if (i < size)
    {
        cout << "Valor " << target << " encontrado na posicao " << i << endl;
        return;
    }

    cout << "Valor " << target << " nao encontrado" << endl;
}

int main()
{
    vector<int> vec(10);
    iota(vec.begin(), vec.end(), 1);
    random_shuffle(vec.begin(), vec.end());
    vector_print(vec);

    quick_sequential_sort(vec, 3);
    quick_sequential_sort(vec, 15);
}
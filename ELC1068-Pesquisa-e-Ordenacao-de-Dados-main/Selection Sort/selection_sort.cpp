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

void selection_sort(vector<int> &vec)
{
    for (int i = 0; i < vec.size() - 1; i++)
    {
        int menor = i;
        for (int j = i + 1; j < vec.size(); j++)
        {
            if (vec[j] < vec[menor])
                menor = j;
        }
        int aux = vec[i];
        vec[i] = vec[menor];
        vec[menor] = aux;
    }

    vector_print(vec);
}

int main()
{
    vector<int> vec(10);
    iota(vec.begin(), vec.end(), 1);
    random_shuffle(vec.begin(), vec.end());
    vector_print(vec);
    selection_sort(vec);
}
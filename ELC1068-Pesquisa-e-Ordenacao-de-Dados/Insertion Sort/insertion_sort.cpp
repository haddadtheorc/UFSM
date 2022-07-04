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

void insertion_sort(vector<int> &vec)
{
    int aux = 0;
    int j = 0;

    for (int i = 1; i < vec.size(); i++)
    {
        aux = vec[i];
        j = i - 1;
        while (j >= 0 && vec[j] > aux)
        {
            vec[j + 1] = vec[j];
            j--;
        }
        vec[j + 1] = aux;
    }

    vector_print(vec);
}

int main()
{
    vector<int> vec(10);
    iota(vec.begin(), vec.end(), 1);
    random_shuffle(vec.begin(), vec.end());
    vector_print(vec);
    insertion_sort(vec);

    return 0;
}

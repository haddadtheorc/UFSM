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

void binary_search(vector<int> vec, int l, int index, int target)
{
    if (index >= l)
    {
        int center = (index + l) / 2;

        if (vec[center] == target)
        {
            cout << target << " encontrado na posicao " << center << endl;
        }
        else if (vec[center] > target)
        {
            return (binary_search(vec, l, center - 1, target));
        }
        else
        {
            return (binary_search(vec, center + 1, index, target));
        }
    }
    else
    {
        cout << target << " nao encontrado " << endl;
    }
}

int main()
{
    vector<int> vec(15);
    iota(vec.begin(), vec.end(), 1);
    vector_print(vec);

    int target = 18;
    int index = vec.size() - 1;

    binary_search(vec, 0, index, target);

    target = 9;
    binary_search(vec, 0, index, target);
}
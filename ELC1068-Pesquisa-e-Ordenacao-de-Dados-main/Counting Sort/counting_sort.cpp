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

void counting_sort(vector<int> &vec, vector<int> &vec_final)
{
    vector<int> vec_aux(vec.size(), 0);

    vector_print(vec);
    for (int i = vec.size(); i > 0; i--)
    {
        for (int j = i - 1; j >= 0; j--)
            if (vec[i] > vec[j])
            {
                vec_aux[i]++;
            }
            else
            {
                vec_aux[j]++;
            }
    }

    for (int i = 0; i < vec.size(); i++)
    {
        vec_final[vec_aux[i]] = vec[i];
    }

    vector_print(vec_final);
}

int main()
{

    vector<int> vec(10);
    vector<int> vec_final(vec.size(), 0);
    iota(vec.begin(), vec.end(), 1);
    random_shuffle(vec.begin(), vec.end());

    counting_sort(vec, vec_final);

    return 0;
}

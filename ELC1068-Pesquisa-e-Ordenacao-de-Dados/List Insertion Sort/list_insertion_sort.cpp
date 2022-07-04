#include <bits/stdc++.h>

using namespace std;

struct No
{
    int data;
    struct No *prox;
    No(int x)
    {
        data = x;
        prox = NULL;
    }
};

class Lista
{

public:
    No *head;
    No *aux;

    void pushback(int data)
    {
        No *new_no = new No(data);
        new_no->prox = head;
        head = new_no;
    }

    void print(No *head)
    {
        while (head != NULL)
        {
            cout << head->data << " ";
            head = head->prox;
        }
    }

    void insertionSort(No *headref)
    {

        No *atual = headref;

        //cria uma lista auxiliar para armazenar os valores ordenados
        aux = NULL;

        //percorre a lista do início até o final
        while (atual != NULL)
        {
            No *prox = atual->prox;
            //para cada elemento da lista original, o insere na lista auxiliar na posicao correta
            sort_insert(atual);
            atual = prox;
        }

        //aponta a lista original para a axuliar ordenada
        head = aux;
    }

    void sort_insert(No *new_no)
    {
        if (aux == NULL || aux->data >= new_no->data)
        {
            new_no->prox = aux;
            aux = new_no;
        }
        else
        {
            No *atual = aux;

            //vai ate o nó cujo proximo é maior que o nó a ser inserido - no caso o ponto para inserir o nó desejado
            while (atual->prox != NULL && atual->prox->data < new_no->data)
            {
                atual = atual->prox;
            }

            //insere o nosso nó entre o atual(menor que ele) e o próximo do atual(maior que ele)
            new_no->prox = atual->prox;
            atual->prox = new_no;
        }
    }
};

int main()
{
    Lista list;
    list.head = NULL;

    int n = 10;
    vector<int> vec(n);
    iota(vec.begin(), vec.end(), 1);
    random_shuffle(vec.begin(), vec.end());
    for (int i = 0; i < n; i++)
    {
        list.pushback(vec[i]);
    }

    cout << "Lista antes da ordenacao: " << endl;
    list.print(list.head);
    cout << endl;

    list.insertionSort(list.head);

    cout << "Lista apos a ordenacao: " << endl;
    list.print(list.head);
    cout << endl;
}

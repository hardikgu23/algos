// union-find implementation with path compression
#include <stdio.h>
#include <stdbool.h>
int find(int x , int Array[]) // returns the parent node of element x
{
    int root = x;
    while(root != Array[root])
    root = Array[root];

    // root = Array[root] , that means root is parent root for x
    // doing path compression

    while(x != root)
    {
        int temp = Array[x];
        Array[x] = root;
        x = temp;
    }

    return root;
}

bool is_cycle(int p , int q , int Array[]) // returns true if they will make a cycle
{
    return find(p , Array) == find(q , Array);
}

void unify(int p ,int q , int Array[] , int size[])
{
    int root1 = find(p);
    int root2 = find(q);

    if(root1 == root2)
    return;

    int size1 = size[root1];
    int size2 = size[root2];

    if(size1 >= size2)
    {
        size[root1] += size[root2];
        Array[root2] = root1;
    }
    else
    {
        size[root2] += size[root1];
        Array[root1] = root2;
    }
}
int main()
{
    int n;
    scanf("%d", &n);
    int Array[n + 1];
    int size[n + 1]; // stores the size of each set
    for (int i = 1; i <= n; i++)
    {
        Array[i] = i; // if Array[i] = i , then i is parent node
        size[i] = 1;
    }
}

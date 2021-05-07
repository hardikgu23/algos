#include <stdio.h>
#include <stdbool.h>
typedef struct edge edge;
struct edge
{
    int start;
    int end;
    long int weight;
};
void merge(edge Array[], int l, int m, int r) // to sort the edges according to their weights
{
    int n1 = m - l + 1;
    int n2 = r - m;
    edge temp1[n1], temp2[n2];
    for (int i = 0; i < n1; i++)
    {
        temp1[i] = Array[l + i];
    }
    for (int i = 0; i < n2; i++)
    {
        temp2[i] = Array[m + 1 + i];
    }

    int i = 0, j = 0, k = l;

    while (i < n1 && j < n2)
    {
        if (temp1[i].weight <= temp2[j].weight)
        {
            Array[k] = temp1[i];
            i++;
        }
        else
        {
            Array[k] = temp2[j];
            j++;
        }

        k++;
    }

    while (i < n1)
    {
        Array[k] = temp1[i];
        i++;
        k++;
    }
    while (j < n2)
    {
        Array[k] = temp2[j];
        j++;
        k++;
    }
}

void merge_sort(edge Array[], int l, int r)
{
    if (r > l)
    {
        int m = (l + r) / 2;

        merge_sort(Array, l, m);
        merge_sort(Array, m + 1, r);

        merge(Array, l, m, r);
    }
}

int find(int x, int Array[]) // returns the parent node of element x
{
    int root = x;
    while (root != Array[root])
        root = Array[root];

    // root = Array[root] , that means root is parent root for x
    // doing path compression

    while (x != root)
    {
        int temp = Array[x];
        Array[x] = root;
        x = temp;
    }

    return root;
}

bool is_cycle(int p, int q, int Array[]) // returns true if they will make a cycle
{
    return find(p, Array) == find(q, Array);
}

void unify(int p, int q, int Array[], int size[])
{
    int root1 = find(p , Array);
    int root2 = find(q, Array);

    if (root1 == root2)
        return;

    int size1 = size[root1];
    int size2 = size[root2];

    if (size1 >= size2)
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
    int n, m; // n-> no of vertex // m -> no of edges
    scanf("%d %d", &n, &m);

    edge Array[m];
    for (int i = 0; i < m; i++)
    {
        scanf("%d %d %ld", &Array[i].start, &Array[i].end, &Array[i].weight);
    }

    // sorting all the edges acc to their weights
    merge_sort(Array , 0 , m-1);

    long int cost =0;
    int count =0;
    int place =0;

    // arrays for union-find
    int parent[n+1];
    int size[n+1];
    for(int i=1;i<=n;i++)
    {
        parent[i] = i;
        size[i] = 1;
    }

    while(count!= n-1) // when vertex n-1 edges has been selected , we can break
    {
        if(!is_cycle(Array[place].start , Array[place].end , parent))
        {
            unify(Array[place].start , Array[place].end ,parent , size);
            cost += Array[place].weight;
            place++;
            count++;
        }
        else 
        {
            place++;
        }
    }

    printf("%ld\n", cost);
}
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define Infinity (int)1e9 + 7
typedef struct pair pair;
// vertex are 1 based indexed , change accordingly
int minm(int a , int b)
{
    if(a<b)
    return a;
    else 
    return b;
}
struct pair
{
    int id;
    int invalue;
};
void enque(pair queue[], int *place, pair i)
{
    queue[*place] = i;
    *place += 1;
}
pair deque(pair queue[], int *place)
{
    *place = *place - 1;
    return queue[*place];
}
int bfs(int s, int t, int parent[], int n, int capacity[n + 1][n + 1])
{
    // mark the parent to be -1 , for bfs traversal
    for (int i = 0; i <= n; i++)
    {
        parent[i] = -1;
    }
    parent[s] = -2;

    pair queue[n]; // will store the k elements in it // storing all element in queue
    int place = 0; // tells where we have to store

    pair temp;
    temp.id = s;
    temp.invalue = Infinity;
    enque(queue , &place , temp);

    while(place!= 0)
    {
        pair out = deque(queue , &place);
        int cur = out.id;
        int flow = out.invalue;

        for(int i=1;i<=n;i++)
        {
            if(parent[i] == -1 && capacity[cur][i])
            {
                parent[i] = cur;
                int new_flow = minm(flow , capacity[cur][i]);
                if(i ==t)
                return new_flow;

                temp.id = i;
                temp.invalue = new_flow;
                enque(queue , &place , temp);
            }
        }
    }
}
int main()
{
    int n; // no of vertices
    scanf("%d", &n);

    int capacity[n + 1][n + 1];// 1 based indexing
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= n; j++)
            capacity[i][j] = 0;
    }

    int parent[n + 1];

    //making the graph
    int e;
    scanf("%d", &e);
    for (int i = 0; i < e; i++)
    {
        int start, end, value;
        scanf("%d %d %d", &start, &end, &value);
        capacity[start][end] = value;
    }

    // assuming source to be 1 and sink to be n
    int s = 1;
    int t = n;

    int flow = 0;
    int new_flow = 0;

    while (new_flow = bfs(s, t, parent, n, capacity))
    {
        flow += new_flow;
        int current = t;
        while (current != s)
        {
            capacity[current][parent[current]] += new_flow;
            capacity[parent[current]][current] -= new_flow;
            current = parent[current];
        }
    }

    // max flow has been stored in the flow
    printf("%d\n", flow);
}
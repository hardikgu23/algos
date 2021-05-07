#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#define ll long long int
#define Infinity (int)2e9 + 7
typedef struct edge edge;
typedef struct graph graph;
typedef struct node node;
struct edge
{
    int start;
    int end;
    ll weight;
};
struct node
{
    int id;
    ll weight;
    node *next;
};
void add_edge(edge temp, node list[]) // since the graph is directed , we would have to add both side
{
    int a = temp.start;
    int b = temp.end;
    node *x1;
    x1 = (node *)malloc(sizeof(node));

    x1->id = b;
    x1->weight = temp.weight;
    x1->next = list[a].next;
    list[a].next = x1;

    // comment this if graph is directed
    // node *x2;
    // x2 = (node *)malloc(sizeof(node));

    // x2->id = a;
    // x2->weight = temp.weight;
    // x2->next = list[b].next;
    // list[b].next = x2;
}
void swap(int*x, int *y)
{
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;
}
int parent(int i)
{
    return (i - 1) / 2;
}
int left(int i)
{
    return 2 * i + 1;
}
int right(int i)
{
    return 2 * i + 2;
}
void insert_key(int pqueue[], int v, int *pqueue_size, ll MinDist[] , int posn[] ) // will insert x in the pqueue after last node and then will pqueueify
{
    int i = *pqueue_size;
    pqueue[i] = v;
    posn[v] = i;
    *pqueue_size = *pqueue_size + 1;

    while (i != 0 && MinDist[pqueue[parent(i)]] > MinDist[pqueue[i]])
    {
        posn[pqueue[parent(i)]] = i;
        posn[pqueue[i]] = parent(i);
        swap(&pqueue[parent(i)], &pqueue[i]);
        i = parent(i);
    }
}

void MinHeapify(int pqueue[], int i, int pqueue_size, int posn[] , ll MinDist[])
{
    int l = left(i);
    int r = right(i);
    int smallest = i;

    if (l < pqueue_size && MinDist[pqueue[l]] < MinDist[pqueue[smallest]])
    {
        smallest = l;
    }
    if (r < pqueue_size && MinDist[pqueue[r]] < MinDist[pqueue[smallest]])
    {
        smallest = r;
    }

    if (smallest != i)
    {
        posn[pqueue[smallest]] = i;
        posn[pqueue[i]] = smallest;
        swap(&pqueue[smallest], &pqueue[i]);
        MinHeapify(pqueue, smallest, pqueue_size, posn , MinDist);
    }
}

void update_key(int pqueue[], int i, ll new_value, int pqueue_size, int posn[] , ll MinDist[])
{
    MinDist[pqueue[i]] = new_value;
    while (i != 0 && MinDist[pqueue[parent(i)]] > MinDist[pqueue[i]])
    {
        posn[pqueue[parent(i)]] = i;
        posn[pqueue[i]] = parent(i);
        swap(&pqueue[parent(i)], &pqueue[i]);
        i = parent(i);
    }
}

int extract_min(int pqueue[], int *pqueue_size, int posn[] , ll MinDist[]) // return the min element and remove it from the pqueue
{
    if (*pqueue_size == 1)
    {
        *pqueue_size = *pqueue_size - 1;
        return pqueue[0];
    }

    posn[pqueue[0]] = *pqueue_size - 1;
    posn[pqueue[*pqueue_size - 1]] = 0;

    swap(&pqueue[0], &pqueue[*pqueue_size - 1]);
    *pqueue_size = *pqueue_size - 1;

    MinHeapify(pqueue, 0, *pqueue_size, posn , MinDist);

    return pqueue[*pqueue_size];
}
int peak_min(int pqueue[])
{
    return pqueue[0];
}
void delete_key(int i, int pqueue[], int *pqueue_size, int posn[] , ll MinDist[])
{
    update_key(pqueue, i, pqueue[0] - 1, *pqueue_size, posn , MinDist);
    extract_min(pqueue, pqueue_size, posn , MinDist);
}
int main()
{
    int n;
    scanf("%d", &n);

    // keep track whether we know shortest distance to that vertex or not
    bool is_known[n + 1];
    for (int i = 1; i <= n; i++)
        is_known[i] = false;

    ll MinDist[n + 1]; // will store the minimum distance to reach vertex
    for (int i = 1; i <= n; i++)
    {
        MinDist[i] = Infinity;
    }

    ll prev_vertex[n + 1]; // will store the previous vertex that has to be reached to that vertex in shortest path

    for (int i = 1; i <= n; i++)
    {
        prev_vertex[i] = -1;
    }

    // making list // assuming vertex are 1 based indexing
    node *list;
    list = (node *)malloc((n + 1) * sizeof(node));
    for (int i = 1; i <= n; i++)
        list[i].next = NULL;

    int e; // e is number of edges
    scanf("%d", &e);

    for (int i = 0; i < e; i++)
    {
        edge temp;
        scanf("%d %d %lld", &temp.start, &temp.end, &temp.weight);
        add_edge(temp, list);
    }

    int priority_queue[n + 1];
    for (int i = 0; i <= n; i++)
    {
        priority_queue[i] = Infinity;
    }
    int posn[n + 1]; // will store the posn of each vertex in priority queue
    for (int i = 1; i <= n; i++)
    {
        posn[i] = i - 1; // posn[i] tells what is the index in pqueue , where vertex i is present
    }

    // making shortest distance to central island 0 and then adding all shortest distance to priority queque
    MinDist[1] = 0;
    is_known[1] = true;


    int pqueue_size = 0;

    for (int i = 1; i <= n; i++) // adding vertices in priority queue according to their shortest distance
    {
        insert_key(priority_queue, i, &pqueue_size, MinDist, posn);
    }
    // apply djikstra // give priority to the path that has less no of waterways in case of same weight

    while (pqueue_size != 0) // or priority queue is not empty
    {
        int i = extract_min(priority_queue, &pqueue_size, posn , MinDist); // extract out the vertex from priority queue which has lowest known distance among all other in queue
        //posn[i] = pqueue_size;

        // mark the min distance of lowest vertex to be known
        is_known[i] = true;

        // update the distance of all the neigbouring vertices of i
        while (list[i].next != NULL)
        {
            list[i] = *(list[i].next);
            if (MinDist[i] + list[i].weight < MinDist[list[i].id]) // if new min dist is less than previous lowest dist
            {
                MinDist[list[i].id] = MinDist[i] + list[i].weight;
                update_key(priority_queue, posn[list[i].id], MinDist[list[i].id], pqueue_size, posn , MinDist);

                prev_vertex[list[i].id] = i;
            }
        }
    }

    //printing min_dist array
    for(int i=1;i<=n;i++)
    {
        printf("%lld ", MinDist[i]);
    }

}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
typedef struct node node;
struct node
{
    int id;
    node *next;
};

void bfs_visit(int i, node list[], int array[], int *position, bool is_visited[])
{
    if (is_visited[i] == true)
        return;
    is_visited[i] = true;
    // array[*position] = i;
    // (*position) += 1;

    node temp = list[i];

    // visit all its neighbour
    while (list[i].next != NULL)
    {
        list[i] = *(list[i].next);
        int a = list[i].id;
        if (is_visited[a] == false)
        {
            // is_visited[a] = true;
            array[*position] = a;
            *position += 1;
        }
    }

    // doing bfs on its neigbours
    while (temp.next != NULL)
    {
        temp = *(temp.next);
        bfs_visit(temp.id, list, array, position, is_visited);
    }
}
int main()
{
    int n, e; // e is the number of edges that will be inputted
    scanf("%d %d", &n, &e);

    int array[n]; // will store the dfs traversal of the graph
    int posn = 0; // (optional)tells where we have to add element in array[]

    bool is_visited[n + 1]; //using 1 based indexing
    for (int i = 1; i <= n; i++)
        is_visited[i] = false;

    node *list;
    list = (node *)malloc((n + 1) * sizeof(node));
    for (int i = 1; i <= n; i++)
        list[i].next = NULL;

    for (int i = 0; i < e; i++)
    {
        int start, end;
        scanf("%d %d", &start, &end);
        node *temp;
        temp = (node *)malloc(sizeof(node));
        temp->id = end;
        temp->next = list[start].next;
        list[start].next = temp;
    }
    array[posn++] = 1;
    bfs_visit(1, list, array, &posn, is_visited);

    for (int i = 0; i < n; i++)
        printf("%d ", array[i]);

    // printf("\n%d\n", posn);
}
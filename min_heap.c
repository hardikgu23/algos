#include <stdio.h>
void swap(int *x, int *y)
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
void insert_key(int Array[], int x, int* heap_size) // will insert x in the array after last node and then will heapify
{
    int i = *heap_size;
    Array[i] = x;
     *heap_size = *heap_size +1;
    if (i == 0)
        return;

    while (i != 0 && Array[parent(i)] > Array[i])
    {
        swap(&Array[parent(i)], &Array[i]);
        i = parent(i);
    }
   
}

void MinHeapify(int Array[], int i, int heap_size)
{
    int l = left(i);
    int r = right(i);
    int smallest = i;

    if (l < heap_size && Array[l] < Array[smallest])
    {
        smallest = l;
    }
    if (r < heap_size && Array[r] < Array[smallest])
    {
        smallest = r;
    }

    if (smallest != i)
    {
        swap(&Array[smallest], &Array[i]);
        MinHeapify(Array, smallest, heap_size);
    }
}

void update_key(int Array[], int i, int new_value, int heap_size)
{
    Array[i] = new_value;
    MinHeapify(Array, i, heap_size);
    while (i != 0 && Array[parent(i)] > Array[i])
    {
        swap(&Array[parent(i)], &Array[i]);
        i = parent(i);
    }
}

int extract_min(int Array[], int* heap_size) // return the min element and remove it from the heap
{
    if (*heap_size == 1)
    {
        *heap_size = *heap_size -1;
        return Array[0];
    }

    swap(&Array[0], &Array[*heap_size - 1]);
     *heap_size = *heap_size -1;

    MinHeapify(Array, 0, *heap_size);

    return Array[*heap_size];
}
int peak_min(int Array[])
{
    return Array[0];
}
void delete_key(int i, int Array[], int *heap_size)
{
    update_key(Array, i, Array[0] - 1 , *heap_size);
    extract_min(Array, heap_size);
}
int main()
{
    int heap_size = 0;
    int n = 6;
    //scanf("%d",&n);
    int Array[n];
    for (int i = 0; i < n; i++)
    {
        insert_key(Array, 5, &heap_size);
    }

    int min = extract_min(Array, &heap_size);

    update_key(Array, 1, 1 , heap_size);
     //min = extract_min(Array, &heap_size);

    for (int i = 0; i < heap_size; i++)
        printf("%d ", Array[i]);

    printf("\n%d ", min);
}
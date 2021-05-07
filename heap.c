// akshat sharma git repository
#include <stdio.h>
int max(int Array[] , int i) // will return which of the i , 2*i +1 , 2*i + 2 will be minimum
{
    if(2*i+1 <= n-1 && 2*i+2 <= n-1)
    {
        int a;
        if(Array[2*i])
    }
    else 
    {
        int a;
        if(Array[2*i+1] > Array[i])
        return 
    }
}
void downheap(int Array , int i)
{
    int a = max(Array, i); 
    if(a == 0)
    return;
    if(a == -1)
    {
        int temp = Array[i];
        Array[i] = Array[2*i +1];
        Array[2*i + 1] = Array[i];
        return;
    }
    if(a == 1)
    {
        int temp = Array[i];
        Array[i] = Array[2*i + 2];
        Array[2*i+2] = Array[i];
        return;
    }

}
int main()
{
    int n;
    scanf("%d",&n);
    int Array[n];
    for(int i=0;i<n;i++)
    {
        scanf("%d",&Array[i]);
    }
    // applying downheap from n/2 - 1 t0 0
    for(int i=n/2 -1 ;i>=0;i--)
    downheap(Array , i);

    // Heap is made 
    // Array[0] contains the max element 
    printf("%d is the max element in the given array\n", Array[0]);
}
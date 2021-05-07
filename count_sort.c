// sort using hashing. works in O(n), space complexicity is also O(n)
#include <stdio.h>
void count_sort(int Array[] ,int n , int max) //max will tell me , how much large my hash_count table will be
{
    // copying the data of Array into a temp array;
    int temp_Array[n];
    for(int i=0;i<n;i++)
    temp_Array[i] = Array[i];

    int Hash_count[max+1];
    for(int i=0;i<max+1;i++)
    Hash_count[i] =0;

    // keeping a count or making a frequency table
    for(int i=0;i<n;i++)
    {
        Hash_count[Array[i]]++;
    }
    // making it cumulative 
    for(int i=1;i<max+1;i++)
    Hash_count[i] = Hash_count[i] + Hash_count[i-1];

    //Sorting the array
    for(int i=0;i<n;i++){
    Array[Hash_count[temp_Array[i]]-1] = temp_Array[i];
    Hash_count[temp_Array[i]]--;
    }
}
int main()
{
    int n;
    scanf("%d",&n);
    int Array[n];

    int max =0;
    for(int i=0;i<n;i++)
    {
    scanf("%d",&Array[i]);
    if(Array[i] > max)
    max = Array[i];
    }

    count_sort(Array, n ,max);

    for(int i=0;i<n;i++)
    printf("%d ",Array[i]);
}
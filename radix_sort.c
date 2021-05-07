// program Radix Sort . Cant sort -ve numbers
#include <stdio.h>
void count_sort(int Array[] , int n, int exp)
{
	int temp[10] = {0};
	int output[n];
	for(int i=0;i<n;i++)
	{
		temp[(Array[i]/exp) %10]++;
	}

	for(int i=1;i<10;i++)
	{
		temp[i] = temp[i] + temp[i-1];
	}
	for(int i=n-1;i>=0;i--)
	{
		output[temp[(Array[i]/exp) %10] -1] = Array[i];
		temp[(Array[i]/exp) %10]--;
	}
	for(int i=0;i<n;i++)
		Array[i] = output[i];
}
void Radix_sort(int Array[] , int n)
{
	int max = Array[0];
	for(int i=0;i<n;i++)
		if(Array[i] > max)
			max = Array[i];

	for (int exp = 1; max / exp > 0; exp *= 10) 
    	count_sort(Array, n, exp);

}
void print_array(int Array[] , int n)
{
	for(int i=0;i<n;i++)
		printf("%d ",Array[i]);
}
int main()
{
	int n; // length of Array;
	scanf("%d",&n);
	int Array[n];
	for(int i=0;i<n;i++)
		scanf("%d",&Array[i]);
	Radix_sort(Array,n);
	print_array(Array,n);
}
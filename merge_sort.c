//program for merge sort
#include <stdio.h>

void merge(int Array[], int l , int m , int r )
{
	int n1 =  m - l +1;
	int n2 = r - m;
	int temp1[n1] , temp2[n2];
	for(int i =0;i<n1;i++)
	{
		temp1[i] = Array[l+i];
	}
	for(int i =0;i<n2;i++)
	{
		temp2[i] = Array[m+1+i];
	}

	int i=0, j=0 , k =l;

	while(i<n1 && j<n2)
	{
		if(temp1[i] <= temp2[j])
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

	while(i<n1)
	{
		Array[k] = temp1[i];
			i++;
			k++;
	}
	while(j<n2)
	{
		Array[k] = temp2[j];
			j++;
			k++;
	}
}

void merge_sort(int Array[] , int l , int r)
{
	if(r>l)
	{
	int m = (l+r)/2 ;

	merge_sort(Array , l , m);
	merge_sort(Array , m+1 , r);

	merge(Array , l , m , r);
	}
}
void print_Array(int Array[], int n)
{
	for(int i=0;i<n;i++)
	printf("%d ",Array[i]);
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

	merge_sort(Array,0,n-1);

	print_Array(Array,n);
}
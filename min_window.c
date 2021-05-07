// this program stores the max of all subarray of length k (window sliding them , so n-k+1 in number) in O(n)
// #include <bits/stdc++.h>
// using namespace std;
#include <stdio.h>

void enque(int queue[], int *place, int i)
{
    queue[*place] = i;
    *place += 1;
}
int deque(int queue[] , int* place)
{
    *place = *place -1;
    return queue[*place];
}

int main()
{
    int n;
    scanf("%d",&n);

    int Array[n];
    for (int i = 0; i < n; i++)
       scanf("%d",&Array[i]);

    int k; // window size
    // cin >> k;
    scanf("%d",&k);

    int answer[n - k + 1];

    int queue[n];   // will store the k elements in it // storing all element in queue
    int place = 0;  // tells where we have to store  
    int index =0; // tells where we have to store in answer array 
    int start =0; // will be used when we want to know where max element of window is stored

    //pushing first k element in the queue
    enque(queue , &place , 0);
    for (int i = 1; i < k; i++) // bottom will remain zero
    {
        while(place != 0 && Array[i] < Array[queue[place-1]])
        {
            deque(queue , &place);
        }
        enque(queue, &place, i);
    }

     answer[index++] = Array[queue[start]];

    // now inserting element one by one and finding the answer of each window
    for(int i=k;i<n;i++)
    {
        while(place != 0 && Array[i] < Array[queue[place-1]])
        {
            deque(queue , &place);
        }
        enque(queue, &place, i);
        while(queue[start] < i-k+1)
        {
            start++;
        }
        answer[index++] = Array[queue[start]];
    }

    for(int i=0;i<n-k+1;i++)
    printf("%d ", answer[i]);
}
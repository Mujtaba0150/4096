#include <iostream>
using namespace std;

//Bubble sort:

int main() 
{
    int j;
    int arr[5]={2,5,3,6,4};
    //Sorted array: {2,3,5,6,8}
    int temp;
    
    for(int i=1;i<5;i++)
    {
        for( j=1;j<=4;j++)
        {
            if(arr[j-1]>arr[j])
            {
               temp=arr[j];
               arr[j]=arr[j-1];
               arr[j-1]=temp;
            }
        }
    }
    for(int k=0;k<5;k++)
    {
        cout<<arr[k]<<",";
    }
    return 0;
}
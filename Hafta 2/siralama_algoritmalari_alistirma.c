#include <stdio.h>
#include <cs50.h>
void print(int dizi[],const int size)
{
    for (int i = 0 ; i < size ; i++){
        printf("%d ",dizi[i]);
    }
    printf("\n");
}
void swap(int dizi[],int a, int b)
{
    int temp = dizi[a];
    dizi[a] = dizi[b];
    dizi[b] = temp;
}
void selectionSort(int dizi[],const int size)
{
    for (int i = 0 ; i < size-1 ; i++)
    {
        int min = dizi[i];
        int index = i;
        for (int k = i+1; k < size ; k++)
        {
            if (dizi[k] < min)
            {
                min = dizi[k];
                index = k;
            }
        }
        swap(dizi,index,i);
    }
}
void bubbleSort(int dizi[],const int size)
{
    for (int i = 0; i < size-1 ; i++)
    {
        for (int k = 1 ; k < size ; k++)
        {
            if (dizi[k] < dizi[k-1])
            {
                swap(dizi,k,k-1);
            }    
        }
    }
}
void insertionSort(int dizi[] , const int size)
{
    for (int i = 1 ; i < size ; i++)
    {
        int k = i;
        while (k > 0 && dizi[k] < dizi[k-1])
        {
            swap(dizi,k,k-1);
            k--;
        }
    }
}
void merge(int dizi[],int left,int mid,int right)
{
    const int size = right-left+1;
    int sirali[size];
    int a = 0;
    int p1 = left;
    int p2 = mid + 1;
    for (int i = 0 ; i < size ; i++){
        if (p1 == mid +1 ) sirali[a++] = dizi[p2++];
        else if (p2 == right+1) sirali[a++] = dizi[p1++];
        else if (dizi[p1] < dizi[p2] )  sirali[a++] = dizi[p1++];
        else sirali[a++] = dizi[p2++];
    }
    for (int i = 0 ; i < size ; i++){
        dizi[i+left] = sirali[i];
    }
}
void merge2(int dizi[],const int min,const int max)
{
    if (max <= min) return;
    int mid = (max+min)/2;
    merge2(dizi,min,mid);
    merge2(dizi,mid+1,max);

    merge(dizi,min,mid,max);
}
void mergeSort(int dizi[],const int size){
    merge2(dizi,0,size-1);
}
int main()
{ 
    const int size = 5;
    int dizi[size];
    for (int i = 5 , k = 0; i > 0 ; i-- , k++)
    {
        dizi[k] = i;
    }
    print(dizi,size);
    mergeSort(dizi,size);
    print(dizi,size);

}

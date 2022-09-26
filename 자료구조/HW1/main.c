#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void InsertionSort(int* arr,int len)
{
    int i,j,key;
    for(i=1; i<len; i++) {
        key = arr[i];
        for(j=i-1; j>=0; j--) {
            if(arr[j] > key) {
                arr[j+1] = arr[j];
            } else break;
        }
        arr[j+1] = key;
    }
}

int main()
{
    clock_t first=clock();
    int* arr;
    int* arr_org;
    int num=0,i=0,arrnum=0;
    arr = (int*)malloc(sizeof(int)*100);
    arr_org = (int*)malloc(sizeof(int)*100);
    FILE *fp;
    fp = fopen("lab1.data","r");
    printf("Input: ");
    
    while(fscanf(fp,"%d",&num)!=EOF)
    {
        arr[i] = num;
        arr_org[i] = num;
        i++;
        arrnum++;
        printf("%d ",num);
    }
    fclose(fp);
    printf("\n");
    InsertionSort(arr, arrnum);
    printf("Sorted : ");
    for(i=0; i<arrnum; i++)
        printf("%d ",arr[i]);    //print output
    printf("\n");
    printf("\tn\trepttition\ttime\n");
    double duration;
    for(int n=0; n<=100; n+=10)
    {
        printf("\t%d",n);
        printf("\t\t%d",2000-10*n);
        clock_t start = clock();
       
        for(int rep=0; rep<2000-10*n;rep++)
        {
            for(i=0; i<arrnum; i++)
                arr[i] = arr_org[i];   //initialize
            InsertionSort(arr, n);
        }
        
        duration = ((double)(clock() - start)) / CLOCKS_PER_SEC * 100;  //결과값이 너무작아서 곱해줌-연산결과단위 1/100초
        duration /= (2000 - 10*n);
        if (n != 0) printf("\t");
        printf("\t%f\n", duration);
    }
    
    duration = ((double)(clock() - first)) / CLOCKS_PER_SEC * 100;
    
    printf("[Finished in %.1f sec]\n",duration);
    return 0;
}

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int flag=0;
int count=0;
int failure[100];
void string_search(char* str, char* search)
{
    int len = strlen(search);
    char* temp;
    int i=0;
    for(int t=0; t<strlen(str)-len +1; t++)
    {
        temp = &str[i];
        if (strncmp(temp,search,len) == 0) {
            count+=len;
            flag = 1;
            return;
        }
        else count+=len;
        i++;
    }
    
    return;
}

int kmpmatch(char *str, char* search)
{
    int i=0; int j=0;
    while(i<strlen(str) && j<strlen(search))
    {
        count++;
        if (str[i] == search[j])
        {
            i++; j++;
        }
        else if (j==0) i++;
        else j=failure[j-1] + 1;
    }
    return ((j==strlen(search)) ? (i - strlen(search)) : -1);
}

void fail(char *search)
{
    int i;
    int n = strlen(search);
    int j;
    failure[0] = -1;
    for(j=1; j<n; j++)
    {
        i = failure[j-1];
        while( i >= 0 && search[j] != search[i+1] )
            i = failure[i];
        if (search[j] == search[i+1])
            failure[j] = i+1;
        else failure[j] = -1;
    }
}


int main()
{
    char search[100];
    char str[100];
    scanf("%s",str);
    scanf("%s",search);
    string_search(str,search);
    if (flag == 1) printf("YES %d\n",count);
    else printf("NO %d\n",count);
    count = 0; flag = 0;
    fail(search);
    flag= kmpmatch(str,search);
    if (flag == -1) printf("NO %d\n",count);
    else printf("YES %d\n",count);
    return 0;
}

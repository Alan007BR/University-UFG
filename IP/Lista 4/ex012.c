#include <stdio.h>
#include <string.h>
#include <stdlib.h>
 
#define MAX_WORDS 200
#define MAX_WORD_LEN 64+1
 
int str_split(char * str, char m[][MAX_WORD_LEN], char * sep);
 
int main(void)  {
    char str[12801];
    char b[MAX_WORDS][MAX_WORD_LEN];
    char sep[MAX_WORDS];
    int n, i, j, igual=0, x=0;
    int *a;
 
    scanf("%[^\n]%*c", str);
    scanf("%[^\n]", sep);
 
    n=str_split(str, b, sep);
    
    a=(int*)malloc(n*sizeof(int));
    
    for(i=0; i<n; i++){
        a[i]=strlen(b[i]);
        
        printf("(%d)%s\n", a[i], b[i]);
        
        if(a[i]>x) x=a[i];
    }
    
    for(i=0; i<n; i++){
        if(x==a[i]) igual++;
    }
    printf("%d\n", igual);
 
    free(a);
    return 0;
}
 
int str_split(char * str, char m[][MAX_WORD_LEN], char * sep){
    int n, n2, i = 0, j = 0, k = 0;
    
    n=strlen(sep);
    n2=strlen(str);
    
    for(i=0; i<n; i++){
        for(j=0; j<n2; j++){
            if(sep[i]==str[j]){
                str[j]=0;
            }
        }
    }
    j=0;
    for(i=0; i<n2; i++) {
        if(str[i]!=0) {
            m[j][k]=str[i];
            k++;
            
            if(str[i+1]==0 || k>=64){
                m[j][k]='\0';
                j++;
                k=0;
            }
 
        }
    }
    
 
    return j;
}
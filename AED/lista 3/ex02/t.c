/*
 * C Program which Converts an Integer to String & vice-versa
 */
#include <stdio.h>
#include <string.h>
#include <math.h>
 
void tostring(char [], int);
int toint(char []);
 
int main()
{
    char str[10];
    int num, result;
 
    printf("Enter a number: ");
    scanf("%d", &num);
    tostring(str, num);
    printf("Number converted to string: %s\n", str);
    result = toint(str);
    printf("Number converted back to integer: %d\n", result);
 
    return 0;
}
 
void tostring(char str[], int num)
{
    int i, rem, len = 0, n;
 
    n = num;
    while (n != 0)
    {
        len++;
        n /= 10;
    }
    for (i = 0; i < len; i++)
    {
        rem = num % 10;
        num = num / 10;
        str[len - (i + 1)] = rem + '0';
    }
    str[len] = '\0';
}
 
int toint(char str[])
{
    int len = strlen(str);
    int i, num = 0;
 
    for (i = 0; i < len; i++)
    {
        num = num + ((str[len - (i + 1)] - '0') * pow(10, i));
    }
 
   return num;
}
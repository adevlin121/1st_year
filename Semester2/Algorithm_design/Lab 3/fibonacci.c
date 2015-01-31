/*
 Aidan Devlin
 20-2-2014
 */


#include <stdio.h>
int fibonacci (int);

main()
{
    int i=0;
    int n=0;
    int term=0;
    printf("Enter term number you want to display\n");
    scanf("%d",&n);
    for (i=0; i<n; i++)
    {
        term = fibonacci(i);
    }

    printf("The term you are looking for is\n");
    printf("%d",term);
}

int fibonacci (int n)
{
    if (n==0 || n==1)
    {
        return(n);
    }
    else
    {
        return(fibonacci(n-1) + fibonacci(n-2));
    }
}
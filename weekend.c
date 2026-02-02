#include <stdio.h>

void main()
{
int weekend;
int cigars;
printf("enter the weekend \n");
scanf("%d",&weekend);
printf("enter the cigars \n");
scanf("%d",&cigars);
if(weekend==1)
{
    if(cigars>=40)
    {
        printf("true ");
    }
    else 
    {
        printf("false");
    }
    }
    else
    {
    if(cigars>=40&&cigars<=60)
    {
        printf("true");
    }
    else
    {
        printf("false");
    }
    }
    }
    


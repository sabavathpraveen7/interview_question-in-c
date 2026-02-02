#include <stdio.h>

void main()
{
    int you, your_date;
    printf("enter the rating of you and your date \n");
    scanf("%d %d",&you,&your_date);
    if(you<=2||your_date<=2)
    {
        printf("0");
    }
    else if(you>=8||your_date>=8)
    {
        printf("2");
    }
    else
    {
        printf("1");
    }
    }
    
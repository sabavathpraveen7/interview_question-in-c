#include <stdio.h>

void main() {
    int tea,candy;
printf("enter the no of tea and candy \n");
scanf("%d %d",&tea,&candy);
if(tea<5||candy<5)
{
    printf("0");
}
else if(tea>=candy*2||candy>=tea*2)
{
    printf("2");
}
else
{
    printf("1");
}
}
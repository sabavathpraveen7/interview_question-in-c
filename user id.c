#include <stdio.h>

void main()
{
int user_id=5371;
int user_password=9647;
int id;
int password;
printf("enter the user id \n");
scanf("%d",&id);
printf("enter the user password \n");
scanf("%d",&password);
if(user_id==id)
{
    if(user_password=password)
    {
        printf("login successful \n");
    }
    else 
    {
        printf("incorrect password \n");
    }
    }
    else
    {
        printf("incorrect user_id \n");
    }
    }
    


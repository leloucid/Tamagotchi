#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
int sys()
{
    int i,j;
    for(i=0;i<2;i++)
    {
       for(j=0;j<52;j++)
       {
          printf("-");
       }
       printf("\n");
       if(i==0)
       {printf("| 1.Food | 2.Play | 3.Light | 4.Medicine | 5.Clean |\n");}
    }
}

int poring_normal(num)
{
    if(num%2==0)
    {
       printf("	          aa\n");
       printf("		    aa\n");
       printf("		   aaaaaa\n");
       printf("	          aaaaaaaa\n");
       printf("	         aaaaaaaaaa\n");
       printf("	       aaaOaa|aaOaaa\n");
       printf("	       aaaaaaWaaaaaaaa\n");
       printf("	       aaaaaaaaaaaaaa\n");
       printf("	        aaaaaaaaaaaa\n");
    }
    else if(num%2==1)
    {
       printf("	         aa\n");
       printf("		    aa\n");
       printf("		   aaaaaa\n");
       printf("	          aaaaaaaa\n");
       printf("	         aaaaaaaaaa\n");
       printf("	       aaa=aa|aa=aaa\n");
       printf("	       aaaaaaWaaaaaaaa\n");
       printf("	       aaaaaaaaaaaaaa\n");
       printf("	        aaaaaaaaaaaa\n");
    }
}

int command_line(command)
{
    switch(command)
    {
       case 1:
              printf("Eating...");
              break;
       case 2:
              printf("Playing...");
              break;
       case 3:
              printf("Sleeping...");
              break;
       case 4:
              printf("Curing...");
              break;
       case 5:
              printf("Cleaning...");
              break;
       default: 
              printf("Nothing");
              break;
    }
}


int main()
{
    int num,command;
    num=0;
    while(1)
    {
       sys();
       poring_normal(num);
       num++;
       sleep(600);
       system("cls");
       /*printf("Your command :");
       scanf("%d",&command);*/
    }
}





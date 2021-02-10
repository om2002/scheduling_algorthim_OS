#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include <termios.h>
typedef struct process {
         char * name;
         int arrival;
         int cpuburst;
         int turnaround;
         int wait;
    } Process;

Process *newProcess(char *c,int arr,int burst)
{
   Process *p = (Process *) malloc(sizeof(Process));
   p->name = (char *)malloc(500*sizeof(char));
   strcpy(p->name,c);
   p->arrival = arr;
   p->cpuburst = burst;
   p->turnaround = 0;
   p->wait;
   return p;
}


void FCFS(Process **pro,int len )
{
   printf("---------------------------------------------------------------------                                                                                        ----------------------------------\n");
   printf("                               First Come First Served Scheduling                                                                                                        \n");
    printf("--------------------------------------------------------------------                                                                                        -----------------------------------\n");
   int total_burst = 0;

   for(int i=0;i<len;i++)
     total_burst +=pro[i]->cpuburst;

   int burst  = 0;
   int l = 0;
   int t = 0;
   while(burst != total_burst)
   {
           if(t < pro[l]->arrival)
           {
                t++;
                continue;
            }
       else{
       printf("[%d-%d] %s running\n",t,t+pro[l]->cpuburst,pro[l]->name);
       pro[l]->wait = t - pro[l]->arrival;
       pro[l]->turnaround = pro[l]->wait + pro[l]->cpuburst;
       t +=pro[l]->cpuburst;
       burst += pro[l]->cpuburst;
       l++;
     }
   }

 }

void SRBF(Process **pro,int len)
{
   int total_burst = 0;

   for(int i=0;i<len;i++)
    total_burst +=pro[i]->cpuburst;

   int arr[len];

   for(int i=0;i<len;i++)
   {
     arr[i] = pro[i]->cpuburst;
   }


    printf("--------------------------------------------------------------------                                                                                        ------------------------------------\n");
    printf("                 Shortest Remaining Burst First\n");
    printf("--------------------------------------------------------------------                                                                                        ------------------------------------\n");
   int start = 0;
   int burst = 0;
   int pretime = 0;
   char * pre = (char *)malloc(100*sizeof(char));
   char *curr = (char *)malloc(100*sizeof(char));
   int small;
   while(burst != total_burst)
   {
        small = -1;
      for(int i=0;i<len;i++)
      {
           if((arr[i] == 0 && small == -1) || start <  pro[i]->arrival && arr[i]                                                                                         )
             continue;

          if(arr[i] && small == -1)
           small = i;
          else if(small != -1 && start >= pro[i]->arrival && arr[i]  !=0 && arr[                                                                                        i]  < arr[small])
            small = i;
      }
      if(small == -1)
      {
         start++;
         continue;
      }
    // printf(" samll = %d   /",small);
     if(start == 0 )
     {
       strcpy(pre,pro[small]->name);
       arr[small]--;
       start++;
       burst++;
       pretime = 0;
       continue;
     }

     strcpy(curr,pro[small]->name);

     if( strcmp(pre,curr)!=0 ||  burst == total_burst -1)
     {
         if(burst == total_burst -1)
        printf("[%d  %d]   %s running\n",pretime,start+1,pre);
         else
                 printf("[%d  %d]   %s running\n",pretime,start,pre);
        pretime = burst;
        burst++;
        start++;
        strcpy(pre,pro[small]->name);
        arr[small]--;
        if( arr[small]  == 0)
        {
            pro[small]->wait = start - 1- pro[small]->cpuburst-pro[small]->arriv                                                                                        al;
            pro[small]->turnaround = pro[small]->wait + pro[small]->cpuburst;
        }
    }

   else{
      burst++;
      start++;
      arr[small] --;
    }
   }
}


void RR(Process **pro,int len,int qnt)
{

     int arr[len];
     int total_burst = 0;
     for(int i=0;i<len;i++)
     {
         arr[i] = pro[i]->cpuburst;
        total_burst += pro[i]->cpuburst;
     }

     printf("-------------------------------------------------------------------                                                                                        ---------------------------------------\n");
     printf("              Round Robin Scheduling     \n");
      printf("------------------------------------------------------------------                                                                                        ----------------------------------------\n");
     int t = 0;
     int t1 = 0;
     int num;
     while(t!=total_burst)
     {
           num = 0;
          for(int i=0;i<len;i++)
          {
             if(arr[i] == 0 || pro[i]->arrival > t1)
             {
               num++;
               continue;
            }

            else if(arr[i] > qnt)
            {
                //[ 0-2]    P0 running
                printf("[%d  %d]     %s is      running \n",t1,t1+qnt,pro[i]->na                                                                                        me);
                arr[i] = arr[i] - qnt;
                t = t+qnt;
                t1 = t1 + qnt;
            }
            else if( arr[i] <=  qnt && arr[i] >0)
            {
                 printf("[%d  %d]     %s is      running \n",t1,t1+arr[i],pro[i]                                                                                        ->name);
               t = t + arr[i];
               t1 = t1 + arr[i];
               arr[i] = 0;
               pro[i]->wait = t1 - pro[i]->arrival - pro[i]->cpuburst;
               pro[i]->turnaround = pro[i]->wait + pro[i]->cpuburst;
            }

         }
         // printf("%d  %d       ",num,len);
         if(num == len)
         {
           t1++;
         }
     }
}

void time(Process **pro,int len)
{
    double  avg_wait = (double)pro[0]->wait;
    double  avg_turn = (double) pro[0]->turnaround;

     printf("Turnaround times : %s [%d]  ",pro[0]->name,pro[0]->turnaround);
     for(int i=1;i<len;i++){
     printf(", %s [%d] ",pro[i]->name,pro[i]->turnaround);
     avg_turn += (double) pro[i]->turnaround;
     }
     printf("\n");
      printf(" Wait times : %s [%d]  ",pro[0]->name,pro[0]->wait);
     for(int i=1;i<len;i++){
     printf(", %s [%d] ",pro[i]->name,pro[i]->wait);
     avg_wait +=(double) pro[i]->wait;
     }

     avg_wait = avg_wait/(double)len;
     avg_turn = avg_turn / (double)len;
      printf("\n");
     printf(" Average turnaround time : %lf\n",avg_turn);
     printf("Average wait time  : %lf \n",avg_wait);

}



 int main(int argc, char *argv[])
{
    char in_name[80];
    FILE *in_file;
    char word[50];
    Process **pro = (Process **)malloc(1000*(sizeof(Process*)));

    int len = 0;
    char *c = (char *)malloc(100*sizeof(char));
    int arr;
    int burst;
   // printf("Enter file name:\n");
   // scanf("%s", in_name);

    if(argc < 1)
    {
       printf("enter file name correctly \n");
       exit(1);
    }
    in_file = fopen(argv[1], "r");

    if (in_file == NULL)
        printf("Can't open %s for reading.\n", in_name);
    else
    {
            int l = 1;
        while (fscanf(in_file, "%s", word) != EOF)
        {
          if(l==1)
          {
           strcpy(c,word);
         //  printf("%s 1--   ",c);
            l++;
        }
        else if(l==2)
        {
          //printf("%s  ",c);
         arr = atoi(word);
         //printf("%s  %d --   ",c,arr);
          l++;
        }
        else{
        //      printf("%s  \n ",c);
                burst = atoi(word);
                pro[len++] = newProcess(c,arr,burst);
           l = 1;
        }
        }
        fclose(in_file);
    }

    // char ch;
    // printf("Enter any key to start :\n ");
    while(1)
   {
      printf("------------------------------------------------------------------                                                                                        -----------------------------\n");
      printf("             CPU Scheduling Simulation  \n");
      printf("------------------------------------------------------------------                                                                                        ----------------------------\n");
      printf("  Select the scheduling algorithm [1,2,3 or 4] : \n");
      printf("  1. First Come First Served (FCFS) \n");
      printf("  2. Round Robin (RR) \n");
      printf("  3. SRBF \n");
      printf("  4. Exit \n ");

      int f ;
      scanf("%d",&f);

      if(f==1)
      {
       FCFS(pro,len);
       time(pro,len);
      }
      else if(f==2)
      {
         int qnt;
         printf("Enter the time quantum : ");
         scanf("%d",&qnt);
         RR(pro,len,qnt);
         time(pro,len);
      }
      else if(f==3)
      {
           SRBF(pro,len);
           time(pro,len);
      }
      else if(f==4)
      {
          exit(1);
      }
      else {
          printf("please enter correct key \n");
      }
      printf("\n");
      printf("Hit any key to continue ... \n");
      getchar();
      getchar();
      printf("\n");
   }

    return 0;
}

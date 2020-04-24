/*
number of states, alphabets, final states: 6 2 3
transition table:
        0       1
0       3       1
1       2       5
2       2       5
3       0       4
4       2       5
5       5       5
final states:1 2 4
MINIMIZED DFA:
        0       1
0       0       2
1       1       0
2       2       2
*/

#include <stdio.h>
#include <stdlib.h>

int ns,na,nf,nfm,np,td[10][10],tdm[10][10],p[10][10],fs[10],fsm[10];


int findRowInPartition(int state)
{   int r;
    for(r=0;r<np;r++)
            if(p[r][state]==1)
                return r;
    return -1;
}
void createNewpartition(int s, int st,int a)
{   for(s=0;s<ns;s++)
        p[np][s]=0;
    p[np][st]=1;
    p[findRowInPartition(td[st][a])][st]=0;
    np++;
}

void inputDFA()
{   int s,a,f;
    printf("Enter the number of states:");
    scanf("%d",&ns);
    printf("Enter the number of input symbols:");
    scanf("%d",&na);	
    printf("Enter the number of final states:");
    scanf("%d",&nf);
    printf("Transition Function:\n");
   
    for(s=0;s<ns;s++)
    {  
        for(a=0;a<na;a++)
        {   
	printf("\nf(%d,%d) : ",s,a);
	scanf("%d",&td[s][a]);
        }
	
    }
    printf("\n");


    
    np=2;
    for(s=0;s<ns;s++)
        p[0][s]=0;
    int temp,fsindex=0;
    printf("Enter the final states:");
    for(f=0;f<nf;f++)
    {   scanf("%d",&temp);
        p[0][temp]=1;
        fs[fsindex++]=temp;
    }
    for(s=0;s<ns;s++)
    {   if(p[0][s]==0)  p[1][s]=1;
        else    p[1][s]=0;
    }
}

void printMinimizedDFA()
{   int s,a,r,i;
    printf("Minimized DFA:\n");
    for(a=0;a<na;a++)
        printf("\t%d",a);
    for(s=0;s<np;s++)
    {   printf("\n%d\t",s);
        for(a=0;a<na;a++)
        {   printf("%d\t",tdm[s][a]);
        }
    }
    printf("\n");
    printf("Initial state:");
    for(r=0;r<np;r++)
        if(p[r][0]==1)
            printf("%d\n",r);
    
    nfm=0;
    for(r=0;r<np;r++)
    {   int foundfinal=0;
        printf("New State %d is the representative of the Old States ",r);
        for(s=0;s<ns;s++)
            if(p[r][s]==1)
            {   printf("%d ",s);
     
                for(i=0;i<nf && foundfinal==0;i++)
                {   if(fs[i]==s)
                    {   fsm[nfm++]=r;foundfinal=1;
                    }
                }
            }
        printf("\n");
    }
    printf("Final states:");
    for(i=0;i<nfm;i++)
        printf("%d ",fsm[i]);
    printf("\n");
}

void minimizeDFA()
{   int r,s,st,a;
    int distinguish=0;
    for(r=0;r<np;r++)
    {   for(s=0;s<ns;s++)
        {   if(p[r][s]==1)
            {   for(st=s+1;st<ns;st++)
                {   if(p[r][st]==1)
                    {   distinguish=0;
                        for(a=0;a<na;a++)
                        {   if(findRowInPartition(td[s][a])!=findRowInPartition(td[st][a]))
                            {   distinguish=1;
                                createNewpartition(s,st,a);
                                break;
                            }
                        }
                        if(distinguish==1)  break;
                    }
                    if(distinguish==1)  break;
                }
            }
            if(distinguish==1)break;
        }
        if(distinguish==1){distinguish=0;r=0;}
    }
    
    for(s=0;s<np;s++)
    {   for(a=0;a<na;a++)
        {   
            for(st=0;st<ns;st++)
            {   if(p[s][st]==1)
                    break;
            }
            tdm[s][a]=findRowInPartition(td[st][a]);
        }
    }
}
int main()
{
    inputDFA();
    minimizeDFA();
    printMinimizedDFA();
    return 0;
}

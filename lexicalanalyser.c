#include<stdio.h>
#include<ctype.h>
#include<string.h>
int i=0;
char keys[32][10]={"auto","break","case","char","const","continue","default","do","double","else","enum","extern","float","for","goto","if",
"int","long","register","return","short","signed","sizeof","static","struct","switch","typedef","union","unsigned","void","volatile","while"};
char seps[15]=" \t\n,;(){}[]#\"<>",oper[]="!%^&*-+=~|.<>/?";
void keywd(char *p)
{	int k,flag=0;
     for(k=0;k<=31;k++)
	{	if(strcmp(keys[k],p)==0)
		{	printf("%s is a keywdord\n",p);
               flag=1;
               break;
          }
     }
     if(flag==0)
	{	if(isdigit(p[0]))
		 	printf("%s is a constant\n",p);
          else
		 	if(p[0]!='\0')
				printf("%s is an identifier\n",p);
	}
     i=-1;
}
int main()
{	char ch,str[25];
	int j;
	char fname[50];
	FILE *f;
	printf("enter file path \n");
	scanf("%s",fname);
	f=fopen(fname,"r");
	if(f==NULL)
     {	printf("file not found");
		return 1;
     }
     while((ch=fgetc(f))!=EOF)
	{	for(j=0;j<=14;j++)
		{	if(ch==oper[j])
			{	printf("%c is an operator\n",ch);
                    str[i]='\0';
                    keywd(str);
                }
          }
          for(j=0;j<=14;j++)
		{	if(i==-1)
                	break;
               if(ch==seps[j])
			{	if(ch=='#')
				{	while(ch!='>')
					{
                            printf("%c",ch);
                            ch=fgetc(f);
                         }
                         printf("%c is a header file\n",ch);
                         i=-1;
                         break;
                    }
                    if(ch=='"')
				{	do
					{	ch=fgetc(f);
                         	printf("%c",ch);
                         }while(ch!='"');
                         printf("%c is a literal\n",ch);
                         i=-1;
                         break;
                    }
                    str[i]='\0';
                    keywd(str);
			}
		}
          if(i!=-1)
		{	str[i]=ch;
               i++;
          }
          else
          	i=0;
	}
}
        


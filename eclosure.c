#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>

typedef struct{
	int i,f;
	char inp;
}triplet;

void ddfs(int a,triplet *triplets, int *visited,int n,int n2){
	printf("%d ",a);
	visited[a]=1;
	for(int i=0;i<n;i++){
		if(triplets[i].i==a && triplets[i].inp=='e'){
			if(visited[triplets[i].f]==0){
				ddfs(triplets[i].f,triplets,visited,n,n2);
			}
		}
	}
}

int isIn(int a,int arr[100],int n){
	for(int i=0;i<n;i++){
		if(arr[i]==a){
			return 1;
		}
	}
	return 0;
}
void main(){
	triplet a[100];
	int temp,i=0,j,n2,n,stlist[100],visited[100];
	printf("Enter transition function elements(use 'e' for epsilon, to finish press -1)\n\n");
	do{
		printf("Initial state:: ");
		scanf("%d",&temp);
		if(temp!=-1)
			a[i].i=temp;
		else
			break;
		printf("Input: ");
		scanf("\n%c",&(a[i].inp));
		printf("Transitioned state: ");
		scanf("%d",&(a[i].f));
		i++;
	}while(1);
	n=i;
	for(i=0;i<n;i++){
		printf("F(%d,%c) = %d\n",a[i].i,a[i].inp,a[i].f);
	}
	j=0;
	for(i=0;i<n;i++){
		if(!isIn(a[i].i,stlist,j)){
			stlist[j]=a[i].i;
			j+=1;
		}
		if(!isIn(a[i].f,stlist,j)){
			stlist[j]=a[i].f;
			j+=1;
		}
	}
	n2=j;
	for(i=0;i<n2;i++){
		for(j=0;j<n2;j++){
			visited[stlist[j]]=0;
		}
		printf("%d: ",stlist[i]);
		ddfs(stlist[i],a,visited,n,n2);
		printf("\n");
	}
}

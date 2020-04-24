#include<stdio.h>
#include<stdlib.h>
typedef struct{
	int q[10];
}trans_tab;

int check(int *a,int b){	//checking if element b is in array a
	for(int i=0;a[i]!=-1;i++){
		if(b==a[i]){
			return 1;
		}
	}
	return 0;
}


void copy(int *a,int *b){ //copying array b to array a
	int i=0;
	a[0]=-1;
	for(i=0;b[i]!=-1;i++){
		a[i]=b[i];
	}
	a[i]=-1;
}


int checkUnique(trans_tab *a,trans_tab *b[],int n){
	int i,j,*temp,f=0,l;
	if(a->q[0]==1 && a->q[1]==-1){
		return 0;
	}	
	for(i=0;i<n;i++){		
		temp=b[i]->q;
		f=0;
		if(a->q[0]==-1 && temp[0]==-1){
			return 0;
		}		
		for(j=0;a->q[j]!=-1;j++){
			if(check(temp,a->q[j])){
				continue;
			}
			f=1;
			break;
		}
		if(f==0){
			for(l=0;temp[l]!=-1;l++);
			if(l==j){
				return 0;
			}
			
		}
	}
	return 1;
}



void unionof(int *a,int b){
	int i;
	for(i=0;a[i]!=-1;i++){
		if(a[i]==b){
			return;
		}
	}
	a[i]=b;
	a[i+1]=-1;
	
}



void main(){
	int i,j,temp,n,s,k,rsize;
	int strt=0,end=0,count=0,n_indx;
	trans_tab nfa[20][10],dfa_states[20],dfa[20][10],*sttemp,*ttemp[100];
	char sym[10];
	
	printf("Enter the number of states in NFA:");
	scanf("%d",&n);
	printf("Enter number of input symbols:");
	scanf("%d",&s);
	printf("Enter the symbols:\n");
	for(i=0;i<s;i++){
		scanf("\n%c",&sym[i]);
	}
	printf("Enter -1 to indicate no transition\n");
	for(i=0;i<n;i++){
		for(j=0;j<s;j++){
			printf("Enter transited states for f(%d,%c)\n",i+1,sym[j]);
			
			k=0;
			while(1){
				scanf("\n%d",&temp);
				if(temp==-1){
					nfa[i][j].q[k]=-1;
					break;
				}
				nfa[i][j].q[k]=temp;
				k++;				
			}
		}
	}
	

	dfa_states[0].q[0]=1;
	dfa_states[0].q[1]=-1;
	for(i=0;i<s;i++){
		copy(dfa[0][i].q,nfa[0][i].q);
		if(checkUnique(&(dfa[0][i]),ttemp,end)){
			ttemp[end]=&(dfa[0][i]);
			end++;
		}
	}
	count=1;
	while(strt<end){
		sttemp=ttemp[strt];
		strt++;
		copy(dfa_states[count].q,sttemp->q);		
		for(i=0;i<s;i++){
			dfa[count][i].q[0]=-1;
			for(j=0;sttemp->q[j]!=-1;j++){
				n_indx=sttemp->q[j]-1;								
				for(k=0;nfa[n_indx][i].q[k]!=-1;k++){					
					unionof(dfa[count][i].q,nfa[n_indx][i].q[k]);
				}				
				
			}
			if(checkUnique((&dfa[count][i]),ttemp,end)){
				ttemp[end]=&(dfa[count][i]);
				end++;
			}			

		}
		count++;		
	}
	printf("\n\n");
	printf("Equivalent DFA:\n");
	for(j=0;j<s;j++){
			
			
			printf("\t%c ",sym[j]);
	}
	printf("\n");
	for(i=0;i<count;i++){	
		for(k=0;dfa_states[i].q[k]!=-1;k++){
				printf("%d",dfa_states[i].q[k]);			
			}
			printf("\t");
			if(dfa_states[i].q[0]==-1){
				printf("phi");
			}			

		for(j=0;j<s;j++){
			
			
			//printf("%c: ",sym[j]);
			if(dfa[i][j].q[0]==-1){
				printf("phi");
				continue;
			}
			
			for(k=0;dfa[i][j].q[k]!=-1;k++){
				printf("%d",dfa[i][j].q[k]);
			}
			printf("\t");
			
		}
		printf("\n\n");		
	}	
	
}

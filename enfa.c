#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

typedef struct{
	int init, final;
	char input;
}enfa;

typedef struct{
	int init, final[10], fin_count;
	char input;
}nfa;

void main(){
	enfa arr[100]; 
	nfa a[100];
	int count = 0, new_count = 0, fin, temp, i = 0, index, j, q, k, m, f, l, z, initial, inp, duplicate, found, final_count = 0, final_[20];
	printf("Enter the number of states:");
	scanf("%d",&q);
	printf("\nEnter the number of inputs(excluding epsilon):");
	scanf("%d",&inp);
	char input[inp];
	for(j = 0; j < inp; j++){
		printf("Enter the input - %d:",j+1);
		scanf("\n%c",&input[j]);
	}
	int closure[q][q];
	for(j=0; j<q; j++){
		for(k=0; k<q; k++){
			closure[j][k] = -1;
		}
	}
	printf("\nEnter the transition table of NFA(Enter e for epsilon and Enter -1 as Initial state to end):");
	do{
		printf("\nInitial state:");
		scanf("%d",&temp);
		if(temp == -1){
			break;
		}
		arr[i].init = temp;
		printf("Input:");
		scanf("\n%c",&(arr[i].input));
		printf("Final state:");
		scanf("%d",&(arr[i].final));
		i++;
		count++;
	}while(1);

	printf("\nEnter the index number of final states(Enter -1 to end):");
	i = 0;
	do{
		scanf("%d",&temp);
		if(temp == -1){
			break;
		}
		final_[i] = temp;
		i++;
		final_count++;
	}while(1);

	for(i=0; i<q; i++){
		index = 0;
		initial = i;
		closure[i][index++] = i;
		for(j=0; j<count; j++){
			if(arr[j].init == initial){
				if(arr[j].input == 'e'){
					duplicate = 0;
					for(k=0; k<index; k++){
						if(closure[i][k] == arr[j].final){
							duplicate = 1;
						}
					}
					if(!duplicate){
						closure[i][index++] = arr[j].final;
						j = -1;
					}
				}
			}
		}		
	}
	for(i=0; i<q; i++){
		index = 0;
		initial = i;
		closure[i][index++] = i;
		for(j=0; j<count; j++){
			if(arr[j].init == initial){
				if(arr[j].input == 'e'){
					duplicate = 0;
					for(k=0; k<index; k++){
						if(closure[i][k] == arr[j].final){
							duplicate = 1;
						}
					}
					if(!duplicate){
						closure[i][index++] = arr[j].final;
						initial = arr[j].final;
						j = -1;
					}
				}
			}
		}		
	} 
	for(i=0; i<q; i++){
		for(j=0; j<inp; j++){
			found = 0;
			a[new_count].init = i;
			a[new_count].input = input[j];
			fin = a[new_count].fin_count;
			for(l=0; l<q; l++){
				if(closure[i][l] != -1){
					for(m=0; m<count; m++){
						if(arr[m].init == closure[i][l] && arr[m].input == input[j]){
							duplicate = 0;
							found = 1;
							for(z=0; z<q; z++){
								if(closure[arr[m].final][z] != -1){
									for(f=0; f<fin; f++){
										if(a[new_count].final[f] == closure[arr[m].final][z]){
											duplicate = 1;
										}
									}
									if(!duplicate){
										a[new_count].final[fin++] = closure[arr[m].final][z];
									}
								}	
							}
						}
					}
				}
			}
			a[new_count].fin_count = fin;
			new_count++;
			if(found == 0){
				a[new_count].fin_count = 0;
			}
		}
	}

	for(i=0; i<q; i++){
		printf("\ne-closure(%d)={ ",i);
		for(j=0; j<q; j++){
			if(closure[i][j] != -1){
				printf("%d ",closure[i][j]);
			}
		}
		printf("}");
	}	

	printf("\n\nNFA\n");
	for(i=0; i<new_count; i++){
		printf("\nF([ ");
		printf("%d ",a[i].init);
		printf("],%c)= ",a[i].input);
		//fin = 0;
		if(a[i].fin_count != 0){
			printf("{ ");
			for(l=0; l<a[i].fin_count; l++){
				for(j=0; j<final_count; j++){
					if(a[i].final[l] == final_[j]){
						fin = 1;
					}
				}
				printf("%d ",a[i].final[l]);
			}
			printf("}");
		}
		else{
			printf("DEAD STATE");
		}	
	}
		
}

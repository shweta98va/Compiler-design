#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

typedef struct{
	char sym, result[15], first_sym[15];
	int rcount, scount;
}first,follow;

first arr[15];
follow a[15];
char prod[15][15], term[15], non_term[15], start_sym;
int count, tcount = 0, ncount = 0;

int is_duplicate(char arr[], int count, char item){
	if(item != ' '){
		for(int i=0; i<count; i++){
			if(arr[i] == item){
				return 1;
			}
		}
	}
	return 0;	
}

int is_terminal(char item){
	for(int i=0; i<tcount; i++){
		if(term[i] == item){
			return 1;
		}
	}
	return 0;
}

int is_nonterminal(char item){
	for(int i=0; i<ncount; i++){
		if(non_term[i] == item){
			return 1;
		}
	}
	return 0;
}

void first_symb(char sym, int index){
	for(int i=0; i<count; i++){
		if(prod[i][0] == sym){
			arr[index].first_sym[arr[index].scount++] = prod[i][2];
		}
	}
}
 

int ret_index(char symb){
	for(int i=0; i<15; i++){
		if(arr[i].sym == symb){
			return i;
		}
	}
}

void create_set(){
	int i, j;
	for(i=0; i<count; i++){
		for(j=0; j<15; j++){
			if(prod[i][j] != '\0' && prod[i][j] != '='){
				if(isupper(prod[i][j])){
					if(!is_duplicate(non_term,ncount,prod[i][j]) && prod[i][j] != '#'){
						non_term[ncount] = prod[i][j];
						first_symb(prod[i][j],ncount++);
					}
				}
				else{
					//printf("\n%d %d %c",i,j,prod[i][j]);
					if(!is_duplicate(term,tcount,prod[i][j]) && prod[i][j] != '#'){
						term[tcount++] = prod[i][j];
					}
				}
			}
		}
	}
	/*printf("\n%d %d\n",tcount,ncount);
	for(i=0; i<tcount; i++){
		printf("%c ",term[i]);
	}
	printf("\n");
	for(i=0; i<ncount; i++){
		printf("%c ",non_term[i]);
	}*/
}

void find_first(){
	int i, j, k , l, m, n, y, z, index, prev_eps, eps_count;
	char item1, item2;
	for(i=0; i<ncount; i++){
		arr[i].sym = non_term[i];
		for(j=0; j<count; j++){
			item1 = prod[j][0];
			item2 = non_term[i];
			if(item1 == item2){
				if(prod[j][2] == '#'){
					if(!is_duplicate(arr[i].result,arr[i].rcount,'#')){
						arr[i].result[arr[i].rcount++] = '#';
					}
				}
				if(is_terminal(prod[j][2])){
					if(!is_duplicate(arr[i].result,arr[i].rcount,prod[j][2])){
						arr[i].result[arr[i].rcount++] = prod[j][2];
					}
				}
			}
		}	
	}

	for(i=0; i<ncount; i++){
		for(j=0; j<count; j++){
			eps_count = 0;
			for(k=2; prod[j][k] != '\0'; k++){
				if(k == 2){
					prev_eps = 1;
				}
				
				if(prev_eps && prod[j][k] != '\0' && arr[i].sym == prod[j][0]){
					if(is_nonterminal(prod[j][k])){
						item1 = prod[j][k];
						for(z=0; z<ncount; z++){
							if(arr[z].sym == item1){
								prev_eps = 0;
								if(arr[z].rcount == 0){
									for(m=0; m<count; m++){
										if(prod[m][0] == item1){
											if(is_nonterminal(prod[m][2])){
												item1 = prod[m][2];
												z = 0;
											}
										}
									}
								}
								else{
									for(y=0; y<arr[z].rcount; y++){
										if(!is_duplicate(arr[i].result,arr[i].rcount,arr[z].result[y]) && arr[z].result[y] != '#'){
											//printf("\n	%c	%c",arr[i].sym,arr[z].result[y]);
											arr[i].result[arr[i].rcount++] = arr[z].result[y];
										}
										if(arr[z].result[y] == '#'){
											prev_eps = 1;
											eps_count++;
										}
										
									}
								}
							}
						}
					}
					if(is_terminal(prod[j][k])){
						prev_eps = 0;
						if(!is_duplicate(arr[i].result,arr[i].rcount,prod[j][k]) && arr[z].result[y] != '#'){
							arr[i].result[arr[i].rcount++] = prod[j][k];
						}
					}
				}
			}
			if(eps_count == k-2){
				if(!is_duplicate(arr[i].result,arr[i].rcount,'#')){
					arr[i].result[arr[i].rcount++] = '#';
				}
			}
		}
	}
	
	for(i=0; i<ncount; i++){
		for(j=0; j<ncount; j++){
			eps_count = 0;
			for(k=2; prod[j][k] != '\0'; k++){
				if(prod[j][k] != '\0' && arr[i].sym == prod[j][0]){
					if(is_nonterminal(prod[j][k])){
						for(z=0; z<ncount; z++){
							if(arr[z].sym == prod[j][k]){
								for(y=0; y<arr[z].rcount; y++){
									if(arr[z].result[y] == '#'){
										eps_count++;
									}
									
								}
							}
						}
					}
				}
			}
			if(eps_count == k-2){
				if(!is_duplicate(arr[i].result,arr[i].rcount,'#')){
					arr[i].result[arr[i].rcount++] = '#';
				}
			}
		}
	}

	for(i=0; i<ncount; i++){
		printf("\nFirst(%c) = { ",arr[i].sym);
		for(j=0; j<arr[i].rcount; j++){
			printf("%c ",arr[i].result[j]);
		}
		printf("}");
	}	
}

void find_follow(){
	int i, j, k, l, m, n, prev_eps, next_eps, found;
	char item;
	for(i=0; i<ncount; i++){
		a[i].sym = non_term[i];
		if(non_term[i] == start_sym){
			a[i].result[a[i].rcount++] = '$';
		}
	}

	for(i=0; i<ncount; i++){
		prev_eps = 1;
		for(j=0; j<count; j++){
			item = a[i].sym;;
			for(k=2; prod[j][k]!='\0'; k++){
				if(prod[j][k] == item){
					if(is_nonterminal(prod[j][k]) && is_nonterminal(prod[j][k+1]) && prev_eps){
						for(l=0; l<ncount; l++){
							if(arr[l].sym == prod[j][k+1]){
								prev_eps = 0;
								for(m=0; m<arr[l].rcount; m++){
									if(!is_duplicate(a[i].result,a[i].rcount,arr[l].result[m]) && arr[l].result[m] != '#'){
										a[i].result[a[i].rcount++] = arr[l].result[m];
									}
									if(arr[l].result[m] == '!'){
										prev_eps = 1;
									}
								}
								item = prod[j][k+1];
							}						
						}
					}
					if(prev_eps && is_terminal(prod[j][k+1])){
						prev_eps = 0;
						if(!is_duplicate(a[i].result,a[i].rcount,prod[j][k+1])){
							a[i].result[a[i].rcount++] = prod[j][k+1];
						}
					}
				}
			}
		}
	}

	
	for(i=0; i<ncount; i++){
		for(j=0; j<count; j++){
			item = a[i].sym;
			for(k=2; prod[j][k]!='\0'; k++){
				if(prod[j][k] == item){
					if(is_nonterminal(prod[j][k]) && is_terminal(prod[j][k+1])){
						if(!is_duplicate(a[i].result,a[i].rcount,prod[j][k+1])){
							a[i].result[a[i].rcount++] = prod[j][k+1];
						}
					}
				}
			}
		}
	}

	for(i=0; i<ncount; i++){
		for(j=0; j<count; j++){
			item = a[i].sym;
			found = 0;
			for(k=2; prod[j][k]!='\0'; k++){
				next_eps = 0;
				if(prod[j][k] == item){
					found = 1;
					next_eps = 1;
					if(is_nonterminal(prod[j][k]) && (is_nonterminal(prod[j][k+1]) || prod[j][k+1] == '\0') && next_eps){
						next_eps = 0;
						if(prod[j][k+1] == '\0'){
							next_eps = 1;
						}
						else{
							for(l=0; l<ncount; l++){
								if(arr[l].sym == prod[j][k+1]){
									for(m=0; m<arr[l].rcount; m++){
										if(arr[l].result[m] == '#'){
											next_eps = 1;
										}
									}
									item = prod[j][k+1];
								}						
							}
						}
					}
				}
			}

			if(next_eps){
				for(n=0; n<ncount; n++){
					if(a[n].sym == prod[j][0]){
						for(l=0; l<a[n].rcount; l++){
							if(!is_duplicate(a[i].result,a[i].rcount,a[n].result[l])){
								a[i].result[a[i].rcount++] = a[n].result[l];
							}
						}
					}
				}
			}
		}
	}

	printf("\n");
	for(i=0; i<ncount; i++){
		printf("\nFollow(%c) = { ",a[i].sym);
		for(j=0; j<a[i].rcount; j++){
			printf("%c ",a[i].result[j]);
		}
		printf("}");
	}	

}

void main(){
	int i, j;
	printf("\nEnter the start symbol:");
	scanf("%c",&start_sym);
	printf("\nEnter the number of productions:");
	scanf("%d",&count);
	for(i=0; i<15; i++){
		for(j=0; j<15; j++){
			prod[i][j] = '\0';
		}
	}

	printf("\nEnter the productions one by one where = represents the arrow and # represents epsilon");
	for(i=0; i<count; i++){
		printf("\nEnter production-%d:",i+1);
		scanf("%s",prod[i]);
	}
	
	create_set();
	find_first();
	find_follow();
}


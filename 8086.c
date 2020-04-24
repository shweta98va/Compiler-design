#include<stdio.h>
#include<string.h>
char expressions[10][10];
int n_exp;

void input(){
    for(int i=0;i<n_exp;i++){
        scanf("%s",expressions[i]);
    }
}

int check_op(char ch){
    switch(ch){
        
    }
}

void gen_8086(){
    for(int i=0;i<n_exp;i++){
        if(strlen(expressions[i]) == 3){
            printf("MOV AX,[ADDR_%c]\n",expressions[i][2]);
            printf("MOV [ADDR_%c],AX\n",expressions[i][0]);
            break;
        }
        
        printf("MOV AX,[ADDR_%c]\n",expressions[i][2]);

        if( expressions[i][3] == '+'){
                printf("ADD AX,[ADDR_%c]\n",expressions[i][4]);
                }
        else if( expressions[i][3] == '-'){
                printf("SUB AX,[ADDR_%c]\n",expressions[i][4]);
        }
        else if( expressions[i][3] == '*' ){
                printf("MOV BX,[ADDR_%c]\n",expressions[i][4]);
                printf("MUL BX\n");
        }

        else if( expressions[i][3] == '/' ){
                printf("MOV BX,[ADDR_%c]\n",expressions[i][4]);
                printf("DIV BX\n");
        }

        printf("MOV [ADDR_%c],AX\n\n",expressions[i][0]);


    }
}
void main(){
    printf("Enter The Number of Expressions:-\n");
    scanf("%d",&n_exp);

    printf("Enter The 3AC Expressions:-\n");
    input();

    gen_8086();

    printf("\n");




}
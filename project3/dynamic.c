#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define DEBUG 0

int max_weight=0;

void verify(int* input,int number);

int selected[4];

int max_profit=0;

void dynamicProgramming(int no_of_elements,int capacity,int* profits,int* weights,int array[no_of_elements+1][capacity+1]){
    for(int i=0;i<=capacity;++i){
        array[0][i]=0;
    }
    for(int k=1;k<=no_of_elements;++k){
        array[k][0]=0;
        for(int j=1;j<=capacity;++j){
            if((weights[k]<=j) && (array[k-1][j-weights[k]]+profits[k])>array[k-1][j]){
                array[k][j]=array[k-1][j-weights[k]]+profits[k];
                selected[k]=1;
            }
            else{
                array[k][j]=array[k-1][j];
            }
        }
    }
    int max_profit=array[no_of_elements][capacity];
    printf("Maximum Profit: %d\n", max_profit);
    printf("Selected items: ");
    int i=no_of_elements;
    while(i>0 && max_profit>0){
        if(max_profit==array[i-1][capacity]){
            --i;
            continue;
        }
        else{
            printf("%d ",i-1);
            max_weight=max_weight+weights[i];
            max_profit=max_profit-profits[i];
            capacity=capacity-weights[i];
        }
        --i;
    }
    printf("\nTotal Weight: %d\n", max_weight);
}

void nullOut2DArray(int no_of_elements,int capacity,int array[no_of_elements+1][capacity+1]){
    for(int i=0;i<=no_of_elements;++i){
        for(int j=0;j<=capacity;++j){
            array[i][j]=0;
        }
    }
}

void nullOutArray(int* array,int capacity){
    for(int i=0;i<=capacity;++i){
        array[i]=0;
    }
}

void fillOutArray(int i,int profit,int* array,int capacity){
    for(i;i<=capacity;++i){
        array[i]=profit;
    }
}

void flushOut(char* temp){
    for(int i=0;temp[i]!='\0';++i){
        temp[i]=0;
    }
}

void verify(int* input,int number){
    for(int i=0;i<number+1;++i){
        printf("%d  ",input[i]);
    }
}

int main(int argc,char* argv[]){
    int no_of_elements=0;
    int capacity=0;
    int profits[50];
    int weights[50];
    FILE* file;
    char buffer[255];
    int line_number=0;
    int i=0,j=0,k=0;
    char temp[255]={};
    
    if(argc!=2){ // There should be one argument as input file
        fprintf(stderr, "Usge: ./bruteForce.out <input file name>\n");
        exit(0);
    }

    file=fopen(argv[1],"r");
    while(1){
        fgets(buffer,256,file);
        if(feof(file)!=0) break;
        if(line_number==0){
            if(DEBUG==1) printf("%s\n",buffer);
            no_of_elements=atoi(buffer);
            *buffer='\0';
        }
        if(line_number==1){  
            if(DEBUG==1) printf("%s\n", buffer);
            capacity=atoi(buffer);
            *buffer='\0';
        }
        if(line_number==2){
            if(DEBUG==1) printf("%s\n", buffer);
            for(i=0;i<strlen(buffer)+1;++i){
                if(buffer[i]==',' || buffer[i]=='\0'){
                    if(DEBUG==1) printf("%s",temp);
                    if(DEBUG==1) printf("\n");  
                    profits[j+1]=atoi(temp);
                    ++i;
                    ++j;
                    k=0;
                    flushOut(temp);
                    continue;
                }
                if(DEBUG==1) printf("%c",buffer[i]);
                if(buffer[i]!='\n') temp[k]=buffer[i];
                ++k;
            }
        }
        if(line_number==3){
            if(DEBUG==1) printf("%s\n", buffer);
            j=0,k=0;
            for(i=0;i<strlen(buffer)+1;++i){
                if(buffer[i]==',' || buffer[i]=='\0'){
                    weights[j+1]=atoi(temp);
                    ++i;
                    ++j;
                    k=0;
                    flushOut(temp);
                    continue;
                }
                if(buffer[i]!='\n') temp[k]=buffer[i];
                ++k;
            }
        }
        ++line_number;
    }

    if(DEBUG==1) verify(profits,no_of_elements);
    if(DEBUG==1) verify(weights,no_of_elements);
    if(DEBUG==1) printf("Capacity: %d, Elements: %d\n",capacity,no_of_elements);

    int array[no_of_elements+1][capacity+1];
    nullOut2DArray(no_of_elements,capacity,array);
    dynamicProgramming(no_of_elements,capacity,profits,weights,array);
    return 0;
}


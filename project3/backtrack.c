#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define DEBUG 0

int no_of_elements=0;
int capacity=0;
int max_profit=0;
int max_weight=0;
int optimal_profit=0;
int optimal_weight=0;
int selected_weights[50];
int max_profit_possible=0;
int items_selected=0;

typedef struct element{
    int weight;
    int profit;
    float profit_per_weight;
}element;

struct element elements[50];

struct element copy_of_elements[50];

void inputProfitPerWeight(){
    for(int i=0;i<no_of_elements;++i){
        elements[i].profit_per_weight=(elements[i].profit)/(elements[i].weight);
    }
}

void sortWeights(){
    for(int i=0;i<no_of_elements;++i){
        for(int j=0;j<no_of_elements;++j){
            if(elements[i].profit_per_weight<elements[j].profit_per_weight){
                struct element temp=elements[i];
                elements[i]=elements[j];
                elements[j]=temp;
            }
        }
    }
}

void computeWeightAndProfit(int* arr,int no_of_elements){
    max_profit=0;
    max_weight=0;
    max_profit_possible=0;

    for(int i=0;i<no_of_elements;++i){
        if((max_weight+(elements[i].weight)*arr[i])<=capacity){
            max_weight=max_weight+(elements[i].weight)*arr[i];
        }
        else{
            return;
        }
        max_profit=max_profit+(elements[i].profit)*arr[i];
        if(optimal_profit<max_profit){
            optimal_profit=max_profit;  
            optimal_weight=max_weight;
        }
    }
    int j=0;
    if(optimal_profit==max_profit){
        items_selected=0;
        for(int j=0;j<no_of_elements;++j){
            selected_weights[j]=0;
        } 
        for(int i=0;i<no_of_elements;++i){
            if(arr[i]==0) continue;
            selected_weights[j]=i;
            ++j;
            ++items_selected;
          //  printf(" %d",i);
        }
    }
  
   // printf("\n");

    /*
    for(int i=0;i<no_of_elements;++i){
        printf(" %d", arr[i]);
    }

    printf("\n");
    printf("Profit= %d\n", max_profit);
    printf("weight= %d\n", max_weight);
    printf("\n");
    */
}

void recursionTree(int* arr,int i){
    if(i==no_of_elements){
        computeWeightAndProfit(arr,no_of_elements);
        return;
    }

    arr[i]=0;
    recursionTree(arr,i+1);
    arr[i]=1;
    recursionTree(arr,i+1);
}

void inputNullValues(int* input,int no_of_elements){
    for(int i=0;i<no_of_elements;++i){
        input[i]=0;
    }
}

void flushOut(char* temp){
    for(int i=0;temp[i]!='\0';++i){
        temp[i]=0;
    }
}

void verify(int* array,int no_of_elements){
    for(int i=0;i<no_of_elements;++i){
        printf("%d ",array[i]);
    }
    printf("\n");
}

int main(int argc,char* argv[]){
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
                    elements[j].profit=atoi(temp);
                    copy_of_elements[j].profit=atoi(temp);
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
                    elements[j].weight=atoi(temp);
                    copy_of_elements[j].weight=atoi(temp);
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
    
    inputProfitPerWeight();
    sortWeights();
    
    int arr[no_of_elements];
    inputNullValues(arr,no_of_elements);
    recursionTree(arr,0);

    printf("Maximum Profit=%d\n", optimal_profit);
    printf("Maximum Weight=%d\n", optimal_weight);
    printf("Items Selected:");
    for(int i=0;i<items_selected;++i){
        for(int j=0;j<no_of_elements;++j){
            if(elements[selected_weights[i]].weight==copy_of_elements[j].weight)
                printf(" %d",j);
        }
       // printf(" %d",elements[selected_weights[i]].weight);
    }
    printf("\n");
    return 0;
}

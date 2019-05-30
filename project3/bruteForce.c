#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define DEBUG 0

int weight=0;
int profit=0;
int j=0;
int max_profit=0;
int max_weight=0;
int max_bits=0;
        
void bruteForce(int no_of_elements,int capacity,int* profits,int* weights,int* bits){
    for(int i=0;i<no_of_elements;++i){
        profit=profit+profits[i]*bits[i];
        weight=weight+weights[i]*bits[i];
        if(weight<=capacity && profit>max_profit){
            max_profit=profit;
            max_weight=weight;
            max_bits=j;
        }
        if(DEBUG==1) printf("%d\t%d\t%d\t%d\n", weights[i],bits[i],profit,weight);
    }
    ++j;
    profit=0;
    weight=0;
}


void clearBits(int* bits,int no_of_elements){
    for(int i=0;i<no_of_elements;++i){
        bits[i]=0;
    }
}


void shiftToArray(int* bits,int binary,int no_of_elements){
    for(int i=0;i<no_of_elements;++i){
        if(binary==0) break;
        bits[i]=binary%10;
        binary=binary/10;

    }
}

int convert(int decimal){
    if(decimal==0) return 0;
    else return (decimal%2+10*convert(decimal/2));
}

void flushOut(char* temp){
    
    for(int i=0;temp[i]!='\0';++i){
        temp[i]=0;
    }

}

void verify(int* input,int number){
    
    for(int i=0;i<number;++i){
        printf("%d\t",input[i]);
    }
    printf("\n");
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
    int decimal,binary;
    
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
                    profits[j]=atoi(temp);
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
                    weights[j]=atoi(temp);
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
    int bits[no_of_elements];
    clearBits(bits,no_of_elements);
    for(int i=0;i<8;++i){
        binary=convert(i);
        shiftToArray(bits,binary,no_of_elements);
        bruteForce(no_of_elements,capacity,profits,weights,bits);
    }
    printf("Total Profit= %d and Total Weight=%d\n", max_profit,max_weight);
    clearBits(bits,no_of_elements);
    binary=convert(max_bits);
    shiftToArray(bits,binary,no_of_elements);
    printf("Selected items:");
    for(int i=0;i<no_of_elements;++i){
        if(bits[i]==0) continue;
        printf(" %d",i);
    }
    printf("\n");
    return 0;
}

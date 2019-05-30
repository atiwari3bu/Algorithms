#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define DEBUG 0

void printVariableValues();
void printVariable();

int root=0;

char* stringreverse(char *string)
{
    int i = 0; 
    int j = strlen(string)-1;
    char character;
    for(i,j;i<j;++i,--j){    
        character = string[i];
        string[i] = string[j];
        string[j] = character;
      }
    return string;
}

typedef struct variable{
    int value;
    char variable;
    char huff_code[10];
    int flag;
    int l_child;
    int r_child;
    int is_leaf;
    int parent;
}variable;

struct variable variables[40];

void recursion(){
    int temp1=10000;
    int temp2=10000;
    int min1=0;
    int min2=0;

    for(int i=0;variables[i].value!=0;++i){
        if(variables[i].flag==1) continue;
        if(temp1>variables[i].value){
            temp1=variables[i].value;
            min1=i;
        }
    }
    for(int j=0;variables[j].value!=0;++j){
        if(j==min1 || variables[j].flag==1) continue;
        if(temp2>variables[j].value){
            temp2=variables[j].value;
            min2=j;
        }
    }

    if(temp2==10000){
        variables[min1].flag=1;
        root=min1;
        return;
    }
    variables[min1].flag=1;
    variables[min2].flag=1;

    int k=0;
    for(;variables[k].value!=0;++k){
    }
    variables[k].value=temp1+temp2;
    variables[k].flag=0;
    variables[k].l_child=min1;
    variables[k].r_child=min2;
    variables[min1].parent=k;
    variables[min2].parent=k;
    variables[k].is_leaf=0;
    //printf("%d\t%d\n",temp1,temp2);
    recursion();
}

void implementHuffCode(){
    recursion(); 
   // printVariableValues();
  //  printf(" Root = %d\n",root);

    for(int i=0;variables[i].value!=0;++i){
        if(variables[i].is_leaf == 1){
            printf(" %c(%d):",variables[i].variable,variables[i].value);
            int parent=-1;
            int curr=i;
            int k=0;
            char str[10];
            while(root !=parent ){
                parent=variables[curr].parent;
                if(variables[parent].l_child==curr){
                    str[k]='0';
                    ++k;
            //        printf("0");
                }
                else{
                    str[k]='1';
                    ++k;
              //      printf("1"); 
                }
                curr=parent;
            }
          //  printf("%s", str);
            char* str_rev=stringreverse(str);
            printf("%s",str_rev);
            printf("\n");
        }
    }
}


void printVariable(){
    for(int i=0;variables[i].variable!='\0';++i){
        printf("%c",variables[i].variable);
    }
    printf("\n");
}

void flushOut(char* temp){   //Flushes out entire array for new entry
    for(int i=0;temp[i]!='\0';++i){
        temp[i]=0;
    }
}

void printVariableValues(){    // Used to print global value[21];
    for(int i=0;i<21;++i){
        if(variables[i].value==0) break;
        printf("%d\t%d\t%d\n",variables[i].value,variables[i].l_child,variables[i].r_child);
    }
    printf("\n");
}

void storeIntoVariable(char* buffer){// Reads from file and store into global value[21];
    char temp[255]={};
    int i=2,j=0,k=0;
    int length=strlen(buffer);
    
    for(int i=0;i<length+1;++i){    
        if(buffer[i]==',' || buffer[i]=='\0'){
            if(DEBUG==1)    printf("%s",temp);
            if(DEBUG==1)    printf("\n");    
            variables[j].value=atoi(temp);
            variables[j].flag=0;
            variables[j].l_child=-1;
            variables[j].r_child=-1;
            variables[j].is_leaf=1;
            variables[j].parent=-1;
            ++j;
            k=0;
            flushOut(temp);
            continue;
        }
        
        if(DEBUG==1) printf("%c",buffer[i]);
        if(buffer[i]!='\n') temp[k]=buffer[i];
        ++k;
    }
    
    if (DEBUG==1)   printVariableValues();
}

void storeVariables(char* buffer){

    int i,j=0;
    
    if (DEBUG==1) printf("%s\n",buffer);
    for(i=0;buffer[i]!='\0';++i){
        if(DEBUG==1) printf("%c\n",buffer[i]);
        if(buffer[i]==',' || buffer[i]=='\n'){
            continue;
        }
        
        if(buffer[i]=='t') break;
        if(DEBUG==1)    printf("%c\n",buffer[i]);
        variables[j].variable=buffer[i];
        ++j;
    }
    
    if(DEBUG==1)    printVariable();
}

void readFile(char* filename){  // Read files line by line
    
    FILE* file;
    int line_number=0;
    char buffer[255];
    file=fopen(filename,"r");
    
    while(1){  // Ignores the first line and reads second line
        fgets(buffer,256,file);
        if(feof(file)!=0) break;
        if(line_number==0){
            storeVariables(buffer);
            ++line_number;
            continue;
        }
    }
    fclose(file);
    
    storeIntoVariable(buffer);// Store into value[21];
}

int main(int argc,char* argv[]){
    
    if(argc!=2){ // There should be only one argument
        fprintf(stderr,"Usage: ./huffman.out <input file name>\n");
        exit(0);
    }

    readFile(argv[1]);// Reads file
    implementHuffCode();
    return 0;
}

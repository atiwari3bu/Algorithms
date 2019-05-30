#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void storeIntoMatrix(char* filename,int row,int column,int matrix[row][column]){
    char buffer[256];
    char* token;
    int r=0,c=0;
    FILE* file=fopen(filename,"r");
    for(;;){
        fgets(buffer,255,file);
        if(feof(file)) break;
        token=strtok(buffer,",");
        while(token!=NULL){
            matrix[r][c]=atoi(token);
            token=strtok(NULL,",");
            ++c;
        }
        ++r;
        c=0;
    }
    fclose(file);
}

void printMatrix(int row,int column,int matrix[row][column]){

    for(int i=0;i<row;++i){
        for(int j=0;j<column;++j){
            printf("%d\t",matrix[i][j]);
        }
        printf("\n");
    }
}
void calculateDistanceMatrix(int row,int column,int matrix[row][column]){
   for(int k=0;k<row;++k){
        for(int i=0;i<row;++i){
            for(int j=0;j<row;++j){
                if(matrix[i][j]>matrix[i][k]+matrix[k][j]){
                    matrix[i][j]=matrix[i][k]+matrix[k][j];
                }
            }
        }
    }
    printf("\n-----Distance Matrix is -----\n\n");
    printMatrix(row,column,matrix);

}


int main(int argc,char* argv[]){

    int row=0,column=0;
    char* token;
    char buffer[256];
    if(argc!=2){
        fprintf(stderr, "\nUsage: ./floyd.out <input file name>\n\n");
        return 0;
    }
    FILE* file=fopen(argv[1],"r");
    for(;;){
        fgets(buffer,255,file);
        if(feof(file)) break;
        token=strtok(buffer,",");
        while(token!=NULL){
            token=strtok(NULL,",");
            ++column;
        }
    ++row;
    }
    fclose(file);
   
    column=column/row;
    int matrix[row][column];
    storeIntoMatrix(argv[1],row,column,matrix);
    printf("\n---Adjacency Matrix is-----\n\n");
    printMatrix(row,column,matrix);
    calculateDistanceMatrix(row,column,matrix);
    return 0;
}

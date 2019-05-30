#include<stdio.h>
#include<stdlib.h>

int tree[100][100];

void createInitialMatrix(int value_of_n,float matrix[value_of_n+2][value_of_n+1]){
    for(int row=1;row<value_of_n+2;++row){
        for(int column=0;column<value_of_n+1;++column){
            matrix[row][column]=0;
        }
    }
}
       
void printMatrix(int value_of_n,float matrix[value_of_n+2][value_of_n+1]){
    for(int row=1;row<value_of_n+2;++row){
        for(int column=0;column<value_of_n+1;++column){
            printf("%.1f\t",matrix[row][column]);
        }
        printf("\n");
    }
}

void printMatrixInt(int value_of_n,int matrix[value_of_n+2][value_of_n+1]){
    for(int row=1;row<value_of_n+2;++row){
        for(int column=0;column<value_of_n+1;++column){
            printf("%.1d\t",matrix[row][column]);
        }
        printf("\n");
    }
}

void createTree(int n,int k_matrix[n+2][n+1],int st,int end,int depth){

    
    if(st > end){
        tree[depth][0] +=1;
        int depthIdx = tree[depth][0];
        tree[depth][depthIdx] =0;
        return;  
    }  

    int root = k_matrix[st][end];
    //printf("Depth: %d Root:%d\n",depth,root);
    tree[depth][0] +=1;
    int depthIdx = tree[depth][0];
    tree[depth][depthIdx] = root;
    createTree(n,k_matrix,st,root-1,depth+1);
    createTree(n,k_matrix,root+1,end,depth+1);
}

void fillValuesInMatrix(int value_of_n,float matrix[value_of_n+2][value_of_n+1],float n_probabilities[value_of_n]){
    int diagonal,i,j,k,l;
    float min=0,probability=0;
    float array[value_of_n+1];
    int k_matrix[value_of_n+2][value_of_n+1];
    
    for(int row=1;row<value_of_n+2;++row){
        for(int column=0;column<value_of_n+1;++column){
            k_matrix[row][column]=0;
        }
    }

    for(int row=1;row<value_of_n+2;++row){
        for(int column=0;column<value_of_n+1;++column){
            if(row==column){
                matrix[row][column]=n_probabilities[row];
                k_matrix[row][column]=row;
            }
        }
    }

    for(diagonal=1;diagonal<=value_of_n-1;++diagonal){
        for(i=1;i<=value_of_n-diagonal;++i){
            j=i+diagonal;
            for(k=i;k<=j;++k){
                probability=probability+n_probabilities[k];
            }
            for(k=i;k<=j;++k){
                min=matrix[i][k-1]+matrix[k+1][j]+probability;
                if(k==i){
                    matrix[i][j]=min;
                    k_matrix[i][j]=k;
                }
                if(min<matrix[i][j]){
                    matrix[i][j]=min;
                    k_matrix[i][j]=k;
                }
                if(j==value_of_n && i==1){
                    array[k]=min;
                }
            }
            probability=0;
            min=0;
        }
    }
    //printTree(value_of_n,array);
    //printMatrixInt(value_of_n,k_matrix);
    createTree(value_of_n,k_matrix,1,value_of_n,0);
    
    /* Trim values */
    for(int i=0;i<100;++i){
        if(tree[i][0] == 0)
            break;
        
        int treeIdx = tree[i][0];
        for(int j=treeIdx;j>=0;--j){
            if(tree[i][j] !=0){
                tree[i][0] = j;
                break;
            }
        }
    }
    
    /* Print the actual tree depth wise */
    for(int i=0;i<100;++i){
        if(tree[i][0] == 0)
            break;
        
        printf(" depth %d: ",i);
        for(int j=1;j<=tree[i][0];++j){
            if(j != 1)
                printf(",");
            
            if(tree[i][j] != 0)
                printf("k%d",tree[i][j]);
            else
                printf("%d",tree[i][j]);
                
        }
    }
    printf("\n");
}


int main(int argc,char* argv[]){

    if(argc < 2){
        printf("Wrong input\n");
        exit(1);
    }

    int value_of_n;                            // Initialization part     
    value_of_n=atoi(argv[1]);
    float n_probabilities[value_of_n];
    int i,j;
    float matrix[value_of_n+2][value_of_n+1];
    
    if(argc!=value_of_n+2){                             // File usage information
        fprintf(stderr, "Usage: ./obst.out <value of n> <n probabilities>\n");
        return 0;

    }
   
    i=2,j=1;                   // Probability array created
    while(i<argc){                             
        n_probabilities[j]=atof(argv[i]);
        ++i;
        ++j;
    }

    createInitialMatrix(value_of_n,matrix);
    fillValuesInMatrix(value_of_n,matrix,n_probabilities);
    //printMatrix(value_of_n,matrix);

    return 0;

}

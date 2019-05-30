#include<stdio.h>
#include<stdlib.h>
#include<math.h>
int count=1;

void creatingBoard(int size_of_matrix,int hole_row_number,int hole_column_number,int matrix[size_of_matrix][size_of_matrix]){
    for(int i=0;i<size_of_matrix;++i){                  // Initital board created by filling 0 in place
        for(int j=0;j<size_of_matrix;++j){
            matrix[i][j]=0;
            if(i==hole_row_number && j==hole_column_number){
                matrix[i][j]=-1;
            }
        }
    }
}

void printMatrix(int size_of_matrix,int matrix[size_of_matrix][size_of_matrix]){
    for(int i=0;i<size_of_matrix;++i){       // Printing the matrix as a table
        for(int j=0;j<size_of_matrix;++j){
            if(matrix[i][j]==-1){
                printf("X\t");
                continue;
            }
            printf("%d\t",matrix[i][j]);
        }
        printf("\n");
    }
} 

void trominoTile(int start_row,int start_column,int size_of_matrix,int original_size_of_matrix,int matrix[original_size_of_matrix][original_size_of_matrix]){
    int half_size_of_board,hole_quadrant=0;
    half_size_of_board=size_of_matrix/2;
    int hole_row_number,hole_column_number;

    if(size_of_matrix==2){
        for(int i=0;i<2;++i){
            for(int j=0;j<2;++j){
                if(matrix[start_row+i][start_column+j]==0) 
                    matrix[start_row+i][start_column+j]=count;
            }
        }
        ++count;
        return;
    }

    //Search for hole
    for(int i=start_row;i<start_row+size_of_matrix;++i){
        for(int j=start_column;j<start_row+size_of_matrix;++j){
            if(matrix[i][j]!=0){
                hole_row_number=i;
                hole_column_number=j;
            }
        }
    }
    
    // Finding out the quadant in which the hole resides originally
    if(hole_row_number<start_row+half_size_of_board && hole_column_number<start_column+half_size_of_board){
        matrix[start_row+half_size_of_board-1][start_column+half_size_of_board]=count;
        matrix[start_row+half_size_of_board][start_column+half_size_of_board]=count;
        matrix[start_row+half_size_of_board][start_column+half_size_of_board-1]=count;
        ++count;
    }
    else if(hole_row_number>=start_row+half_size_of_board && hole_column_number<start_column+half_size_of_board){
        matrix[start_row+half_size_of_board-1][start_column+half_size_of_board-1]=count;
        matrix[start_row+half_size_of_board-1][start_column+half_size_of_board]=count;
        matrix[start_row+half_size_of_board][start_column+half_size_of_board]=count;
        ++count;
    }
    else if(hole_row_number<start_row+half_size_of_board && hole_column_number >= start_column + half_size_of_board){
        matrix[start_row+half_size_of_board-1][start_column+half_size_of_board-1]=count;
        matrix[start_row+half_size_of_board][start_column+half_size_of_board-1]=count;
        matrix[start_row+half_size_of_board][start_column+half_size_of_board]=count;
        ++count;
    }
    else if(hole_row_number>=start_row+half_size_of_board && hole_column_number >= start_column +half_size_of_board){  
        matrix[start_row+half_size_of_board][start_column+half_size_of_board-1]=count;
        matrix[start_row+half_size_of_board-1][start_column+half_size_of_board-1]=count;
        matrix[start_row+half_size_of_board-1][start_column+half_size_of_board]=count;
        ++count;
    }

    trominoTile(start_row,start_column+half_size_of_board,half_size_of_board,original_size_of_matrix,matrix);
    trominoTile(start_row,start_column,half_size_of_board,original_size_of_matrix,matrix);
    trominoTile(start_row+half_size_of_board,start_column,half_size_of_board,original_size_of_matrix,matrix);
    trominoTile(start_row+half_size_of_board,start_column+half_size_of_board,half_size_of_board,original_size_of_matrix,matrix);

}


int main(int argc, char* argv[]){
    
    int k_value,hole_row_number,hole_column_number;   // Initialization part
    k_value=atoi(argv[1]);
    hole_row_number=atoi(argv[2]);
    hole_column_number=atoi(argv[3]);
    int size_of_matrix=pow(2,k_value);
    int matrix[size_of_matrix][size_of_matrix];

    if(argc!=4){            // File Usage Information
        fprintf(stderr, "\nUsage: ./tromino.out <value of k> <hole position row number> <hole position column number> \n\n");
        return 0;
    }


    creatingBoard(size_of_matrix,hole_row_number,hole_column_number,matrix); // Creating the initial board
    printf("\n -------Initial Board with hole as X --------\n\n");
    printMatrix(size_of_matrix,matrix);// Print the matrix initially
    trominoTile(0,0,size_of_matrix,size_of_matrix,matrix);   // Tromino tile function called 
    printf("\n-------Matrix with Tromino Tiles-------\n\n");
    printMatrix(size_of_matrix,matrix);



    return 0;    
}

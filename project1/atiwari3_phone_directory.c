#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

typedef struct record{
	char index[256];
	char firstname[256];
	char lastname[256];
	char number[256];
}record;

struct record directory[257];

int count=0;


void create(char* filepath){
	int i=0,record_number=0,j=0;
	FILE* fp;
	fp=fopen(filepath,"r");
	while(1){
		char buff[256];
		fgets(buff,256,fp);
		if(feof(fp)!=0){ break;}
		++count;
		for(i=0;i<256;++i){
			if(buff[i]==' '){ break;}
			directory[record_number].index[i]=buff[i];
		}
		for(j=i+1,i=0;j<256,i<256;++j,++i){
			if(buff[j]==' '){break;}
			directory[record_number].firstname[i]=buff[j];
		}
		for(j=j+1,i=0;j<256,i<256;++j,++i){
			if(buff[j]==','){break;}
			directory[record_number].lastname[i]=buff[j];
		}
		for(j=j+2,i=0;j<256,i<256;++j,++i){
			if(buff[j]=='\n'){break; }
			directory[record_number].number[i]=buff[j];
		}
		++record_number;
	}
	fclose(fp);

}


void quickSort(int* i,int* j,int* k,struct record* left,struct record* right){
	if(strcmp(left[*i].number,right[*j].number)<0){
		strcpy(directory[*k].lastname,left[*i].lastname);
		strcpy(directory[*k].firstname,left[*i].firstname);
		strcpy(directory[*k].number,left[*i].number);
		++*i;
	}
	else{
		strcpy(directory[*k].lastname,right[*j].lastname);
		strcpy(directory[*k].firstname,right[*j].firstname);
		strcpy(directory[*k].number,right[*j].number);
		++*j;
	}
}


void join(int first,int middle,int last){
	int i,j,k;
	int first_half,second_half;
	first_half=middle-first+1;       //first half is calculated by subtracting middle index by first index and adding 1
	second_half=last-middle;	// second half is calculated by subtrating last index by middle index
 
	struct record left[first_half];		//temporary struct is created for first half and second half	
	struct record right[second_half];
	
	for(i=0;i<first_half;++i){
		strcpy(left[i].lastname,directory[first+i].lastname);	//components from first half copied to temporary left struct
		strcpy(left[i].firstname,directory[first+i].firstname);
		strcpy(left[i].number,directory[first+i].number);	
	}
	
	for(j=0;j<second_half;++j){
		strcpy(right[j].lastname,directory[middle+1+j].lastname);
		strcpy(right[j].firstname,directory[middle+1+j].firstname);
		strcpy(right[j].number,directory[middle+1+j].number);
	}
	i=0,j=0,k=first;
	while(i<first_half&&j<second_half){
		if(strcmp(left[i].lastname,right[j].lastname)<0){   // Compare  element of first half with second half
			strcpy(directory[k].lastname,left[i].lastname);
			strcpy(directory[k].firstname,left[i].firstname);// If condition holds true then copy to kth element of directory
			strcpy(directory[k].number,left[i].number);	
			++i;						// If condtion hold true then only increment the index of first_half and for second iteration the next item of first_half will be again compared with same element of second half
		}
		
		
		else if(strcmp(left[i].lastname,right[j].lastname)==0){ // Condition when last names are same
			if(strcmp(left[i].firstname,right[j].firstname)<0){
				strcpy(directory[k].lastname,left[i].lastname);
				strcpy(directory[k].firstname,left[i].firstname);
				strcpy(directory[k].number,left[i].number);
				++i;
			}
			else if(strcmp(left[i].firstname,right[j].firstname)==0){//condition when both first and last names are same
				quickSort(&i,&j,&k,left,right);
			}
			
			else{	
				strcpy(directory[k].lastname,right[j].lastname);
				strcpy(directory[k].firstname,right[j].firstname);
				strcpy(directory[k].number,right[j].number);
				++j;					
			}

		}
		
		else{
			strcpy(directory[k].lastname,right[j].lastname);
			strcpy(directory[k].firstname,right[j].firstname);
			strcpy(directory[k].number,right[j].number);
			++j;						// increment j only when condition is false
		}
		++k;							// increment k for every iteration
	}
	for(i,k;i<first_half;++i,++k){
			strcpy(directory[k].lastname,left[i].lastname);// Add remaining elements from first half to directory
			strcpy(directory[k].firstname,left[i].firstname);
			strcpy(directory[k].number,left[i].number);
	}
	for(j,k;j<second_half;++j,++k){
			strcpy(directory[k].lastname,right[j].lastname);// Add remaining elements from second half to directory
			strcpy(directory[k].firstname,right[j].firstname);
			strcpy(directory[k].number,right[j].number);
	}

}

void mergeSort(int first,int last){
	int middle;
	if(first<last){
		 middle=first+(last-first)/2;    // Middle element is calculated here
		mergeSort(first,middle);	//Function is called iteratively untill it satisfies the condition of first index less than last index
		mergeSort(middle+1,last);
		join(first,middle,last);    //join function is called to merge the splitted components
	}
}

void sortDirectory(){
	int size_of_directory=count;
	                                                      // The size of directory is determined here
	mergeSort(0,size_of_directory-1);		       // The mergeSort function is called with first and last indexes	
}

void insertEntry(char* name,char* phone_number){
	int i,j;
	char first_name[256]={};
	char last_name[256]={};
	for(i=0;i<255;++i){
		if(name[i]==' '){break;}
		first_name[i]=name[i];
	}
	for(j=i+1,i=0;j<255,i<255;++j,++i){
		if(name[i]=='\n'){break;}
		last_name[i]=name[j];
	}
	sortDirectory();
	int size_of_directory=count;
	for(i=0;i<size_of_directory;++i){
		if(strcmp(directory[i].lastname,last_name)>0){
			for(j=size_of_directory-1;j>=i;--j){
				if(j==size_of_directory-1){
					int index=atoi(directory[j].index);
					index=index+1;
					char index_c[256];
					sprintf(index_c,"%d",index);
					strcpy(directory[j+1].index,index_c);
					strcpy(directory[j+1].firstname,directory[j].firstname);
					strcpy(directory[j+1].lastname,directory[j].lastname);
					strcpy(directory[j+1].number,directory[j].number);
				}
			
				strcpy(directory[j+1].firstname,directory[j].firstname);
				strcpy(directory[j+1].lastname,directory[j].lastname);
				strcpy(directory[j+1].number,directory[j].number);
			}
			strcpy(directory[i].firstname,first_name);
			strcpy(directory[i].lastname,last_name);
			strcpy(directory[i].number,phone_number);
			break;
		}

		else if(strcmp(directory[i].lastname,last_name)==0){
			if(strcmp(directory[i].firstname,first_name)>0){
				for(j=size_of_directory-1;j>=i;--j){
					if(j==size_of_directory-1){
						int index=atoi(directory[j].index);
						index=index+1;
						char index_c[256];
						sprintf(index_c,"%d",index);
						strcpy(directory[j+1].index,index_c);
						strcpy(directory[j+1].firstname,directory[j].firstname);
						strcpy(directory[j+1].lastname,directory[j].lastname);
						strcpy(directory[j+1].number,directory[j].number);
					}
				
					strcpy(directory[j+1].firstname,directory[j].firstname);
					strcpy(directory[j+1].lastname,directory[j].lastname);
					strcpy(directory[j+1].number,directory[j].number);
				}
				strcpy(directory[i].firstname,first_name);
				strcpy(directory[i].lastname,last_name);
				strcpy(directory[i].number,phone_number);
				break;
			
			}
			else if(strcmp(directory[i].firstname,first_name)==0){
				if(strcmp(directory[i].number,phone_number)>0){
					for(j=size_of_directory-1;j>=i;--j){
						if(j==size_of_directory-1){
							int index=atoi(directory[j].index);
							index=index+1;
							char index_c[256];
							sprintf(index_c,"%d",index);
							strcpy(directory[j+1].index,index_c);
							strcpy(directory[j+1].firstname,directory[j].firstname);
							strcpy(directory[j+1].lastname,directory[j].lastname);
							strcpy(directory[j+1].number,directory[j].number);
						}
					
						strcpy(directory[j+1].firstname,directory[j].firstname);
						strcpy(directory[j+1].lastname,directory[j].lastname);
						strcpy(directory[j+1].number,directory[j].number);
					}
					strcpy(directory[i].firstname,first_name);
					strcpy(directory[i].lastname,last_name);
					strcpy(directory[i].number,phone_number);
					break;
				}
				else if(strcmp(directory[i].number,phone_number)==0){
					printf("Entry Already exists in the directory\n");
					break;
				}
			
			
			}
		}
	}
	strcpy(directory[i].firstname,first_name);
	strcpy(directory[i].lastname,last_name);
	strcpy(directory[i].number,phone_number);
	int index=atoi(directory[i-1].index);
	index=index+1;
	char index_c[256];
	sprintf(index_c,"%d",index);
	strcpy(directory[i].index,index_c);
	++count;

}

	
		
void deleteEntry(char* name){
	int i,j;
	char first_name[256]={};
	char last_name[256]={};
	for(i=0;i<255;++i){
		if(name[i]==' '){break;}
		first_name[i]=name[i];
	}
	for(j=i+1,i=0;j<255,i<255;++j,++i){
		if(name[i]=='\n'){break;}
		last_name[i]=name[j];
	}
	sortDirectory();
	int size_of_directory=count;
	for(i=size_of_directory-1;i>=0;--i){
		if(strcmp(directory[i].lastname,last_name)==0&&strcmp(directory[i].firstname,first_name)==0){
			for(j=i;j<size_of_directory-1;++j){
				int index=atoi(directory[j+1].index);
				index=index-1;
				char index_c[256];
				sprintf(index_c,"%d",index);
				strcpy(directory[j+1].index,index_c);
				directory[j]=directory[j+1];
			}
			strcpy(directory[j+1].index,"\0");
			strcpy(directory[j].index,"\0");
			break;
		}

	}
	if(i<0){
		printf("Unable to delete as entry not found\n");
	}
	--count;
}


void goLeft(int mid,char* first_name,char* last_name){
	if(strcmp(directory[mid].lastname,last_name)==0&&strcmp(directory[mid].firstname,first_name)==0){
		goLeft(mid-1,first_name,last_name);
		printf("%s %s %s, %s\n",directory[mid].index,directory[mid].firstname,directory[mid].lastname,directory[mid].number);
	}
	else{
		return;
	}
}

void goRight(int mid,char* first_name,char* last_name){
	if(strcmp(directory[mid].lastname,last_name)==0&&strcmp(directory[mid].firstname,first_name)==0){
		printf("%s %s %s, %s\n",directory[mid].index,directory[mid].firstname,directory[mid].lastname,directory[mid].number);
		goRight(mid+1,first_name,last_name);
	}
	else{
		return;
	}
}
	

void binarySearch(int first,int last,char* first_name,char* last_name){
       if(last>=first){
               int mid=first+(last-first)/2;
               if(strcmp(directory[mid].lastname,last_name)==0&&strcmp(directory[mid].firstname,first_name)==0){
			goLeft(mid,first_name,last_name);
			goRight(mid+1,first_name,last_name);			       

	       }
		else if(strcmp(directory[mid].lastname,last_name)>0){
			binarySearch(first,mid-1,first_name,last_name);
		}
		else{
			binarySearch(mid+1,last,first_name,last_name);
		}
       }
	else{
		printf("Name not found\n");
	}
}


void searchDirectory(char* name){
	int i,j;
	char first_name[256]={};
	char last_name[256]={};
	for(i=0;i<255;++i){
		if(name[i]==' '){break;}	
		first_name[i]=name[i];
	}
	for(j=i+1,i=0;j<255,i<255;++j,++i){
		if(name[i]=='\n'){break;}
		last_name[i]=name[j];
	}
	sortDirectory();
	int size_of_directory;
	for(size_of_directory=0;size_of_directory<256;++size_of_directory){
		if(directory[size_of_directory].index[0]=='\0'){break;}
	}    
        int first=0;
        int last=size_of_directory-1;
        binarySearch(first,last,first_name,last_name);
	
}

void showDirectory(){
	sortDirectory();
	int size_of_directory;
	size_of_directory=count;
	for(int i=0;i<size_of_directory;++i){
		printf("%d %s %s, %s\n",i+1,directory[i].firstname,directory[i].lastname,directory[i].number);
	}
}

void showMenu(){
	printf("Please provide options:\n");
	printf("Insert\t\t(press 1)\n");
	printf("Search\t\t\(press 2)\n");
	printf("Delete\t\t(press 3)\n");
	printf("Show Directory\t(press 4)\n");
	printf("Exit\t\t(press 5)\n");
}

void fflushstdin(){
	int c;
	while((c=fgetc(stdin)) != EOF && c!='\n');
}


int main(int argc,char** argv){

	if(argc !=2){
		fprintf(stderr,"Usage: ./atiwari3_phone_directory.out <input_file_name>\n");
		exit(1);
	}
	

	char* filepath=argv[1];
	create(filepath);

	while(1){
		int num;
		showMenu();
		printf("Enter your option:");
		scanf("%d",&num);
		fflushstdin();
		char name[100],phoneNum[100];

		switch (num){
			case 1:
				fprintf(stderr,"\nEnter name: ");
				scanf("%99[ 0-9A-Za-z]",name);
				fflushstdin();

				fprintf(stderr,"\nEnter phone number: ");
				scanf("%s",phoneNum);
				fflushstdin();

				insertEntry(name,phoneNum);
				break;

			case 2:
				printf("\nEnter name: ");
				scanf("%99[ 0-9A-Za-z]",name);
				fflushstdin();
				searchDirectory(name);
				break;

			case 3:
				printf("\nEnter name: ");
				scanf("%99[ 0-9A-Za-z]",name);
				fflushstdin();
				deleteEntry(name);
				break;

			case 4:
				showDirectory();
				break;
			
			case 5:
				exit(0);
				break;
		}

	}
	return 0;

}

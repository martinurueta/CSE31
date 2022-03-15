#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Declarations of the two functions you will implement
// Feel free to declare any helper functions or global variables
void printPuzzle(char** arr);
void searchPuzzle(char** arr, char* word);
void searchPath(char** arr, char* word, int** path);
void buildPath();
void printPath();   
int bSize;
int count = 0;
int** path;

// Main function, DO NOT MODIFY 	
int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <puzzle file name>\n", argv[0]);
        return 2;
    }
    int i, j;
    FILE *fptr;

    // Open file for reading puzzle
    fptr = fopen(argv[1], "r");
    if (fptr == NULL) {
        printf("Cannot Open Puzzle File!\n");
        return 0;
    }

    // Read the size of the puzzle block
    fscanf(fptr, "%d\n", &bSize);
    
    // Allocate space for the puzzle block and the word to be searched
    char **block = (char**)malloc(bSize * sizeof(char*));
    char *word = (char*)malloc(20 * sizeof(char));

    // Read puzzle block into 2D arrays
    for(i = 0; i < bSize; i++) {
        *(block + i) = (char*)malloc(bSize * sizeof(char));
        for (j = 0; j < bSize - 1; ++j) {
            fscanf(fptr, "%c ", *(block + i) + j);            
        }
        fscanf(fptr, "%c \n", *(block + i) + j);
    }
    fclose(fptr);

    printf("Enter the word to search: ");
    scanf("%s", word);
    
    // Print out original puzzle grid
    printf("\nPrinting puzzle before search:\n");
    printPuzzle(block);
    
    // Call searchPuzzle to the word in the puzzle
    searchPuzzle(block, word);
    
    return 0;
}

void printPuzzle(char** arr) {
	// This function will print out the complete puzzle grid (arr). 
    // It must produce the output in the SAME format as the samples 
    // in the instructions.
    // Your implementation here...
    for (int i = 0; i < bSize; i++){ // prints puzzle
		for (int j = 0; j < bSize; j++){
			printf("%c ", *(*(arr + i) + j));
		}
		printf("\n");
	}
    printf("\n");
}

void searchPuzzle(char** arr, char* word) {
    // This function checks if arr contains the search word. If the 
    // word appears in arr, it will print out a message and the path 
    // as shown in the sample runs. If not found, it will print a 
    // different message as shown in the sample runs.
    // Your implementation here...
  	if(count == 0){ // converts word to uppercase, only once
        for (int i = 0; *(word+i)!='\0'; i++){ 
  		    if(*(word+i) >= 'a' && *(word+i) <= 'z'){
  			    *(word+i) = *(word+i) -32;
		    }
  	    }
        count++;
    }
    buildPath();
    searchPath(arr, word, path);
    printf("Printing the search path: \n");
    printPath();
}

void searchPath(char** arr, char* word, int** path){
    int letterCount = 0;
    for(int i = 0; i < bSize; i++){
        for(int j = 0; j < bSize; j++){
            if(i < bSize && (j+1) < bSize){ // left to right
            for(int h=1; ((((i) < bSize) && ((j+h) < bSize)) && h < word); h++){
                if((*(word+h)) == *(*(arr + i)+ j+h)){
                    letterCount++;
                    *(*(path+i)+j) = letterCount;
                }
				else if((*(word+h)) == *(*(arr + i)+ j+h)){
                    letterCount++;
                    *(*(path+i)+j) = letterCount;
                }
            }
            if(i < bSize && (j-1) < bSize){ // right to left

            }
            if((i+1) < bSize && j < bSize){ // up to down 
                
            }
            if((i+1) < bSize && (j+1) < bSize){ // top left to bottom right

            }
            if((i-1) < bSize && (j-1) < bSize && (i-1) > 0){ // top right to bottom left

            }

            // if(*(word+letterCount) == *(*(arr+i)+j)){
            //     letterCount++;
            //     *(*(path+i)+j) = letterCount;
            // }
        }
    }
}

void buildPath(){ // setting up the search path as 0's
    path = (int**)malloc(bSize * sizeof(int*));    
	for (int i = 0; i < bSize; i++){
		*(path + i) = (int*)malloc(bSize * sizeof(int));
	}
    for (int i = 0; i < bSize; i++){
		for (int j = 0; j < bSize; j++){
			*(*(path + i) + j) = 0;
		}
	}
}

void printPath(){ // prints path after word is found
    for (int i = 0; i < bSize; i++){
		for (int j = 0; j < bSize; j++){
			printf("%d ", *(*(path + i) + j));
		}
        printf("\n");
	}
}
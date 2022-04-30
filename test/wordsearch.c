#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Declarations of the two functions you will implement
// Feel free to declare any helper functions or global variables


void printPuzzle(char **arr); //declaring search puzzle function

void searchPuzzle(char **arr, char *word);// declaring searchPuzzle function

bool searchHelper(char **arr, char *word, int r, int c, int i, int n, int **s); //declaring searchHelper function

void caseHelper(char *word); //declaring caseHelper function

int bSize; //defining a global variable

// Main function, DO NOT MODIFY 

// The main function starts with two arguments of int and char type
//argc refers to the number of command line arguments passed in,
// which includes the actual name of the program, as invoked by the user.
//argv contains the actual arguments, starting with index 1. Index 0 is the program name.


int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <puzzle file name>\n", argv[0]);
        return 2;
    }
    int i, j;
    FILE *fptr;

    // Open file for reading puzzle
    fptr = fopen(argv[1], "r");
    if (fptr == NULL) {//here checking if the file exist or not if not then simply printing "Cannot Open Puzzle File!"
        printf("Cannot Open Puzzle File!\n");
        return 0;
    }

    // Read the size of the puzzle block
    fscanf(fptr, "%d\n", &bSize); //reads formatted input from a stream and storing in bsize 

    // Allocate space for the puzzle block and the word to be searched
    char **block = (char **) malloc(bSize * sizeof(char *));//creating an array that will store the address of arrays of char  
    char *word = (char *) malloc(20 * sizeof(char)); //storing starting address of an array of char of 20 length 

    // Read puzzle block into 2D arrays
    //running loop bsize times
    for (i = 0; i < bSize; i++) {
        *(block + i) = (char *) malloc(bSize * sizeof(char));//storing starting address of an array of char of bsize length 
        for (j = 0; j < bSize - 1; ++j) { // again inside previous loop running one more loop of bsize-1 times
            fscanf(fptr, "%c ", *(block + i) + j); //reads formatted input from a stream and storing it.
        }
        fscanf(fptr, "%c \n", *(block + i) + j); //reads formatted input from a stream and storing it.
    }
    fclose(fptr); //here it is closing the file 

    printf("Enter the word to search: "); //here I ask the user to enter the word taht has to be find
    scanf("%s", word); //getting that input and storing in word variable

    printf("\nPrinting puzzle before search:\n"); //here printing that puzzle before searching
    printPuzzle(block); //now here calling printPuzzle function (with passing that block array of adresses) to print that puzzle before search

    searchPuzzle(block, word);///now here calling searchPuzzle function(with passing that block array of adresses and that input word from user) to search that word 

    return 0;
}// here I end the program 

//from here onward I am defining the  functions that I decleared earlier and used in main function

//defining printPuzzle function
void printPuzzle(char **arr) {
    //here going through each row and columns to print puzzle with the help of two for loops one in another
    for (int i = 0; i < bSize; i++) {
        for (int j = 0; j < bSize; j++) {
            printf("%c ", *(*(arr + i) + j));
        }
        printf("\n");//after each row making a line change --> command to next line
    }
    printf("\n"); //after printing the  puzzle making another line change -->comand to next line


}

//defining searchPuzzle function
//this function going to help to find the word and printing that searched path
void searchPuzzle(char **arr, char *word) {
    // This function checks if arr contains the search word. If the word appears in arr, it will print out a message and the path as shown in
    // the sample runs. If not found, it will print a different message as shown in the sample runs.
    // your implementation here...
    int **sol = (int **) malloc(bSize * sizeof(int *));//creating a varible taht stores adress of ararys taht will contain adress of int type variables
    for (int i = 0; i < bSize; i++) {
        *(sol + i) = (int *) malloc(bSize * sizeof(int)); //setting the adress of a new created array of bSize length of int type to sol+i th position
        for (int j = 0; j < bSize; j++) {
            *(*(sol + i) + j) = 0; //iterating to location of sol+i by j and then setting there value of int by 0
//this means first iterating to sol+i location by j and then taking the adress of taht cell then 
//by that going to that adress of int type to set this zero value
        }
    }

    int length = (strlen(word) - 1);// it is storing the length of word
    int status = 0; //using as status checking zero

    int counter; //for counting throgth each word length

    for (int c = 0; c < length; c++) {
        caseHelper(word); //here it is getting all lower case alphabets into upper case alphabets

    }
    //here getting total sum of counter to length of word times
    for (counter = 0; counter < strlen(word); counter++) {
        counter += counter;
    }
    //here going through each row and column for searching that word
    for (int row = 0; row < bSize; row++) {
        for (int col = 0; col < bSize; col++) {
            if (*(*(arr + row) + col) == *(word)) {
                status = searchHelper(arr, word, row, col, 0, length, sol);//here calling searchHelper function by passing that word taht has to searchHelper
//if status is 1 that means we got that word
                if (status) {
//so after that simply print that "Word found!" and then Print the searched path of word

                    printf("Word found!\n");
                    printf("Printing the search path:\n");

                    for (int p = 0; p < bSize; p++) {
                        for (int q = 0; q < bSize; q++) {
                            printf("%d\t", sol[p][q]);
                        }
                        printf("\n");
                    }
                    return;
                }
            }
        }
    }
    //if the status is not 1 it will print word not found
    printf("Word not found!\n");
    free(sol); // here it is releasing the space 
}
//defining caseHelper function here we are passing adress of taht same char variable so this function can modify this passed char
///here this function is basically for  converting any lower alphabet into upper alphabet like a--> A, b-->B  so on
void caseHelper(char *word) {
    char *c = word; //declering a variable to access that char data from char adress
    while (*c) {//running loop for  char
        if (97 <= *c || *c >= 122) {
            *c -= 32; //here we are basically converting any lower alphabet into upper alphabet like a--> A, b-->B  so on
        }
        c++;
    }
}
//defining validate function with two arguments of both int type
//we use this function in searchHelper function for validation purpose
//this is for checking we are in puzzle board or not
bool validate(int r, int c) {
    //only return true when  c >= 0 but  c < bSize and r >= 0 but  r < bSize
    return (c >= 0) && (c < bSize) && (r >= 0) && (r < bSize);
}
//defining searchHelper function
//this function does the main task of searching that word is present or not
bool searchHelper(char **arr, char *word, int r, int c, int i, int n, int **s) {
    //for searching in all 8 directions from point 
    int x[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int y[] = {-1, 0, 1, -1, 1, -1, 0, 1};
    if (i > (n) || arr[r][c] != word[i]) {
        return false;
    }
    
    if (i == n) {
        s[r][c] = s[r][c] * 10 + i + 1;
        return true;
    }

    for (int direction = 0; direction < 8; direction++) {
        //this function does that main task of searching that word is present or not
        if (i == n) {
            return true;
        }
        //checking if it is inside board or not
        if (validate(r + x[direction], c + y[direction])) {
            if (searchHelper(arr, word, r + x[direction], c + y[direction], i + 1, n, s)) {//if next move is in the board of puzzle then call same function
            //recursively for   r + x[direction], c + y[direction] and i+1 
            //and modifing value as shown below for each i if inside the board
                s[r][c] = s[r][c] * 10 + i + 1;
                return true;
            }

        }
    }
    return false;
    //if not returned yet/not got yet so that means not present so simply return false
}




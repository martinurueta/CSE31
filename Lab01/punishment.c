#include <stdio.h> //Library
int main() { 
    int repeat, typo;
    printf("Enter the number of times to repeat the punishment phrase: "); // printing to console thats in the quotes
    scanf("%d", &repeat); // user input
    while (repeat <= 0){ // checks to see if variable repeat is less than or equal to 0 
        printf("You entered an invalid value for the number of repetitions! \n"); // run code if condition is met
        printf("Enter the number of times to repeat the punishment phrase again: "); // printing to console thats in the quotes
        scanf("%d", &repeat); //user input
    }
    printf("Enter the repetition line where you want to introduce the typo: "); // printing to console thats in the quotes
    scanf("%d", &typo); // user input
    while (typo <= 0 || (repeat < typo)){ // checks to see if variable typo is less than or equal to 0 or typo is greater than repeat
        printf("You entered an invalid value for the typo placement! \n"); // run code if condition is met
         printf("Enter the repetition line where you want to introduce the typo again: "); // printing to console thats in the quotes
        scanf("%d", &typo); //user input
    }
    for (int i = 1; i <= repeat; i++){// repeats condition until i mets its value
        if (i == typo){// if i = to typo change it to the error phrase
            printf("Progranming in c is phun!\n");
        }else{
            printf("Progranming in c is fun!\n");
        }
    }


    return 0; 
} 
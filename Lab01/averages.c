#include <stdio.h> //Library
int main() { 
    int tempadd = 0, counter = 0, temp = 0; // tempadd is adding up the seperate number :: counter is the amount of loops :: temp is equal for usertemp
    float avgodd = 0, avgeven = 0, usertemp, numeven = 0, numodd = 0; // avgodd is the adding up and dived by numodd count :: avgeven is add up and dived by numeven count // usertemp is the user input of their number
    do{
        counter++; // counting the phrase of (Please enter the "counter" integer)
        printf("Please enter the %d integer:", counter);
        scanf("%f", &usertemp);
        temp = usertemp; // set temp the same number as usertemp
        if (temp < 0){
            temp = -temp; // if temp is negative change it to positive
        }
         //printf("%d" ,usertemp); // check for change to postive
        while(temp != 0){
            tempadd = tempadd + (temp % 10); // temp % 10 seperate the single digit
            temp = temp / 10; // divide the by ten for ex: 1112 / 10 = 111 get rid of a first digit 
            // repeat the loop til it equals zero
        }
        // printf("%d" ,tempadd); // to check if adding works

        if (tempadd % 2 == 0 && usertemp != 0){ // if even from all the adding start this if else do other
            avgeven = avgeven + usertemp; // add up user value 
            numeven++; // counter for each number being added even
            // printf("%f" ,usertemp); // to check to see if usertemp is hold the user input number for even
            tempadd = 0; //reset the temp add of single digit
        }else if(usertemp != 0){
            avgodd = avgodd + usertemp; // add up user value for odd
            numodd++; // counter for each number being added odd
            // printf("%f" ,usertemp); // to check to see if usertemp is hold the user input number for odd
            tempadd = 0; //reset the temp add of single digit
        }
        
    } while(usertemp != 0);// end of while loop

    if (avgeven != 0){// if avgeven value does not equal to zero print the value
        // printf("numeven = %f \n" ,numeven); to check the counter for even numbers
        avgeven = avgeven / numeven;
        printf("Average of inputs whose digits sum up to an even number: %0.2f\n", avgeven);
    }
    if (avgodd != 0){// if avgodd value does not equal to zero print the value
        avgodd = avgodd / numodd;
        printf("Average of inputs whose digits sum up to an odd number: %0.2f\n", avgodd);
    }
    if (avgodd == 0 && avgeven == 0){// if avgeven and avgodd is equal to zero print the error message
        printf("There is no average to compute. ");
    }
    return 0;
}
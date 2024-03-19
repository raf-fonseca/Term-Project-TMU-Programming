
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ROWS 3200
#define COLS 11

// Declare the arrays to store the data
char dates[ROWS];
char LandAvrgTemp[ROWS]; // 
char LandAvrgTempUncertainty[ROWS];
char LandMaxTemp[ROWS];
char LandMaxTempUncertainty[ROWS];
char LandMinTemp[ROWS];
char LandMinTempUncertainty[ROWS];
char LandAndOceanAvrgTemp[ROWS];
char LandAndOceanAvrgTempUncertainty[ROWS];


void assignArrays() {
    FILE* fp = fopen("GlobalTemperatures.csv", "r");
    if (fp == NULL) {
        printf("Failed to open file.\n");
        return;
    }

    char str[100000];
    char* token;

    fgets(str, 100000, fp); // Read and discard the first line

    int i = 0;
    while (fgets(dates, ROWS, fp) != NULL) {
        token = strtok(str, ",");
        strcpy(&dates[i], token); // Store the date in the dates array

        token = strtok(NULL, ",");
        strcpy(&LandAvrgTemp[i], token); // Store the land average temperature in the LandAvrgTemp array

        token = strtok(NULL, ",");
        strcpy(&LandAvrgTempUncertainty[i], token); // Store the land average temperature uncertainty in the LandAvrgTempUncertainty array

        token = strtok(NULL, ",");
        strcpy(&LandMaxTemp[i], token); // Store the land maximum temperature in the LandMaxTemp array

        token = strtok(NULL, ",");
        strcpy(&LandMaxTempUncertainty[i], token); // Store the land maximum temperature uncertainty in the LandMaxTempUncertainty array

        token = strtok(NULL, ",");
        strcpy(&LandMinTemp[i], token); // Store the land minimum temperature in the LandMinTemp array

        token = strtok(NULL, ",");
        strcpy(&LandMinTempUncertainty[i], token); // Store the land minimum temperature uncertainty in the LandMinTempUncertainty array

        token = strtok(NULL, ",");
        strcpy(&LandAndOceanAvrgTemp[i], token); // Store the land and ocean average temperature in the LandAndOceanAvrgTemp array

        token = strtok(NULL, ",");
        strcpy(&LandAndOceanAvrgTempUncertainty[i], token); // Store the land and ocean average temperature uncertainty in the LandAndOceanAvrgTempUncertainty array

        i++;

        printf("%s\n", dates);
    }

    fclose(fp);
}
// char dates[ROWS];

/*void readData() {
    FILE *fp = fopen("GlobalTemperatures.csv" , "r");
   char str[100000];
   char date[30];
   double avgtemp;

   char *sp; // this allows for assignment, which we cant do with str[100000]

   // Read and discard the first line
   fgets(str, 100000, fp);

   while (fgets(str, 100000, fp) != NULL) {
    sp = strtok(str, ","); // start at the beginning of str and stop at the "," string and assign it to our string pointer
    strcpy(date, sp); // copy the above string into date[30]
    
    // Parse the year from the date
    int year = atoi(date);

    // If the year is less than 1760, skip this iteration
    if (year < 1760) {
        continue;
    }

    sp = strtok(NULL, ","); //pick up where you left off 

    avgtemp = atof(sp); // convert the string to a float
    
    printf("\n%s %lf", date, avgtemp);

   }
   fclose(fp);
}
*/



int main (void) {
    //Q1  calculate the yearly averages for each year between 1760 and 2015 
   assignArrays();
   return(0);
}   

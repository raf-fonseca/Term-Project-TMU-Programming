
//ksdhjf jkasdhf kh sdfa jthe nekjasdf the new stuff
//Testing 123ut128312y31897187
// ksdhjf jkasdhf kh sdfa jthe nekjasdf the new stuff
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// #define ROWS 3200
// #define COLS 11


// char data[ROWS][COLS];
// char LandAvrgTemp[ROWS];
// char dates[ROWS];

void readData() {
    FILE *fp = fopen("GlobalTemperatures.csv" , "r");
   char str[100000];
   char date[30];
   double avgtemp;
   double avgyeartemp;
   int counter = 0;

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

    // adds average temp to yearly avg temp for 12 consecutive entries, counter and yearly avg temp resets after 12 entries
    avgyeartemp += avgtemp;
    counter++;
    if (counter == 12) {
        printf("\n\nthe year is %d and avg year temp is %lf\n\n", year, avgyeartemp / 12);
        counter = 0;
        avgyeartemp = 0;
    }


   }
   fclose(fp);
}


int main (void) {
    //Q1  calculate the yearly averages for each year between 1760 and 2015 
   readData();
   return(0);
}   

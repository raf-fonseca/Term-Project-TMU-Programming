
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ROWS 3192
#define COLS 11

// Declare the arrays to store the data
char dates[ROWS][COLS];
double LandAvrgTemp[ROWS];
double LandAvrgTempUncertainty[ROWS];
double LandMaxTemp[ROWS];
double LandMaxTempUncertainty[ROWS];
double LandMinTemp[ROWS];
double LandMinTempUncertainty[ROWS];
double LandAndOceanAvrgTemp[ROWS];
double LandAndOceanAvrgTempUncertainty[ROWS];
double YearlyLandAvrgTemp[ROWS];

void assignArrays()
{
    FILE *fp = fopen("GlobalTemperatures.csv", "r");
    if (fp == NULL)
    {
        printf("Failed to open file.\n");
        return;
    }

    char line[1000]; // Line for every row

    for (int row = -1; row < ROWS; row++)
    {
        fgets(line, 1000, fp); // Skip the first line
        char *token = strtok(line, ",");
        int col = 0;

        if (row == -1)
        {
            continue; // Skip the first row
        }

        while (token != NULL)
        {
            switch (col)
            {
            case 0:
                strcpy(dates[row], token);
                break;
            case 1:
                LandAvrgTemp[row] = atof(token);
                break;
            case 2:
                LandAvrgTempUncertainty[row] = atof(token);
                break;
            case 3:
                LandMaxTemp[row] = atof(token);
                break;
            case 4:
                LandMaxTempUncertainty[row] = atof(token);
                break;
            case 5:
                LandMinTemp[row] = atof(token);
                break;
            case 6:
                LandMinTempUncertainty[row] = atof(token);
                break;
            case 7:
                LandAndOceanAvrgTemp[row] = atof(token);
                break;
            case 8:
                LandAndOceanAvrgTempUncertainty[row] = atof(token);
                break;
            }
            token = strtok(NULL, ","); // Keep going from where you left off till the end
            col++;
        }
    }

    fclose(fp);
}
void printArrays()
{
    for (int i = 0; i < ROWS; i++)
    {
        printf("Date: %s\n", dates[i]);
        printf("Land Average Temperature: %.2lf\n", LandAvrgTemp[i]);
        // printf("Land Average Temperature Uncertainty: %f\n", latu[i]);
        // printf("Land Max Temperature: %f\n", lmt[i]);
        // printf("Land Max Temperature Uncertainty: %f\n", lmtu[i]);
        // printf("Land Min Temperature: %f\n", lmit[i]);
        // printf("Land Min Temperature Uncertainty: %f\n", lmitu[i]);
        // printf("Land and Ocean Average Temperature: %f\n", loat[i]);
    }
}

void q1() // Calculate yearly average for each year between 1760 and 2015
{
    int counter = 0;
    double yearlytotaltemp = 0;
    char Year[ROWS];

    for (int i = 120; i < ROWS; i++) // Index 120 starts at the beginning of year 1760
    {
        strncpy(Year, dates[i], 4);
        yearlytotaltemp += LandAvrgTemp[i];
        counter++;

        if (counter == 12) // Assigns an average yearly temperature and resets the counter after every 12 months
        {
            YearlyLandAvrgTemp[i] = yearlytotaltemp / 12;
            printf("The average temperature for the year %s is %lf degrees Celsius.\n", Year, YearlyLandAvrgTemp[i]);
            counter = 0;
            yearlytotaltemp = 0;
        }
    }
}

void q3() // Calculate monthly averages for all years combined between 1900 and 2015
{
    double MonthlyAvrgTemp[12]; // Each element represent a month of the year
    double monthlytotaltemp = 0;
    int j;
    int counter = 0;

    for (int i = 0; i < 12; i++) // array for each month
    {
        for (j = 1680 + i; j < ROWS; j += 12) // each temperature average
        {
            monthlytotaltemp += LandAvrgTemp[j];
            counter ++;
        }
        MonthlyAvrgTemp[i] = monthlytotaltemp / counter;
        printf("average for this month is %lf", MonthlyAvrgTemp[i]);
        monthlytotaltemp = 0;
        counter = 0;

    }

    // for (int i = 1680; i < ROWS; i++) // Index 1680 starts at the beginning of year 1900
    // {
    //     for (int j = 0; j < 12; j++) // Inner loops produces average temperature for each month
    //     {
    //         MonthlyAvrgTemp[j] += LandAvrgTemp[i];
    //         printf("The monthly average temp is %lf", );
    //         i += 12;
    //     }
        
    // }
}

int main(void)
{
    assignArrays();
    printArrays();
    q1();
    q3();
    return (0);
}

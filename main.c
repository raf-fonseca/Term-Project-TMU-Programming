
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ROWS 3192
#define COLS 11

// Declare the arrays to store the data
char dates[ROWS][COLS];
double LandAvrgTemp[ROWS]; //
double LandAvrgTempUncertainty[ROWS];
double LandMaxTemp[ROWS];
double LandMaxTempUncertainty[ROWS];
double LandMinTemp[ROWS];
double LandMinTempUncertainty[ROWS];
double LandAndOceanAvrgTemp[ROWS];
double LandAndOceanAvrgTempUncertainty[ROWS];

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

void q1()
{
    // Q1 calculate the yearly averages for each year between 1760 and 2015
}
int main(void)
{
    assignArrays();
    printArrays();
    return (0);
}

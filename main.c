
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ROWS 3192
#define COLS 11
#define YEARROWS 256 // (ROWS - index of year 1760) / 12 months

// Declare the arrays to store the data
char dates[ROWS][COLS];
char years[YEARROWS][COLS];
double LandAvrgTemp[ROWS];
double LandAvrgTempUncertainty[ROWS];
double LandMaxTemp[ROWS];
double LandMaxTempUncertainty[ROWS];
double LandMinTemp[ROWS];
double LandMinTempUncertainty[ROWS];
double LandAndOceanAvrgTemp[ROWS];
double LandAndOceanAvrgTempUncertainty[ROWS];
double YearlyLandAvrgTemp[YEARROWS];
double MonthlyAvrgTemp[12];
char month[12][10] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
char YearString[ROWS];
int YearInt[ROWS];

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

void q1() // Calculate yearly average for each year between 1760 and 2015
{
    int counter = 0;
    double yearlytotaltemp = 0;
    int j = 0; // j is the tracker variable for each years[]'s element
    FILE *q6 = fopen("q6.txt", "w");
    for (int i = 120; i < ROWS; i++) // Index 120 starts at the beginning of year 1760
    {
        yearlytotaltemp += LandAvrgTemp[i];
        counter++;

        if (counter == 12) // Assigns an average yearly temperature and resets the counter after every 12 months
        {
            strncpy(years[j], dates[i], 4);
            YearlyLandAvrgTemp[j] = yearlytotaltemp / 12;
            printf("The average temperature for the year %s is %lf degrees Celsius.\n", years[j], YearlyLandAvrgTemp[j]);
            fprintf(q6, "%s %lf\n", years[j], YearlyLandAvrgTemp[j]);
            counter = 0;
            yearlytotaltemp = 0;
            j++;
        }
    }
}

void q2()
{ // Calculate the average land temperature for the different centuries
    char century[4][5] = {"18th", "19th", "20th", "21th"};
    double centuryTotals[4] = {0, 0, 0, 0};
    double centuryCounter[4] = {0, 0, 0, 0};
    double centuryAvrgTemp[4];

    for (int i = 120; i < ROWS; i++)
    {
        strncpy(YearString, dates[i], 4);
        YearInt[i] = atoi(YearString);
        if (YearInt[i] >= 1760 && YearInt[i] < 1800)
        {
            centuryTotals[0] += LandAvrgTemp[i];
            centuryCounter[0]++;
        }
        else if (YearInt[i] >= 1800 && YearInt[i] < 1900)
        {
            centuryTotals[1] += LandAvrgTemp[i];
            centuryCounter[1]++;
        }
        else if (YearInt[i] >= 1900 && YearInt[i] < 2000)
        {
            centuryTotals[2] += LandAvrgTemp[i];
            centuryCounter[2]++;
        }
        else if (YearInt[i] >= 2000 && YearInt[i] < 2100)
        {
            centuryTotals[3] += LandAvrgTemp[i];
            centuryCounter[3]++;
        }
    }
    for (int i = 0; i < 4; i++)
    {
        centuryAvrgTemp[i] = centuryTotals[i] / centuryCounter[i];
        printf("The average temperature for the %s century is %.5lf degrees Celsius.\n", century[i], centuryAvrgTemp[i]);
    }
}

void q3() // Calculate monthly averages for all years between 1900 and 2015
{
    double monthlytotaltemp = 0;
    int counter = 0;
    int j;

    for (int i = 0; i < 12; i++) // Outer loop iterates for each month
    {
        for (j = 1680 + i; j < ROWS; j += 12) // Index 1680 starts at the beginning of year 1900 plus the current month, inner loop assigns value to each month element
        {
            monthlytotaltemp += LandAvrgTemp[j];
            counter++;
        }
        MonthlyAvrgTemp[i] = monthlytotaltemp / counter;
        printf("The average temperature for %s is %lf degrees Celsius.\n", month[i], MonthlyAvrgTemp[i]);
        monthlytotaltemp = 0; // Counter and total monthly accumulation resets after all iterations of the specific month ends
        counter = 0;
    }
}

void q4()
{ // What was the hottest month recorded and what was the coldest month recorded? Ignore ties
    double coldest = LandAvrgTemp[0];
    double hottest = LandAvrgTemp[0];
    char *hottestDate = malloc(7);
    char *coldestDate = malloc(7);
    for (int i = 120; i < ROWS; i++)
    {
        if (coldest > LandAvrgTemp[i])
        {
            coldest = LandAvrgTemp[i];
            strncpy(coldestDate, dates[i], 7);
        }
        if (hottest < LandAvrgTemp[i])
        {
            hottest = LandAvrgTemp[i];
            strncpy(hottestDate, dates[i], 7);
        }
    }
    printf("The hottest month recorded is %s and its temperature is %.2lf˚\n", hottestDate, hottest);
    printf("The coldest month recorded is %s and its temperature is %.2lf˚\n", coldestDate, coldest);
}

void q5() // Determine the hottest and coldest year between 1760 and 2015
{
    double coldtemp = YearlyLandAvrgTemp[0]; // Hot and cold temperatures are intially set as the first element in the array
    double hottemp = YearlyLandAvrgTemp[0];
    char hotyear[5], coldyear[5];

    for (int i = 0; i < YEARROWS; i++) // The hot and cold temperature values update with each iteration of loop
    {
        if (hottemp < YearlyLandAvrgTemp[i])
        {
            hottemp = YearlyLandAvrgTemp[i];
            strncpy(hotyear, years[i], 5);
        }
        if (coldtemp > YearlyLandAvrgTemp[i])
        {
            coldtemp = YearlyLandAvrgTemp[i];
            strncpy(coldyear, years[i], 5);
        }
    }
    printf("The hottest year is %s and its average temperature is %lf degrees Celsius.\nThe coldest year is %s and its average temperature is %lf degrees Celsius.", hotyear, hottemp, coldyear, coldtemp);
}

int main(void)
{
    assignArrays();
    // printArrays();
    q1();
    // q2();
    // q3();
    // q4();
    // q5();
    return (0);
}

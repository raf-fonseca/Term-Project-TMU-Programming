#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ROWS 3192
#define COLS 11
#define YEARROWS 266 // (ROWS - index of year 1760) / 12 months (index of 1760 is 120)

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
double YearlyLandAvrgTemp[YEARROWS]; // Starts at year 1760
double MonthlyAvrgTemp[12];
char month[12][10] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
char YearString[ROWS];
int YearInt[ROWS];

// Function to read data from a CSV file and assign it to various arrays
void assignArrays()
{
    // Open the CSV file for reading
    FILE *fp = fopen("GlobalTemperatures.csv", "r");
    // Check if the file was opened successfully
    if (fp == NULL)
    {
        printf("Failed to open file.\n");
        return; // Exit the function if file cannot be opened
    }

    char line[1000]; // Array to hold each line of the file

    // Loop through each row of the file
    // Start with row = -1 to skip the header of the CSV
    for (int row = -1; row < ROWS; row++)
    {
        fgets(line, 1000, fp);           // Read a line from the file
        char *token = strtok(line, ","); // Use strtok to split the line into tokens based on commas
        int col = 0;                     // Column index

        // Check if the current row is the header
        if (row == -1)
        {
            continue; // Skip the rest of the loop if it's the header
        }

        // Process each token (column) in the line
        while (token != NULL)
        {
            // Use a switch statement to assign the token to the correct array based on the column index
            switch (col)
            {
            case 0: // Date
                strcpy(dates[row], token);
                break;
            case 1: // Average Land Temperature
                LandAvrgTemp[row] = atof(token);
                break;
            case 2: // Land Average Temperature Uncertainty
                LandAvrgTempUncertainty[row] = atof(token);
                break;
            case 3: // Maximum Land Temperature
                LandMaxTemp[row] = atof(token);
                break;
            case 4: // Maximum Land Temperature Uncertainty
                LandMaxTempUncertainty[row] = atof(token);
                break;
            case 5: // Minimum Land Temperature
                LandMinTemp[row] = atof(token);
                break;
            case 6: // Minimum Land Temperature Uncertainty
                LandMinTempUncertainty[row] = atof(token);
                break;
            case 7: // Average Land and Ocean Temperature
                LandAndOceanAvrgTemp[row] = atof(token);
                break;
            case 8: // Land and Ocean Average Temperature Uncertainty
                LandAndOceanAvrgTempUncertainty[row] = atof(token);
                break;
            }
            token = strtok(NULL, ","); // Move to the next token in the line
            col++;                     // Increment the column index for the next token
        }
    }

    fclose(fp); // Close the file after reading all lines
}

// Calculate the yearly average of an array
void YearlyAvgCalculator(double *inputArray, double *outputArray)
{
    double yearlytotaltemp = 0;
    int counter = 0;
    int j = 0;
    int noDataCounter = 0;
    for (int i = 0; i < ROWS; i++) // Index 120 starts at the beginning of year 1760
    {
        yearlytotaltemp += inputArray[i];
        counter++;

        if (inputArray[i] == 0)
        {
            noDataCounter++;
        }
        if (counter == 12) // Assigns an average yearly temperature and resets the counter after every 12 months
        {
            if (noDataCounter == 12)
            {
                outputArray[j] = 0;
            }
            else
            {
                outputArray[j] = yearlytotaltemp / (12 - noDataCounter);
            }

            // printf("The average temperature for the year %s is %lf degrees Celsius.\n", years[j], YearlyLandAvrgTemp[j]);
            counter = 0;
            yearlytotaltemp = 0;
            j++; // Increment the tracker variable
            noDataCounter = 0;
        }
    }
}

// Calculate yearly average for each year between 1760 and 2015
void q1()
{

    for (int i = 10; i < YEARROWS; i++) // Index 10 starts at the beginning of year 1760, and goes on till 2015
    {
        printf("The average temperature for the year %d is %lf degrees Celsius.\n", (i + 1750), YearlyLandAvrgTemp[i]); // Print the average temperature for each year
    }
}

// Calculate the average land temperature for the different centuries
void q2()
{
    // Define century names for easy reference
    char century[4][5] = {"18th", "19th", "20th", "21th"};
    // Initialize total temperature sums for each century to 0
    double centuryTotals[4] = {0, 0, 0, 0};
    // Initialize counters for the number of temperature records per century
    double centuryCounter[4] = {0, 0, 0, 0};
    // Array to store the calculated average temperatures for each century
    double centuryAvrgTemp[4];

    // Loop through all rows starting from index 120 (assumed start year of 1760)
    for (int i = 120; i < ROWS; i++)
    {
        // Extract the year from the dates array and convert it to an integer
        strncpy(YearString, dates[i], 4);
        YearInt[i] = atoi(YearString);
        // Determine the century of the current year and accumulate the total temperature and count
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
    // Calculate and print the average temperature for each century
    for (int i = 0; i < 4; i++)
    {
        // Calculate the average by dividing the total by the count
        centuryAvrgTemp[i] = centuryTotals[i] / centuryCounter[i];
        // Print the calculated average temperature for the century
        printf("The average temperature for the %s century is %lf degrees Celsius.\n", century[i], centuryAvrgTemp[i]);
    }
}

// Calculate monthly averages for all years between 1900 and 2015
void q3()
{
    double monthlytotaltemp = 0; // Variable to store the total temperature for each month
    int counter = 0;             // Counter to keep track of the number of records for each month
    int j;

    for (int i = 0; i < 12; i++) // Outer loop iterates for each month
    {
        for (j = 1800 + i; j < ROWS; j += 12) // Index 1800 starts at the beginning of year 1900 plus the current month, inner loop assigns value to each month element
        {
            monthlytotaltemp += LandAvrgTemp[j]; // Accumulates the total temperature for the specific month
            counter++;                           // Increments the counter for the specific month
        }
        MonthlyAvrgTemp[i] = monthlytotaltemp / counter;                                                  // Assigns the average temperature to the respective month
        printf("The average temperature for %s is %lf degrees Celsius.\n", month[i], MonthlyAvrgTemp[i]); // Print the average temperature for each month
        monthlytotaltemp = 0;                                                                             // Counter and total monthly accumulation resets after all iterations of the specific month ends
        counter = 0;
    }
}

// Determine the hottest and coldest month
void q4()
{
    // Initialize the coldest and hottest temperatures to the first temperature in the dataset
    double coldest = LandAvrgTemp[0];
    double hottest = LandAvrgTemp[0];
    // Allocate memory for the hottest and coldest dates
    char *hottestDate = malloc(7);
    char *coldestDate = malloc(7);

    // Iterate through the dataset starting from the 120th index (assuming data relevant to the query starts here)
    for (int i = 120; i < ROWS; i++)
    {
        // Update the coldest temperature and its date if a new minimum is found
        if (coldest > LandAvrgTemp[i])
        {
            coldest = LandAvrgTemp[i];
            strncpy(coldestDate, dates[i], 7); // Copy the date of the coldest temperature
        }
        // Update the hottest temperature and its date if a new maximum is found
        if (hottest < LandAvrgTemp[i])
        {
            hottest = LandAvrgTemp[i];
            strncpy(hottestDate, dates[i], 7); // Copy the date of the hottest temperature
        }
    }

    // Print the results
    printf("The hottest month recorded is %s and its temperature is %.2lf˚\n", hottestDate, hottest);
    printf("The coldest month recorded is %s and its temperature is %.2lf˚\n", coldestDate, coldest);
}

// Determine the hottest and coldest year
void q5()
{
    // Initialize the coldest and hottest temperatures to the first year's average temperature
    double coldtemp = YearlyLandAvrgTemp[0];
    double hottemp = YearlyLandAvrgTemp[0];
    // Initialize variables to store the hottest and coldest year, starting from the base year of 1750
    int hotYear, coldYear;

    // Iterate through the YearlyLandAvrgTemp array to find the hottest and coldest years
    for (int i = 0; i < YEARROWS; i++)
    {
        // If the current year's temperature is higher than the current hottest, update hottemp and hotYear
        if (hottemp < YearlyLandAvrgTemp[i])
        {
            hottemp = YearlyLandAvrgTemp[i]; // Update the hottest temperature
            hotYear = i + 1750;              // Calculate the year based on the index and base year
        }
        // If the current year's temperature is lower than the current coldest, update coldtemp and coldYear
        if (coldtemp > YearlyLandAvrgTemp[i])
        {
            coldtemp = YearlyLandAvrgTemp[i]; // Update the coldest temperature
            coldYear = i + 1750;              // Calculate the year based on the index and base year
        }
    }
    // Print the hottest and coldest years with their corresponding average temperatures
    printf("The hottest year is %d and its average temperature is %lf degrees Celsius.\nThe coldest year is %d and its average temperature is %lf degrees Celsius.", hotYear, hottemp, coldYear, coldtemp);
}

// Graph (line plot) of the yearly temperatures for the years 1760 to 2015
void q6()
{
    FILE *q6 = fopen("q6.txt", "w"); // Open the file for writing

    for (int i = 10; i < YEARROWS; i++) // Index 10 starts at the beginning of year 1760
    {
        fprintf(q6, "%d %lf\n", (i + 1750), YearlyLandAvrgTemp[i]); // Print x and y values for the yearly temperature
    }
    fclose(q6); // Close the file
}

// Separate the yearly temperatures into two files for the 19th and 20th centuries
void q7()
{

    FILE *century19th = fopen("century19th.txt", "w"); // Open the file for writing
    FILE *century20th = fopen("century20th.txt", "w");
    for (int i = 50; i < YEARROWS; i++) // Index 50 starts at the beginning of year 1800
    {
        // Assigns the average yearly temperature to the respective century file
        if (i >= 50 && i <= 149)
        {
            fprintf(century19th, "%d %lf\n", (i - 49), YearlyLandAvrgTemp[i]); // Print x and y values for the yearly temperature for 19th century
        }
        else if (i >= 150 && i <= 249)
        {
            fprintf(century20th, "%d %lf\n", (i - 149), YearlyLandAvrgTemp[i]); // Print x and y values for the yearly temperature for 19th century
        }
    }

    fclose(century19th); // Close the file
    fclose(century20th);
}

// Average land temperature, land max temperature, land min temperature for each year between 1850 and 2015
void q8()
{
    double YearlyLandMaxTemp[YEARROWS];                  // Array to store the yearly maximum temperatures
    double YearlyLandMinTemp[YEARROWS];                  // Array to store the yearly minimum temperatures
    YearlyAvgCalculator(LandMaxTemp, YearlyLandMaxTemp); // Calculate the yearly maximum temperatures
    YearlyAvgCalculator(LandMinTemp, YearlyLandMinTemp); // Calculate the yearly minimum temperatures

    FILE *q8 = fopen("q8.txt", "w"); // Open the file for writing

    for (int i = 100; i < YEARROWS; i++) // Index 100 starts at the beginning of year 1850
    {
        fprintf(q8, "%d %lf %lf %lf\n", (i + 1750), YearlyLandAvrgTemp[i], YearlyLandMaxTemp[i], YearlyLandMinTemp[i]); // Print x and y values for the yearly temperature, maximum, and minimum
    }
    fclose(q8); // Close the file
}

// Show the average, low and high temperatures for each of the 19th (after 1850), 20th and 21st centuries.
void q9()
{
    int counter = 0;        // Counter to keep track of the number of records for each century
    double totAvrgTemp = 0; // Variable to store the total avrg temperature for each century
    double totMaxTemp = 0;  // Variable to store the total max temperature for each century
    double totMinTemp = 0;  // Variable to store the total min temperature for each century

    double avrgTemp; // Variable to store the avrg temperature for each century
    double maxTemp;  // Variable to store the max temperature for each century
    double minTemp;  // Variable to store the min temperature for each century

    FILE *q9 = fopen("q9.txt", "w");

    for (int i = 12 * (1850 - 1750); i < 12 * (1901 - 1750); i++)
    {
        totAvrgTemp += LandAvrgTemp[i];
        totMaxTemp += LandMaxTemp[i];
        totMinTemp += LandMinTemp[i];
        counter++;
    }

    avrgTemp = totAvrgTemp / counter;
    maxTemp = totMaxTemp / counter;
    minTemp = totMinTemp / counter;
    fprintf(q9, "%lf %lf %lf\n", avrgTemp, maxTemp, minTemp);
    avrgTemp = 0;
    maxTemp = 0;
    minTemp = 0;

    for (int i = 12 * (1901 - 1750); i < 12 * (2001 - 1750); i++) // 1812 is the index of the year 1901
    {
        totAvrgTemp += LandAvrgTemp[i];
        totMaxTemp += LandMaxTemp[i];
        totMinTemp += LandMinTemp[i];
        counter++;
    }

    avrgTemp = totAvrgTemp / counter;
    maxTemp = totMaxTemp / counter;
    minTemp = totMinTemp / counter;
    fprintf(q9, "%lf %lf %lf\n", avrgTemp, maxTemp, minTemp);
    avrgTemp = 0;
    maxTemp = 0;
    minTemp = 0;

    for (int i = 12 * (2001 - 1750); i < 12 * (2016 - 1750); i++) // 3012 is the index of the year 2001
    {
        totAvrgTemp += LandAvrgTemp[i];
        totMaxTemp += LandMaxTemp[i];
        totMinTemp += LandMinTemp[i];
        counter++;
    }

    avrgTemp = totAvrgTemp / counter;
    maxTemp = totMaxTemp / counter;
    minTemp = totMinTemp / counter;

    fprintf(q9, "%lf %lf %lf\n", avrgTemp, maxTemp, minTemp);
    avrgTemp = 0;
    maxTemp = 0;
    minTemp = 0;

    fclose(q9);
}

// Calculate the average temperature and uncertainty for each month (2000 - 2015)
void q10()
{
    FILE *q10 = fopen("q10.txt", "w");

    double monthlytotaltemp = 0; // Variable to store the total temperature for each month

    double monthlytotaluncertainty = 0;
    int bounter = 0;
    int k = 0; // Q10 variable
    double MonthlyUncertaintyTemp[ROWS];

    for (int i = 3000; i < ROWS; i++)
    {

        fprintf(q10, "%d %lf %lf\n", 1 + bounter, LandAvrgTemp[i], LandAvrgTempUncertainty[i]);
        bounter++;
    }
    fclose(q10);
}

// Calculate the yearly average land and ocean temperatures for each year between 1850 and 2015
void q11()
{
    double YearlyLandAndOceanAvrgTemp[YEARROWS];                           // Array to store the yearly average land and ocean temperatures
    FILE *q11 = fopen("q11.txt", "w");                                     // Open the file for writing
    YearlyAvgCalculator(LandAndOceanAvrgTemp, YearlyLandAndOceanAvrgTemp); // Calculate the yearly average land and ocean temperatures
    for (int i = 100; i < YEARROWS; i++)                                   // Index 100 starts at the beginning of year 1850
    {
        fprintf(q11, "%d %lf %lf\n", (i + 1750), YearlyLandAvrgTemp[i], YearlyLandAndOceanAvrgTemp[i]); // Print x and y values for the yearly temperature and average land and ocean temperature
    }
    fclose(q11); // Close the file
}

int main(void)
{
    assignArrays();
    YearlyAvgCalculator(LandAvrgTemp, YearlyLandAvrgTemp);
    // q1();
    // q2();
    // q3();
    // q4();
    // q5();
    // q6();
    // q7();
    // q8();
    // q9();
    // q10();
    // q11();

    return (0);
}
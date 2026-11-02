#include <stdio.h>
#define MAXC 50
void inputReadings(float temp[][MAXC], int sensors, int hours){
    int i, j;
    for (i = 0; i < sensors; i++){
        for (j = 0; j < hours; j++)
        {
            printf("Sensor %d, Hour %d: ", i + 1, j + 1);
            scanf("%f", &temp[i][j]);
        }
    }
}
float analyzeSensor(float r[], int hours, int id){
    int j;
    float total = 0, avg;
    float high = r[0], low = r[0];
    int critical = 0, warning = 0;
    int streak = 0, longest = 0;
    for (j = 0; j < hours; j++){
        total = total + r[j];
        if (r[j] > high) high = r[j];
        if (r[j] < low)  low = r[j];
        if (r[j] >= 40)
            critical++;
        else if (r[j] >= 35)
            warning++;
        if (r[j] >= 35){
            streak++;
            if (streak > longest)
                longest = streak;
        }
        else
            streak = 0;
    }
    avg = total / hours;
    printf("\n--- Sensor %d Report ---\n", id);
    printf("Total: %.2f\n", total);
    printf("Average: %.2f\n", avg);
    printf("Highest: %.2f\n", high);
    printf("Lowest: %.2f\n", low);
    printf("Critical readings: %d\n", critical);
    printf("Warning readings: %d\n", warning);
    printf("Longest streak (>=35): %d hours\n", longest);
    return avg;
}
int highestAverage(float avgs[], int sensors){
    int i, best = 0;
    for (i = 1; i < sensors; i++)
        if (avgs[i] > avgs[best])
            best = i;
    return best;
}
int main(){
    float temp[50][MAXC];
    float avgs[50];
    int sensors, hours, i, best;
    printf("Enter number of sensors: ");
    scanf("%d", &sensors);
    printf("Enter number of readings per sensor: ");
    scanf("%d", &hours);
    inputReadings(temp, sensors, hours);
    for (i = 0; i < sensors; i++)
        avgs[i] = analyzeSensor(temp[i], hours, i + 1);
    best = highestAverage(avgs, sensors);
    printf("\nSensor with highest average: %d (Average = %.2f)\n", best + 1, avgs[best]);
    return 0;
}

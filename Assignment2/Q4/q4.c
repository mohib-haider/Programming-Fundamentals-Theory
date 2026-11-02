#include <stdio.h>
int getValidDays(){
    int d;
    do{
        printf("Enter number of festival days (1-7): ");
        scanf("%d", &d);
        if (d < 1 || d > 7)
            printf("Invalid! Try again.\n");
    } while (d < 1 || d > 7);
    return d;
}
float calculateDailySales(int dayNumber){
    int orders, i;
    float amount, total = 0, highest = 0;
    printf("\nDay %d - Number of orders: ", dayNumber);
    scanf("%d", &orders);
    for (i = 1; i <= orders; i++){
        do{
            printf("Order %d amount: ", i);
            scanf("%f", &amount);
            if (amount <= 0)
                printf("Amount must be greater than zero.\n");
        } while (amount <= 0);
        total = total + amount;
        if (amount > highest)
            highest = amount;
    }
    printf("Day %d Total: Rs. %.2f\n", dayNumber, total);
    printf("Day %d Average: Rs. %.2f\n", dayNumber, total / orders);
    printf("Day %d Highest: Rs. %.2f\n", dayNumber, highest);
    return total;
}
int findHighestSalesDay(float dailySales[], int numberOfDays){
    int i, best = 0;
    for (i = 1; i < numberOfDays; i++)
        if (dailySales[i] > dailySales[best])
            best = i;
    return best + 1;
}
void displayBarChart(float dailySales[], int numberOfDays){
    int i, j, stars;
    printf("\nDaily Sales Bar Chart:\n");
    for (i = 0; i < numberOfDays; i++)
    {
        stars = (int)(dailySales[i] / 100);
        printf("Day %d: ", i + 1);
        for (j = 0; j < stars; j++)
            printf("*");
        printf("\n");
    }
}
int main(){
    float dailySales[7];
    float festivalTotal = 0;
    int days, i;
    days = getValidDays();
    for (i = 0; i < days; i++){
        dailySales[i] = calculateDailySales(i + 1);
        festivalTotal = festivalTotal + dailySales[i];
    }
    printf("\nTotal festival sales: Rs. %.2f\n", festivalTotal);
    printf("Day with highest sales: Day %d\n", findHighestSalesDay(dailySales, days));
    displayBarChart(dailySales, days);
    return 0;
}

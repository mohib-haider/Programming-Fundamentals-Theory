#include <stdio.h>
int main(){
    int seats[50][50];
    int rows, cols,count;
    int i, j, k;
    int total = 0;
    int rowFree[50];
    int mid, d, t, r;
    int found = 0;
    int foundRow = -1, startSeat = -1;
    printf("Enter number of rows: ");
    scanf("%d", &rows);
    printf("Enter seats per row: ");
    scanf("%d", &cols);
    printf("Enter seating status (0 = free, 1 = booked):\n");
    for (i = 0; i < rows; i++)
        for (j = 0; j < cols; j++)
            scanf("%d", &seats[i][j]);
    for (i = 0; i < rows; i++){
        rowFree[i] = 0;
        for (j = 0; j < cols; j++)
            if (seats[i][j] == 0)
                rowFree[i]++;
        total = total + rowFree[i];
    }
    printf("\nSeating Arrangement:\n");
    printf("   ");
    for (j = 0; j < cols; j++)
        printf("%d ", j);
    printf("\n");
    for (i = 0; i < rows; i++){
        printf("R%d ", i);
        for (j = 0; j < cols; j++)
            printf(seats[i][j] == 0 ? "_ " : "X ");
        printf("\n");
    }
    printf("\nFree seats per row: ");
    for (i = 0; i < rows; i++)
        printf("%d ", rowFree[i]);
    printf("  Total free: %d\n", total);
    printf("\nEnter number of customers (k): ");
    scanf("%d", &k);
    if (k <= 0 || k > cols){
        printf("Invalid group size!\n");
        return 0;
    }
    mid = rows / 2;
    for (d = 0; d < rows && !found; d++){
        for (t = 0; t < 2 && !found; t++){
            if (t == 0)
                r = mid - d;
            else
                r = mid + d;
            if (t == 1 && d == 0)
                continue;
            if (r < 0 || r >= rows)
                continue;
            count = 0;
            for (j = 0; j < cols && !found; j++){
                if (seats[r][j] == 0)
                    count++;
                else
                    count = 0;
                if (count == k){
                    found = 1;
                    foundRow = r;
                    startSeat = j - k + 1;
                }
            }
        }
    }
    if (found){
        for (j = startSeat; j < startSeat + k; j++)
            seats[foundRow][j] = 1;
        printf("\nGroup of %d seated in Row %d, Seats %d to %d\n",
               k, foundRow, startSeat, startSeat + k - 1);
        printf("\nUpdated Seating Arrangement:\n   ");
        for (j = 0; j < cols; j++)
            printf("%d ", j);
        printf("\n");
        for (i = 0; i < rows; i++){
            printf("R%d ", i);
            for (j = 0; j < cols; j++)
                printf(seats[i][j] == 0 ? "_ " : "X ");
            printf("\n");
        }
        printf("\nRemaining free seats: %d\n", total - k);
    }
    else{
        printf("\nNo %d consecutive seats available. Seating plan unchanged.\n", k);
    }
    return 0;
}

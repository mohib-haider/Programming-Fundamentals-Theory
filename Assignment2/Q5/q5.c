#include <stdio.h>
#include <string.h>
void displayMenu(){
    printf("\n===== LIBRARY MENU =====\n");
    printf("1. Register Member\n");
    printf("2. Display Available Books\n");
    printf("3. Borrow a Book\n");
    printf("4. Return a Book\n");
    printf("5. Display Member Record\n");
    printf("6. Exit\n");
    printf("Enter choice: ");
}
void registerMember(char name[], int *studentID, int *memberType){
    printf("Enter name: ");
    scanf(" %[^\n]", name);
    printf("Enter student ID: ");
    scanf("%d", studentID);
    do{
        printf("Membership type (1 = Student, 2 = Faculty): ");
        scanf("%d", memberType);
        if (*memberType != 1 && *memberType != 2)
            printf("Invalid membership type!\n");
    } while (*memberType != 1 && *memberType != 2);
}
void displayBooks(int bookIDs[], char bookTitles[][50], int availableCopies[], int totalBooks){
    int i;
    printf("\n%-5s %-30s %s\n", "ID", "Title", "Copies");
    for (i = 0; i < totalBooks; i++)
        printf("%-5d %-30s %d\n", bookIDs[i], bookTitles[i], availableCopies[i]);
}
void borrowBook(int bookIDs[], char bookTitles[][50], int availableCopies[], int totalBooks,
                int borrowedBookIDs[], int *borrowedCount, int memberType){
    int id, days, i, index = -1;
    int limit = (memberType == 1) ? 14 : 30;
    if (*borrowedCount >= 3){
        printf("You already borrowed 3 books. Return one first.\n");
        return;
    }
    printf("Enter book ID: ");
    scanf("%d", &id);
    for (i = 0; i < totalBooks; i++)
        if (bookIDs[i] == id)
            index = i;
    if (index == -1){
        printf("Invalid book ID!\n");
        return;
    }
    if (availableCopies[index] == 0){
        printf("Sorry, no copies available.\n");
        return;
    }
    do{
        printf("Number of days you want to keep it: ");
        scanf("%d", &days);
        if (days <= 0)
            printf("Days must be positive.\n");
    } while (days <= 0);
    borrowedBookIDs[*borrowedCount] = id;
    (*borrowedCount)++;
    availableCopies[index]--;
    printf("You borrowed \"%s\". Allowed period: %d days.\n", bookTitles[index], limit);
}
float returnBook(int bookIDs[], int availableCopies[], int totalBooks, int borrowedBookIDs[],
                 int *borrowedCount, int memberType, float *totalFine){
    int id, days, i, pos = -1, index = -1, limit, extra;
    float fine = 0, payable;
    char code[20];
    printf("Enter book ID to return: ");
    scanf("%d", &id);
    for (i = 0; i < *borrowedCount; i++)
        if (borrowedBookIDs[i] == id)
            pos = i;
    if (pos == -1){
        printf("You have not borrowed this book!\n");
        return 0;
    }
    do{
        printf("Actual days kept: ");
        scanf("%d", &days);
        if (days <= 0)
            printf("Days must be positive.\n");
    } while (days <= 0);
    for (i = 0; i < totalBooks; i++)
        if (bookIDs[i] == id)
            index = i;
    availableCopies[index]++;
    limit = (memberType == 1) ? 14 : 30;
    if (days > limit){
        extra = days - limit;
        if (memberType == 1)
            fine = extra * 20;
        else
            fine = extra * 10;
    }
    payable = fine;
    if (fine > 0){
        printf("Late fine: Rs. %.2f\n", fine);
        printf("Enter membership code: ");
        scanf("%s", code);
        if (strcmp(code, "LIB2026") == 0)
        {
            payable = fine * 0.5;
            printf("Code accepted. Fine after waiver: Rs. %.2f\n", payable);
        }
        else
            printf("Wrong code. No waiver.\n");
    }
    else
        printf("Returned on time. No fine.\n");
    *totalFine = *totalFine + fine;
    for (i = pos; i < *borrowedCount - 1; i++)
        borrowedBookIDs[i] = borrowedBookIDs[i + 1];
    (*borrowedCount)--;
    return payable;
}
void displayMemberRecord(char name[], int studentID, int memberType, int borrowedBookIDs[],
                         int borrowedCount, float totalFine, float fineAfterWaiver){
    int i;
    printf("\nName: %s\nStudent ID: %d\n", name, studentID);
    printf("Type: %s\n", memberType == 1 ? "Student" : "Faculty");
    printf("Currently borrowed book IDs: ");
    if (borrowedCount == 0)
        printf("None");
    for (i = 0; i < borrowedCount; i++)
        printf("%d ", borrowedBookIDs[i]);
    printf("\nTotal fine before waiver: Rs. %.2f\n", totalFine);
    printf("Final fine payable: Rs. %.2f\n", fineAfterWaiver);
}
int main(){
    int bookIDs[5] = {101, 102, 103, 104, 105};
    char bookTitles[5][50] = {"C Programming", "Data Structures", "Discrete Math", "Physics", "English Grammar"};
    int availableCopies[5] = {3, 2, 1, 4, 2};
    int totalBooks = 5;
    char name[50] = "";
    int studentID = 0, memberType = 0;
    int borrowedBookIDs[3], borrowedCount = 0;
    float totalFine = 0, fineAfterWaiver = 0;
    int registered = 0;
    int choice;
    do{
        displayMenu();
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            registerMember(name, &studentID, &memberType);
            registered = 1;
            break;
        case 2:
            displayBooks(bookIDs, bookTitles, availableCopies, totalBooks);
            break;
        case 3:
            if (!registered) printf("Please register first.\n");
            else borrowBook(bookIDs, bookTitles, availableCopies, totalBooks,
                            borrowedBookIDs, &borrowedCount, memberType);
            break;
        case 4:
            if (!registered) printf("Please register first.\n");
            else fineAfterWaiver += returnBook(bookIDs, availableCopies, totalBooks,
                            borrowedBookIDs, &borrowedCount, memberType, &totalFine);
            break;
        case 5:
            if (!registered) printf("Please register first.\n");
            else displayMemberRecord(name, studentID, memberType, borrowedBookIDs,
                            borrowedCount, totalFine, fineAfterWaiver);
            break;
        case 6:
            printf("Goodbye!\n");
            break;
        default:
            printf("Invalid choice!\n");
        }
    } while (choice != 6);
    return 0;
}

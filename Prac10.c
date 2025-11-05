#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Function declarations
int SSTF();
int SCAN();
int CLOOK();

int main() {
    int ch, YN = 1;

    do {
        printf("\n\n\t*********** MENU ***********");
        printf("\n\n\t1: SSTF");
        printf("\n\n\t2: SCAN");
        printf("\n\n\t3: C-LOOK");
        printf("\n\n\t4: EXIT");
        printf("\n\n\tEnter your choice: ");
        scanf("%d", &ch);

        switch (ch) {
            case 1:
                SSTF();
                break;
            case 2:
                SCAN();
                break;
            case 3:
                CLOOK();
                break;
            case 4:
                exit(0);
            default:
                printf("\nInvalid choice! Please try again.\n");
        }

        printf("\n\n\tDo you want to continue?");
        printf("\n\tIf YES press 1");
        printf("\n\tIf NO press 0: ");
        scanf("%d", &YN);

    } while (YN == 1);

    return 0;
}

// ============================
// SSTF Algorithm
// ============================
int SSTF() {
    int RQ[100], i, n, TotalHeadMovement = 0, initial, count = 0;
    printf("\n--- SSTF Disk Scheduling Algorithm ---\n");
    printf("Enter the number of Requests: ");
    scanf("%d", &n);
    printf("Enter the Requests sequence:\n");

    for (i = 0; i < n; i++) {
        scanf("%d", &RQ[i]);
    }

    printf("Enter initial head position: ");
    scanf("%d", &initial);

    while (count != n) {
        int min = 1000, d, index = -1;
        for (i = 0; i < n; i++) {
            if (RQ[i] != 1000) {
                d = abs(RQ[i] - initial);
                if (min > d) {
                    min = d;
                    index = i;
                }
            }
        }
        TotalHeadMovement += min;
        initial = RQ[index];
        RQ[index] = 1000;
        count++;
    }

    printf("\nTotal head movement is %d\n", TotalHeadMovement);
    return 0;
}

// ============================
// SCAN Algorithm
// ============================
int SCAN() {
    int RQ[100], i, j, n, TotalHeadMovement = 0, initial, size, move;

    printf("\n--- SCAN Disk Scheduling Algorithm ---\n");
    printf("Enter the number of Requests: ");
    scanf("%d", &n);

    printf("Enter the Requests sequence:\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &RQ[i]);
    }

    printf("Enter initial head position: ");
    scanf("%d", &initial);
    printf("Enter total disk size: ");
    scanf("%d", &size);
    printf("Enter the head movement direction (for high = 1, for low = 0): ");
    scanf("%d", &move);

    // Sort the request queue
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (RQ[j] > RQ[j + 1]) {
                int temp = RQ[j];
                RQ[j] = RQ[j + 1];
                RQ[j + 1] = temp;
            }
        }
    }

    int index = 0;
    for (i = 0; i < n; i++) {
        if (initial < RQ[i]) {
            index = i;
            break;
        }
    }

    if (move == 1) { // Move right
        for (i = index; i < n; i++) {
            TotalHeadMovement += abs(RQ[i] - initial);
            initial = RQ[i];
        }
        TotalHeadMovement += abs((size - 1) - RQ[n - 1]);
        initial = size - 1;
        for (i = index - 1; i >= 0; i--) {
            TotalHeadMovement += abs(RQ[i] - initial);
            initial = RQ[i];
        }
    } else { // Move left
        for (i = index - 1; i >= 0; i--) {
            TotalHeadMovement += abs(RQ[i] - initial);
            initial = RQ[i];
        }
        TotalHeadMovement += abs(RQ[0] - 0);
        initial = 0;
        for (i = index; i < n; i++) {
            TotalHeadMovement += abs(RQ[i] - initial);
            initial = RQ[i];
        }
    }

    printf("\nTotal head movement is %d\n", TotalHeadMovement);
    return 0;
}

// ============================
// C-LOOK Algorithm
// ============================
int CLOOK() {
    int RQ[100], i, j, n, TotalHeadMovement = 0, initial, size, move;

    printf("\n--- C-LOOK Disk Scheduling Algorithm ---\n");
    printf("Enter the number of Requests: ");
    scanf("%d", &n);

    printf("Enter the Requests sequence:\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &RQ[i]);
    }

    printf("Enter initial head position: ");
    scanf("%d", &initial);
    printf("Enter total disk size: ");
    scanf("%d", &size);
    printf("Enter the head movement direction (for high = 1, for low = 0): ");
    scanf("%d", &move);

    // Sort the request queue
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (RQ[j] > RQ[j + 1]) {
                int temp = RQ[j];
                RQ[j] = RQ[j + 1];
                RQ[j + 1] = temp;
            }
        }
    }

    int index = 0;
    for (i = 0; i < n; i++) {
        if (initial < RQ[i]) {
            index = i;
            break;
        }
    }

    if (move == 1) { // Move right
        for (i = index; i < n; i++) {
            TotalHeadMovement += abs(RQ[i] - initial);
            initial = RQ[i];
        }
        for (i = 0; i < index; i++) {
            TotalHeadMovement += abs(RQ[i] - initial);
            initial = RQ[i];
        }
    } else { // Move left
        for (i = index - 1; i >= 0; i--) {
            TotalHeadMovement += abs(RQ[i] - initial);
            initial = RQ[i];
        }
        for (i = n - 1; i >= index; i--) {
            TotalHeadMovement += abs(RQ[i] - initial);
            initial = RQ[i];
        }
    }

    printf("\nTotal head movement is %d\n", TotalHeadMovement);
    return 0;
}

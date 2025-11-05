parent.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void bubbleSort(int arr[], int n) {
    int i, j, temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    int n, i;

    printf("Enter the number of integers to be sorted: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter the integers to be sorted: ");
    for (i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    pid_t pid = fork();

    if (pid < 0) {
        printf("Fork failed!\n");
        return 1;
    } 
    else if (pid == 0) {
        // Child process - execute child program with the array as arguments
        char *args[n + 2];
        args[0] = "./child";

        for (i = 0; i < n; i++) {
            char *arg = (char *)malloc(20);
            sprintf(arg, "%d", arr[i]);
            args[i + 1] = arg;
        }

        args[n + 1] = NULL;

        execve(args[0], args, NULL);
        perror("execve failed");
        return 1;
    } 
    else {
        // Parent process - sort the array
        printf("Parent process (PID: %d) sorting the integers...\n", getpid());
        bubbleSort(arr, n);

        printf("Parent process (PID: %d) sorted integers: ", getpid());
        for (i = 0; i < n; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");

        wait(NULL); // Wait for child to finish
    }

    return 0;
}

child.c

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void bubbleSort(int arr[], int n) {
    int i, j, temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main(int argc, char *argv[]) {
    int n = argc - 1;
    int arr[n];

    for (int i = 0; i < n; i++) {
        arr[i] = atoi(argv[i + 1]);
    }

    printf("Child process (PID: %d) sorting the integers...\n", getpid());
    bubbleSort(arr, n);

    printf("Child process (PID: %d) sorted integers: ", getpid());
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}

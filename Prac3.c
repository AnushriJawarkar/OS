File 1: parent.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1]) {
                int t = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = t;
            }
}

int main() {
    int n, i;
    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter %d integers:\n", n);
    for (i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    // Sort array in parent
    sort(arr, n);

    pid_t pid = fork();

    if (pid == 0) {
        // Child process
        char *args[n + 2];
        args[0] = "./child";

        for (i = 0; i < n; i++) {
            char *num = malloc(10);
            sprintf(num, "%d", arr[i]);
            args[i + 1] = num;
        }
        args[n + 1] = NULL;

        execve(args[0], args, NULL);
        perror("execve failed");
        exit(1);
    } 
    else if (pid > 0) {
        wait(NULL);
        printf("Parent process finished.\n");
    } 
    else {
        perror("fork failed");
        exit(1);
    }

    return 0;
}


File 2: child.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    printf("\nChild process (PID: %d)\n", getpid());
    printf("Array in reverse order:\n");
    
    for (int i = argc - 1; i > 0; i--) {
        printf("%s ", argv[i]);
    }
    printf("\n");
    return 0;
}


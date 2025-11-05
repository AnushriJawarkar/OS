Server.c 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHMSZ 25

int main() {
    int shmid, cnt = 0;
    key_t key;
    char *shm, *s;
    char str[SHMSZ];

    key = 5678;

    // Create the shared memory segment
    if ((shmid = shmget(key, SHMSZ, IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        exit(1);
    }

    // Attach the segment to our data space
    if ((shm = (char *)shmat(shmid, NULL, 0)) == (char *)-1) {
        perror("shmat");
        exit(1);
    }

    s = shm;

    // Writing message to shared memory
    printf("Enter message from Server to Client: ");
    fgets(str, sizeof(str), stdin);

    for (cnt = 0; str[cnt] != '\0'; cnt++) {
        *s++ = str[cnt];
    }
    *s = '\0'; // Null terminate string in shared memory

    printf("Message written to shared memory successfully.\n");

    // Detach from shared memory
    shmdt(shm);

    return 0;
}

Client.c
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>

#define SHMSZ 25

int main() {
    int shmid;
    key_t key;
    char *shm, *s;

    key = 5678; // Same key as used by the server

    // Locate the segment created by server
    if ((shmid = shmget(key, SHMSZ, 0666)) < 0) {
        perror("shmget");
        exit(1);
    }

    // Attach the segment to our data space
    if ((shm = (char *)shmat(shmid, NULL, 0)) == (char *)-1) {
        perror("shmat");
        exit(1);
    }

    printf("Client reading data from Server:\n");

    // Read from shared memory
    for (s = shm; *s != '\0'; s++) {
        putchar(*s);
    }
    printf("\n");

    // Detach from shared memory
    shmdt(shm);

    // Remove the shared memory segment
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}


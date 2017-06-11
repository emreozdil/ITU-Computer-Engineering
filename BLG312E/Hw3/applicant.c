//
//  applicant.c
//  OS-Hw2
//
//  Created by Emre Özdil on 12/05/2017.
//  Copyright © 2017 Emre Özdil. All rights reserved.
//

#define _GNU_SOURCE
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>
#include <pthread.h>

#define HRKEY 67623
#define KEY 123321

// Semaphore wait function to decrement the semaphore value
void sem_wait1(int semid, int val)
{
    struct sembuf semaphore;
    semaphore.sem_num = 0;
    semaphore.sem_op = (-1*val);
    semaphore.sem_flg = 1;
    semop(semid, &semaphore, 1);
}

// Semaphore signal function to increment the semaphore value
void sem_signal(int semid, int val)
{
    struct sembuf semaphore;
    semaphore.sem_num = 0;
    semaphore.sem_op = val;
    semaphore.sem_flg = 1;
    semop(semid, &semaphore, 1);
}


int main(int argc, char ** argv) {
    // read applicants count from terminal
    int applicantsCount = atoi(argv[1]);
    
    // control semaphor between applicant.c and hr.c
    int semaphoreHr;
    semaphoreHr = semget(HRKEY, 1, 0700 | IPC_CREAT);
    semctl(semaphoreHr, 0, SETVAL, 0);
    
    // shared memory
    int statusId = shmget(KEY, (sizeof(int)* applicantsCount), 0700 | IPC_CREAT);
    int *status;
    status = shmat(statusId, 0, 0);
    
    // fork
    int f;
    int index;
    for (index = 0; index < applicantsCount; index++)
    {
        f = fork();
        if(f == -1)
        {
            printf("FORK ERROR\n");
            exit(1);
        }
        if(f == 0)
        break;
    }
    sem_signal(semaphoreHr, 1);
    
    return 0;
}

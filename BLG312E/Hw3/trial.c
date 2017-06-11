//
//  trial.c
//  OS-Hw2
//
//  Created by Emre Özdil on 13/04/2017.
//  Copyright © 2017 Emre Özdil. All rights reserved.
//

#define _GNU_SOURCE
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>

#define HRKEY 67623
#define KEY 123321
#define TRAINERSEMKEY 3456
#define TRAINERKEY 2344
#define SEMKEY1 4321
#define SEMKEY2 8765
#define MAX 100

int *status;
int *trainingSet;
int indis;                           // Global variables for indis
int trainerCount;
int s1,s2,applicantNumber;          // Global variables for semaphores, applicantNumber, nr
int applicants[MAX][2];                   // Global pointer for shared applicants
int semaphoreTrainer;
int trainID;
FILE * inputFile;                           // input file

void sem_wait1(int semid, int val){          // decrement the semaphore value
    struct sembuf semaphore;
    semaphore.sem_num = 0;
    semaphore.sem_op = (-1*val);
    semaphore.sem_flg = 1;
    semop(semid, &semaphore, 1);
}

void sem_signal(int semid, int val){        // increment the semaphore value
    struct sembuf semaphore;
    semaphore.sem_num = 0;
    semaphore.sem_op = val;
    semaphore.sem_flg = 1;
    semop(semid, &semaphore, 1);
}
void * trainer(void * typ){      // Thread function
    //printf("trainer \n");
    
    int localTrainID = trainingSet[trainID];
    trainID++;
    int trainTime;
    applicantNumber++;
    int applicantID;
    // loop for come to trainer applicants
    while (applicantNumber <= trainerCount){
        sem_signal(s1, 1);
        applicantID = applicantNumber;
        trainTime= applicants[applicantID-1][0];
        printf("Trainer %d started training with Applicant %d (status of applicant %d: %d)\n", localTrainID, applicantID, applicantID, 2);
        sem_wait1(s1, 1);
        sleep(trainTime);
        if(applicants[applicantID - 1][1] == 0){
            status[applicantID - 1] = 3;}
        else{
            status[applicantID - 1] = 4;}
        printf("Trainer %d finished training with Applicant %d (status of applicant %d: %d)\n", localTrainID, applicantID, applicantID, status[applicantID - 1]);
        applicantNumber++;
    }
    
    pthread_exit(NULL);
}


int main(int argc, char ** argv) {
    
    sleep(3);
    semaphoreTrainer = semget(TRAINERSEMKEY, 1, 0);
    sem_wait1(semaphoreTrainer, 1);

    //printf("Trainer is beginned\n");
    
    applicantNumber = 0;
    trainID = 0;
    
    indis = 0;
    
    inputFile = fopen(argv[1], "r+");       // Open the file
    if (!inputFile) {
        printf("File not found");
        return EXIT_FAILURE;
    }
    
    rewind(inputFile);                  // Take the cursor on the beginning
    int delayTime;
    fscanf(inputFile, "%d",&delayTime);
    // printf("Registration time is: %d seconds\n", delayTime);
    indis = 0;
    trainerCount = 0;
    int irrelevantInterviewTime;
    int trainingTime;
    int irrelevantpassInterview;
    int passTraining;
    
    // read file for trainers
    while (fscanf(inputFile, "%d %d %d %d", &irrelevantInterviewTime, &trainingTime, &irrelevantpassInterview, &passTraining)!=EOF) {
        sem_wait1(s2,1);
        applicants[indis][0] = trainingTime;
        applicants[indis][1] = passTraining;
        trainerCount += passTraining;
        indis++;
        sem_signal(s2,1);
    }
    
    int statusId = shmget(KEY, (sizeof(int)* indis), 0700 | IPC_CREAT);
    
    status = shmat(statusId, 0, 0);
    
    int trainerSetId = shmget(TRAINERKEY, (sizeof(int)* trainerCount), 0700 | IPC_CREAT);
    
    trainingSet = shmat(trainerSetId, 0, 0);
    
    // THREAD 4 trainers
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    setvbuf(stdout, (char*)NULL, _IONBF, 0);
    pthread_t * trainerThread = malloc(4 * sizeof(pthread_t));
    int train;
    int trainerID;
    for (trainerID = 1; trainerID < 5; trainerID++) {         // Creating threads
        train = pthread_create(&trainerThread[trainerID], &attr, trainer, (void *)trainerID);
        if(train){
            printf("\n Error: Thread not created");
            exit(EXIT_FAILURE);
        }
    }
    pthread_attr_destroy(&attr);
    
    
    for (trainerID = 1; trainerID < 5; trainerID++) {
        train = pthread_join(trainerThread[trainerID], NULL);
        if(train){
            printf("\n Error: Thread not joined");
            exit(EXIT_FAILURE);
        }
    }
    
    fclose(inputFile);
    semctl(s1,0,IPC_RMID,0);
    semctl(s2,0,IPC_RMID,0);
    printf("Training process is done.\n");

    return 0;
}

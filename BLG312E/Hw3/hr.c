//
//  hr.c
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
#define SEMKEY1 1234
#define SEMKEY2 5678
#define TRAINERSEMKEY 3456
#define TRAINERKEY 2344
#define MAX 100

int *status;
int *trainingSet;
int indis;                           // Global variables for indis
int s1,s2,applicantNumber,trainerNumber;          // Global variables for semaphores, applicantNumber, nr
int applicants[MAX][2];                   // Global pointer for shared applicants
int semaphoreTrain;
int interID;
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

// Thread  interviewer function
void * interviewer(void * typ){
    interID++;
    int localinterID = interID;
    int interviewTime;
    applicantNumber++;
    int applicantID;
    while (applicantNumber <= indis){
        applicantID = applicantNumber;
        interviewTime= applicants[applicantID-1][0];
        // wait next applicant
        sem_signal(s1, 1);
        printf("Applicant %d’s registeration is done (status of applicant %d: %d)\n", applicantID, applicantID, 0);
        if(applicantID == indis)
        	printf("Registration process is done.\n");
        printf("Interviewer %d started interview with Applicant %d (status of applicant %d: %d)\n", localinterID, applicantID, applicantID, 0);
        sem_wait1(s1, 1);
        sleep(interviewTime);
        if(applicants[applicantID - 1][1] == 0)
            status[applicantID - 1] = 1;
        else
            status[applicantID - 1] = 2;
        printf("Interviewer %d finished interview with Applicant %d (status of applicant %d: %d)\n", localinterID, applicantID, applicantID, status[applicantID - 1]);
        if(applicantID == indis)
        	printf("Interview process is done.\n");
        
        if (status[applicantID - 1] == 2)
        {
            trainingSet[trainerNumber] = applicantID;
            sem_signal(semaphoreTrain,1);
            trainerNumber++;
        }
        applicantNumber++;
    }
    pthread_exit(NULL);
}

// Thread receptionist function
void* receptionist(void* typ){
    int delayTime;
    fscanf(inputFile, "%d",&delayTime);
    printf("Registration time is: %d seconds\n", delayTime);
    indis = 0;
    int interviewTime;
    int irrelevantTrainingTime;
    int passInterview;
    int irrelevantPassTraining;
    
    int trainerCount = 0;
    // read the file
    while (fscanf(inputFile, "%d %d %d %d", &interviewTime, &irrelevantTrainingTime, &passInterview, &irrelevantPassTraining)!=EOF) {
        sem_wait1(s2,1);
        applicants[indis][0] = interviewTime;
        applicants[indis][1] = passInterview;
        trainerCount += irrelevantPassTraining;
        indis++;
        sem_signal(s2,1);
        printf("Applicant %d applied to the receptionist (status of applicant %d: %d)\n", indis, indis, 0); 
        sleep(delayTime);   
    }
    
    int shmid = shmget(KEY, (sizeof(int)* indis), 0700 | IPC_CREAT);
    
    status = shmat(shmid, 0, 0);
    
    int trainerSetId = shmget(TRAINERKEY, (sizeof(int)* trainerCount), 0700 | IPC_CREAT);
    
    trainingSet = shmat(trainerSetId, 0, 0);

    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    setvbuf(stdout, (char*)NULL, _IONBF, 0);

    pthread_t * interviewThread = malloc(3*sizeof(pthread_t));
    int interview;
    int interviewerID;

    // Creating threads
    for (interviewerID = 1; interviewerID < 4; interviewerID++) {

        interview = pthread_create(&interviewThread[interviewerID], &attr, interviewer, (void *)interviewerID);
        if(interview){
            printf("\n Error: Thread not created");
            exit(EXIT_FAILURE);
        }
    }

    pthread_attr_destroy(&attr);


    for (interviewerID = 1; interviewerID < 4; interviewerID++) {
        interview = pthread_join(interviewThread[interviewerID], NULL);
        if(interview){
            printf("\n Error: Thread not joined");
            exit(EXIT_FAILURE);
        }
    }
    pthread_exit(NULL);
}



int main(int argc, char * argv[]) {

    sleep(1);

    int semaphoreHr;
    semaphoreHr = semget(HRKEY, 1, 0);
    sem_wait1(semaphoreHr, 1);
    
    semaphoreTrain = semget(TRAINERSEMKEY, 1, 0700 | IPC_CREAT);
    semctl(semaphoreTrain, 0, SETVAL, 0);
    // printf("Hr is beginned\n");
    
    applicantNumber = 0;
    interID = 0;
    trainerNumber = 0;
    
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    setvbuf(stdout, (char*)NULL, _IONBF, 0);
    indis = 0;
    int rcptn;

    // Open the file
    inputFile = fopen(argv[1], "r+");
    if (!inputFile) {
        printf("File not found");
        return EXIT_FAILURE;
    }

    s1 = semget(SEMKEY1, 1, 0700|IPC_CREAT);
    semctl(s1, 0, SETVAL, 1);

    s2 = semget(SEMKEY2, 1, 0700|IPC_CREAT);
    semctl(s2, 0, SETVAL, 1);

    // Take the cursor on the beginning
    rewind(inputFile);
    pthread_t reception;
    int i = 0;
    rcptn = pthread_create(&reception, &attr, receptionist, (void *)i);
    if(rcptn) {
        printf("\n Error: Thread not created");
        exit(EXIT_FAILURE);
    }

    pthread_attr_destroy(&attr);
    rcptn = pthread_join(reception, NULL);
    if(rcptn){
        printf("\n Error: Thread not joined");
        exit(EXIT_FAILURE);
    }
    fclose(inputFile);
    semctl(s1,0,IPC_RMID,0);
    semctl(s2,0,IPC_RMID,0);
    return 0;
}

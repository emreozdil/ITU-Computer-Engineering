//
//  main.c
//  OS-Hw2
//
//  Created by Emre Özdil on 13/04/2017.
//  Copyright © 2017 Emre Özdil. All rights reserved.
//

#define _GNU_SOURCE
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SEMKEY1 1234
#define SEMKEY2 5678
#define MAX 100

int indis,i;
int s1,s2,applicantNumber,nr;          // Global variables for semaphores, question number, member number
int applicants[MAX];                   // Global pointer for shared question sheet

int interID;
FILE * inputFile;                           // Global pointer for input file

void sem_wait1(int semid, int val){          // Semaphore wait function to decrement the semaphore value
    struct sembuf semaphore;
    semaphore.sem_num = 0;
    semaphore.sem_op = (-1*val);
    semaphore.sem_flg = 1;
    semop(semid, &semaphore, 1);
}

void sem_signal(int semid, int val){        // Semaphore signal function to increment the semaphore value
    struct sembuf semaphore;
    semaphore.sem_num = 0;
    semaphore.sem_op = val;
    semaphore.sem_flg = 1;
    semop(semid, &semaphore, 1);
}
void * interviewer(int intID, void * typ){                  // Thread function
    interID++;
    int localinterID = interID;
    int waitTime = applicants[applicantNumber];
    applicantNumber++;
    int applicantID;
    while (applicantNumber <= indis){
        //sem_wait1(s1, 1);
        applicantID = applicantNumber;
        printf("Applicant %d’s registeration is done\n", applicantID);
        sem_signal(s1, 1);
        sem_wait1(s1, 1);
        
        printf("Interviewer %d started interview with Applicant %d\n", localinterID, applicantID);
        sem_signal(s1, 1);
        sleep(waitTime);
        printf("Interviewer %d finished interview with Applicant %d\n", localinterID, applicantID);
        applicantNumber++;
    }
    sem_signal(s1, 1);
    

    pthread_exit(NULL);
}

void* receptionist(void* typ){                  // Thread function
    
    indis = 0;
    int waitTime;
    while (fscanf(inputFile, "%d",&waitTime)==1) {
        sem_wait1(s2,1);
        applicants[indis] = waitTime;
        indis++;
        sem_signal(s2,1);
        printf("Applicant %d applied to the receptionist\n", indis);
        sleep(nr);
    }
    
    // When one thread get in the checking section it makes the next thread get in too.
    pthread_attr_t attr;                // thread attribute initilaziton to join them
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    setvbuf(stdout, (char*)NULL, _IONBF, 0);                    // No buffer to write outputs to console

    pthread_t * interviewThread = malloc(3*sizeof(pthread_t));
    int interview;
    int interviewerID;
    
    for (interviewerID = 1; interviewerID < 4; interviewerID++) {         // Creating threads
        sem_wait1(s1, 1);
        interview = pthread_create(&interviewThread[interviewerID], &attr, interviewer, (void *)interviewerID);
    
        sem_signal(s1, 1);
        if(interview){
            printf("\n Error: Thread not created");
            exit(EXIT_FAILURE);
        }
    }
    sem_wait1(s2, 1);
    
    printf("All applicants have interviewed successfully.\n");
    sem_signal(s2, 1);
    pthread_attr_destroy(&attr);        // We dont need attr value anymore
    
    
    for (interviewerID = 1; interviewerID < 4; interviewerID++) {
        interview = pthread_join(interviewThread[interviewerID], NULL);    // such as free, fclose, semctl
        // We pause execution of main until all threads finish their jobs
        if(interview){
            printf("\n Error: Thread not joined");
            exit(EXIT_FAILURE);
        }
    }
    
    pthread_exit(NULL);
}



int main(int argc, char * argv[]) {
    nr = 1;
    //nr = atoi(argv[2]);           // read the member number from command line
    
    applicantNumber = 0;
    interID = 0;
    pthread_attr_t attr;                // thread attribute initilaziton to join them
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    setvbuf(stdout, (char*)NULL, _IONBF, 0);                    // No buffer to write outputs to console
    indis = 0;
    int rcptn;
    
    //inputFile = fopen(argv[1], "r+");       // Open the file in main function
    inputFile = fopen("input.txt", "r+");
    if (!inputFile) {
        printf("File not found");
        return EXIT_FAILURE;
    }
    
    
    s1 = semget(SEMKEY1, 1, 0700|IPC_CREAT);            // Create s1 semaphore for sync
    semctl(s1, 0, SETVAL, 1);
    
    s2 = semget(SEMKEY2, 1, 0700|IPC_CREAT);            // Create s2 semaphore for mutex
    semctl(s2, 0, SETVAL, 1);
    
    rewind(inputFile);                  // Take the cursor to beginning
    pthread_t reception;
    int x =0;
    rcptn = pthread_create(&reception, &attr, receptionist, (void *)x);
    if(rcptn) {
        printf("\n Error: Thread not created");
        exit(EXIT_FAILURE);
    }
    
    pthread_attr_destroy(&attr);        // We dont need attr value anymore
    rcptn = pthread_join(reception, NULL);    // such as free, fclose, semctl
    // We pause execution of main until all threads finish their jobs
    if(rcptn){
        printf("\n Error: Thread not joined");
        exit(EXIT_FAILURE);
    }
    
    fclose(inputFile);
    
    semctl(s1,0,IPC_RMID,0);            // Delete semaphores
    semctl(s2,0,IPC_RMID,0);
    
    return 0;
}

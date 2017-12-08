#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/unistd.h>

static const char * names = "/NAMES";
static const char * codes = "/CODES";
static const char * hey = "/05";
static const char * txt = ".txt";
static const char * code = "code:";
static const char * neighbourhood = "neighbourhood:";
static const char * city = "city:";
static const char * district = "district:";
static const char * latitude = "latitude:";
static const char * longitude = "longitude:";


struct code{
	char code[15];
	char inputOfTxt[50000];
	struct code* next;
};

struct plate {
	char plate[4];
	struct plate* next;
    struct code* headCode;
};

struct neighbourhood{
	char neighbourhood[40];
	char inputOfTxt[500];
	struct neighbourhood* next;
};

struct district {
	char district[25];
	char districtPath[50];
	struct district* next;
	struct neighbourhood* headNeighbourhood;
};

struct city {
	char city[20];
	struct city* next;
	struct district* headDistrict;
};

struct address {
    char code[6];
    char neighbourhood[35];
    char city[20];
    char district[25];
    char latitude[10];
    char longitude[10];
    char codePath[50];
    char cityPath[120];
    char inputOfTxt[300];
    char plate[4];
    struct address* next;
    struct plate* headPlate;
    struct city* headCity;
};


struct address* head;
struct plate* headPlate;
struct city* headCity;
struct district* headDistrict;
struct neighbourhood* headNeighbourhood;
struct code* headCode;

struct address* readFile() {
	printf("Read File Function STARTS\n");
    FILE *input;
    if ((input = fopen("postal-codes.csv", "r")) == NULL)
        puts("File cannot open.");

    struct address* traverse = NULL;
    struct plate* traversePlate = NULL;
    struct city* traverseCity = NULL;
    struct district* traverseDistrict = NULL;
    struct neighbourhood* traverseNeighbourhood = NULL;
    struct code* traverseCode = NULL;

    int i = 0, j;
    struct stat st = {0};
    FILE *fp;
    
    while(!feof(input)) {
        struct address* newNode = malloc(sizeof(struct address));
        struct plate* newPlate = malloc(sizeof(struct plate));
        struct city* newCity = malloc(sizeof(struct city));
        struct district* newDistrict = malloc(sizeof(struct district));
        struct neighbourhood* newNeighbourhood = malloc(sizeof(struct neighbourhood));
        struct code* newCode = malloc(sizeof(struct code));
        newNode->next = NULL;
        newPlate->next = NULL;
        newCity->next = NULL;
        newDistrict->next = NULL;
        newNeighbourhood->next = NULL;
        newCode->next = NULL;

        i++;
        fscanf(input, "%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t %s\n", newNode->code, newNode->neighbourhood, newNode->city, newNode->district, newNode->latitude, newNode->longitude);

        for (j = 0; j < strlen(newNode->neighbourhood); ++j) {
            if(newNode->neighbourhood[j] == '/'){
                newNode->neighbourhood[j] = '-';
            }
        }

        strcpy(newNode->inputOfTxt, code);
        strcat(newNode->inputOfTxt, newNode->code);
        strcat(newNode->inputOfTxt, "\n");
        strcat(newNode->inputOfTxt, neighbourhood);
        strcat(newNode->inputOfTxt, newNode->neighbourhood);
        strcat(newNode->inputOfTxt, "\n");
        strcat(newNode->inputOfTxt, city);
        strcat(newNode->inputOfTxt, newNode->city);
        strcat(newNode->inputOfTxt, "\n");
        strcat(newNode->inputOfTxt, district);
        strcat(newNode->inputOfTxt, newNode->district);
        strcat(newNode->inputOfTxt, "\n");
        strcat(newNode->inputOfTxt, latitude);
        strcat(newNode->inputOfTxt, newNode->latitude);
        strcat(newNode->inputOfTxt, "\n");
        strcat(newNode->inputOfTxt, longitude);
        strcat(newNode->inputOfTxt, newNode->longitude);
        strcat(newNode->inputOfTxt, "\n");
        strcat(newNode->inputOfTxt, "\n\0");

        char plate[4];
        plate[0] = '/';
        plate[1] = newNode->code[0];
        plate[2] = newNode->code[1];
        plate[3] = '\0';

        strcpy(newPlate->plate, plate);

        char code[15];
        strcpy(code, "/");
        strcat(code, newNode->code);
        strcat(code, txt);
        strcpy(newCode->code, code);
        strcpy(newCode->inputOfTxt, newNode->inputOfTxt);

        if (headPlate == NULL){
        	headCode = newCode;
        	traverseCode = headCode;
        	headPlate = newPlate;
        	headPlate->headCode = headCode;
        	traversePlate = headPlate;
        }
        else if(strcmp(newPlate->plate, traversePlate->plate) != 0){
        	newPlate->headCode = newCode;
        	traverseCode = newPlate->headCode;
            traversePlate->next = newPlate;
            traversePlate = traversePlate->next;
        }
        else if(strcmp(newCode->code, traverseCode->code) != 0){
            traverseCode->next = newCode;
            traverseCode = traverseCode->next;
        }
        else{
        	strcat(traverseCode->inputOfTxt, newCode->inputOfTxt);
        }

        char city[20];
        strcpy(city, "/");
        strcat(city, newNode->city);
        strcpy(newCity->city, city);

        char district[25];
        char districtPath[50];
        strcpy(district, "/");
        strcat(district, newNode->district);
        strcpy(newDistrict->district, district);

        strcpy(districtPath, names);
        strcat(districtPath, "/");
        strcat(districtPath, newNode->city);
        strcat(districtPath, "/");
        strcat(districtPath, newNode->district);
        strcpy(newDistrict->districtPath, districtPath);

        char neighbourhood[40];
        strcpy(neighbourhood, "/");
        strcat(neighbourhood, newNode->neighbourhood);
        strcat(neighbourhood, txt);
        strcpy(newNeighbourhood->neighbourhood, neighbourhood);

        strcpy(newNeighbourhood->inputOfTxt, newNode->inputOfTxt);

        if (headCity == NULL){
        	headNeighbourhood = newNeighbourhood;
        	traverseNeighbourhood = headNeighbourhood;
        	headDistrict = newDistrict;
        	headDistrict->headNeighbourhood = headNeighbourhood;
        	traverseDistrict = headDistrict;
        	headCity = newCity;
        	headCity->headDistrict = headDistrict;
        	traverseCity = headCity;
        }
        else if(strcmp(newCity->city, traverseCity->city) != 0){
        	newDistrict->headNeighbourhood = newNeighbourhood;
        	traverseNeighbourhood = newDistrict->headNeighbourhood;
        	newCity->headDistrict = newDistrict;
        	traverseDistrict = newCity->headDistrict;
            traverseCity->next = newCity;
            traverseCity = traverseCity->next;
        } 
        else if(strcmp(newDistrict->district, traverseDistrict->district) != 0){
        	newDistrict->headNeighbourhood = newNeighbourhood;
        	traverseNeighbourhood = newDistrict->headNeighbourhood;
            traverseDistrict->next = newDistrict;
            traverseDistrict = traverseDistrict->next;
        }
        else if(strcmp(newNeighbourhood->neighbourhood, traverseNeighbourhood->neighbourhood) != 0){
        	traverseNeighbourhood->next = newNeighbourhood;
            traverseNeighbourhood = traverseNeighbourhood->next;
        }
        else{
        	strcat(traverseNeighbourhood->inputOfTxt, newNeighbourhood->inputOfTxt);
        }

        strcpy(newNode->plate, plate);
        if (head == NULL) {
            head = newNode;
            head->headPlate = headPlate;
            head->headCity = headCity;
            traverse = head;
        }

        else {
            traverse->next = newNode;
            traverse = traverse->next;
        }
    }
    

    printf("Read File Function ENDS\n");
    return head;
}

void writeFile() {
	printf("Write File Function STARTS\n");
    struct address* traverse;
    FILE *fp;
    traverse = head;
    fp = fopen("newPostalCodes.csv", "w+");
    if(!fp){
            printf("Can not open the file\n");
    }
    while(traverse) {
    	fprintf(fp, "%s\t%s\t%s\t%s\t%s\t%s\n", traverse->code, traverse->neighbourhood, traverse->city, traverse->district, traverse->latitude, traverse->longitude);
    	traverse = traverse->next;
    }
    fclose(fp);
    printf("Write File Function ENDS\n");
}



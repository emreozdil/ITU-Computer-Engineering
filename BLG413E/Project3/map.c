#define FUSE_USE_VERSION 26

#include <fuse.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/unistd.h>
#include <unistd.h>
#include "readWriteLibrary.c"

struct address* headMap;

static int map_getattr(const char *path, struct stat *stbuf)
{
	printf("MAP: GETATTR FUNCTION STARTS\n");
    int res = 0;
    int i, countOfSubfolder = 0;
    for (i=0; path[i]; i++){
    	if(path[i] == '/'){
    		countOfSubfolder += 1;
    	}
    }
    memset(stbuf, 0, sizeof(struct stat));

    if (strcmp(path, "/") == 0) {
    	printf("MAP: GETATTR ROOT FUNCTION\n");
        stbuf->st_mode = S_IFDIR | 0755;
        stbuf->st_nlink = 2;
    }
    else if (strcmp(path, names) == 0){
    	printf("MAP: GETATTR NAMES FUNCTION \n");
    	stbuf->st_mode = S_IFDIR | 0755;
        stbuf->st_nlink = 3;

    }
    else if(strcmp(path, codes) == 0){
    	printf("MAP: GETATTR CODES FUNCTION \n");
    	stbuf->st_mode = S_IFDIR | 0755;
        stbuf->st_nlink = 3;
    }
    else if(countOfSubfolder == 2){
    	printf("MAP: GETATTR NAMES & CODES SUBFOLDER \n");
    	stbuf->st_mode = S_IFDIR | 0755;
        stbuf->st_nlink = 2;
    }
    else if(countOfSubfolder == 3 && strstr(path, codes) != NULL){
    	printf("MAP: GETATTR CODES CODES TXT \n");
    	stbuf->st_mode = S_IFREG | 0444;
        stbuf->st_nlink = 1;
        stbuf->st_size = 50000;
    }
    else if(countOfSubfolder == 3){
    	printf("MAP: GETATTR CODES subfolder \n");
    	stbuf->st_mode = S_IFDIR | 0755;
        stbuf->st_nlink = 2;
    }
    else if(countOfSubfolder == 4){
    	printf("MAP: GETATTR NAMES TXT \n");
    	stbuf->st_mode = S_IFREG | 0444;
        stbuf->st_nlink = 1;
        stbuf->st_size = 500;
    }
    else
        res = -ENOENT;
    printf("MAP: GETATTR FUNCTION ENDS\n");
    return res;
}

static int map_readdir(const char *path, void *buf, fuse_fill_dir_t filler,
                         off_t offset, struct fuse_file_info *fi)
{
	printf("MAP: READDIR FUNCTION STARTS\n");
    (void) offset;
    (void) fi;
    int i, countOfSubfolder = 0;
    for (i=0; path[i]; i++){
    	if(path[i] == '/'){
    		countOfSubfolder += 1;
    	}
    }
	if (strcmp(path, "/") == 0){
   		printf("MAP: READDIR FUNCTION ROOT\n");
		filler(buf, names + 1, NULL, 0);
		filler(buf, codes + 1, NULL, 0);
   	}
   	else  if (strcmp(path, names) == 0){
   		printf("MAP: READDIR FUNCTION NAMES\n");
   		struct city* traverse = headMap->headCity;
   		while(traverse){
   			filler(buf, traverse->city + 1, NULL, 0);
   			traverse = traverse->next;
   			printf("traverse\n");
   		}
   	}
   	else  if (strcmp(path, codes) == 0){
   		printf("MAP: READDIR FUNCTION CODES\n");
   		struct plate* traverse = headMap->headPlate;
   		while(traverse){
   			filler(buf, traverse->plate + 1, NULL, 0);
   			traverse = traverse->next;
   			printf("traverse\n");
   		}
   	}
   	else  if (strstr(path, codes) != NULL && countOfSubfolder == 2 ){
   		printf("MAP: READDIR FUNCTION CODES TXT\n");
   		struct plate* traverse = headMap->headPlate;
   		while(traverse){
   			if (strstr(path, traverse->plate) != NULL) {
   				struct code* traverseCode = traverse->headCode;
	   			while(traverseCode){
					filler(buf, traverseCode->code + 1, NULL, 0);
	   				traverseCode = traverseCode->next;
	   			}
   			}
   			traverse = traverse->next;
   		}
   	}
   	else  if (strstr(path, names) != NULL && countOfSubfolder == 2){
   		printf("MAP: READDIR FUNCTION CODES\n");
   		struct city* traverse = headMap->headCity;
   		while(traverse){
   			if (strstr(path, traverse->city) != NULL) {
   				struct district* traverseDistrict = traverse->headDistrict;
   				struct district* compareDistrict = malloc(sizeof(struct district));
   				struct district* headCompare = NULL;
   				struct district* copmTrav = NULL;
   				int count = 0;
	   			while(traverseDistrict){
	   				struct district* temp = malloc(sizeof(struct district));
	   				strcpy(temp->district, traverseDistrict->district);
	   				temp->next = NULL;
	   				int comp = 0;
	   				headCompare = compareDistrict;
	   				if (count == 0) {
	   					compareDistrict = temp;
	   					copmTrav = compareDistrict;
	   					headCompare = compareDistrict;
	   					filler(buf, traverseDistrict->district + 1, NULL, 0);
	   				}
	   				while(headCompare) {
	   					if (strcmp(headCompare->district, traverseDistrict->district) == 0) {
	   						comp++;
	   					}
	   					headCompare = headCompare->next;
	   				}
	   				if (count) {
	   					copmTrav->next = temp;
	   					copmTrav = copmTrav->next;
	   				}
	   				if(comp == 0) {
	   					filler(buf, traverseDistrict->district + 1, NULL, 0);
	   				}
	   				traverseDistrict = traverseDistrict->next;
	   				count++;
	   			}
   			}
   			traverse = traverse->next;
   		}
   	}
   	else if (strstr(path, names) != NULL && countOfSubfolder == 3){
   		printf("MAP: READDIR FUNCTION NAMES TXT\n");
   		struct city* traverse = headMap->headCity;
   		while(traverse){
   			if (strstr(path, traverse->city) != NULL) {
   				struct district* traverseDistrict = traverse->headDistrict;
	   			while(traverseDistrict){
					if (strstr(path, traverseDistrict->districtPath) != NULL) {
   						struct neighbourhood* traverseNeighbourhood = traverseDistrict->headNeighbourhood;
   						while(traverseNeighbourhood){
   							filler(buf, traverseNeighbourhood->neighbourhood + 1, NULL, 0);
   							traverseNeighbourhood = traverseNeighbourhood->next;
   						}
   					}
	   				traverseDistrict = traverseDistrict->next;
	   			}
   			}
   			traverse = traverse->next;
   		}
   	}
   	else
   		return -ENOENT;
    printf("MAP: READDIR FUNCTION ENDS\n");
    return 0;
}

static int map_open(const char *path, struct fuse_file_info *fi)
{
	printf("MAP: OPEN FUNCTION STARTS\n");
	printf("PATH = %s \n", path);
    if ((fi->flags & 3) != O_RDONLY)
        return -EACCES;
    printf("MAP: OPEN FUNCTION ENDS\n");
    return 0;
}

static int map_read(const char *path, char *buf, size_t size, off_t offset,
                      struct fuse_file_info *fi)
{
	printf("MAP: READ FUNCTION STARTS\n");
    size_t len;
    (void) fi;
   	if (strstr(path, names) != NULL){
   		struct city* traverse = headMap->headCity;
   		while(traverse){
   			if (strstr(path, traverse->city) != NULL) {
   				struct district* traverseDistrict = traverse->headDistrict;
	   			while(traverseDistrict){
					if (strstr(path, traverseDistrict->districtPath) != NULL) {
   						struct neighbourhood* traverseNeighbourhood = traverseDistrict->headNeighbourhood;
   						while(traverseNeighbourhood){
	   							if (strstr(path, traverseNeighbourhood->neighbourhood) != NULL){
	   							len = strlen(traverseNeighbourhood->inputOfTxt);
								if (offset < len) {
						    		if (offset + size > len)
						        		size = len - offset;
						    		memcpy(buf, traverseNeighbourhood->inputOfTxt + offset, size);
								} else
						    		size = 0;
					    	}
   							traverseNeighbourhood = traverseNeighbourhood->next;
   						}
   					}
	   				traverseDistrict = traverseDistrict->next;
	   			}
   			}
   			traverse = traverse->next;
   		}

   	}
   	else  if (strstr(path, codes) != NULL){
   		printf("MAP: READ FUNCTION CODES\n");
   		struct plate* traverse = headMap->headPlate;
   		while(traverse){
   			if (strstr(path, traverse->plate) != NULL) {
   				struct code* traverseCode = traverse->headCode;
	   			while(traverseCode){
	   				if (strstr(path, traverseCode->code) != NULL){
	   					len = strlen(traverseCode->inputOfTxt);
						if (offset < len) {
					    	if (offset + size > len)
					        	size = len - offset;
					    	memcpy(buf, traverseCode->inputOfTxt + offset, size);
						} else
					    	size = 0;
	   				}
	   				traverseCode = traverseCode->next;
	   			}
   			}
   			traverse = traverse->next;
   		}
   	}
    printf("MAP: READ FUNCTION ENDS\n");
    return size;
}

static int map_unlink(const char *path){
	printf("MAP: UNLINK FUNCTION STARTS\n");
	struct address* traverseAddress = headMap;
	(void)path;
	int status;
	status = unlink(path);
	char newPath[20];
	int i = 0;
	int j = 0;
	int count = 0;
	struct city* traverse = headMap->headCity;
	if (strstr(path, names) != NULL) {
		for(i; i<strlen(path); i++){
			if(path[i] == '.') break;
			if (count == 4){
				newPath[j] = path[i];
				j++;
			}
			if(path[i] == '/') count++;
		}
		newPath[j]='\0';
		while(traverse){
			if (strstr(path, traverse->city) != NULL) {
				struct district* traverseDistrict = traverse->headDistrict;
				while(traverseDistrict){
				if (strstr(path, traverseDistrict->districtPath) != NULL) {
						struct neighbourhood* traverseNeighbourhood = traverseDistrict->headNeighbourhood;
						while(traverseNeighbourhood){
							if(traverseNeighbourhood->next && strstr(path, traverseNeighbourhood->next->neighbourhood) != NULL){
								traverseNeighbourhood->next = traverseNeighbourhood->next->next;
								while (traverseAddress->next){
									if(strstr(path, traverseAddress->next->city) != NULL){
										if(strstr(path, traverseAddress->next->district) != NULL){
											if(strstr(newPath, traverseAddress->next->neighbourhood) != NULL){
												traverseAddress->next = traverseAddress->next->next;
												writeFile();
											}
										}
									}
									traverseAddress = traverseAddress->next;
								}
							}
							traverseNeighbourhood = traverseNeighbourhood->next;
						}
					}
					traverseDistrict = traverseDistrict->next;
				}
			}
			traverse = traverse->next;
		}
	}
	if (strstr(path, codes) != NULL) {
		for(i; i<strlen(path); i++){
			if(path[i] == '.') break;
			if (count == 3){
				newPath[j] = path[i];
				j++;
			}
			if(path[i] == '/') count++;
		}
		newPath[j]='\0';
		struct plate* traverse = headMap->headPlate;
   		while(traverse){
   			if (strstr(path, traverse->plate) != NULL) {
   				struct code* traverseCode = traverse->headCode;
	   			while(traverseCode){
					if(traverseCode->next && strstr(path, traverseCode->next->code) != NULL){
						traverseCode->next = traverseCode->next->next;
						while (traverseAddress->next){
							if(strstr(newPath, traverseAddress->next->code) != NULL){
								traverseAddress->next = traverseAddress->next->next;
								writeFile();
							}
							traverseAddress = traverseAddress->next;
						}
					}
	   				traverseCode = traverseCode->next;
	   			}
   			}
   			traverse = traverse->next;
   		}
	}
    printf("MAP: UNLINK FUNCTION ENDS\n");
    return 0;
}

static int map_rename(const char *path, const char *to){
	printf("MAP: RENAME FUNCTION STARTS\n");
	struct address* traverseAddress = headMap;
	(void)path;
    (void)to;
    int status;
	status = rename(path, to);
	printf("%d\n", status);
    struct city* traverse = headMap->headCity;
    int i = 0;
 	int count = 0;
    int j = 0;
    char newName[20];
    char newNameWithTxt[20];

	if (strstr(path, names) != NULL) {
		for(i; i<strlen(to); i++){
			if(to[i] == '.') break;
			if (count == 4){
				newName[j] = to[i];
				j++;
			}
			if(to[i] == '/') count++;
		}
		newName[j]='\0';
		strcpy(newNameWithTxt, "/");
		strcat(newNameWithTxt, newName);
		strcat(newNameWithTxt, txt);
		while(traverse){
			if (strstr(path, traverse->city) != NULL) {
				struct district* traverseDistrict = traverse->headDistrict;
				while(traverseDistrict){
				if (strstr(path, traverseDistrict->districtPath) != NULL) {
						struct neighbourhood* traverseNeighbourhood = traverseDistrict->headNeighbourhood;
						while(traverseNeighbourhood){
							if(traverseNeighbourhood && strstr(path, traverseNeighbourhood->neighbourhood) != NULL){
								strcpy(traverseNeighbourhood->neighbourhood, newNameWithTxt);
								while (traverseAddress){
									if(strstr(path, traverseAddress->city) != NULL){
										if(strstr(path, traverseAddress->district) != NULL){
											if(strstr(path, traverseAddress->neighbourhood) != NULL){
												strcpy(traverseAddress->neighbourhood, newName);
												writeFile();
											}
										}
									}
									traverseAddress = traverseAddress->next;
								}
							}
							traverseNeighbourhood = traverseNeighbourhood->next;
						}
					}
					traverseDistrict = traverseDistrict->next;
				}
			}
			traverse = traverse->next;
		}
	}
	if (strstr(path, codes) != NULL) {
		for(i; i<strlen(to); i++){
			if(to[i] == '.') break;
			if (count == 3){
				newName[j] = to[i];
				j++;
			}
			if(to[i] == '/') count++;
		}
		newName[j]='\0';
		strcpy(newNameWithTxt, "/");
		strcat(newNameWithTxt, newName);
		strcat(newNameWithTxt, txt);
		struct plate* traverse = headMap->headPlate;
   		while(traverse){
   			if (strstr(path, traverse->plate) != NULL) {
   				struct code* traverseCode = traverse->headCode;
	   			while(traverseCode){
					if(traverseCode && strstr(path, traverseCode->code) != NULL){
						strcpy(traverseCode->code, newNameWithTxt);
						while (traverseAddress){
							if(strstr(path, traverseAddress->code) != NULL){
								strcpy(traverseAddress->code, newName);
								writeFile();
							}
							traverseAddress = traverseAddress->next;
						}
					}
	   				traverseCode = traverseCode->next;
	   			}
   			}
   			traverse = traverse->next;
   		}
	}
    printf("MAP: RENAME FUNCTION ENDS\n");
    return -EROFS;
}

static struct fuse_operations map_oper = {
    .getattr	= map_getattr,
    .readdir	= map_readdir,
    .open	= map_open,
    .read	= map_read,
    .unlink = map_unlink, 
    .rename	= map_rename
};

int main(int argc, char **argv)
{
	struct stat st = {0};
	printf("MAP: MAIN FUNCTION STARTS\n");
	if(stat(argv[argc-1], &st) == -1) {
        mkdir(argv[argc-1], 0700);  
    }
    headMap = readFile();
    writeFile();
	printf("MAP: MAIN FUNCTION ENDS\n");
	return fuse_main(argc, argv, &map_oper, NULL);
}

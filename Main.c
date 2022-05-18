#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

char wrd[256];
void* reader(void* data);


int main() {

    int numberOfFiles;
    printf("How many files to search (max 5)");
    scanf("%d", &numberOfFiles);

    do{
        printf("Enter the word you want to search in the file: ");
        fscanf(stdin,"%s",wrd);

        pthread_t threads[numberOfFiles];
        for(int i=0; i<numberOfFiles; i++){
            int isCreated = pthread_create(&threads[i],NULL,reader,(void*)(intptr_t)i+1);

            if(isCreated){
                printf("Error: Couldn't create thread %d\n", i);
                exit(-1);
            }
        }

        for(int i=0; i<numberOfFiles; i++) {                                                                            
            int isJoined = pthread_join(threads[i], NULL);
            if(isJoined){
                printf("Error: coudn't join thread %d\n", i);                                                                                                       
                exit(-2);                                                                                                                                                                                                                                                                                                           
            }
        }
        printf("All positions of word \"%s\"\n" , wrd);
    }while(1 == 1);

    return 0;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              
}

void* reader(void* data){

    char buffer[256];
	int n, m, i, j, line, size = 256;
    char filename[10];

    sprintf(filename, "text%d.txt", (int)(intptr_t)data);
   // printf("%d", (int)(intptr_t)i)
	
	FILE* fp;                                                                                                                                                                                                                                                                                                                                                                                                                                               
	fp = fopen(filename, "r");	// open file                                


	m = strlen(wrd); // length of input word

	//printf("All positions of word \"%s\" in the %s\n", wrd, filename);
    //printf("All positions of word \"%s\n" , wrd);

	line = 0;
	// the following loop the file fp line by line
	// each line is stored in buffer
	while (fgets(buffer, 256, fp) != NULL) {

		i = 0;
		n = strlen(buffer);
		// the followinf loop find position of the input word in the current line and
		// print the position of the word on the screen
		// the loop basically reads each word of the file and compare it with the input word
		while (i < n) {

			// comparing current word with input word
			j = 0;
			while (i < n && j < m && buffer[i] == wrd[j]) {
				++i, ++j;
			}

			// the following condition implies that the current word of buffer
			// is equal to input word
			if ((i == n || buffer[i] == ' ' || buffer[i] == '\n') && j == m) {
				printf("FileName: %s ", filename);
                printf("Line: %d ", line);
				printf("Column: %d\n", i - m);
			}

			// moving to next word
			while (i < n && buffer[i] != ' ') {
				++i;
			}
			++i;

		}

		++line;

	}

	fclose(fp);
}
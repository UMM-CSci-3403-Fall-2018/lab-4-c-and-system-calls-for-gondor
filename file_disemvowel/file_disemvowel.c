#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>

#include "file_disemvowel.h"
#define BUF_SIZE 1024

// Takes a character and converts it to lowercase.
// If it is a vowel returns true, otherwise false
bool isVowel(char letter) {
        letter = tolower(letter);
        switch(letter) {
                case 'a':
                        return true;
                case 'e':
                        return true;
                case 'i':
                        return true;
                case 'o':
                        return true;
                case 'u':
                        return true;
                default :
                        return false;

        }
}

// Takes a character array, counts the number of non-vowels inside and returns
// this number. This provides the size needed for the returned disemvoweled string
int determineLength(char *str) {
int count = 0;

for(unsigned int i = 0; i < strlen(str); i++) {
	if (str[i] != isVowel(str[i])) {
		count++;
		}
	}
	return count;
}

/*
 * Copy all the non-vowels from in_buf to out_buf. 
 * num_chars indicates how many characters are in in_buf, 
 * and this function should return the number of non-vowels that
 * that were copied over.
 */
int copyNonVowels(int num_chars, char* in_buf, char* out_buf) {
	//int streamlen = determineLength(in_buf);
	int j = 0;

	//out_buf = (char*)calloc(streamlen + 1, sizeof(char));

	for(int i = 0; i < num_chars; i++) {
	  if (!(isVowel(in_buf[i]))) {
		out_buf[j] = in_buf[i];
		j++;
	  }
	}
	out_buf[j] = '\0';

	return j;
}


/*
 * Copy all the non-vowels from inputFile to outputFile.
 * Create input and output buffers, and use fread() to repeatedly read
 * in a buffer of data, copy the non-vowels to the output buffer and
 * use fwrite to write that out.         
 */
void disemvowel(FILE* inputFile, FILE* outputFile) {
	char in_buf[BUF_SIZE];
	char out_buf[BUF_SIZE + 1];
	//in_buf = (char*)calloc(BUF_SIZE, sizeof(char));
	int non_vowels = 0;

	int num_read = fread(in_buf, sizeof(char), BUF_SIZE, inputFile);
	while(num_read > 0) {
		non_vowels = copyNonVowels(num_read, in_buf, out_buf);
		fwrite(out_buf, sizeof(char), non_vowels, outputFile);
		num_read = fread(in_buf, sizeof(char), BUF_SIZE, inputFile);
	}
	fclose(inputFile);
	fclose(outputFile);
}

int main(int argc, char *argv[]) { 
    FILE *inputFile; 
    FILE *outputFile;

    if (argc == 1) {
    inputFile = stdin; 
    outputFile = stdout;
	}
    else if (argc == 2) {
    inputFile = fopen(argv[1], "r");
    outputFile = stdout;
    }
    else if (argc == 3) {
    inputFile = fopen(argv[1], "r");
    outputFile = fopen(argv[2], "w");
    }
    else printf("Too many arguments given");    

    disemvowel(inputFile, outputFile);
    

    return 0; 
}


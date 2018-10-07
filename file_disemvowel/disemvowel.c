#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>

#include "disemvowel.h"
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

// Takes the size of the disemvoweled string and the original string
// Allocates memory for the new string, and copies each non-vowel
// into the new string, and increments the index for the position
// in the new string. Returns the disemvoweled string
int copyNonVowels(int num_chars, char* in_buf, char* out_buf) {
	int streamlen = determineLength(in_buf);
	int j = 0;

	out_buf = (char*)calloc(streamlen, sizeof(char));

	for(int i = 0; i < num_chars; i++) {
	if (!(isVowel(in_buf[i]))) {
		out_buf[j] = in_buf[i];
		j++;
		}
	}
	out_buf[j] = '\0';

	return j;
}


// Upper level function that takes a string to be disemvowled.
// Calls determineLength on the string to find its length and
// uses this value as an argument for its call to copyNonVowels
// which also takes the given string. Returns the disemvowled string
void disemvowel(FILE* inputFile, FILE* outputFile) {
	char* in_buf[BUF_SIZE];
	char* out_buf[BUF_SIZE];

	while(fread(in_buf, sizeof(in_buf), BUF_SIZE, inputFile) > 0) {
		fread(in_buf, sizeof(in_buf), BUF_SIZE, inputFile);
		copyNonVowels(BUF_SIZE, in_buf, out_buf);
		fwrite(out_buf, sizeof(out_buf), BUF_SIZE, outputFile);
	}
}

int main(int argc, char *argv[]) { 
    FILE *inputFile; 
    FILE *outputFile;

    inputFile = argv[0];

    fopen(inputFile, "r");
    fopen(outputFile, "w");

    // Code that processes the command line arguments 
    // and sets up inputFile and outputFile.

    disemvowel(inputFile, outputFile);

    return 0; 
}


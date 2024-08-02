/*
IZP keyfilter
Author: Martin Mendl x247581@stud.fit.vut.cz
Date: 10.10.2023
note:
    The program was created to minimize memory consumption, which is why it uses fewer variables, and arrays are allocated statically. 
    The program is set to work with characters from the C ASCII table in the range of 32-96 and 123-126 + \n and OEF (lowercase letters are converted to uppercase). 
    The program is case insensitive.
    The program's argument (search str) is limited to 100 characters, just like each line in the file.
    **compatibility** if file encoding is CLRF, the program will not work properly. (new line interpratation is different)
*/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

/**
* @param newChar - character to be checked
* @return - true if the character is valid, else false
* @brief - checks if a character is valid
*/
bool isCharValid(char newChar) {

    if (!((newChar >= ' ' && newChar <= '~') || newChar == '\n' || newChar == EOF))
        return false;
    return true;
}

/**
* @param charStorageIndicator - array of bools, that indicate if a character should be present in the Enable: string
* @param newChar - character to be saved
* @brief - saves a character to an array of bools, if there not allready
*/
void saveEndChar(bool* charStorageIndicator, char newChar) {

    int index;

    (newChar >= ' ' && newChar <='`') ? (index = newChar - 32) : (index = newChar - 58);

    charStorageIndicator[index] = true;
}

/**
* @param boolArrIndicator - array of bools, that indicate if a character is valid
* @param endStringStorage - array of characters, where the valid characters are stored
* @brief - recreates a string of valid characters from a bool array
*/
void RecreateEndCharString(bool* boolArrIndicator, char* endStringStorage) {

    int counter = 0;

    for (int idx = 0; idx < 69; idx++) {

        if (!boolArrIndicator[idx]) {
            continue;
        }
        if (idx >= 0 && idx <= 64) {
            endStringStorage[counter] = idx + 32;

        } else {
            endStringStorage[counter] = idx + 58;
        }
        counter++;
    }
    endStringStorage[counter] = '\0';
}

/**
* @param str[] - string to be converted to uppercase
* @brief - converts a string to uppercase
*/
void uperCase(char str[]) {
   
    char currentChar;

    for (unsigned idx = 0; idx < strlen(str); idx++) {
        currentChar = str[idx];
        if (currentChar >= 'a' && currentChar <= 'z')
           currentChar -= 32;
        
        str[idx] = currentChar;
    }
}

/**
* @brief - skips to the next line in the file (skipping untill \n or EOF)
* @param - storage - array of charactes, where the skipped characters are stored if saveData
* @param - saveData - bool, if true, the skipped characters are stored in storage
* @return - true if all characters, ware valid and the total lenght is shorter than 100 else false
*/
bool skipToNextCity(char* storage, bool saveData, int curretnSequeceIdx) {
  
    char oneChar = getchar();
    int index = 0;
    int charCount = curretnSequeceIdx;

    while (oneChar != '\n' && oneChar != EOF) {

        charCount++;

        if (charCount > 100) {
            printf("error, the city name is too long\n");
            return false;
        }

        if (!isCharValid(oneChar)) {
           printf("error, invalid character present in file\n");
           return false;
        }

        if (saveData) {
            storage[index++]  = oneChar;
        }
        oneChar = getchar();
    }
    if (saveData) 
        storage[index] = '\0';

    return true;
}

/**
* @brief - program that finds cities form a file that start with a given char string
* @param argc - number of arguments, value -> (1 or 2)
* @param argv[] - arguments (searched string, file to be searched)
* @return Program exit code -1 -> error, 0 -> success
*/
int main (int argc, char*argv[]) {


    if (argc > 2) {
        printf("error, too many arugments suplied\n");
        return 1;
    }

    char citySearchWindow[100];

    if (argc == 2){
        if (strlen(argv[1]) > 100) {
            printf("error, too many characters in searched string\n");
            return 1;
        }
	    strcpy(citySearchWindow, argv[1]);
        uperCase(citySearchWindow);
	}

	char oneChar = EOF;
    bool endCharactes[70]; // bool array, that indicates if a character should be present in the Enable: string
    char cityStorage[101]; // array of characters, where the skipped characters are stored if saveData

    for(int i = 0; i < 70; i++) { // init bool array
        endCharactes[i] = false;
    }

	int foundCities = ((argc == 1) ? 2 : 0); // number of cities found
    unsigned int sequenceIdx = 0; // index of the current character in the searched string
    
	while (1) 
	{
        oneChar=getchar(); // read one char from file

        if (!isCharValid(oneChar)) {
            printf("error, invalid character present in file\n");
            return 1;
        }
       
        if (oneChar == EOF) // end of file handling
            break;

        if (oneChar >= 'a' && oneChar <= 'z') // convert to uppercase
            oneChar -= 32;

        if (argc == 1) { // if no argument is supplied, print characters, that the cities start with
            
            if (!skipToNextCity(cityStorage, false, sequenceIdx)) 
                return 1;

            saveEndChar(endCharactes, oneChar);
            continue;
        }
        if (oneChar != citySearchWindow[sequenceIdx++]) { // if the sequence is broken, skip to the next city
            if (!skipToNextCity(cityStorage, false, sequenceIdx)) 
                return 1;

            sequenceIdx= 0;
            continue;
        }
        if (sequenceIdx == strlen(citySearchWindow)) { // if the sequence is complete, save the next character

            if (!skipToNextCity(cityStorage, true, sequenceIdx)) 
                return 1;

            sequenceIdx = 0;

            uperCase(cityStorage);
            oneChar = cityStorage[0];

            if (oneChar == '\0' || oneChar == EOF) { // found an excact match
                printf("Found: %s\n", citySearchWindow); // replace
                return 0;
                }
            foundCities++;
            saveEndChar(endCharactes, oneChar);
        }
    }
    
    if (foundCities == 0) { // no cities found
        printf("Not found\n");
        return 0;
    }

    if (foundCities == 1) { // one city found
        printf("Found: %s", citySearchWindow);
        printf("%s\n", cityStorage);
        return 0;
    }

    char endStr[71]; // more thatn one city found
    RecreateEndCharString(endCharactes, endStr);
    printf("Enable: ");
    printf("%s\n", endStr);
    
    return 0;
}

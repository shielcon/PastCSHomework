#include "hashMap.h"
#include <assert.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#pragma warning(disable: 4996)

/**
 * Allocates a string for the next word in the file and returns it. This string
 * is null terminated. Returns NULL after reaching the end of the file.
 * @param file
 * @return Allocated string or NULL.
 */

/*
generates an array of suggestion strings, which
are valid recommendations from the dictionary                           
*/

int Levenshtein(char *str1, char *str2);
int generateSuggestions(HashMap* map, char* str, HashLink* arr[]);

char* nextWord(FILE* file)
{
	int maxLength = 16;
	int length = 0;
	char* word = malloc(sizeof(char) * maxLength);
	//Fix me: Do the necessary change to make the implementation //case-insensitive  
	char c = fgetc(file);
	while (c != EOF)
	{
		if ((c >= '0' && c <= '9') ||
			(c >= 'A' && c <= 'Z') ||
			(c >= 'a' && c <= 'z') ||
			c == '\'')
		{
			if (length + 1 >= maxLength)
			{
				maxLength *= 2;
				word = realloc(word, maxLength);
			}
			if (c >= 'A' && c <= 'Z')
				c = tolower(c);
			word[length] = c;
			length++;
		}
		else if (length > 0 || c == EOF)
		{
			break;
		}
		c = fgetc(file);
	}
	if (length == 0)
	{
		free(word);
		return NULL;
	}
	word[length] = '\0';
	return word;
}

/**
 * Loads the contents of the file into the hash map.
 * @param file
 * @param map
 */
void loadDictionary(FILE* file, HashMap* map)
{
	if (file)
	{
		int wordCount;
		char *word = nextWord(file);
		while (word)
		{
			if (hashMapGet(map, word) != NULL)
			{
				wordCount = *hashMapGet(map, word);
				wordCount++;
				hashMapPut(map, word, wordCount);
				free(word);
			}
			else
			{
				wordCount = 1;
				hashMapPut(map, word, wordCount);
				free(word);
			}
			word = nextWord(file);
		}
	}
	else
	{
		printf("Couldn't open file\n");
	}
	/*
	for (int i = 0; i < map->capacity; i++)
	{
		if (map->table[i] != NULL)
		{
			HashLink* link = map->table[i];
			while (link != NULL)
			{

			}
		}
	}*/
	//printf("%d\n", hashMapSize(map));
	//hashMapPrint(map);
}

/**
 * Prints the concordance of the given file and performance information. Uses
 * the file input1.txt by default or a file name specified as a command line
 * argument.
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, const char** argv)
{
    // FIXME: implement
    HashMap* map = hashMapNew(1000);
    
	const char* fileName;
	if (argc > 1)
	{
		fileName = argv[1];
	}
	else
		fileName = "dictionary.txt";
	FILE *text = fopen(fileName, "r"); 
	clock_t timer = clock();
    loadDictionary(text, map);
    timer = clock() - timer;
    printf("Dictionary loaded in %f seconds\n", (float)timer / (float)CLOCKS_PER_SEC);
	if (text)
		fclose(text);

    
    char inputBuffer[256];
    int quit = 0;
    while (!quit)
    {
        printf("Enter a word or \"quit\" to quit: ");
        scanf("%s", inputBuffer);
        
        // Implement the spell checker code here..
        
        if (strcmp(inputBuffer, "quit") == 0)
        {
			quit = 1;
        }
		else
		{
			if (hashMapContainsKey(map, inputBuffer) == 1)
			{
				printf("Word spelled correctly\n");
			}
			else
			{
				HashLink* suggestions[5];
				int count;
				count = generateSuggestions(map, inputBuffer, suggestions);
				
				if (count > -1)
				{
					printf("That's not a word! Here are some alternatives:\n");
					for (int i = 0; i <= count; i++)
					{
						printf("%s\n", suggestions[i]->key);
					}
				}
				else
					printf("That's not a word! Or even close to a word... no alternatives for that one. Sorry!\n");
			}
		}

    }

    
    hashMapDelete(map);
    return 0;
}

/*
generates suggested edits for
given word.
param: HashMap, string, array
returns: amount of suggested strings
arr is modified
*/
int generateSuggestions(HashMap* map, char *str, HashLink *arr[])
{
	int lev = 1;
	int words = 0;
	for (int i = 194; i < map->capacity; i++)
	{
		HashLink* link = map->table[i];
		if (link != NULL)
		{
			while (link != NULL)
			{
				link->value = Levenshtein(str, link->key);
				link = link->next;
			}
		}
	}
	while (words < 5 && lev < 6)
	{
		int i = 194;
		while (i < map->capacity && words < 5)
		{
			HashLink* link = map->table[i];
			if (link != NULL)
			{
				while (link != NULL && words < 5)
				{
					if (link->value <= lev)
					{
						int contained = 0;
						for (int j = 0; j < words; j++)
						{
							if (strcmp(arr[j]->key, link->key) == 0)
								contained = 1;
						}
						if (contained != 1)
						{
							arr[words] = link;
							words++;
						}
					}
					link = link->next;
				}
			}
			i++;
		}
		lev++;
	}
	return words - 1;
}

/*
calculates the levenshtein distance between
two words.
params: 2 strings
returns: levenshtein distance
*/
int Levenshtein(char* str1, char* str2)
{
	int str1length = strlen(str1);
	int str2Length = strlen(str2);
	int *arr = malloc(sizeof(int) * str1length);
	int index = 0;
	int str2Index = 0;
	int distance;
	int str2Distance;
	int result;
	char code;

	if (strcmp(str1, str2) == 0) {
		return 0;
	}

	if (str1length == 0) {
		return str2Length;
	}

	if (str2Length == 0) {
		return str1length;
	}

	while (index < str1length) {
		arr[index] = index + 1;
		index++;
	}

	while (str2Index < str2Length) {
		code = str2[str2Index];
		distance = str2Index;
		result = distance;
		str2Index++;
		index = 0;

		while (index < str1length) {
			if (code == str1[index])
				str2Distance = distance;
			else
				str2Distance = distance + 1;
			distance = arr[index];


			if (distance > result) {
				if (str2Distance > result) {
					result++;
				}
				else {
					result = str2Distance;
				}
			}
			else {
				if (str2Distance > distance) {
					result = distance + 1;
				}
				else {
					result = str2Distance;
				}
			}
			arr[index] = result;
			index++;
		}
	}

	free(arr);

	return result;
}
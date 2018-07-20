#include "hashMap.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include <ctype.h>
#pragma warning(disable: 4996)

/**
 * Allocates a string for the next word in the file and returns it. This string
 * is null terminated. Returns NULL after reaching the end of the file.
 * @param file
 * @return Allocated string or NULL.
 */
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
    const char* fileName;
	if (argc > 1)
	{
		fileName = argv[1];
	}
	else
		fileName = "input1.txt";
    printf("Opening file: %s\n", fileName);
	FILE *text = fopen(fileName, "r");
	if (text)
	{
		clock_t timer = clock();

		HashMap* map = hashMapNew(10);
		int wordCount;

		// --- Concordance code begins here ---

		char *word = nextWord(text);
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
			word = nextWord(text);
		}
		fclose(text);

		for (int i = 0; i < map->capacity; i++)
		{
			HashLink* link = map->table[i];
			if (link != NULL)
			{
				while (link != NULL)
				{
					printf("%s: %d", link->key, link->value);
					link = link->next;
					printf("\n");
				}
			}
		}
		

		// --- Concordance code ends here ---

		
		
		timer = clock() - timer;
		printf("\nRan in %f seconds\n", (float)timer / (float)CLOCKS_PER_SEC);
		printf("Empty buckets: %d\n", hashMapEmptyBuckets(map));
		printf("Number of links: %d\n", hashMapSize(map));
		printf("Number of buckets: %d\n", hashMapCapacity(map));
		printf("Table load: %f\n", hashMapTableLoad(map));

		hashMapDelete(map);
	}
	else
	{
		printf("error\n");
		perror("fopen");
	}
    return 0;
}
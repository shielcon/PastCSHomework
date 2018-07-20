/*
 * CS 261 Data Structures
 * Assignment 5
 * Name: Connor Shields
 * Date: 3/12/2018
 */

#pragma warning(disable: 4996)

#include "hashMap.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

int hashFunction1(const char* key)
{
    int r = 0;
    for (int i = 0; key[i] != '\0'; i++)
    {
        r += key[i];
    }
    return r;
}

int hashFunction2(const char* key)
{
    int r = 0;
    for (int i = 0; key[i] != '\0'; i++)
    {
        r += (i + 1) * key[i];
    }
    return r;
}

/**
 * Creates a new hash table link with a copy of the key string.
 * @param key Key string to copy in the link.
 * @param value Value to set in the link.
 * @param next Pointer to set as the link's next.
 * @return Hash table link allocated on the heap.
 */
HashLink* hashLinkNew(const char* key, int value, HashLink* next)
{
    HashLink* link = malloc(sizeof(HashLink));
    link->key = malloc(sizeof(char) * (strlen(key) + 1));
    strcpy(link->key, key);
    link->value = value;
    link->next = next;
    return link;
}

/**
 * Free the allocated memory for a hash table link created with hashLinkNew.
 * @param link
 */
static void hashLinkDelete(HashLink* link)
{
    free(link->key);
    free(link);
}

/**
 * Initializes a hash table map, allocating memory for a link pointer table with
 * the given number of buckets.
 * @param map
 * @param capacity The number of table buckets.
 */
void hashMapInit(HashMap* map, int capacity)
{
    map->capacity = capacity;
    map->size = 0;
    map->table = malloc(sizeof(HashLink*) * capacity);
    for (int i = 0; i < capacity; i++)
    {
        map->table[i] = NULL;
    }
}

/**
 * Removes all links in the map and frees all allocated memory. You can use
 * hashLinkDelete to free the links.
 * @param map
 */
void hashMapCleanUp(HashMap* map)
{
	int i;
	HashLink *currentList, *temp;
	for (i = 0; i < map->capacity; i++)
	{
		currentList = map->table[i];
		while (currentList != NULL)
		{
			temp = currentList->next;
			hashLinkDelete(currentList);
			currentList = temp;
		}
	}
	free(map->table);
}

/**
 * Creates a hash table map, allocating memory for a link pointer table with
 * the given number of buckets.
 * @param capacity The number of buckets.
 * @return The allocated map.
 */
HashMap* hashMapNew(int capacity)
{
    HashMap* map = malloc(sizeof(HashMap));
    hashMapInit(map, capacity);
    return map;
}

/**
 * Removes all links in the map and frees all allocated memory, including the
 * map itself.
 * @param map
 */
void hashMapDelete(HashMap* map)
{
    hashMapCleanUp(map);
    free(map);
}

/**
 * Returns a pointer to the value of the link with the given key. Returns NULL
 * if no link with that key is in the table.
 * 
 * Use HASH_FUNCTION(key) and the map's capacity to find the index of the
 * correct linked list bucket. Also make sure to search the entire list.
 * 
 * @param map
 * @param key
 * @return Link value or NULL if no matching link.
 */
int* hashMapGet(HashMap* map, const char* key)
{
	int index;
	index = HASH_FUNCTION(key) % map->capacity;

	if (index < 0)
	{
		index += map->capacity;
	}

	HashLink *current = map->table[index];
		while (current != NULL && strcmp(current->key, key) != 0)
		{
			current = current->next;
		}
		if (current != NULL)
			return &current->value;
		else
			return NULL;
}

/**
 * Resizes the hash table to have a number of buckets equal to the given
 * capacity. After allocating the new table, all of the links need to be
 * rehashed into it because the capacity has changed.
 * 
 * Remember to free the old table and any old links if you use hashMapPut to
 * rehash them.
 * 
 * @param map
 * @param capacity The new number of buckets.
 */
void resizeTable(HashMap* map, int capacity)
{
	/*HashMap* temp;
	HashLink* tempLink;
	HashMap* newMap = hashMapNew(capacity);

	int i;
	HashLink *currentLink;
	for (i = 0; i < map->capacity; i++)
	{
		currentLink = map->table[i];
		while (currentLink != NULL)
		{
			hashMapPut(newMap, currentLink->key, currentLink->value);
			tempLink = currentLink;
			currentLink = currentLink->next;
			free(tempLink);
		}
	}
	hashMapCleanUp(map);
	map->size = newMap->size;
	map->table = newMap->table;
	map->capacity = newMap->capacity;
	newMap->table = NULL;
	free(newMap);
	*/
	/*
	map = newMap;
	map->table = newMap->table;
	map->size = newMap->size;
	map->capacity = newMap->capacity;
	*/
	HashMap *newMap = hashMapNew(capacity);
	HashLink *currentLink;
	for (int i = 0; i < map->capacity; i++) {
		currentLink = map->table[i];

		while (currentLink != NULL) {
			hashMapPut(newMap, currentLink->key, currentLink->value);
			currentLink = currentLink->next;
		}
	}

	hashMapCleanUp(map);
	map->size = newMap->size;
	map->table = newMap->table;
	map->capacity = newMap->capacity;

	newMap->table = NULL;
	free(newMap);
}

/**
 * Updates the given key-value pair in the hash table. If a link with the given
 * key already exists, this will just update the value. Otherwise, it will
 * create a new link with the given key and value and add it to the table
 * bucket's linked list. You can use hashLinkNew to create the link.
 * 
 * Use HASH_FUNCTION(key) and the map's capacity to find the index of the
 * correct linked list bucket. Also make sure to search the entire list.
 * 
 * @param map
 * @param key
 * @param value
 */
void hashMapPut(HashMap* map, const char* key, int value)

{
	//compute hash value to find the correct bucket
	int idx = HASH_FUNCTION(key) % map->capacity;
	if (idx < 0) 
		idx += map->capacity;
	int *contained = hashMapGet(map, key);
	if (contained != NULL)
	{
		*contained = value;
		return;
	}
	HashLink *newLink = map->table[idx];
	while (newLink != NULL)
	{
		newLink = newLink->next;
	}
	newLink = hashLinkNew(key, value, map->table[idx]);
	map->table[idx] = newLink;
	map->size++;
	if (hashMapTableLoad(map) > 10.0)
		resizeTable(map, map->capacity * 2);
}

/**
 * Removes and frees the link with the given key from the table. If no such link
 * exists, this does nothing. Remember to search the entire linked list at the
 * bucket. You can use hashLinkDelete to free the link.
 * @param map
 * @param key
 */
void hashMapRemove(HashMap* map, const char* key)
{
	HashLink *link;
	HashLink *prev;
	int idx = HASH_FUNCTION(key) % map->capacity;
	if (idx < 0)
		idx += map->capacity;
	link = map->table[idx];
	prev = link;
	while (link != NULL)
	{
		if (strcmp(link->key, key) == 0)
		{
			if (link == map->table[idx])
				map->table[idx] = link->next;
			else
				prev->next = link->next;
			hashLinkDelete(link);
			map->size--;
			return;
		}
		prev = link;
		link = link->next;
	}
}

/**
 * Returns 1 if a link with the given key is in the table and 0 otherwise.
 * 
 * Use HASH_FUNCTION(key) and the map's capacity to find the index of the
 * correct linked list bucket. Also make sure to search the entire list.
 * 
 * @param map
 * @param key
 * @return 1 if the key is found, 0 otherwise.
 */
int hashMapContainsKey(HashMap* map, const char* key)
{
	HashLink *link;
	int idx = HASH_FUNCTION(key) % map->capacity;
	if (idx < 0)
		idx += map->capacity;
	link = map->table[idx];
	while (link != NULL)
	{
		if (strcmp(link->key, key) == 0)
			return 1;
		link = link->next;
	}
	return 0;
}

/**
 * Returns the number of links in the table.
 * @param map
 * @return Number of links in the table.
 */
int hashMapSize(HashMap* map)
{
	return map->size;
}

/**
 * Returns the number of buckets in the table.
 * @param map
 * @return Number of buckets in the table.
 */
int hashMapCapacity(HashMap* map)
{
	return map->capacity;
}

/**
 * Returns the number of table buckets without any links.
 * @param map
 * @return Number of empty buckets.
 */
int hashMapEmptyBuckets(HashMap* map)
{
	int empties = map->capacity;
	int i;
	for (i = 0; i < map->capacity; i++)
	{
		if (map->table[i] != NULL)
			empties--;
	}
	return empties;
}

/**
 * Returns the ratio of (number of links) / (number of buckets) in the table.
 * Remember that the buckets are linked lists, so this ratio tells you nothing
 * about the number of empty buckets. Remember also that the load is a floating
 * point number, so don't do integer division.
 * @param map
 * @return Table load.
 */
float hashMapTableLoad(HashMap* map)
{
	float cap = map->capacity;
	float size = map->size;
	return size / cap;
}

/**
 * Prints all the links in each of the buckets in the table.
 * @param map
 */
void hashMapPrint(HashMap* map)
{
    for (int i = 0; i < map->capacity; i++)
    {
        HashLink* link = map->table[i];
        if (link != NULL)
        {
            printf("\nBucket %i ->", i);
            while (link != NULL)
            {
                printf(" (%s, %d) ->", link->key, link->value);
                link = link->next;
            }
        }
    }
    printf("\n");
}

/*

int main()
{
	HashMap *map = hashMapNew(2);
	hashMapPut(map, "bob", 1);
	hashMapPut(map, "bob", 2);
	hashMapPut(map, "jocelyn", 2);
	hashMapPut(map, "joe", 3);

	hashMapPut(map, "amy", 4);

	hashMapPut(map, "dick", 5);
	hashMapPut(map, "peter", 6);
	hashMapPut(map, "joe", 7);
	hashMapPut(map, "andrew", 8);
	hashMapPut(map, "andrew", 9);
	hashMapPut(map, "jane", 10);
	hashMapPut(map, "cory", 11);
	hashMapPut(map, "amanda", 12);
	hashMapPut(map, "sue", 13);
	hashMapPut(map, "pete", 14);
	hashMapPrint(map);

	

	hashMapPut(map, "petey", 14);
	hashMapPut(map, "jacob", 14);
	hashMapPut(map, "emanuel", 14);
	hashMapPut(map, "colin", 14);
	hashMapPut(map, "sarah", 14);

	hashMapPut(map, "jean", 14);
	hashMapPut(map, "terry", 14);
	hashMapPrint(map);
	hashMapPut(map, "perry", 14);

	hashMapPut(map, "joanna", 14);
	hashMapPrint(map);
	hashMapPut(map, "yvonne", 14);
	return 0;
}*/
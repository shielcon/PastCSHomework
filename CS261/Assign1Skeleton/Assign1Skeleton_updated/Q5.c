/* CS261- Assignment 1 - Q.5*/
/* Name: Connor Shields
 * Date: 1/22/18
 * Solution description:
 This program allows the user to enter a word. It then
 modifies that word and outputs it in sticky case.

 Input:
 A single word.

 Output:
 The same word, but in sticky case.
 */
#include <stdio.h>
#include <stdlib.h>

/*converts ch to upper case, assuming it is in lower case currently*/
char toUpperCase(char ch) {
	return ch - 'a' + 'A';
}

/*converts ch to lower case, assuming it is in upper case currently*/
char toLowerCase(char ch) {
	return ch - 'A' + 'a';
}

void sticky(char* word) {
	/*Convert to sticky caps*/
	int i = 0;
	while (word[i] != '\0')
	{
		if (word[i] < 'a' && word[i] >= 'A')
			word[i] = toLowerCase(word[i]);
		if (i % 2 == 0)
			word[i] = toUpperCase(word[i]);
		i++;
	}
}

int main() {
	/*Read word from the keyboard using scanf*/
	char word[100];
	scanf("%s", word);
	/*Call sticky*/
	sticky(word);
	/*Print the new word*/
	printf(word);
	printf("\n");
	return 0;
}



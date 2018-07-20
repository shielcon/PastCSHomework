#include <string.h>
#include <stdio.h>
#include <stdlib.h>

struct Word {

char word[50];
struct Word * next;

};

void reverse(char *sentence) {

  struct Word *curWord = NULL;
  struct Word *prevWord;
  int i = 0;
  int j;

  while (sentence[i] != '\0'){

	prevWord = malloc(sizeof(struct Word));
	prevWord->next = curWord;
	curWord = prevWord;
	j = 0;
	while (sentence[i] != 32 && sentence[i] != '\0'){
		curWord->word[j] = sentence[i];
		j++;
		i++;
	}
	if (sentence[i] == 32)
		i++;
  }

  struct Word *firstWord = curWord;

  while (curWord){
	printf("%s ", curWord->word);
	curWord = curWord->next;
  }
  printf("\n");

  curWord = firstWord;
  while (curWord){
  prevWord = curWord;
  curWord = curWord->next;
  free(prevWord);
  }
  
}

int main(){

	char sentence[100];
	printf("Type a sentence that I will reverse\n");
	gets(sentence);
	reverse(sentence);
	
	return 0;

}

/* dict.c */
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include "list.h"

int main(int argc, const char *argv[])
{
	char word[32];
	const char *filename;
	queue *que;
	node *index[26], *res, **results;

	/* load dictionary */
	if (argc < 2) 
		filename = "dict.dat";
	else 
		filename = argv[1];
	que = load_dict(filename);	
	if (que == NULL) 
		return 1;
		

	/* bulid index */
	build_index(que, index);

	/* run */
	while (1) {
		/* input */
		printf("%s", "Please input a word!\n^_^ : ");
		fgets(word, sizeof(word), stdin);

		/* remove '\n' */
		if (word[strlen(word)-1] == '\n')
			word[strlen(word)-1] = '\0';

		/* empty */
		if (!strlen(word)) {
			putchar('\n');
			continue;
		}

		/* exit */
		if (strchr(word, '$')) {
			puts("~_~");
			break;
		}

		/* challenge */
		if (strstr(word, "cha")) {
			printf("%s", "0_0 : Challenge? (y/n) : ");
			if (confirm(true)) {
				challenge();
				continue;
			}
		}

		/* search */
		res = search(index, word);
		if (res) {
			search_out(res);
			continue;
		} 

		/* similar search */
		results = similar_search(index, word, results);
		if (*results) {
			printf("%s", "0_0 : I can't find it.\n0_0 : "
					"Show similar? (y/n): ");
			if (confirm(true))
				similar_search_out(results);
			else
				putchar('\n');
		} else {	/* nothing */
			printf("0_0 : Sorry, no results!\n0_0 : "
					"Add new word %s? (y/n): ", word);
			if (confirm(false))
				add_word(que, word);
			else
				putchar('\n');
		}
		free(results);
	}

	/* unload dictionary */
	unload_dict(que, filename);

	return 0;
}
#if 0
typedef struct item {
	char *word, **trans;
	int cnt;
} item;
typedef struct node {
	item *data;
	struct node *next;	
} node;
typedef struct queue {
	node headnode;
	node *head;
	node *tail;
} queue;
#endif

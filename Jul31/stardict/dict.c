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
		filename = "dict.txt";
	else 
		filename = argv[1];
	que = load_dict(filename);	

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
		/* search */
		res = search(index, word);
		if (res) {
			search_out(res);
			continue;
		} 
		/* similar search */
		results = similar_search(index, word, results);
		if (*results) {
			printf("%s", "I can't find it. "
					"Show similar? (y/n): ");
			if (confirm())
				similar_search_out(results);
			else
				putchar('\n');
		} else {	/* nothing */
			puts("-_- : Sorry, no results!\n");
		}
		free(results);
	}

	/* unload dictionary */
	unload_dict(que);

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

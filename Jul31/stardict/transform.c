/* dict.c */
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include "list.h"

int count_word(queue *que)
{
	node *pn;
	int cnt;

	for (pn = que->head->next; pn; pn = pn->next) 
		++cnt;	
	return cnt;
}

void convert(queue *que)
{
	FILE *fp;
	char *desc = "stardict";
	int i, word_cnt, trans_cnt, cnt;
	node *pn;

	/* the length of string write to file contains '\0' */
	/* write to file */
	fp = fopen("dict.dat", "w");
	/* description */
	cnt = strlen(desc) + 1;
	fwrite(desc, 1, cnt, fp);
	/* all word count */
	word_cnt = count_word(que);
	fwrite(&word_cnt, 1, 4, fp);
	//printf("%d\n", word_cnt);

	for (pn = que->head->next; pn; pn = pn->next) {
		/* per word length */
		cnt = strlen(pn->data->word) + 1;	
		fwrite(&cnt, 1, 4, fp);
		/* per word content */
		fwrite(pn->data->word, 1, cnt, fp);	
		
		/* translations count corresponding to a word */
		trans_cnt = pn->data->cnt;
		fwrite(&trans_cnt, 1, 4, fp);

		for (i = 0; i < trans_cnt; ++i) {
			/* per translation length */
			cnt = strlen(pn->data->trans[i]) + 1;
			fwrite(&cnt, 1, 4, fp);
			/* per translation content */
			fwrite(pn->data->trans[i], 1, cnt, fp);
		}
	}

	fclose(fp);
}
#if 0
	char *desc = "stardict", *word = "hello", 
	     *trans = "哈喽啊，饭已ok啦，下来米西米西吧！";
	FILE *fp;
	int i, j, cnt, word_cnt = 1, trans_cnt = 1;

	/* write to file */
	fp = fopen("dict.dat", "w");
	/* description */
	cnt = strlen(desc) + 1;
	fwrite(desc, 1, cnt, fp);
	/* all word count */
	fwrite(&word_cnt, 1, 4, fp);
	for (i = 0; i < word_cnt; ++i) {
		/* per word length */
		cnt = strlen(word) + 1;
		fwrite(&cnt, 1, 4, fp);
		/* per word content */
		fwrite(word, 1, cnt, fp);	

		/* translations count corresponding to a word */
		fwrite(&trans_cnt, 1, 4, fp);
		for (j = 0; j < trans_cnt; ++j) {
			/* per translation length */
			cnt = strlen(trans) + 1;
			printf("%d\n", cnt);
			fwrite(&cnt, 1, 4, fp);
			/* per translation content */
			fwrite(trans, 1, cnt, fp);
		}
	}
	fclose(fp);
	return 0;
#endif

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
	convert(que);
#if 0
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
#endif

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

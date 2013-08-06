#include "list.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

/* load dictionary */
queue *load_dict(const char *filename)
{
	FILE *fp;
	char desc[9], *word, *trans;
	int i, j, word_cnt, trans_cnt, cnt;
	item *pi;
	node *pn;
	queue *que;

	que = malloc(sizeof(queue));
	init_queue(que);

	/* the length of string read from file contains '\0' */
	/* read from file */
	fp = fopen(filename, "r");
	if (!fp) {
		printf("Open file %s failed!\n", filename);
		return NULL;
	}

	/* description */
	fread(desc, 1, 9, fp);
	/* all word count */
	fread(&word_cnt, 1, 4, fp);

	for (i = 0; i < word_cnt; ++i) {
		pi = malloc(sizeof(item));
		/* per word length */
		fread(&cnt, 1, 4, fp);
		/* per word content */
		word = malloc(cnt);
		fread(word, 1, cnt, fp);
		pi->word = word;

		/* translations count corresponding to a word */
		fread(&trans_cnt, 1, 4, fp);
		pi->cnt = trans_cnt;
		pi->trans = malloc(sizeof(char *) * trans_cnt);

		for (j = 0; j < trans_cnt; ++j) {
			/* per translation length */
			fread(&cnt, 1, 4, fp);
			/* per translation content */
			trans = malloc(cnt);
			fread(trans, 1, cnt, fp);
			pi->trans[j] = trans;
		}

		/* make node */
		pn = make_node(pi);
		/* enqueue */
		enqueue(que, pn);
	}	

	fclose(fp);
	return que;
}

/* make node */
node *make_node(item *it)
{
	node *n;

	n = malloc(sizeof(node));	/* malloc for node */
	n->data = it;
	n->next = NULL;	
}

/* initialize queue */
void init_queue(queue *que)
{
	que->headnode.data = NULL;
	que->headnode.next = NULL;
	que->head = &(que->headnode);
	que->tail = que->head;
}

/* enqueue */
void enqueue(queue *que, node *n)
{
	que->tail->next = n;
	que->tail = n;
}

/* bulid index */
node **build_index(queue *que, node **index)
{
	int i;
	char ch;
	node *n;

	ch = 'a';
	for (i = 0, n = que->head->next; i < 26; n = n->next) {
		if (*(n->data->word) == ch) {
			index[i] = n;
		} else {
			++i;
			++ch;
		}
	}

	for (i = 25; i > 0; --i)
		index[i] = index[i-1]->next;
	index[0] = que->head->next;

	return index;
}

/* search */
node *search(node **index, char *word)
{
	node *n, *begin;

	if (isalpha(*word))
		begin = index[*word-'a'];
	else
		begin = index['z'-'a'];

	for (n = begin; n; n = n->next) {
		if (strcasecmp(n->data->word, word) == 0) {
			return n;
		}
	}
	return NULL;
}

/* similar search */
node **similar_search(node **index, char *word, node **results)
{
	node *n, *begin;
	int cnt;

	if (isalpha(*word))
		begin = index[*word-'a'];
	else
		begin = index['z'-'a'];

	for (cnt = 0, n = begin; n; n = n->next) {
		if (strcasestr(n->data->word, word) != 0) {
			++cnt;
		}
	}
	results = (node **)malloc(sizeof(node *) * ++cnt);

	for (cnt = 0, n = begin; n; n = n->next) {
		if (strcasestr(n->data->word, word) != 0) {
			results[cnt++] = n;
		}
	}
	results[cnt] = NULL;

	return results;
}

/* search output */
void search_out(node *res)
{
	int i;

	for (i = 0; i < res->data->cnt; ++i)
		printf("0_0 : %s\n", res->data->trans[i]);
	putchar('\n');
}

/* similar search output */
void similar_search_out(node **results)
{
	int i;
	int cnt;

	cnt = 0;
	while (*results) {
		printf("^_^ : %s\n", (*results)->data->word);	
		for (i = 0; i < (*results)->data->cnt; ++i)
			printf("0_0 : %s\n", (*results)->data->trans[i]);

		/* 3 items per time */
		if (++cnt % 3 == 0) {
			printf("%s", "0_0 : More? (y/n): ");			
			if (!confirm(true))
				break;
		}

		++results;
	}	
	putchar('\n');
}

/* add new word */
void add_word(queue * que, char *word)
{
	item *pi;
	node *pn;
	char comments[1024];

	pi = malloc(sizeof(item));
	pi->word = malloc(strlen(word) + 1);
	strcpy(pi->word, word);
	pi->cnt = 1;
	pi->trans = malloc(sizeof(char *));

	printf("%s", "0_0 : Comments?\n*_* : ");
	fgets(comments, sizeof(comments), stdin);

	/* remove '\n' */
	if (comments[strlen(comments)-1] == '\n')
		comments[strlen(comments)-1] = '\0';
	pi->trans[0] = malloc(strlen(comments) + 1);
	strcpy(pi->trans[0], comments);
	puts("^_^ : Copy that!\n");

	/* make node */
	pn = make_node(pi);
	/* enqueue */
	enqueue(que, pn);
}

/* confirm */
bool confirm(bool flag)
{
	char ch, ret;

	ret = ch = getchar();
	while (ch != '\n')
		ch = getchar();

	if (flag)	// flag = true : '\n' <=> 'y'
		return ret == '\n' || ret == 'y';
	else	
		return ret == 'y';
}

/* unload dictionary */
void unload_dict(queue *que, char *filename)
{
	save_queue(que, filename);
	destroy_queue(que);
}

/* save queue */
void save_queue(queue *que, char *filename)
{
	FILE *fp;
	char *desc = "stardict";
	int i, word_cnt, trans_cnt, cnt, total;
	node *pn;

	/* the length of string write to file contains '\0' */
	/* write to file */
	fp = fopen(filename, "w");
	//fp = fopen("user.dat", "w");
	/* description */
	cnt = strlen(desc) + 1;
	fwrite(desc, 1, cnt, fp);
	/* all word count */
	word_cnt = 0;
	fwrite(&word_cnt, 1, 4, fp);

	//total = 0;
	for (pn = que->head->next; pn; pn = pn->next) {
	#if 0
		for (i = 0; i < 3; ++i)
			pn = pn->next;
		if (total > 10000)
			break;
		++total;
		puts(pn->data->word);
	#endif
		++word_cnt;
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

	/* rewrite all word count */
	fseek(fp, strlen(desc)+1, SEEK_SET);
	fwrite(&word_cnt, 1, 4, fp);

	fclose(fp);
}

/* destroy queue */
void destroy_queue(queue *que)
{
	node *pn, *next;
	int i;

	for (pn = que->head->next; pn; pn = next) {
		next = pn->next;

		free(pn->data->word);
		for (i = 0; i < pn->data->cnt; ++i) {
			free(pn->data->trans[i]);
		}
		free(pn->data->trans);

		free(pn);
	}
	free(que);
}

/* challenge */
void challenge(void)
{
	char *userfilename = "user.dat", word[32];
	int ques_amt = 5, word_amt = 10000, i, j;
	queue *userque;
	node *ppn[ques_amt];

	/* load user dictionary */
	userque = load_dict(userfilename);	

	/* select word */
	select_word(userque, ppn, ques_amt, word_amt);
	for (i = 0; i < ques_amt; ++i) {
		/* print translations */
		printf("\n^_^ : ");
		for (j = 0; j < 3 && j < ppn[i]->data->cnt; ++j) {
			printf("%s ", ppn[i]->data->trans[j]);
		}

		/* prompt or not */
		printf("\n%s", "^_^ : Prompt? (y/n) : ");
		if (confirm(true)) {
			printf("^_^ : ");
			for (j = 0; j <= strlen(ppn[i]->data->word) / 3; ++j) {
				putchar(ppn[i]->data->word[j]);	
			}	
			putchar('\n');
		}

		/* input word */
		printf("0_0 : ");
		fgets(word, sizeof(word), stdin);
		/* remove '\n' */
		if (word[strlen(word)-1] == '\n')
			word[strlen(word)-1] = '\0';
		/* give up */
		if (strchr(word, '$')) {
			putchar('\n');
			continue;
		}
		/* compare */
		if (!strcasecmp(word, ppn[i]->data->word)) {
			/* success */
			puts("^_^ : Congratulations!");
			/* remove from user queue */
			delete_node(userque, ppn[i]);
			free(ppn[i]->data->word);
			for (j = 0; j < ppn[i]->data->cnt; ++j) {
				free(ppn[i]->data->trans[j]);
			}
			free(ppn[i]->data->trans);
			free(ppn[i]);
			ppn[i] = NULL;
		} else {
			puts("-_-!: Come on!");	
		}
	}
	putchar('\n');

	/* unload user dictionary */
	unload_dict(userque, userfilename);
}

/* delete node */
node *delete_node(queue *userque, node *t)
{
	node *pn;
	
	for (pn = userque->head->next; pn; pn = pn->next) {
		if (pn->next == t) {
			pn->next = t->next;
			break;
		}	
	}
	return t;
}

/* randomly select a word */
node **select_word(queue *userque, node **ppn, int ques_amt, int word_amt)
{
	node *pn;
	int ran[ques_amt], i;

	srand(time(NULL));
	for (i = 0; i < ques_amt; ++i) {
		ran[i] = rand() % word_amt + 1;	
	}

	for (pn = userque->head->next; pn; pn = pn->next) {
		for (i = 0; i < ques_amt; ++i) {
			if (--ran[i] == 0) {
				ppn[i] = pn;
			}
		}
	}
	return ppn;	
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

#include "list.h"
#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

/* load dictionary */
queue *load_dict(const char *filename)
{
	FILE *fp;
	char word[32], translation[1024];
	item *pi;
	node *pn;
	queue *que;

	/* read file */
	fp = fopen(filename, "r");
	if (!fp) {
		printf("Open file %s failed!", filename);
		return;
	}
	que = malloc(sizeof(queue));
	init_queue(que);
	while (1) {
		if (fgets(word, sizeof(word), fp) == NULL) {
			break;
		}
		if (fgets(translation, sizeof(translation), fp) == NULL) {
			break;
		}
		/* make item */
		pi = make_item(word, translation);
		/* make node */
		pn = make_node(pi);
		/* enqueue */
		enqueue(que, pn);
	}
	fclose(fp);
	return que;
}

/* make item */
item *make_item(char *word, char *translation)
{
	item *pi;
	int cnt, i;
	char *sub, *str;

	/* remove '\n' */
	if (word[strlen(word)-1] == '\n') {
		word[strlen(word)-1] = '\0';
	}
	if (translation[strlen(translation)-1] == '\n') {
		translation[strlen(translation)-1] = '\0';
	}
	/* remove '#' */
	word++;

	/* remove "Trans:" */
	translation += 6;

	/* malloc for item */
	pi = malloc(sizeof(item));
	pi->word = malloc(strlen(word)+1);	/* malloc for word */
	strcpy(pi->word, word);			/* item.word */
	cnt = count_trans(translation);				
	pi->cnt = cnt;				/* item.cnt */
	pi->trans = malloc(cnt * sizeof(char *));/* malloc for trans */
	i = 0;
	while ((sub = strsep(&translation, "@")) != NULL) {
		str = malloc(strlen(sub)+1);	
		strcpy(str, sub);
		pi->trans[i++] = str;		/* item.trans */
	}
	return pi;
}

/* count number of translation */
int count_trans(const char *translation)
{
	int cnt;

	cnt = 1;
	while (*translation) {
		if (*translation++ == '@') {
			++cnt;
		}
	}
	return cnt;
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
	for (i = 25; i > 0; --i) {
		index[i] = index[i-1]->next;
	}
	index[0] = que->head->next;
	return index;
}

/* search */
node *search(node **index, char *word)
{
	node *n, *begin;

	if (isalpha(*word)) {
		begin = index[*word-'a'];
	} else {
		begin = index['z'-'a'];
	}
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

	if (isalpha(*word)) {
		begin = index[*word-'a'];
	} else {
		begin = index['z'-'a'];
	}
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

	for (i = 0; i < res->data->cnt; ++i) {
		printf("0_0 : %s\n", res->data->trans[i]);
	}
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

		for (i = 0; i < (*results)->data->cnt; ++i) {
			printf("0_0 : %s", (*results)->data->trans[i]);
		}
		putchar('\n');

		/* 3 items per time */
		if (++cnt % 3 == 0) {
			printf("%s", "More? (y/n): ");			
			if (!confirm()) {
				break;
			}
		}
		++results;
	}	
	putchar('\n');
}

/* confirm */
bool confirm(void)
{
	char ch, ret;

	ret = ch = getchar();
	while (ch != '\n') {
		ch = getchar();
	}
	return ret == '\n' || ret == 'y';
}

/* unload dictionary */
void unload_dict(queue *que)
{
	destroy_queue(que);
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

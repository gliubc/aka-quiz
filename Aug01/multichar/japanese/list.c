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
	char buf[4096], *word, *translation;
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
	while (fgets(buf, sizeof(buf), fp) != NULL) {
		word = strtok_r(buf, "=", &translation);	

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
	if (translation[strlen(translation)-1] == '\n')
		translation[strlen(translation)-1] = '\0';

	/* malloc for item */
	pi = malloc(sizeof(item));
	pi->word = malloc(strlen(word)+1);	/* malloc for word */
	strcpy(pi->word, word);			/* item.word */
	cnt = count_trans(translation);				
	pi->cnt = cnt;				/* item.cnt */
	pi->trans = malloc(cnt * sizeof(char *));/* malloc for trans */
	i = 0;
	while ((sub = split_str(&translation)) != NULL) {
		str = malloc(strlen(sub)+1);	
		strcpy(str, sub);
		pi->trans[i++] = str;		/* item.trans */
	}

	return pi;
#if 0
#endif
}

/* count number of translation */
int count_trans(const char *translation)
{
	int cnt;

	cnt = 1;
	while (*(translation) && *(translation+1) && *(translation+2)) {
		if (*translation == 0xffffffef && 
				*(translation+1) == 0xffffffbc && 
				*(translation+2) == 0xffffff8e)
			++cnt;
		++translation;	
	}

	return cnt;
}

/* split string */
char *split_str(char **translation)
{
	static char *remainder = NULL;	
	char *p;
	
	if (remainder == NULL) {
		remainder = malloc(strlen(*translation) + 1);
		strcpy(remainder, *translation);
	}

	if (*remainder == '\0') {
		free(remainder);	
		remainder = NULL;
		return NULL;
	}

	p = remainder;
	while (*p && *(p+1) && *(p+2)) {
		if (*p == 0xffffffef && 
				*(p+1) == 0xffffffbc && 
				*(p+2) == 0xffffff8e) {
			*p = *(p+1) = *(p+2) = '\0';
			p = p + 3;
			memmove(*translation, remainder, strlen(remainder)+1);
			memmove(remainder, p, strlen(p)+1);
			return *translation;
		}
		++p;
	} 
	memmove(*translation, remainder, strlen(remainder)+1);
	*remainder = '\0';
	return *translation;
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

/* search */
node *search(queue *que, char *word)
{
	node *n;

	for (n = que->head->next; n; n = n->next) {
		if (strcasecmp(n->data->word, word) == 0) {
			return n;
		}
	}
	return NULL;
}

/* similar search */
node **similar_search(queue *que, char *word, node **results)
{
	node *n;
	int cnt;

	for (cnt = 0, n = que->head->next; n; n = n->next) {
		if (strcasestr(n->data->word, word) != 0) {
			++cnt;
		}
	}
	results = (node **)malloc(sizeof(node *) * ++cnt);

	for (cnt = 0, n = que->head->next; n; n = n->next) {
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
			printf("%s", "More? (y/n): ");			
			if (!confirm())
				break;
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
	while (ch != '\n')
		ch = getchar();
	
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

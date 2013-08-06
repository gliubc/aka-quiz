#ifndef _LIST_H_
#define _LIST_H_
#include <stdbool.h>

/* word item contains word and translations */
typedef struct item {
	char *word, **trans;
	int cnt;
} item;

/* node contains item and next node */
typedef struct node {
	item *data;
	struct node *next;	
} node;

/* queue contains head and tail of node */
typedef struct queue {
	node headnode;
	node *head;
	node *tail;
} queue;

/* load dictionary */
queue *load_dict(const char *filename);

/* bulid index */
node **build_index(queue *que, node **index);

/* make item */
item *make_item(char *word, char *translation);

/* count number of translation */
int count_trans(const char *translation);

/* make node */
node *make_node(item *it);

/* initialize queue */
void init_queue(queue *que);

/* enqueue */
void enqueue(queue *que, node *n);

/* search */
node *search(node **index, char *word);

/* similar search */
node **similar_search(node **que, char *word, node **results);

/* confirm */
bool confirm(void);

/* search output */
void search_out(node *res);

/* similar search output */
void similar_search_out(node **results);

/* unload dictionary */
void unload(queue *que);

/* destroy queue */
void destroy_queue(queue *que);

#endif //_LIST_H_

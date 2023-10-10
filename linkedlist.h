/*
 * Public
 */
struct node {
  char *value;
  struct node *next;
};

struct list {
  struct node *head;
  struct node *tail;
};

struct list *list_new();
void list_append(struct list *list, const char *value);
struct node *list_find(struct list *list, const char *value);
void list_free(struct list *list);

void list_print(struct list *list);
void node_print(struct node *node);

/*
 * Private
 */

struct node *node_new(const char *value);

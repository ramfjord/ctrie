#define TRY_END_INDEX -1

typedef struct trynode{	
  void		*payload;
  int		nchildren;
  struct trynode **children;
  int		nbelow;
  int		(*get_index)(void *);
  int		cur_i;
} trynode;

trynode *init_trymap(int (*indexer)(void *), int n_children);

int put_try(trynode *root, void *key, void *val);
int sput_try(trynode *root, char *key, void *val);
int iput_try(trynode *root, int *key, void *val);

void *get_try(trynode *root, void *key);
void *sget_try(trynode *root, char *key);
void *iget_try(trynode *root, int *key);

int size_try(trynode *root);

int traverse_from_0(trynode *root);

int free_try(trynode *root);

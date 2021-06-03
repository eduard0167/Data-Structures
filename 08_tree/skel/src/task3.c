#include "binary_tree.h"

#define MAX_NODES 100

void read_tree(b_tree_t *b_tree)
{
    int i, N, data;

    scanf("%d", &N);

    for (i = 0; i < N; ++i) {
        scanf("%d", &data);
        b_tree_insert(b_tree, &data);
    }
}

int tree_is_complete(b_tree_t *binary_tree)
{
  if (!binary_tree->root) {
      return 0;
  }

  queue_t *q = q_create(sizeof(void**), MAX_NODES);
  q_enqueue(q, &binary_tree->root);
  int found = 0;
  while (!q_is_empty(q)) {
      b_node_t *tmp = *(b_node_t**)q_front(q);
      
      if (!tmp->left) {
          found = 1;
      } else if (!found) {
          q_enqueue(q, &(tmp->left));
      } else {
        return 0;
      }
      
      if (!tmp->right) {
          found = 1;
      } else if (!found) {
          q_enqueue(q, &(tmp->right));
      } else {
        return 0;
      }

      q_dequeue(q);
  }

  return 1;
}

int main(void)
{
    b_tree_t *binary_tree = b_tree_create(sizeof(int));
    read_tree(binary_tree);

    if (tree_is_complete(binary_tree)) {
        printf("true");
    } else {
        printf("false");
    }

    b_tree_free(binary_tree, free);
    return 0;
}
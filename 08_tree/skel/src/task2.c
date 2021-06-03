/**
 * SD, 2020
 * 
 * Lab #8, Binary Tree
 * 
 * Task #2 - <resume_or_paste_the_task_here>
 */

#include "binary_tree.h"

void read_tree(b_tree_t *b_tree)
{
    int i, N, data;

    scanf("%d", &N);

    for (i = 0; i < N; ++i) {
        scanf("%d", &data);
        b_tree_insert(b_tree, &data);
    }
}

static int __is_sum_of_children(b_node_t *root) {
    // nu exista root sau root este frunza
    if (!root || (!root->left && !root->right)) {
        return 1;
    }

    // root are doar fiul stang
    if (!root->right) {
        return (*(int*)root->data) == (*(int*)root->left->data) &&  __is_sum_of_children(root->left);
    }
    // root are doar fiul drept
    if (!root->left) {
        return (*(int*)root->data) == (*(int*)root->right->data) && __is_sum_of_children(root->right);
    }
    // root are ambii fii
    return ((*(int*)root->data) == (*(int*)root->right->data) + (*(int*)root->left->data)) && 
        __is_sum_of_children(root->left) && __is_sum_of_children(root->right);

}

int is_sum_of_children(b_tree_t *b_tree) {
    return __is_sum_of_children(b_tree->root);
}

int main(void)
{
    b_tree_t *binary_tree = b_tree_create(sizeof(int));
    read_tree(binary_tree);

    if (is_sum_of_children(binary_tree)) {
        printf("true");
    } else {
        printf("false");
    }

    b_tree_free(binary_tree, free);
    return 0;
}

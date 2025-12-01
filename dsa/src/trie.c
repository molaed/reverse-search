#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dsa/dsa_errno.h"
#include "dsa/trie.h"

// If a string has children, it is unlikely to be sparse
#define STARTING_CHILDREN_AMT 8

#ifdef DEBUG
#define IS_POWER_OF_TWO(x) (((x) & ((x)-1)) == 0)
#else
#define IS_POWER_OF_TWO(x) (((x) > 8) && (((x) & ((x)-1)) == 0))
#endif

struct Node {
    char letter;
    bool is_end_of_word;
    size_t num_children;
    uint8_t num_usages; // TODO: implement a most freq sorting
    struct Node *children;
};

static struct Node root = {
    .letter = 0,
    .is_end_of_word = false,
    .num_children = 0,
    .num_usages = 0,
    .children = NULL,
};

dsa_errno_t trie_insert_word(char *new_word) {
    struct Node *cur = &root;

    for (size_t i = 0; i < strlen(new_word); i++) {
        if (cur->children == NULL) {
            cur->children = calloc(STARTING_CHILDREN_AMT, sizeof(struct Node));

            cur->num_children++;
            cur = cur->children;
            cur->letter = new_word[i];

        } else {
            if (IS_POWER_OF_TWO(cur->num_children)) {
                // should never be realloced to > 128 as we only accept standard ascii
                // '~' = 126, ' ' = 32: difference of 94        
                void *tmp = realloc(cur->children, 2 * cur->num_children * sizeof(struct Node));

                if (tmp == NULL) {
                    free(cur->children);
                    return DSA_OUT_OF_MEM; // catastrophic failure, delete entire tree

                } else {
                    cur->children = tmp;
                }
            }

            bool found_letter = false;
            for (size_t j = 0; j < cur->num_children; j++) { // TODO: consider starting at index proportional to the letter order 
                if (cur->children[j].letter == new_word[i]) {
                    cur = cur->children + j;
                    found_letter = true;
                    break; 
                }
            }

            if (!found_letter) {
                cur->num_children++;
                cur = cur->children + cur->num_children - 1;
                cur->letter = new_word[i];
            }
        }
    }

    cur->is_end_of_word = true;

    return DSA_NO_ERR;
}

#ifdef DEBUG
static dsa_errno_t trie_debug_print_all_recursive(struct Node *node);

dsa_errno_t trie_debug_print_all() {
    return trie_debug_print_all_recursive(&root);
}

static dsa_errno_t trie_debug_print_all_recursive(struct Node *node) {
    dsa_errno_t ret = DSA_NO_ERR;
    if (node == NULL) return ret;

    printf("letter: %c, num_children: %ld, word_end: %s\n", 
            node->letter, node->num_children, (node->is_end_of_word ? "true" : "false"));

    for (uint8_t i = 0; i < node->num_children; i++) {
        ret = trie_debug_print_all_recursive(node->children + i);
    }

    return ret;
}
#endif
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "dsa/dsa_errno.h"
#include "dsa/trie.h"

// If a string has children, it is unlikely to be sparse
#define STARTING_CHILDREN_AMT 8

#define IS_POWER_OF_TWO(x) (((x) & ((x)-1)) == 0)

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
            cur->children = calloc(STARTING_CHILDREN_AMT, sizeof (struct Node));

            cur->num_children++;
            cur->children[0].letter = new_word[i];
            cur = cur->children;

        } else {
            if (IS_POWER_OF_TWO(cur->num_children)) {
                // should never be realloced to > 128 as we only accept standard ascii
                // '~' = 126, ' ' = 32: difference of 94
                
                void *tmp = realloc(cur->children, cur->num_children * 2);

                if (tmp == NULL) return DSA_OUT_OF_MEM; 
                else cur->children = tmp;
            }

            // TODO: consider starting at index proportional to the letter order 
            for (size_t j = 0; j < cur->num_children; j++) {
                if (cur->children[j].letter == new_word[i]) {
                    cur = cur->children + j; 
                }
            }
        }
    }

    cur->is_end_of_word = true;

    return DSA_NO_ERR;
}
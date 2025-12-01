#ifndef _INC_TRIE_
#define _INC_TRIE_

#include "dsa/dsa_errno.h"

uint8_t trie_insert_word(char *new_word);

#ifdef DEBUG
uint8_t trie_debug_print_all();
#endif

#endif
#include "dsa/trie.h"

int main() {
#ifdef DEBUG
    trie_insert_word("ooglyboogly");
    trie_insert_word("ooglyboogly");
    trie_insert_word("ooglyboog");
    trie_insert_word("aaazzz");
    trie_insert_word("aaa");
    trie_insert_word("ooo");
    trie_debug_print_all();
#endif

    return 0;
}
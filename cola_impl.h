#include "cola_puzzle.h"

SGLIB_DEFINE_RBTREE_FUNCTIONS(puzzle_rb_tree, left, right, color, PUZZLE_RB_CMPARATOR)
SGLIB_DEFINE_RBTREE_FUNCTIONS(rb_tree, left, right, color, PUZZLE_HASH_COMPARATOR)
SGLIB_DEFINE_HASHED_CONTAINER_FUNCTIONS(rb_tree, HASH_SIZE, puzzle_list_hash_function)

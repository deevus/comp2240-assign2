/*
	gcc atomic builtins
*/

/* increment count */
#define atomic_inc(ptr) (__sync_fetch_and_add(ptr, 1)) 
/* decrement count */
#define atomic_dec(ptr) (__sync_fetch_and_sub(ptr, 1)) 
/* swap/compare */
#define atomic_compare_swap(ptr, old, new) __sync_val_compare_and_swap(ptr, old, new)
#include <stdio.h>
#include <string.h>
#include "minunit.h"
#include "linkedlist.h"

int tests_run = 0;

static char *test_linkedlist_insert_one() {
	linkedlist_t list;
	linkedlist_init(&list);

	int x = 5;
	linkedlist_insert(&list, &x);

	mu_assert_equals_int("Error: insert error.", x, *(int *)linkedlist_gethead(&list));
	mu_assert_equals_int("Error: incorrect size.", 1, linkedlist_getsize(&list));

	linkedlist_destroy(&list);
	return 0;
}

static char *test_linkedlist_insert_two() {
	linkedlist_t list;
	linkedlist_init(&list);

	int x = 1;
	linkedlist_insert(&list, &x);

	mu_assert_equals_int("Error: Invalid head value", 
		x, 
		*(int *)linkedlist_gethead(&list));

	int y = 2;
	linkedlist_insert(&list, &y);

	mu_assert_equals_int("Error: Invalid head value", 
		x, 
		*(int *)linkedlist_gethead(&list));

	mu_assert_equals_int("Error: Invalid tail value", 
		y, 
		*(int *)linkedlist_gettail(&list));

	mu_assert_equals_int("Error: incorrect size.", 2, linkedlist_getsize(&list));

	linkedlist_destroy(&list);
	return 0;
}

static char *test_linkedlist_remove() {
	linkedlist_t list;
	linkedlist_init(&list);

	int x = 1, y = 2, z = 3;
	linkedlist_insert(&list, &x); 
	linkedlist_insert(&list, &y);
	linkedlist_insert(&list, &z);

	mu_assert_equals_int("Error: head value", x, *(int *)linkedlist_gethead(&list));
	mu_assert_equals_int("Error: tail value", z, *(int *)linkedlist_gettail(&list));
	mu_assert_equals_int("Error: size value before remove", 3, linkedlist_getsize(&list));

	linkedlist_remove(&list, &y);

	mu_assert_equals_int("Error: head value", x, *(int *)linkedlist_gethead(&list));
	mu_assert_equals_int("Error: tail value", z, *(int *)linkedlist_gettail(&list));
	mu_assert_equals_int("Error: size value after remove", 2, linkedlist_getsize(&list));

	linkedlist_destroy(&list);
	return 0;
}

static char *all_tests() {
	mu_run_test(test_linkedlist_insert_one);
	mu_run_test(test_linkedlist_insert_two);
	mu_run_test(test_linkedlist_remove);
	return 0;
} 

int main(int argc, char *argv[]) {
	char *result = all_tests();
	if (result != 0) {
		printf("%s\r\n", result);
	}
	else {
		printf("ALL TESTS PASSED\r\n");
		printf("Tests run: %d\r\n", tests_run);

		return result != 0;
	}
}
#include <stdio.h>
#include <string.h>
#include "minunit.h"
#include "node.h"

int tests_run = 0;

static char *test_node_init() {
	node_t node;
	int n = 5;
	node_init(&node, &n);

	mu_assert_equals_int("Error: Invalid value", n, *(int *)node.data);
	return 0;
}

static char *test_node_link_two() {
	node_t n, m;
	int x = 1, y = 2;

	node_init(&n, &x);
	node_init(&m, &y);

	n.nextptr = &m;
	m.prevptr = &n;

	mu_assert_equals_int("Error: left node invalid.", x, *(int *)n.data);
	mu_assert_equals_int("Error: right node invalid.", y, *(int *)m.data);
	return 0;
}

static char *all_tests() {
	mu_run_test(test_node_init);
	mu_run_test(test_node_link_two);
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

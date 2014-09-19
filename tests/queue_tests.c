#include <stdio.h>
#include <string.h>
#include "minunit.h"
#include "queue.h"

int tests_run = 0;

static char *test_queue_empty() {
	queue_t queue;
	queue_init(&queue);

	mu_assert("Error: queue not empty", queue_isempty(&queue));
	queue_destroy(&queue);
	return 0;
}

static char *test_queue_one() {
	queue_t queue;
	queue_init(&queue);

	int x = 5;
	queue_enqueue(&queue, &x);

	int front = *(int *)queue_front(&queue);
	mu_assert_equals_int("Error: Incorrect value", x, front);
	mu_assert("Error: queue reporting empty", !queue_isempty(&queue));

	queue_destroy(&queue);
	return 0;
}

static char *test_queue_dequeue() {
	queue_t queue;
	queue_init(&queue);

	int x = 5;
	queue_enqueue(&queue, &x);
	queue_dequeue(&queue);
	mu_assert("Error: queue not empty", queue_isempty(&queue));

	queue_destroy(&queue);
	return 0;	
}

static char *test_queue_two() {
	queue_t queue;
	queue_init(&queue);

	int x = 5, y = 6;
	queue_enqueue(&queue, &x);
	queue_enqueue(&queue, &y);

	int front = *(int *)queue_front(&queue);
	mu_assert_equals_int("Error: Incorrect value", x, front);
	mu_assert_equals_int("Error: Incorrect size", 2, queue_getsize(&queue));

	queue_dequeue(&queue);
	front = *(int *)queue_front(&queue);
	mu_assert_equals_int("Error: Incorrect value", y, front);
	mu_assert_equals_int("Error: Incorrect size", 1, queue_getsize(&queue));

	mu_assert("Error: queue reporting empty", !queue_isempty(&queue));
	queue_destroy(&queue);
	return 0;
}

static char *all_tests() {
	mu_run_test(test_queue_empty);
	mu_run_test(test_queue_one);
	mu_run_test(test_queue_two);
	mu_run_test(test_queue_dequeue);
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
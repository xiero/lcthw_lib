#include "minunit.h"
#include <lcthw/list_algos.h>
#include <assert.h>
#include <string.h>

char* values[] = {"xxxx", "1234", "abcd", "xjvet", "NDSS"};

#define NUM_VALES 5

List *create_words()
{
    int i = 0;
    List *words = List_create();

    for(i = 0; i < NUM_VALUES; i++)
    {
		List_push(words, values[i]);
    }

    return words;
}
//-------------------------------------------------------------------------
int is_sorted(List* words)
{
	LIST_FOREACH(words, first, next, cur)
	{
		if(cur->next && strcmp(cur->value, cur->next->value) > 0)
		{
			debug("%s %s",(char*)cur->value, (char*)cur->next->value);
			return 0;
		}
	}

	return 1;
}
//--------------------------------------------------------------------------
char *test_bubble_sort()
{
	List* words = create_words();

	//should work on a list that needs sorting
	int rc = List_bubble_sort(words, (List_compare) strcmp);

	mu_assert( rc == 0, "Bubble sort failed.");
	mu_assert(is_sorted(words), "Words are not sorted after bubble sort.");

	//should work on an already sorted list
	rc = List_bubble_sort(words, (List_compare) strcmp);
	mu_assert(rc == 0, "Bubble sort of already sorted failed.");
	mu_assert(is_sorted(words), "Words should be sort if already bubble sorted.");

	List_destroy(words);

	//should work on an empty list
	words = List_create(words);
	rc = List_bubble_sort(words, (List_compare) strcmp);

	mu_assert(rc == 0, "Bubble sort failed on empty list.");
	mu_assert(is_sorted(words), "Words should be sorted if empty.");

	List_destroy(words);

	return NULL;
}
//--------------------------------------------------------------------------------
char *test_merge_sort()
{
	List *words = create_words();

	//should work on a list that needs sorting
	List *res = List_merge_sort(words, (List_compare) strcmp);
	mu_assert(is_sorted(res), "Should still be sorted after merge sort.");

	List *res2 = List_merge_sort(res, (List_compare) strcmp);
	mu_assert(is_sorted(res), "Should still be sorted after merge sort");

	List_destroy(res2);
	List_destroy(res);

	List_destroy(words);
	return NULL;
}
//--------------------------------------------------------------------------------

RUN_TESTS(all_tests);

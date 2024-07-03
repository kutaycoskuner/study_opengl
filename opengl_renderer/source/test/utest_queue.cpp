// lib
#include "../../headers/abstract/queue.h"
#include "../../headers/utils/utilities.h"
#include <cassert>

// self keys
using namespace math_utils;


// pre
void unitTest_Queue();

// functions
static void unitTest_Queue_defaultConstructor()
{
	Queue<int> q;
	assert(
		q.is_empty() == true
	);
}

static void unitTest_Queue_functions()
{
	Queue<int> q;
	
	q.add(3);
	q.add(4);
	assert(
		q.peek() == 3
	);

	q.remove();
	assert(
		q.peek() == 4
	);

	q.add(25);
	q.add(26);
	assert(
		q.size() == 3
	);
	assert(
		q.is_empty() == false
	);
}

void unitTest_Queue()
{
	unitTest_Queue_defaultConstructor();
	unitTest_Queue_functions();
}

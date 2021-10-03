#pragma warning (disable : 5045)
#include "unitTests.h"
#include <assert.h>

void assertInnerLIst(const void* self, int* arr, size_t arrSize)
{
	const arrayList* list = (const arrayList*)self;
	assert(arrSize == list->size);
	
	for (size_t i = 0; i < list->size; i++)
		assert(list->list[i] == arr[i]);
}

void assertList(const void* self, const void* other)
{
	const arrayList* list = (const arrayList*)self;
	const arrayList* another = (const arrayList*)other;

	assert(list->capacity == another->capacity);
	assert(list->size == another->size);

	for (size_t i = 0; i < list->size; i++)
		assert(list->list[i] == another->list[i]);
}

void addTest(void)
{
	arrayList* list = newArrayList();

	//add an element to an empty list
	int element = 1;
	list->add(list, element);
	assertInnerLIst(list, &element, 1);

	//add an element to a populated list
	int arr[] = { 1, 2, 3, 4 };
	for (size_t i = 1; i < sizeof(arr) / sizeof(arr[0]); i++)
		list->add(list, arr[i]);

	assertInnerLIst(list, arr, sizeof(arr) / sizeof(arr[0]));
	destruct(list);
}

void addAllTest(void)
{
	arrayList* list = newArrayList();
	int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
	list->addAll(list, arr, sizeof(arr) / sizeof(arr[0]));
	assertInnerLIst(list, arr, sizeof(arr) / sizeof(arr[0]));
	destruct(list);
}

void clearTest(void)
{
	//construct a list
	arrayList* list = newArrayList();
	int arr[] = { 1, 2, 3, 4 };
	list->addAll(list, arr, sizeof(arr) / sizeof(arr[0]));

	size_t capacity = list->capacity;

	//clear the list
	list->clear(list);

	assert(capacity == list->capacity);
	assert(list->size == 0);

	destruct(list);
}

void cloneTest(void)
{
	arrayList* list = newArrayList();
	int arr[] = { 1, 2, 3, 4 };
	list->addAll(list, arr, sizeof(arr) / sizeof(arr[0]));

	arrayList* another = list->clone(list);

	assertList(list, another);

	destruct(another);
	destruct(list);
}

void containsTest(void)
{
	arrayList* list = newArrayList();
	int arr[] = { 1, 2, 3, 4 };
	list->addAll(list, arr, sizeof(arr) / sizeof(arr[0]));

	for (size_t i = 0; i < 10; i++)
	{
		if (i < list->size)
			assert(list->contains(list, arr[i]));
		else
			assert(!list->contains(list, 5));
	}

	destruct(list);
}

void getTest(void)
{
	arrayList* list = newArrayList();
	int arr[] = { 1, 2, 3, 4 };
	list->addAll(list, arr, sizeof(arr) / sizeof(arr[0]));

	bool valid;

	//assert valid index
	int element = list->get(list, 2, &valid);
	assert(valid);
	assert(element == 3);

	//assert invalid index
	element = list->get(list, 4, &valid);
	assert(!valid);
	assert(element == -1);

	//assert invalid index
	element = list->get(list, -1, &valid);
	assert(!valid);
	assert(element == -1);

	destruct(list);
}

void indexOfTest(void)
{
	arrayList* list = newArrayList();
	int arr[] = { 1, 2, 3, 4 };
	list->addAll(list, arr, sizeof(arr) / sizeof(arr[0]));

	assert(list->indexOf(list, 3) == 2);
	assert(list->indexOf(list, -100) == -1);

	destruct(list);
}

void isEmptyTest(void)
{
	arrayList* list = newArrayList();

	assert(list->isEmpty(list));

	int arr[] = { 1, 2, 3, 4 };
	list->addAll(list, arr, sizeof(arr) / sizeof(arr[0]));

	assert(!list->isEmpty(list));

	list->clear(list);

	assert(list->isEmpty(list));

	destruct(list);
}

void removeElementTest(void)
{
	arrayList* list = newArrayList();
	int arr[] = { 1, 2, 3, 4, 2 };
	list->addAll(list, arr, sizeof(arr) / sizeof(arr[0]));
	size_t size = list->size;

	assert(list->removeElement(list, 2));
	assert(list->size == size - 1);
	bool valid;
	assert(list->get(list, 1, &valid) == 3);
	assert(list->indexOf(list, 2) == 3);

	size = list->size;
	assert(!list->removeElement(list, 5));
	assert(list->size == size);

	destruct(list);

	list = newArrayList();
	int anohterArr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	list->addAll(list, anohterArr, sizeof(anohterArr) / sizeof(anohterArr[0]));
	size = list->size;

	assert(list->removeElement(list, 10));
	assert(list->size == size - 1);
	assert(list->get(list, (int)list->size - 1, &valid) == 9);

	destruct(list);
}

void removeAllTest(void)
{
	arrayList* list = newArrayList();
	int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	list->addAll(list, arr, sizeof(arr) / sizeof(arr[0]));
	size_t size = list->size;

	int del[] = { 4,5,6 };
	assert(list->removeAll(list, del, sizeof(del) / sizeof(del[0])));
	assert(list->size == size - sizeof(del) / sizeof(del[0]));

	size = list->size;
	int del2[] = { 0, 1 };
	assert(!list->removeAll(list, del2, sizeof(del2) / sizeof(del2[0])));
	assert(list->size == size - sizeof(del2) / sizeof(del2[0]) + 1);

	destruct(list);
}

void toArrayTest(void)
{
	arrayList* list = newArrayList();
	int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	list->addAll(list, arr, sizeof(arr) / sizeof(arr[0]));

	int* toArr = list->toArray(list);
	assertInnerLIst(list, toArr, list->size);

	free(toArr);
	destruct(list);
}

void runTests(void)
{
	addTest();
	addAllTest();
	clearTest();
	cloneTest();
	containsTest();
	getTest();
	indexOfTest();
	isEmptyTest();
	removeElementTest();
	removeAllTest();
}
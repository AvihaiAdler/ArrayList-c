#pragma warning (disable : 5045)
#include "arrayList.h"

arrayList* newArrayList(void)
{
	arrayList* list = malloc(sizeof* list);
	if (!list)
		return NULL;

	list->capacity = 0;
	list->size = 0;
	list->list = NULL;

	list->add = add;
	list->addAll = addAll;
	list->clear = clear;
	list->clone = clone;
	list->contains = contains;
	list->get = get;
	list->indexOf = indexOf;
	list->isEmpty = isEmpty;
	list->removeElement = removeElement;
	list->removeAll = removeAll;
	list->getSize = getSize;
	list->sort = sort;
	list->toArray = toArray;

	return list;
}

bool allocate(arrayList* self, int capacity)
{
	self->capacity = capacity;
	int* tmp = realloc(self->list, self->capacity * sizeof * self->list);
	if (!tmp)
		return false;

	self->list = tmp;
	return true;
}

bool add(void* self, int element)
{
	arrayList* list = (arrayList*)self;
	bool alloc = false;
	bool allocted = false;

	if (!list->capacity) 
	{
		//empty list
		alloc = allocate(list, BASE_CAPACITY);
		allocted = true;
	}
	else if (list->size >= list->capacity - 1) 
	{
		//full list
		alloc = allocate(list, (int)list->capacity * BASE_CAPACITY);
		allocted = true;
	}

	if (allocted && !alloc)	//failure to allocate
		return false;

	list->list[list->size] = element;
	list->size++;
	return true;
}

bool addAll(void* self, const int elements[], size_t size)
{
	arrayList* list = (arrayList*)self;

	for (size_t i = 0; i < size; i++)
	{
		bool res = add(list, elements[i]);
		if (!res)
			return false;
	}

	return true;
}

void clear(void* self)
{
	arrayList* list = (arrayList*)self;
	list->size = 0;
	free(list->list);
	list->list = NULL;
}

arrayList* clone(const void* self)
{
	const arrayList* list = (const arrayList*)self;
	arrayList* tmp = newArrayList();
	
	for (size_t i = 0; i < list->size; i++)
		add(tmp, list->list[i]);
	return tmp;
}

bool contains(const void* self, int element)
{
	int index = indexOf(self, element);
	if (index < 0)
		return false;
	return true;
}

int indexOf(const void* self, int element)
{
	const arrayList* list = (const arrayList*)self;
	for (size_t i = 0; i < list->size; i++)
	{
		if (list->list[i] == element)
			return (int)i;
	}
	return -1;
}

int get(const void* self, int index, bool* valid)
{
	const arrayList* list = (const arrayList*)self;
	if (index >= (int)list->size || index < 0)
	{
		*valid = false;
		return -1;
	}
	else
		*valid = true;

	return list->list[index];
}

bool isEmpty(const void* self)
{
	if (((const arrayList*)self)->size > 0)
		return false;
	return true;
}

bool removeElement(void* self, int element)
{
	arrayList* list = (arrayList*)self;

	int index = indexOf(self, element);
	if (index < 0)
		return false;

	for (size_t i = 0; i < list->size; i++)
		if ((int)i >= index)
			list->list[i] = list->list[i + 1];
	list->size--;
	return true;
}

bool removeAll(void* self, const int elements[], size_t size)
{
	bool allDeleted = true;
	for (size_t i = 0; i < size; i++)
		allDeleted &= removeElement(self, elements[i]);

	return allDeleted;
}

size_t getSize(const void* self)
{
	return ((const arrayList*)self)->size;
}

void destruct(arrayList* list)
{
	if (list)
	{
		if (list->capacity)
			free(list->list);
		free(list);
	}
}

int compare(const void* a, const void* b)
{
	int aa = *(const int*)a;
	int bb = *(const int*)b;
	return (aa > bb) - (aa < bb);
}

void sort(void* self)
{
	arrayList* list = (arrayList*)self;
	qsort(list->list, list->size, sizeof * list->list, compare);
}

int* toArray(const void* self)
{
	const arrayList* list = (const arrayList*)self;
	if (!list->size)
		return NULL;

	int* arr = malloc(list->size * sizeof * list->list);
	if (!arr)
		return NULL;

	for (size_t i = 0; i < list->size; i++)
		arr[i] = list->list[i];
	return arr;
}

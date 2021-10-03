#ifndef ARRAY_LIST__
#define ARRAY_LIST__
#include <stdbool.h>
#include <stdlib.h>

#define MULTIPLIER 2
#define BASE_CAPACITY 10

//array list for simple int primitive using OOP style functions
typedef struct arrayList
{
	int* list;
	size_t capacity;
	size_t size;

	bool (*add)(void* self, int);
	bool (*addAll)(void* self, const int[], size_t size);
	void (*clear)(void* self);	
	struct arrayList* (*clone)(const void* self);
	bool (*contains)(const void* self, int);
	int (*get)(const void* self, int index, bool* valid);
	int (*indexOf)(const void* self, int element);
	bool (*isEmpty)(const void* self);
	bool (*removeElement)(void* self, int element);
	bool (*removeAll)(void* self, const int elements[], size_t size);
	size_t (*getSize)(const void* self);
	int* (*toArray)(const void* self);
	void (*sort)(void* self);
}arrayList;

//initialization
arrayList* newArrayList(void);

//append an element to the end of the list
bool add(void* self, int element);

//append an array of elements to the end of the list
bool addAll(void* self, const int elements[] , size_t size);

//clear all elements in the list, capacity doesn't change, size becomes 0
void clear(void* self);

//retruns a new array list which contains all the element in self->list
arrayList* clone(const void* self);

//returns true if element found in self->list, false otherwise
bool contains(const void* self, int element);

//get the element at index [index], returns -1 and sets valid to 0 if index >= size
int get(const void* self, int index, bool* valid);

//returns the index of the first occurrence of an element, return -1 if no element found 
int indexOf(const void* self, int element);

//returns true if size <= 0
bool isEmpty(const void* self);

//remove the first occurrence of an element, returns false if no element found
bool removeElement(void* self, int element);

//remove all of the first occurrences of an array of elements, returns true if ALL elements got deleted, false otherwise
bool removeAll(void* self, const int elements[], size_t size);

//returns the number of elements in list->list (or list->size)
size_t getSize(const void* self);

//sort the list (ascending)
void sort(void* self);

//returns a copy of list->list. must be freed seperately
int* toArray(const void* self);

//destructor, free(list->list) and free(array list)
void destruct(arrayList* list);	

#endif // !ARRAY_LIST__



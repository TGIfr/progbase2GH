//
// Created by tgifr on 26.02.17.
//

#include <malloc.h>
#include <assert.h>
#include "list.h"

struct Student{
    char * name;
    int course;
    float mark;
};
struct Teacher {
    char * Name;
    List * list;
};

Teacher * Teacher_new(char * name){
    Teacher * res = malloc(sizeof(Teacher));
    res->Name = name;
    res->list = NULL;
    return res;
}
void Teacher_free(Teacher ** teacher){
    free(*teacher);
    *teacher = NULL;
}
void Teacher_attachList(Teacher * teacher, List * toAttach){
    teacher->list = toAttach;
}
char * Teacher_getName(Teacher * teacher){
    return teacher->Name;
}
List * Teacher_getList(Teacher * teacher){
    return teacher->list;
}

List * separateLists(Teacher * first, Teacher * second){
    List * result = List_new();
    List * firstList = Teacher_getList(first);
    List * secondList = Teacher_getList(second);
    int length = List_count(secondList);
    for (int i = 0; i < length; ++i) {
        Student * temp = List_get(secondList, i);
        if(List_contains(firstList, temp) == 0){
            List_add(result, Student_new(Student_getName(temp), Student_getCourse(temp), Student_getMark(temp)));
        }
    }
    return result;
}


Student * Student_new(char * name, int course, float mark){
    Student * new = malloc(sizeof(Student));
    new->course = course;
    new->name = name;
    new->mark = mark;
    return new;
}
char * Student_getName(Student * stud){
    return stud->name;
}
int Student_getCourse(Student *stud){
    return stud->course;
}
float Student_getMark(Student *stud){
    return stud->mark;
}
void Student_free(Student ** self){
    free(*self);
    *self = NULL;
}


#define throw(MSG) assert(0 && MSG);

struct List {
    size_t capacity;
    size_t size;
    void ** items;    /**< holds a pointer to items array */
};

static const int initialCapacity = 4;

static void __ensureCapacity(List * self, size_t min);

List * List_new(void) {
    List * self = malloc(sizeof(struct List));
    self->capacity = initialCapacity;
    self->size = 0;
    self->items = malloc(0);
    __ensureCapacity(self, 0);
    return self;
}

void List_free(List ** selfPtr) {
    if (selfPtr == NULL) throw("Null pointer on free()");
    List * self = *selfPtr;
    free(self->items);
    free(self);
    *selfPtr = NULL;
}

void * List_get(List * self, int index) {
    if (index < 0 || index >= self->size) throw("Index out of bounds");
    return self->items[index];
}
void List_set(List * self, int index, void * ref) {
    if (ref == NULL) throw("NULL reference");
    if (index < 0 || index >= self->size) throw("Index out of bounds");
    self->items[index] = ref;
}
void List_add(List * self, void * ref) {
    if (ref == NULL) throw("NULL reference");
    if (self->size <= self->capacity) {
        __ensureCapacity(self, self->size + 1);
    }
    List_set(self, self->size++, ref);
}


int List_indexOf(List * self, void * ref) {
    if (ref == NULL) throw("NULL reference");
    for (int i = 0; i < self->size; i++) {
        if (self->items[i] == ref) {
            return i;
        }
    }
    return -1;
}

int List_contains(List * self, void * ref) {
    if (ref == NULL) throw("NULL reference");
    return List_indexOf(self, ref) >= 0;
}



int List_isEmpty(List * self) {
    return self->size == 0;
}

int  List_count(List * self) {
    return self->size;
}


static void __ensureCapacity(List * self, size_t min) {
    if (self->size <= min) {
        int newCapacity = self->size == 0 ? initialCapacity : self->size * 2;
        if (newCapacity < min) newCapacity = min;
        self->capacity = newCapacity;
        size_t newSize = sizeof(void *) * self->capacity;
        self->items = realloc(self->items, newSize);
    }
}


//
// Created by tgifr on 26.02.17.
//

#ifndef PROGBASE2GH_LIST_H
#define PROGBASE2GH_LIST_H

typedef struct Student Student;
typedef struct List List;
typedef struct Teacher Teacher;


Teacher * Teacher_new(char * name);
void Teacher_attachList(Teacher * teacher, List * toAttach);
char * Teacher_getName(Teacher * teacher);
List * separateLists(Teacher * first, Teacher * second);
List * Teacher_getList(Teacher * teacher);
void Teacher_free(Teacher ** teacher);

Student * Student_new(char * name, int course, float mark);
char * Student_getName(Student * stud);
int Student_getCourse(Student *stud);
float Student_getMark(Student *stud);
void Student_free(Student ** self);

typedef struct List List;

List * List_new(void);

void List_free(List ** self);

void * List_get(List * self, int index);

void List_set(List * self, int index, void * ref);

void List_add(List * self, void * ref);

int List_isEmpty(List * self);

int  List_count(List * self);

int  List_indexOf(List * self, void * ref);

int List_contains(List * self, void * ref);




#endif //PROGBASE2GH_LIST_H

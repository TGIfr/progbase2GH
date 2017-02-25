//
// Created by tgifr on 19.02.17.
//

#include "listBasic.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


void List_print(struct List * self) {
    struct ListNode * cur = self->head;
    while (cur != NULL) {
        printf("%i ", cur->value);
        cur = cur->next;
    }
}
int List_count(struct List * self) {
    int count = 0;
    struct ListNode * cur = self->head;
    while (cur != NULL) {
        count += 1;
        cur = cur->next;
    }
    return count;
}

int List_elementAt(struct List * self, int position) {
    assert(position >= 0);
    if (self->head == NULL) assert(0); // just to throw error
    int i = 0;
    struct ListNode * cur = self->head;
    while (cur->next != NULL && i != position) {
        i += 1;
        cur = cur->next;
    }
    if (i != position) assert(0);
    return cur->value;
}
struct ListNode * ListNode_new(int value) {
    struct ListNode * node = (struct ListNode *)malloc(sizeof(struct ListNode));
    node->next = NULL;
    node->value = value;
    return node;
}

void ListNode_free(struct ListNode ** self) {
    assert(NULL != self);
    free(*self);
    *self = NULL;
}

void List_addFirst(struct List * self, int value) {
    struct ListNode * node = ListNode_new(value);
    node->next = self->head;
    self->head = node;
}
void List_addLast(struct List * self, int value) {
    struct ListNode * node = ListNode_new(value);
    if (self->head == NULL) {
        self->head = node;
        return;
    }
    struct ListNode * cur = self->head;
    while (cur->next != NULL) {
        cur = cur->next;
    }
    cur->next = node;
}
void List_insert(struct List * self, int position, int value) {
    assert(position >= 0);
    if (position == 0) {
        List_addFirst(self, value);
        return;
    }
    struct ListNode * node = ListNode_new(value);
    int i = 0;
    struct ListNode * cur = self->head;
    while (cur->next != NULL && i != position - 1) {
        cur = cur->next;
    }
    if (i != position - 1) assert(0);
    node->next = cur->next;
    cur->next = node;
}

int List_removeFirst(struct List * self) {
    struct ListNode * node = self->head;
    if (node == NULL) assert(0);
    int value = node->value;
    self->head = node->next;
    ListNode_free(&node);
    return value;
}
int List_removeLast(struct List * self) {
    struct ListNode * cur = self->head;
    if (cur == NULL) assert(0);
    if (cur->next == NULL) {
        int value = cur->value;
        ListNode_free(&cur);
        self->head = NULL;
        return value;
    }
    while (cur->next->next != NULL) {
        cur = cur->next;
    }
    int value = cur->next->value;
    ListNode_free(&(cur->next));
    cur->next = NULL;
    return value;
}
int List_removeAt(struct List * self, int position) {
    assert(position >= 0);
    if (position == 0) {
        return List_removeFirst(self);
    }
    int i = 0;
    struct ListNode * cur = self->head;
    while (cur->next->next != NULL && i != position - 1) {
        i += 1;
        cur = cur->next;
    }
    if (i != position - 1) assert(0);
    struct ListNode * node = cur->next;
    int value = node->value;
    cur->next = node->next;
    ListNode_free(&node);
    return value;
}
struct List * List_new(void) {
    struct List * list = (struct List *)malloc(sizeof(struct List));
    list->head = NULL;
    return list;
}

void List_free(struct List ** self) {
    assert(NULL != self);
    free(*self);
    *self = NULL;
}

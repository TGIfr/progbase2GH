//
// Created by tgifr on 19.02.17.
//

#ifndef NLP_LISTBASIC_H
#define NLP_LISTBASIC_H
struct ListNode {
    int value;
    struct ListNode * next;
};
struct List {
    struct ListNode * head;
};

int List_count(struct List * self);
void List_print(struct List * self);
void List_addFirst(struct List * self, int value);
void List_addLast(struct List * self, int value);
void List_insert(struct List * self, int position, int value);
int List_elementAt(struct List * self, int position);
struct ListNode * ListNode_new(int value);
void ListNode_free(struct ListNode ** self);
struct List * List_new(void);
void List_free(struct List ** self);


int List_removeFirst(struct List * self);
int List_removeLast(struct List * self);
int List_removeAt(struct List * self, int position);




#endif //NLP_LISTBASIC_H

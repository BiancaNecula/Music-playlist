// Copyright 2020 Necula Bianca

#ifndef DOUBLYLINKEDLIST_H_
#define DOUBLYLINKEDLIST_H_

struct Meta {
  char tag[4];
  char name[31];
  char artist[31];
  char album[31];
  char year[5];
};

struct Node {
  struct Meta data;
  struct Node *next, *prev;
};

struct DoublyLinkedList {
  struct Node *head;
  struct Node *tail;
  struct Node *cursor;
};

struct DoublyLinkedList *create_list();

void add_first(struct DoublyLinkedList *list, struct Meta meta, FILE *out);

void add_last(struct DoublyLinkedList *list, struct Meta meta, FILE *out);

void add_after(struct DoublyLinkedList *list, struct Meta meta, FILE *out);

void del_first(struct DoublyLinkedList *list, FILE *out);

void del_last(struct DoublyLinkedList *list, FILE *out);

void del_curr(struct DoublyLinkedList *list, FILE *out);

void del_song(struct DoublyLinkedList *list, struct Meta meta, FILE *out);

void move_next(struct DoublyLinkedList *list, FILE *out);

void move_prev(struct DoublyLinkedList *list, FILE *out);

void show_first(struct DoublyLinkedList *list, FILE *out);

void show_last(struct DoublyLinkedList *list, FILE *out);

void show_curr(struct DoublyLinkedList *list, FILE *out);

void show_playlist(struct DoublyLinkedList *list, FILE *out);

void free_list(struct DoublyLinkedList *list);

#endif  // DOUBLYLINKEDLIST_H_

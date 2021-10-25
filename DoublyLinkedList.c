// Copyright 2020 Necula Bianca

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./DoublyLinkedList.h"

/*
 * Functie care trebuie apelata dupa declararea unei liste, pentru a-i aloca
 * memorie si a o initializa.
 * (Setare valori initiale pentru campurile specifice structurii
 * DoublyLinkedList).
 */
struct DoublyLinkedList *create_list() {
  struct DoublyLinkedList *list;
  list = calloc(1, sizeof(struct DoublyLinkedList));
  list->head = NULL;
  list->tail = NULL;
  list->cursor = NULL;
  return list;
}

/*
 * Functia aloca memorie si adauga un nod in lista pe prima pozitie.
 * Daca lista e goala, se adauga primul element.
 * Se verifica daca melodia exista in playlist. Daca da, se sterge din pozitia
 * respectiva si se adauga la inceput.
*/
void add_first(struct DoublyLinkedList *list, struct Meta meta, FILE *out) {
  struct Node *new, *curr;
  new = calloc(1, sizeof(struct Node));
  new->data = meta;
  // daca lista e goala, adaugam primul element
  if (list->head == NULL) {
    new->next = NULL;
    new->prev = NULL;
    list->head = new;
    list->tail = new;
    list->cursor = new;
  } else {
    curr = list->head;
    while (curr != NULL) {
      if (!strcmp(curr->data.name, meta.name)) {
        del_song(list, meta, out);
        break;
      }
      curr = curr->next;
    }
    new->next = list->head;
    new->prev = NULL;
    list->head->prev = new;
    list->head = new;
  }
}

/*
 * Functia aloca memorie si adauga un nod in lista pe ultima pozitie.
 * Daca lista e goala, se adauga primul element.
 * Se verifica daca melodia exista in playlist. Daca da, se sterge din pozitia
 * respectiva si se adauga la sfarsit.
*/
void add_last(struct DoublyLinkedList *list, struct Meta meta, FILE *out) {
  struct Node *new, *curr;
  new = malloc(sizeof(struct Node));
  new->data = meta;
  // daca lista e goala, adaugam primul element
  if (list->tail == NULL) {
    new->next = NULL;
    new->prev = NULL;
    list->head = new;
    list->tail = new;
    list->cursor = new;
  } else {
    curr = list->head;
    while (curr != NULL) {
      if (!strcmp(curr->data.name, meta.name)) {
        del_song(list, meta, out);
        break;
      }
      curr = curr->next;
    }
    new->next = NULL;
    new->prev = list->tail;
    list->tail->next = new;
    list->tail = new;
  }
}

/*
 * Functia aloca memorie si adauga un nod in lista pe pozitia de dupa cursor.
 * Daca lista e goala, se ignora comanda.
 * Daca melodia de pe pozitia cursorului este identica cu cea care urmeaza a fi
 * adaugata, se ignora comanda.
 * Daca cursorul este pe ultima pozitile, se adauga nodul dupa acesta cu
 * ajutorul functiei add_last().
 * Se verifica daca melodia exista in playlist. Daca da, se sterge din pozitia
 * respectiva si se adauga la sfarsit.
*/
void add_after(struct DoublyLinkedList *list, struct Meta meta, FILE *out) {
  struct Node *new, *curr;
  if (list->cursor == NULL) {
    return;
  } else if (!strcmp(list->cursor->data.name, meta.name)) {
    return;
  } else if (list->cursor == list->tail) {
    add_last(list, meta, out);

  } else {
    new = malloc(sizeof(struct Node));
    new->data = meta;
    curr = list->head;
    while (curr != NULL) {
      if (!strcmp(curr->data.name, meta.name)) {
        del_song(list, meta, out);
        break;
      }
      curr = curr->next;
    }
    new->next = list->cursor->next;
    list->cursor->next->prev = new;
    list->cursor->next = new;
    new->prev = list->cursor;
  }
}

/*
 * Functia sterge primul nod si elibereaza memoria acestuia.
 * Daca lista e goala, se afiseaza un mesaj de eroare.
 * Se ia in considerare cazul in care exista un singur nod in lista.
*/
void del_first(struct DoublyLinkedList *list, FILE *out) {
  struct Node *curr;
  if (list->head == NULL) {
    fprintf(out, "Error: delete from empty playlist\n");
    return;
  } else if (list->head->next == NULL) {
    curr = list->head;
    list->head = NULL;
    list->tail = NULL;
    list->cursor = NULL;
    free(curr);
  } else {
    curr = list->head;
    list->head = list->head->next;
    if (list->head != NULL) {
      list->head->prev = NULL;
      if (list->cursor == curr) list->cursor = list->head;
    }
    free(curr);
  }
}

/*
 * Functia sterge ultimul nod si elibereaza memoria acestuia.
 * Daca lista e goala, se afiseaza un mesaj de eroare.
 * Se ia in considerare cazul in care exista un singur nod in lista.
*/
void del_last(struct DoublyLinkedList *list, FILE *out) {
  struct Node *curr;
  if (list->tail == NULL) {
    fprintf(out, "Error: delete from empty playlist\n");
    return;
  } else if (list->tail->prev == NULL) {
    curr = list->tail;
    list->tail = NULL;
    list->head = NULL;
    list->cursor = NULL;
    free(curr);
  } else {
    curr = list->tail;
    list->tail = list->tail->prev;
    if (list->tail != NULL) {
      list->tail->next = NULL;
      if (list->cursor == curr) list->cursor = list->tail;
    }
    free(curr);
  }
}

/*
 * Functia sterge nodul de pe pozitia cursorului si elibereaza memoria acestuia.
 * Daca lista e goala, se afiseaza un mesaj de eroare.
 * Daca nodul este pe prima sau ultima pozitie se folosesc functiile
 * del_first(), respectiv del_last().
 * Cursorul se va muta pe urmatoarea pozitie disponibila (precedenta sau
 * urmatoarea).
*/
void del_curr(struct DoublyLinkedList *list, FILE *out) {
  struct Node *curr;
  if (list->cursor == NULL) {
    fprintf(out, "Error: no track playing\n");
    return;
  } else if (list->cursor == list->tail) {
    del_last(list, out);
  } else if (list->cursor == list->head) {
    del_first(list, out);
  } else {
    curr = list->cursor;
    curr->prev->next = curr->next;
    curr->next->prev = curr->prev;
    list->cursor = curr->next;
    free(curr);
  }
}

/*
 * Functia sterge nodul care corespunde melodiei date ca parametru si elibereaza
 * memoria acestuia.
 * Daca lista e goala, se afiseaza un mesaj de eroare.
 * Daca melodia nu exista, se afiseaza un mesaj de eroare.
 * Daca nodul este pe prima sau ultima pozitie sau pe pozitia pe care se afla
 * cursorul se folosesc functiile del_first(), del_last(), respectiv del_curr.
*/
void del_song(struct DoublyLinkedList *list, struct Meta meta, FILE *out) {
  struct Node *curr;
  if (list->head == NULL) {
    fprintf(out, "Error: no song found to delete\n");
    return;
  }
  curr = list->head;
  while (curr != NULL) {
    if (!strcmp(curr->data.name, meta.name)) break;
    curr = curr->next;
  }
  if (curr == NULL) {
    fprintf(out, "Error: no song found to delete\n");
    return;
  } else if (curr == list->head) {
    del_first(list, out);
  } else if (curr == list->tail) {
    del_last(list, out);
  } else if (curr == list->cursor) {
    del_curr(list, out);

  } else {
    curr->prev->next = curr->next;
    curr->next->prev = curr->prev;
    free(curr);
  }
}

/*
 * Functia muta pozitia cursorului pe urmatoarea pozitie.
 * Daca lista e goala, se afiseaza un mesaj de eroare.
 * Daca urmatoarea pozitie e nula, se ignora comanda.
*/
void move_next(struct DoublyLinkedList *list, FILE *out) {
  if (list->cursor == NULL) {
    fprintf(out, "Error: no track playing\n");
    return;
  }
  if (list->cursor->next != NULL) {
    list->cursor = list->cursor->next;
  }
}

/*
 * Functia muta pozitia cursorului pe urmatoarea pozitie.
 * Daca lista e goala, se afiseaza un mesaj de eroare.
 * Daca urmatoarea pozitie e nula, se ignora comanda.
*/
void move_prev(struct DoublyLinkedList *list, FILE *out) {
  if (list->cursor == NULL) {
    fprintf(out, "Error: no track playing\n");
    return;
  }
  if (list->cursor->prev != NULL) {
    list->cursor = list->cursor->prev;
  }
}

/*
 * Functia afiseaza date despre prima melodie din lista.
 * Daca lista e goala, se afiseaza un mesaj de eroare.
*/
void show_first(struct DoublyLinkedList *list, FILE *out) {
  if (list->head == NULL) {
    fprintf(out, "Error: show empty playlist\n");
    return;
  }
  fprintf(out, "Title: %s\n", list->head->data.name);
  fprintf(out, "Artist: %s\n", list->head->data.artist);
  fprintf(out, "Album: %s\n", list->head->data.album);
  fprintf(out, "Year: %s\n", list->head->data.year);
}

/*
 * Functia afiseaza date despre ultima melodie din lista.
 * Daca lista e goala, se afiseaza un mesaj de eroare.
*/
void show_last(struct DoublyLinkedList *list, FILE *out) {
  if (list->tail == NULL) {
    fprintf(out, "Error: show empty playlist\n");
    return;
  }
  fprintf(out, "Title: %s\n", list->tail->data.name);
  fprintf(out, "Artist: %s\n", list->tail->data.artist);
  fprintf(out, "Album: %s\n", list->tail->data.album);
  fprintf(out, "Year: %s\n", list->tail->data.year);
}

/*
 * Functia afiseaza date despre melodia de pe pozitia cursorului din lista.
 * Daca lista e goala, se afiseaza un mesaj de eroare.
*/
void show_curr(struct DoublyLinkedList *list, FILE *out) {
  if (list->cursor == NULL) {
    fprintf(out, "Error: show empty playlist\n");
    return;
  }
  fprintf(out, "Title: %s\n", list->cursor->data.name);
  fprintf(out, "Artist: %s\n", list->cursor->data.artist);
  fprintf(out, "Album: %s\n", list->cursor->data.album);
  fprintf(out, "Year: %s\n", list->cursor->data.year);
}

/*
 * Functia afiseaza numele tuturor melodiilor din playlist.
 * Daca lista e goala, se afiseaza lista goala [].
*/
void show_playlist(struct DoublyLinkedList *list, FILE *out) {
  struct Node *curr;
  if (list->head == NULL) {
    fprintf(out, "[]\n");
    return;
  }
  curr = list->head;
  fprintf(out, "[");
  while (curr->next != NULL) {
    fprintf(out, "%s; ", curr->data.name);
    curr = curr->next;
  }
  fprintf(out, "%s]\n", curr->data.name);
}

// Functia elibereaza memoria tuturor nodurilor din playlist.
void free_list(struct DoublyLinkedList *list) {
  struct Node *curr, *next;
  curr = list->head;
  while (curr != NULL) {
    next = curr->next;
    free(curr);
    curr = next;
  }
}


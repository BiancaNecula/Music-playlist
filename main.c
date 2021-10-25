// Copyright 2020 Necula Bianca

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "./DoublyLinkedList.h"

int main(int argc, char *argv[]) {
  // declarari variabile si fisiere
  int nr, index, j;
  char command[100], *p;
  char delim[] = " -\n";
  FILE *in, *out, *song_file;
  struct Meta song;
  char song_name2[100];
  struct DoublyLinkedList *list = create_list();
  char *rest = NULL;
  // verificam daca utilizatorul a introdus fisierele de I/O
  if (argc != 3) return -1;
  // deschidem fisierele de I/O
  in = fopen(argv[1], "r");
  out = fopen(argv[2], "w");
  // citim numarul de comenzi care urmeaza sa fie prelucrate
  fscanf(in, "%d\n", &nr);
  for (int i = 0; i < nr; i++) {
    // citim prima comanda si preluam prima parte care reprezinta operatia ce
    // trebuie efectuata
    // comparam operatia cu una din posibilele variante si efectuam comanda
    fgets(command, 100, in);
    p = strtok_r(command, delim, &rest);

    // comanda: ADD_FIRST; parametrii: numele melodiei
    if (!strcmp(p, "ADD_FIRST")) {
      // se adauga in string calea directorului in care se afla melodia
      snprintf(song_name2, sizeof(song_name2), "%s", "songs/");

      // se obtine numele melodiei
      p = strtok_r(NULL, "?", &rest);

      // se prelucreaza numele melodiei astfel incat sa nu mai existe whitespace
      // la final
      // "<song>    "->"<song>"
      index = -1;
      j = 0;
      while (p[j] != '\0') {
        if (p[j] != ' ' && p[j] != '\t' && p[j] != '\n') {
          index = j;
        }
        j++;
      }
      p[index + 1] = '\0';

      // se concateneaza directorul in care se afla melodia cu numele acesteia
      // si se deschide fisierul
      snprintf(song_name2 + strlen(song_name2),
               sizeof(song_name2) - strlen(song_name2), "%s", p);
      song_file = fopen(song_name2, "rb");
      if (song_file == NULL) {
        continue;
      } else {
        // se zeroizeaza memoria alocata unei structuri de tip Meta (metadate
        // ale melodiei)
        memset(&song, 0, sizeof(struct Meta));

        // se muta cursorul pe ultimii 97 de bytes si se citesc datele melodiei
        fseek(song_file, -97, SEEK_END);
        fread(&song.tag, 3, 1, song_file);
        fread(&song.name, 30, 1, song_file);
        fread(&song.artist, 30, 1, song_file);
        fread(&song.album, 30, 1, song_file);
        fread(&song.year, 4, 1, song_file);

        // se adauga in lista primul nod continand datele extrase
        add_first(list, song, out);
        fclose(song_file);
      }

      // comanda: ADD_LAST; parametrii: numele melodiei
    } else if (!strcmp(p, "ADD_LAST")) {
      // se adauga in string calea directorului in care se afla melodia
      snprintf(song_name2, sizeof(song_name2), "%s", "songs/");

      // se obtine numele melodiei
      p = strtok_r(NULL, "?", &rest);

      // se prelucreaza numele melodiei astfel incat sa nu mai existe whitespace
      // la final
      // "<song>    "->"<song>"
      index = -1;
      j = 0;
      while (p[j] != '\0') {
        if (p[j] != ' ' && p[j] != '\t' && p[j] != '\n') {
          index = j;
        }
        j++;
      }
      p[index + 1] = '\0';

      // se concateneaza directorul in care se afla melodia cu numele acesteia
      // si se deschide fisierul
      snprintf(song_name2 + strlen(song_name2),
               sizeof(song_name2) - strlen(song_name2), "%s", p);
      song_file = fopen(song_name2, "rb");
      if (song_file == NULL) {
        continue;
      } else {
        // se zeroizeaza memoria alocata unei structuri de tip Meta (metadate
        // ale melodiei)
        memset(&song, 0, sizeof(struct Meta));

        // se muta cursorul pe ultimii 97 de bytes si se citesc datele melodiei
        fseek(song_file, -97, SEEK_END);
        fread(&song.tag, 3, 1, song_file);
        fread(&song.name, 30, 1, song_file);
        fread(&song.artist, 30, 1, song_file);
        fread(&song.album, 30, 1, song_file);
        fread(&song.year, 4, 1, song_file);

        // se adauga in lista ultimul nod continand datele extrase
        add_last(list, song, out);
        fclose(song_file);
      }

      // comanda: ADD_AFTER; parametrii: numele melodiei
    } else if (!strcmp(p, "ADD_AFTER")) {
      // se adauga in string calea directorului in care se afla melodia
      snprintf(song_name2, sizeof(song_name2), "%s", "songs/");

      // se obtine numele melodiei
      p = strtok_r(NULL, "?", &rest);

      // se prelucreaza numele melodiei astfel incat sa nu mai existe whitespace
      // la final
      // "<song>    "->"<song>"
      index = -1;
      j = 0;
      while (p[j] != '\0') {
        if (p[j] != ' ' && p[j] != '\t' && p[j] != '\n') {
          index = j;
        }
        j++;
      }
      p[index + 1] = '\0';

      // se concateneaza directorul in care se afla melodia cu numele acesteia
      // si se deschide fisierul
      snprintf(song_name2 + strlen(song_name2),
               sizeof(song_name2) - strlen(song_name2), "%s", p);
      song_file = fopen(song_name2, "rb");
      if (song_file == NULL) {
        continue;
      } else {
        // se zeroizeaza memoria alocata unei structuri de tip Meta (metadate
        // ale melodiei)
        memset(&song, 0, sizeof(struct Meta));

        // se muta cursorul pe ultimii 97 de bytes si se citesc datele melodiei
        fseek(song_file, -97, SEEK_END);
        fread(&song.tag, 3, 1, song_file);
        fread(&song.name, 30, 1, song_file);
        fread(&song.artist, 30, 1, song_file);
        fread(&song.album, 30, 1, song_file);
        fread(&song.year, 4, 1, song_file);

        // se adauga in lista un nod dupa cursor continand datele extrase
        add_after(list, song, out);
        fclose(song_file);
      }

      // comanda: DEL_FIRST
    } else if (!strcmp(p, "DEL_FIRST")) {
      // se sterge primul nod
      del_first(list, out);

      // comanda: DEL_LAST
    } else if (!strcmp(p, "DEL_LAST")) {
      // se sterge ultimul nod
      del_last(list, out);

      // comanda: DEL_CURR
    } else if (!strcmp(p, "DEL_CURR")) {
      // se sterge nodul unde este pozitionat cursorul
      del_curr(list, out);

      // comanda: DEL_SONG; parametrii: numele melodiei
    } else if (!strcmp(p, "DEL_SONG")) {
      // se adauga in string calea directorului in care se afla melodia
      snprintf(song_name2, sizeof(song_name2), "%s", "songs/");

      // se obtine numele melodiei
      p = strtok_r(NULL, "?", &rest);

      // se prelucreaza numele melodiei astfel incat sa nu mai existe whitespace
      // la final
      // "<song>    "->"<song>"
      index = -1;
      j = 0;
      while (p[j] != '\0') {
        if (p[j] != ' ' && p[j] != '\t' && p[j] != '\n') {
          index = j;
        }
        j++;
      }
      p[index + 1] = '\0';

      // se concateneaza directorul in care se afla melodia cu numele acesteia
      // si se deschide fisierul
      snprintf(song_name2 + strlen(song_name2),
               sizeof(song_name2) - strlen(song_name2), "%s", p);
      song_file = fopen(song_name2, "rb");
      if (song_file == NULL) {
        continue;
      } else {
        // se zeroizeaza memoria alocata unei structuri de tip Meta (metadate
        // ale melodiei)
        memset(&song, 0, sizeof(struct Meta));

        // se muta cursorul pe ultimii 97 de bytes si se citesc datele melodiei
        fseek(song_file, -97, SEEK_END);
        fread(&song.tag, 3, 1, song_file);
        fread(&song.name, 30, 1, song_file);
        fread(&song.artist, 30, 1, song_file);
        fread(&song.album, 30, 1, song_file);
        fread(&song.year, 4, 1, song_file);

        // se sterge din lista nodul care contine datele citite anterior
        del_song(list, song, out);
        fclose(song_file);
      }

      // comanda: MOVE_NEXT
    } else if (!strcmp(p, "MOVE_NEXT")) {
      // se muta cursorul la urmatorul nod
      move_next(list, out);

      // comanda: MOVE_PREV
    } else if (!strcmp(p, "MOVE_PREV")) {
      // se muta cursorul la nodul precedent
      move_prev(list, out);

      // comanda: SHOW_FIRST
    } else if (!strcmp(p, "SHOW_FIRST")) {
      // se afiseaza primul nod
      show_first(list, out);

      // comanda: SHOW_LAST
    } else if (!strcmp(p, "SHOW_LAST")) {
      // se afiseaza ulimul nod
      show_last(list, out);

      // comanda: SHOW_CURR
    } else if (!strcmp(p, "SHOW_CURR")) {
      // se afiseaza nodul unde este pozitionat cursorul
      show_curr(list, out);

      // comanda: SHOW_PLAYLIST
    } else if (!strcmp(p, "SHOW_PLAYLIST")) {
      // se afiseaza toate melodiile din lista
      show_playlist(list, out);
    }
  }

  // se elibereaza memoria nodurilor din lista.
  free_list(list);
  // se elibereaza memoria listei.
  free(list);
  // se inchid fisierele de I/O.
  fclose(in);
  fclose(out);

  return 0;
}


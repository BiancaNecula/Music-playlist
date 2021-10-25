Data Structures Course \
HOMEWORK 1 - Music Playlist 

March, 2020

Bianca Necula \
Faculty of Automatic Control and Computer Science \
315CA 

# Info
```bash
git clone https://github.com/BiancaNecula/Music-playlist.git
```
Run ./check.sh for testing with the checker. 

## Use

```bash
gcc -o tema1 main.c DoublyLinkedList.c
./topic1 <media.in> <media.out>
```
# About the project:
Implementation of a program similar to Spotify in the C language with the help of the notions learned so far in the course Data structures: 
Structs, Linked Lists, Circular Linked Lists and Doubly Linked Lists.  
We're using MP3 Metadata - ID3 TAG. It allows information (title, artist, album, track number, genre, etc.) 
about the file to be stored right inside the file. The ID3v1 container takes up 128 bytes, starting with the TAG string, 
and is located at the end of the file to maintain compatibility with older media players.  
ID3 header: https://en.wikipedia.org/wiki/ID3  

## Input
On the first line there will be a number q, representing the number of commands that will be performed on the music player. The following types of commands can be found on the following q lines:

* Addition  
  - ADD_FIRST <song name> → adds a song to the top of the list
  - ADD_LAST <song name> → adds a song to the end of the list
  - ADD_AFTER <song name> → adds a song after the cursor
* Deletion
  - DEL_FIRST → delete the song from the beginning of the list
  - DEL_LAST → delete the song from the end of the list
  - DEL_CURR → delete the current song (the song the cursor is pointing to)
  - DEL_SONG <song name> → delete the song, if it exists in the list
* Move cursor
  - MOVE_NEXT → move the cursor to the next song (if the end of the list has been reached, the command is ignored)
  - MOVE_PREV → move the cursor to the previous song (if the list has been reached, the command is ignored)
* Display
  - SHOW_FIRST → Displays song information at the top of the list
  - SHOW_LAST → Displays song information at the end of the list
  - SHOW_CURR → show information about the current song (the one on which the cursor is set)
  - SHOW_PLAYLIST → displays the title for all songs in the list
 
 The display format for song information is:  
 ```
   "Title: <melody title> \ n"
   "Artist: <melody artist> \ n"
   "Album: <melody album> \ n"
   "Year: <melody year> \ n"
```
Playlist display format is:
 ```
   "[<melody title_1>; <melody title_2>;… <melody title_n>] \ n"
 ```
 
## Output
The <media.out> file will contain both the information that was requested and the errors of the commands when they could not be executed, in the order they were received from the input file.

# About the code:
The project includes 3 files:
* main.c: solving the statement
* DoublyLinkedList.c: implement functions for double-linked lists
* DoublyLinkedList.h: function definitions and declaration of DoublyLinkedList, Node and Meta structures

### main.c

* Open I/O files.
* Reading commands from the input file, processing and performing them.
* The implementation of the playlist is done with the help of a double chained list.
* For commands that have a song as a parameter, open the song file, read the metadata (last 97 bytes) and save it in a Meta structure.
* Specific functions are called for each command.
* At the end, the memory allocated for the list is released.

### DoublyLinkedList.c / DoublyLinkedList.h

* Implementation of functions specific to a double-linked list.
 
```C
// initialize the list
struct DoublyLinkedList * create_list ();
// add the first node
void add_first (struct DoublyLinkedList * list, struct Meta meta, FILE * out);
// add the last node
void add_last (struct DoublyLinkedList * list, struct Meta meta, FILE * out);
// add the node according to the cursor position
void add_after (struct DoublyLinkedList * list, struct Meta meta, FILE * out);
// delete the first node
void del_first (struct DoublyLinkedList * list, FILE * out);
// delete the last node
void del_last (struct DoublyLinkedList * list, FILE * out);
// delete the node from the cursor position
void del_curr (struct DoublyLinkedList * list, FILE * out);
// delete the given song as a parameter
void del_song (struct DoublyLinkedList * list, struct Meta meta, FILE * out);
// move the cursor to the next position
void move_next (struct DoublyLinkedList * list, FILE * out);
// move the cursor to the previous position
void move_prev (struct DoublyLinkedList * list, FILE * out);
// display information about the first node
void show_first (struct DoublyLinkedList * list, FILE * out);
// display information about the last node
void show_last (struct DoublyLinkedList * list, FILE * out);
// display information about the node on the current cursor position
void show_curr (struct DoublyLinkedList * list, FILE * out);
// display all the songs in the list
void show_playlist (struct DoublyLinkedList * list, FILE * out);
// release the used memory
void free_list (struct DoublyLinkedList * list);
```
For information on particular cases, read the comments in the DoublyLinkedList.c file.


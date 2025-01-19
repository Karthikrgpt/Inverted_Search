#ifndef INVERTED_SEARCH_H
#define INVERTED_SEARCH_H

#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#define MAX_WORD_LEN        20
#define MAX_FILENAME_LEN    20
#define MAX_CHARACTERS      27 //26 charecters and 27th for word starting with numbers or special charecter

#define SUCCESS             0
#define FAILURE             -1
#define NOT_POSSIBLE        -2
#define DATA_PRESENT        -3
#define EMPTY_DATA          -4

typedef struct node {

	char fname[MAX_FILENAME_LEN];
    char add_flag;                  //helps to check that, the file is added to the database or not
                                    //if add_flag == 1 then data is added if 0, then not
	struct node *link;
}Slist;

typedef struct main {

    int file_count;
    char word[MAX_WORD_LEN];
    struct main *word_link;
    struct sub *filename_link;

}word;

typedef struct sub {

    int word_count;
    char filename[MAX_FILENAME_LEN];
    struct sub *Slink;
}file;

/*To vrify the user enterd arguments*/
int validate_arguments(Slist **head, char *argv[]);

/*To create data base*/
int create_database(Slist *head, word *(*Character)[]);

/*To store the word to the data base*/
int get_word_store_db(word *(*Character)[], char *word, char *fname);

/*To display the data*/
int display_output(word *(*Char_lsit)[]);

/*To add additional add to the data base*/
int add_data(Slist **head, word *(*Character)[]);

/*To Search the data*/
int Search_data(word *(*Char_lsit)[]);

/*to save the data for the backup*/
int Backup_data(word *(*Char_lsit)[]);

/*to backup the data from backupfile.txt*/
int Restore_data(Slist **head, word *(*Character)[]);

/*To store the data to database*/
int store(word **Character_index, word **new_word, file **new_file, Slist **head);

/*To check file is backup file or not*/
int isbackupfile(char *filename);

/*to check data base is empty or not*/
int isempty(word *(*Character_index)[]);

void print_title();
void continue_key();
int create_node(Slist **head, char *filename);
int create_slist(Slist **head, char *filename);
void display_error( char *message);
void loading(void);

#endif
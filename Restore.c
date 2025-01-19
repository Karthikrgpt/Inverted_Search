
#include "inverted_search.h"

int Restore_data(Slist **head, word *(*Character)[]) {

    if (isempty(Character) == DATA_PRESENT) {
        printf("\nERROR: Data present in the database.\n");
        return DATA_PRESENT;
    }

    char fptr_name[MAX_FILENAME_LEN];
    printf("\nEnter the Backup File name: ");
    scanf("%s", fptr_name);

    FILE *fptr = fopen(fptr_name, "r");
    if (!fptr) {
        printf("\nERROR: file \"%s\" is not present in the current directory.\n", fptr_name);
        return NOT_POSSIBLE;
    }

    fseek(fptr, 0, SEEK_END);

    if (!ftell(fptr)) {
        printf("\nERROR: \"%s\" is a Empty file.\n", fptr_name);
        return NOT_POSSIBLE;
    }

    if (isbackupfile(fptr_name) == FAILURE) {
        printf("\nERROR: \"%s\" is not a Backup file.\n", fptr_name);
        return NOT_POSSIBLE;
    }

    fseek(fptr, 0, SEEK_SET);

    char *line = NULL;
    size_t len = 0;

    while (getline(&line, &len, fptr) != FAILURE) {
        
        line[strcspn(line, "\n")] = '\0'; // Remove the trailing newline character if present

        char *token = strtok(line, ";");

        token = strtok(NULL, ";");//token for index
        int index = atoi(token); 
        
        token = strtok(NULL, ";"); //token for Word
        char *Word = token; 

        if (!strcmp(Word, "//://")) strcpy(Word, ";");
        
        token = strtok(NULL, ";");//token for filecount
        int filecount = atoi(token);

        word *new_word = (word*)malloc(sizeof(word));
        if (new_word == NULL) return FAILURE;

        strcpy(new_word->word, Word);
        new_word->file_count = filecount;
        new_word->filename_link = NULL;
        new_word->word_link = NULL;

        for (int i = 0; i < filecount; i++) {

            token = strtok(NULL, ";"); //token for file name
            char *fname = token;
            
            token = strtok(NULL, ";"); //token for Word count
            int wordcount = atoi(token);

            file *new_file = (file*)malloc(sizeof(file));
            if (new_file == NULL) return FAILURE;

            strcpy(new_file->filename, fname);
            new_file->word_count = wordcount;
            new_file->Slink = NULL;

            store(&(*Character)[index], &new_word, &new_file, head);

            //adding the file name to the Slist
            if (create_slist(head, fname) == FAILURE) continue;

        }

    } 

    free(line); // Free the dynamically allocated buffer

    fclose(fptr); // Close the file

    loading();

    return SUCCESS;
}

int store(word **Character_index, word **new_word, file **new_file, Slist **head) {

    if (!(*Character_index)) {
        *Character_index = *new_word;
        (*new_word)->filename_link = *new_file;
        return SUCCESS;
    }

    word *temp_word = *Character_index, *prev_word;
    file *temp_file = *new_file, *prev_file = temp_file;

    while (temp_word) {

        if (!strcmp((*new_word)->word, temp_word->word)) {

            prev_file = temp_file;
            temp_file = temp_word->filename_link;

            while (temp_file) {

                prev_file = temp_file;
                temp_file = temp_file->Slink;
            }

            prev_file->Slink = *new_file;
            
            return SUCCESS;
        }

        prev_word = temp_word;
        temp_word = temp_word->word_link;
    }

    (*new_word)->filename_link = *new_file;
    prev_word->word_link = *new_word;

    return SUCCESS;
}
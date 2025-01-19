
#include "inverted_search.h"

int add_data(Slist **head, word *(*Character)[]) {

    char filename[MAX_FILENAME_LEN];
    printf("\nEnter the File name: ");
    scanf("%s", filename);

    if (strlen(filename) < 4) {
        printf("\nERROR: The file %s is not in supportive formate.\n", filename);
        return NOT_POSSIBLE;
    }

    if (strcmp(filename + strlen(filename) - 4, ".txt")) {
        printf("\nERROR: The file %s is not in supportive formate.\n", filename);
        return NOT_POSSIBLE;
    }

    Slist *temp = *head;
    while (temp) {
        if (!strcmp(temp->fname, filename) && temp->add_flag == 1) {
            printf("\nERROR: The file is present in the Data base.\n");
            return NOT_POSSIBLE;
        }
        temp = temp->link;
    }

    FILE *fptr = fopen(filename, "r");
    if (!fptr) {
        printf("\nERROR: file %s is not present in the current directory.\n", filename);
        return NOT_POSSIBLE;
    }

    fseek(fptr, 0, SEEK_END);

    if (!ftell(fptr)) {
        printf("\nERROR: %s is a Empty file.\n", filename);
        return NOT_POSSIBLE;
    }

    fclose(fptr);
    
    if (isbackupfile(filename) == SUCCESS) {
        printf("\nERROR: The file %s is Backup file.\n", filename);
        return NOT_POSSIBLE;
    }

    if (create_slist(head, filename) == FAILURE) {
        printf("\nWARNING: The file name %s is already validated.\n", filename);
        return NOT_POSSIBLE;
    }

    fptr = fopen(filename, "r");
    if (!fptr) {
        printf("\nERROR: file %s is not present in the current directory.\n", filename);
        return NOT_POSSIBLE;
    }

    char Word[MAX_WORD_LEN];

    while (fscanf(fptr, "%s", Word) != EOF) {
		if (get_word_store_db( Character, Word, filename) == FAILURE) {
			printf("ERROR: Failed to store the data to the database");
			return FAILURE;
		}
    }

    fclose(fptr);

    loading();

    return SUCCESS;
}
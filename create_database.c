
#include "inverted_search.h"

int create_database(Slist *head, word *(*Character)[]) {

	while (head) { 
		
		FILE *fptr = fopen( head->fname, "r");
    	if (fptr == NULL) {
        	printf("ERROR: file %s is not present in the current directory.\n", head->fname);
        	return FAILURE;
    	}

    	char Word[MAX_WORD_LEN];

    	while ( head->add_flag == 0 && fscanf(fptr, "%s", Word) != EOF) {
			if (get_word_store_db( Character, Word, head->fname) == FAILURE) {
				printf("ERROR: Failed to store the data to the database");
				return FAILURE;
			}
    	}

    	fclose(fptr);

        head->add_flag = 1;

		head = head->link;
	}

    loading();

	return SUCCESS;

}

int get_word_store_db(word *(*Character)[], char *Word, char *fname) {

    int index = isupper(Word[0]) ? (Word[0] - 'A') : (Word[0] - 'a');
    if (index < 0 || index >= 26) index = 26;
    
    word *new_word = (word*)malloc(sizeof(word));
    if (new_word == NULL) return FAILURE;

    new_word->file_count = 1;
    strcpy(new_word->word, Word);
    new_word->filename_link = NULL;
    new_word->word_link = NULL;

    file *new_file = (file*)malloc(sizeof(file));
    if (new_file == NULL) return FAILURE;

    new_word->filename_link = new_file;
    strcpy(new_file->filename, fname);
    new_file->word_count = 1;
    new_file->Slink = NULL;

    //if index store the null charactor
    if ((*Character)[index] == NULL) {
        new_word->filename_link = new_file;
        (*Character)[index] = new_word;
        return SUCCESS;
    }

    word *temp_word = (*Character)[index], *prev_word;
    file *temp_file, *prev_file;

    while (temp_word) {

        if (!strcmp(Word, temp_word->word)) {

            prev_file = temp_file;
            temp_file = temp_word->filename_link;

            while ( temp_file) {

                if (!strcmp(temp_file->filename, fname)) {
                    temp_file->word_count = temp_file->word_count + 1;
                    return SUCCESS;
                }

                prev_file = temp_file;
                temp_file = temp_file->Slink;
            }

            temp_word->file_count = temp_word->file_count + 1;
            prev_file->Slink = new_file;

            return SUCCESS;
        }

        prev_word = temp_word;
        temp_word = temp_word->word_link;
    }

    prev_word->word_link = new_word;

    return SUCCESS;
}

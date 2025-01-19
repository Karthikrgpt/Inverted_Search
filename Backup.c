
#include "inverted_search.h"

int Backup_data(word *(*Char_lsit)[]) {

	if (isempty(Char_lsit) == EMPTY_DATA) {
        printf("\nERROR: Database is Empty.\n");
        return EMPTY_DATA;
    }

    print_title();

    FILE *fptr = fopen("Backupfile.txt", "w+");
    if (!fptr) {
        printf("ERROR: Unable to open the backup file.\n");
        return FAILURE;
    }

	for ( int index = 0; index < MAX_CHARACTERS; index++) {
 
		word *temp_word = (*Char_lsit)[index];
		while (temp_word) {

			if (strcmp(temp_word->word, ";")) fprintf( fptr, "#;%d;%s;%d;", index, temp_word->word, temp_word->file_count);
			else fprintf( fptr, "#;%d;//://;%d;", index, temp_word->file_count);

			file *temp_file = temp_word->filename_link;
			while (temp_file) {

				fprintf( fptr, "%s;%d;", temp_file->filename, temp_file->word_count);

				temp_file = temp_file->Slink;
			}

			fprintf( fptr, "#\n");
			temp_word = temp_word->word_link;
		}
	}

    fclose(fptr);

	loading();

    return SUCCESS;
}
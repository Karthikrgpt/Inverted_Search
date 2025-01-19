
#include "inverted_search.h"

int display_output(word *(*Char_lsit)[]) {

	print_title();

	if (isempty(Char_lsit) == EMPTY_DATA) {
        printf("\nERROR: Database is Empty.\n");
        return NOT_POSSIBLE;
    }

	printf("\nThe Words present in the data base are:\n");
	printf("\033[2;37m-----------------------------------------------------------------------------\033[0m\n");
	printf("\033[3;37m%-8s%-20s%-20s%-30s\033[0m\n", "Index", "Word", "File count", "Filename[Word count]");
	printf("\033[2;37m-----------------------------------------------------------------------------\033[0m\n");

	for ( int index = 0; index < MAX_CHARACTERS; index++) {
 
		word *temp_word = (*Char_lsit)[index];
		while (temp_word) {

			if (index != 26) printf("%-8d%-24s%-8d", index, temp_word->word, temp_word->file_count);
			else printf("%-8c%-24s%-8d", '#', temp_word->word, temp_word->file_count);
			file *temp_file = temp_word->filename_link;
			while (temp_file) {

				printf("%s[%d] ", temp_file->filename, temp_file->word_count);

				temp_file = temp_file->Slink;
			}

			printf("\n");
			temp_word = temp_word->word_link;
		}
	}

	printf("\033[2;37m-----------------------------------------------------------------------------\033[0m\n");

}
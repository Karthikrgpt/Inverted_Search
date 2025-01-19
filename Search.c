#include "inverted_search.h"

int Search_data(word *(*Char_lsit)[]) {

    if (isempty(Char_lsit) == EMPTY_DATA) {
        printf("\nERROR: Database is Empty.\n");
        return NOT_POSSIBLE;
    }

    char Word[MAX_CHARACTERS];

    printf("\nEnter the word, that need to search: ");
    scanf("%s", Word);

    int i = 0, flag = 0;
    int index = isupper(Word[0]) ? (Word[0] - 'A') : (Word[0] - 'a');
    if (index < 0 || index >= 26) index = 26;

    if (!(*Char_lsit)[index]) {
        printf("\nNo Data Found for %s in the Data base\n", Word);
        return FAILURE;
    }

	word *temp_word = (*Char_lsit)[index];
	while (temp_word) {

        if (!strcasestr(temp_word->word, Word)) {
            temp_word = temp_word->word_link;
            continue;
        }

        if (!flag) {
            printf("\nMatching data for %s is found at\n\n", Word);
            printf("\033[2;37m-----------------------------------------------------------------------------\033[0m\n");
	        printf("\033[3;37m%-8s%-20s%-20s%-30s\033[0m\n", "Sl.No.", "Word", "File count", "Filename[Word count]");
	        printf("\033[2;37m-----------------------------------------------------------------------------\033[0m\n");
        }

		if (index != 26) printf("%-8d%-24s%-8d", index, temp_word->word, temp_word->file_count);
        else printf("%-8c%-24s%-8d", '#', temp_word->word, temp_word->file_count);

		file *temp_file = temp_word->filename_link;
		while (temp_file) {

			printf("%s[%d] ", temp_file->filename, temp_file->word_count);

			temp_file = temp_file->Slink;
		}

		printf("\n");
		temp_word = temp_word->word_link;

        flag++;
	}

    if (!flag) {
        printf("\nNo Data Found for %s in the Data base\n", Word);
        return FAILURE;
    } else printf("\033[2;37m-----------------------------------------------------------------------------\033[0m\n");

    return SUCCESS;

}
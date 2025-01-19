
#include "inverted_search.h"

int validate_arguments(Slist **head, char *argv[]) {

    print_title();
    printf("\n");

    if (!argv[1]) return NOT_POSSIBLE;

    if (!strcmp(argv[1], "-h") || !strcmp(argv[1], "--help")) {
        printf("Sample argument:\n\t./output.out filename1.txt filename2.txt .... filenameN.txt");
        printf("\n\t\t\tor\n\t./output.out *.txt\n");
        return FAILURE;
    }

    for ( int i = 1; argv[i] != NULL; i++) {

        if ( strlen(argv[i]) < 4) {
            printf("WARNING: The file %s is not in supportive formate.\n", argv[i]);
            continue;
        }     
        
        if (strcmp(argv[i] + strlen(argv[i]) - 4, ".txt")) {
            printf("WARNING: The file %s is not in supportive formate.\n", argv[i]);
            continue;
        }

        if (!strcmp(argv[i], "Backupfile.txt")) continue;

        FILE *fptr = fopen(argv[i], "r");
        if (!fptr) {
            printf("WARNING: file %s is not present in the current directory.\n", argv[i]);
            continue;
        }

        fseek(fptr, 0, SEEK_END);

        if (!ftell(fptr)) {
            printf("WARNING:  %s is a Empty file.\n", argv[i]);
            continue;
        }

        fclose(fptr);

        if (create_node(head, argv[i]) == DATA_PRESENT) {
            printf("WARNING: The file %s is already validated.\n", argv[i]);
            continue;
        } else printf("INFO: The file %s is validated.\n", argv[i]);

    }

    printf("INFO: Validation Completed.\n");

    printf("\nPress \"Enter\" key to continue");
    getchar();

    return SUCCESS;
}

int create_node(Slist **head, char *filename) {

    Slist *new = (Slist *) malloc (sizeof(Slist));
    if ( new == NULL ) return FAILURE;

    strcpy(new->fname, filename);
    new->link = NULL;
    new->add_flag = 0;

    if ( *head == NULL ) {
        *head = new;
        return SUCCESS;
    }

    Slist *temp = *head, *prev;
    
    while (temp) {
        if (!strcmp(temp->fname, filename)) return DATA_PRESENT;
        prev = temp;
        temp = temp->link;
    }
    prev->link = new;

    return SUCCESS;
}

int create_slist(Slist **head, char *filename) {

    Slist *new = (Slist *) malloc (sizeof(Slist));
    if ( new == NULL ) return FAILURE;

    strcpy(new->fname, filename);
    new->link = NULL;
    new->add_flag = 1;

    if ( *head == NULL ) {
        *head = new;
        return SUCCESS;
    }

    Slist *temp = *head, *prev;
    
    while (temp) {
        if (!strcmp(temp->fname, filename)) {
            temp->add_flag = 1;
            return DATA_PRESENT;
        }
        prev = temp;
        temp = temp->link;
    }

    prev->link = new;

    return SUCCESS;
}

int isbackupfile(char *filename) {

    FILE *file = fopen(filename, "r"); // Open the file in read mode
    if (file == NULL) return FAILURE;

    char *line = NULL;
    size_t len = 0;

    if (getline(&line, &len, file) != FAILURE) {

        line[strcspn(line, "\n")] = '\0'; // Remove the trailing newline character

        // Check if the line starts with "#;" and ends with ":#"
        if (strncmp(line, "#;", 2) == 0 && strcmp(line + strlen(line) - 2, ";#") == 0) {
            free(line);
            fclose(file);
            return SUCCESS;
        }

    }

    free(line);
    fclose(file);
    
    return FAILURE;
}

int isempty(word *(*Character_index)[]) {

    int i;
    for (i = 0; !(*Character_index)[i] && i < MAX_CHARACTERS; i++);

    // if i == MAX_CHARACTER then data is not presnet
    return (i != MAX_CHARACTERS) ? DATA_PRESENT : EMPTY_DATA;
}

void display_error( char *message) {
    printf("ERROR: %s\n", message);
}

void print_title() {
    system("clear"); //clear the stdout window
    printf("\t\t\t\033[4;37mInverted Search\033[0m\n");
}

void continue_key() {

    // to clear the buffer data in the output window
    char buffer[100];
    fgets(buffer, sizeof(buffer), stdin);

    //waits till user press enter
    printf("\nPress \"Enter\" key to continue");
    getchar();
}

void loading(void) {
        
    int progressBarWidth = 25;

    printf("\n");

    for (int i = 0; i <= progressBarWidth; i++) {
        printf("Loading: [");
        for (int j = 0; j < progressBarWidth; j++) {
            if (j < i) {
                printf("#");
            } else {
                printf(" ");
            }
        }
        printf("]%d%%", (i * 100) / progressBarWidth);
        fflush(stdout);
        usleep(100000);
        printf("\r");
    }

    printf("\033[2K"); //to clear the current line 

}
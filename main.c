
#include "inverted_search.h"

char option;
char status;

int main(int argc, char *argv[]) {

	print_title();

	word *Character[MAX_CHARACTERS] = {NULL}; //hash table
	Slist *filename = NULL; 

	status = validate_arguments(&filename, argv);
	
	if (status == FAILURE) {
		display_error("Failed in Validation of arguments.");
		return FAILURE;
	} else if (status == NOT_POSSIBLE) {
		printf("\nWARNING: No file passed throught command line\n");
		printf("\nPress \"Enter\" key to continue");
    	getchar();
	}

	while (1) {

		print_title();
		printf("\nSelect the option:\n\n\t0. Create Data Base\n\t1. Add Data from File\n\t2. Search Data\n\t3. Restore Data\n\t4. Backup data\n\t5. Display\n\t6. Exit\nEnter the option : ");
		scanf("%c", &option);
		print_title();
		
		switch(option) {
			case '0':
				if (create_database(filename, &Character) == FAILURE) {
					display_error("Failed to create the data base.");
					return FAILURE;
				} else printf("INFO: Data base successfully created.\n");
				break;
			case '1': 
				status = add_data(&filename, &Character);
				if ( status == FAILURE) {
					display_error("Failed to add the data to the Database.");
					return FAILURE;
				} else if (status == NOT_POSSIBLE) printf("WORNING: Failed to add the data to the system.\n");
				else printf("INFO: Data added to the Data Base.\n");
				break;
			case '2':
				Search_data(&Character);
				break;
			case '3': 
				status = Restore_data(&filename, &Character);
				if (status == FAILURE) {
					display_error("Failed to restore the data from backup file.");
					return FAILURE;
				} else if (status == DATA_PRESENT || status == NOT_POSSIBLE) printf("WARNING: Restore not possible.\n");
				else printf("INFO: Data restore is successfull.\n");
				break;
			case '4':
				status = Backup_data(&Character);
				if ( status == FAILURE ) {
					display_error("Failed to Save the data base to backup file.");
					return FAILURE;
				} else if (status == EMPTY_DATA) printf("WARNING: Backup not possible.\n");
				else printf("INFO: Data Base is Saved to the system.\n");
				break;
			case '5':
				display_output(&Character);
				break;
			case '6':
				printf("\nData base terminated.\n");
				return SUCCESS;
			default: 
				printf("\nERROR: Invalid Option.\n");	
				break;
		}

		continue_key();
	}

	return SUCCESS;
}
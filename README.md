------------------------------------------------------------------------------------------------------------
                                            INVERTED SEARCH
------------------------------------------------------------------------------------------------------------
Created by Karthik R
Last updated on 13th Jan 2024
------------------------------------------------------------------------------------------------------------

Description:-

  An inverted index is an index data structure storing a mapping from content, such as words or numbers, 
to its locations in a database file, or in a document or a set of documents. The purpose of an inverted 
index is to allow fast full text searches, at a cost of increased processing when a document is added to the 
database. The inverted file may be the database file itself, rather than its index. It is the most popular 
data structure used in document retrieval systems, used on a large scale for example in search engines. 
The purpose of this project is to implement the inverted search using Hash Algorithms.

Here’s a breakdown to its key features :-

1. Create Data Base :- To Create a Data Base
2. Add Data from File :- To add new data to the Data base
3. Search Data :- To search a perticular data in a data Base
4. Restore Data :- To Restore the Backuped files
5. Backup data :- To create a Backup file 
6. Display :- to display the data present in the data base

------------------------------------------------------------------------------------------------------------
Output :-
  
  The files name can be passed through command line or else we can add the files later on.
	-> to pass files name through command line 
		make && ./Project.out Database_A.txt Database_B.txt Database_C.txt
	-> to just command make && ./Project.out

Result (display function) :-

	                        Inverted Search

	The Words present in the data base are:
	-----------------------------------------------------------------------------
	Index   Word                File count          Filename[Word count]
	-----------------------------------------------------------------------------
	0       are                     2       Database_A.txt[2] Database_B.txt[1]
	5       fine.                   1       Database_A.txt[1]
	6       Good                    1       Database_B.txt[1]
	7       Hi                      2       Database_A.txt[1] Database_B.txt[1]
	7       How                     2       Database_A.txt[1] Database_B.txt[1]
	7       Hello12                 1       Database_A.txt[1]
	8       I                       1       Database_A.txt[1]
	10      Karthik                 2       Database_A.txt[1] Database_B.txt[1]
	10      karthik                 1       Database_B.txt[1]
	12      morning,                1       Database_B.txt[1]
	19      think                   1       Database_A.txt[1]
	24      you                     2       Database_A.txt[2] Database_B.txt[1]
	#       0123                    1       Database_A.txt[1]
	#       ...                     1       Database_B.txt[1]
	#       ?                       1       Database_B.txt[1]
	-----------------------------------------------------------------------------

------------------------------------------------------------------------------------------------------------
Files enclosed :-

1. Add_data.c
2. Backup.c
3. create_database.c
4. display_database.c
5. main.c
6. Restore.c
7. Search.c
8. suportive_file.c
9. inverted_search.h
10. Backupfile.txt
11. Database_A.txt
12. Database_B.txt
13. Database_C.txt
14. makefile

------------------------------------------------------------------------------------------------------------
                                                THE END
------------------------------------------------------------------------------------------------------------

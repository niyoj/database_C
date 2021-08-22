/******************************************************************************************************
*   Program name: db.c,
*   Author name: NiyojOli(THA077BCT029),
*   Created Path: /modules/db.c,
*   Created Date: 08 Aug 2021, 12:21:10 (DD MON YYYY, HH:MM:SS),
*   Description: This  program acts as the database module and consists of function to interact with database module.
*******************************************************************************************************/

/*
The commands and its format to be given for the database modules are as follows;

# For Creating New Table
* CREATE TABLE;<TABLE_NAME>;<FILED1>,<FIELD2>,<FIELD3>;<data-type-1>,....
    * To be  noted that, the fieldname can contain only 0 to 1, _, A to Z or a to z.
    * The data-types can be;
        * INT :- integer type
        //* BOOLEAN :- 0 or 1
        * STRING :- string type
        //* DATETIME :- date and time in format DD:MM:YYYY/HH:MM:SS(Note that the timestamp is 24 hour format) 
        //* DATE :- date type in format DD:MM:YYYY
        //* TIME :- time in format HH:MM:SS (in 24 hour format)
        //* FILE :- absolute path to the file

    * Note you can use keywords like PRIMARY and AUTO, with the datatype in order to declare it as a primary a key and autonumber respectively.

# For Deleting Table and Table Field
* DELETE TABLE;<TABLE_NAME>,<TABLE_NAME>
* DELETE TABLE;ALL
* DELETE ROW;<TABLE_NAME>;WHERE;<FIELD_NAME>;<VALUE>
* DELETE COLUMN;<TABLE_NAME>;<COLUMN_NAME>

# For Inserting a Row
* INSERT ROW;<TABLE_NAME>;<FIELD_NAME>,<FIELD_NAME>,...;<VALUE>,<VALUE>,...

# For Updating a Row 
* UPDATE ROW;<TABLE_NAME>;WHERE;<FIELD_NAME>;<VALUE>;UPDATE;<FIELD_NAME>,<FIELD_NAME>,...;<VALUE>,<VALUE>,...
* UPDATE ROW;<TABLE_NAME>;WHERE;<FIELD_NAME>;<VALUE>;AND;<FIELD_NAME>;<VALUE>;UPDATE;<FIELD_NAME>,<FIELD_NAME>,...;<VALUE>,<VALUE>,...
* UPDATE ROW;<TABLE_NAME>;WHERE;<FIELD_NAME>;<VALUE>;OR;<FIELD_NAME>;<VALUE>;UPDATE;<FIELD_NAME>,<FIELD_NAME>,...;<VALUE>,<VALUE>,...

# For Retriving a Row
* GET ROW;<TABLE_NAME>;WHERE;<FIELD_NAME>;<VALUE>;UPDATE;<FIELD_NAME>,<FIELD_NAME>,...
* GET ROW;<TABLE_NAME>;WHERE;<FIELD_NAME>;<VALUE>;AND;<FIELD_NAME>;<VALUE>;UPDATE;<FIELD_NAME>,<FIELD_NAME>,...
* GET ROW;<TABLE_NAME>;WHERE;<FIELD_NAME>;<VALUE>;OR;<FIELD_NAME>;<VALUE>;UPDATE;<FIELD_NAME>,<FIELD_NAME>,...

*/

#include "string.c"     //contains functions like explode() and str_join()
#include <string.h>     //contains functions like strcmp()
#include <stdio.h>      //contains functions for standard input and output
#include <unistd.h>     //contains functions remove() and access()

FILE *handle;

int create_table(char[], char[], char[]);
int db(char cmd[]);
int create_table(char name[], char fields[], char datatypes[]);
int delete_table(char name[]);
int table_exists(char name[]);
int insert_row(char name[], char fields[], char values[]);

//db() function is responsible to interpret the database related commands 
int db(char cmd[]) {
    char exploded[256][256];        
    explode(cmd, ';', exploded);        //exploding the command received with reference to ; 

    if(!strcmp(exploded[0], "CREATE TABLE")) {      //if command for creating table is recieved
        int status = create_table(exploded[1], exploded[2], exploded[3]);

        if(status == 2) {
            printf("Undefined data types.\n");
        } else if (status ==1) {
            printf("The table was succefully created.\n");
        } else {
            printf("The table already exists.\n");
        }

    }

    return 1;
}

//function `create_table()` is used to create a table
int create_table(char name[], char fields[], char datatypes[]) {
    char src[256];
    strcpy(src, "./.db/tables/");
    strcat(src, name);                      //setting the src

    if(table_exists(name)) {
        return 0;                           //if table already exists
    }

    handle = fopen(src, "w");               //creating a file inside.db/tables
    fprintf(handle, "%s\n", fields);        //printing the first line which is fields
    
    char datas[256][256];
    explode(datatypes, ',', datas);

    for(int i=0; datas[i][0]!='\0'; i++) {  //checking if the datatypes are valid or not
        if(strcmp(datas[i], "int") == 0 || strcmp(datas[i], "string")) {
            continue;
        } else {
            return 2;           //if the data type was undefined
        }
    }

    fprintf(handle, "%s", datatypes);       //adds the datatypes of fields in line 2
    fclose(handle); 

    return 1;
}

//function `table_exists()` is used to check whether the table exists or not inside database tables 
int table_exists(char name[]) {
    char src[256];                                          //stores the src of the file
    strcat(src, "./.db/tables/");                           //preparing the src
    strcat(src, name);                                      

    if(access(src, F_OK) == 0) return 1; else return 0;     //returns 1 if file exists
}
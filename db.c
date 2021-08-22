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

/*
For developers only,
0 => success,
1 => failure;
*/

#include "string.c"
#include "ui.c"
#include <stdio.h>
#include <unistd.h>

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

    explode(cmd, ';', exploded);

    if(str_same(exploded[0], "CREATE TABLE")) {
        int status = create_table(exploded[1], exploded[2], exploded[3]);

        if(!status) {
            ui_success("The table was succefully created");
        } else {
            ui_warn("The table already exists.");
        }

    } else if(str_same(exploded[0], "DELETE TABLE")) {
        char delete[256][256];
        explode(exploded[1], ',', delete);

        for(int i=0; delete[i]!="\0"; i++) {
            delete_table(delete[i]);
        }

    } else if(str_same(exploded[0], "DELETE ROW")) {
        
    } else if(str_same(exploded[0], "DELETE COLUMN")) {
    
    } else if(str_same(exploded[0], "INSERT ROW")) {
        insert_row(exploded[1], exploded[2], exploded[3]);
    } else if(str_same(exploded[0], "UPDATE ROW")) {
    
    } else if(str_same(exploded[0], "GET ROW")) {

    } else {
        return 0;
    }

    return 1;
}

int create_table(char name[], char fields[], char datatypes[]) {
    char src[256];
    str_join("./.db/tables/", name, src);

    if(table_exists(name)) return 1;

    handle = fopen(src, "w");
    fprintf(handle, "%s", fields);
    fprintf(handle, "\n%s", datatypes);
    fclose(handle);

    return 0;
}

//function delete_table() can be used to delete a table from the database
int delete_table(char name[]) {
    char delete_src[256];
    str_join("./.db/tables/", name, delete_src);       //to be deleted file

    if(remove(delete_src) == 0) return 0; else return 1;
}

//INSERT ROW;<TABLE_NAME>;<FIELD_NAME>,<FIELD_NAME>,...;<VALUE>,<VALUE>,...
int insert_row(char name[], char fields[], char values[]) {
    
    if(!table_exists(name)) return 2;               //if table doesnot exists at all

    char src[256], c, str[256], fields_array[256][256], values_array[256][256];
    int num_line=1, i=0;
    str_join("./.db/tables/", name, src);
    explode(fields, ',', fields_array);
    explode(values, ',', values_array);
    
    handle = fopen(src, "r+");

    while ((c = fgetc(handle)) != EOF) {
        if(num_line == 1) {
            str[i] = c;
            i++;
        }
        if (c == '\n') num_line++;
    }    

    
    

    printf("%s", str);
    return 0;
}

int update_table() {
    printf("Updated the table");
}

int get_table() {
    printf("Got the table");
}

int table_exists(char name[]) {
    char src[256];
    str_join("./.db/tables/", name, src);

    if(access(src, F_OK) == 0) return 1; else return 0;
}

int main(void) {
    //db("CREATE TABLE;keys;s.n.,username,public key,common key;autonumber int, string, string, string");
    db("INSERT ROW;keys;s.n.,username,public_key,common_key;,someone,123,456");
    //delete_table('\0');
    return 0;
}
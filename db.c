/******************************************************************************************************
*   Program name: db.c,
*   Author name: NiyojOli,
*   Created Path: /db.c,
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
        * STRING :- string type
    * Note you can use keywords like `primary` and `autonumber`, with the datatype in order to declare it as a primary a key and autonumber respectively.

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
* GET ROW;<TABLE_NAME>;WHERE;<FIELD_NAME>;<VALUE>
* GET ROW;<TABLE_NAME>;WHERE;<FIELD_NAME>;<VALUE>;AND;<FIELD_NAME>;<VALUE>
* GET ROW;<TABLE_NAME>;WHERE;<FIELD_NAME>;<VALUE>;OR;<FIELD_NAME>;<VALUE>

*/

//including section for standard header files
#include <string.h>     //contains functions like strcmp()
#include <stdio.h>      //contains functions for standard input and output
#include <unistd.h>     //contains functions remove() and access()

//including section for user-defined header files
#include "string.c"     //contains functions like explode() and str_join()

//structures definition section here
struct Table_element {  //this stucture is used to return the affected rows and their values
    char header[1000];
    char values[1000];
};

typedef struct Table_element FIELD;

//function prototype section
FIELD db(char []);
int table_exists(char []);
int create_table(char [], char [], char []);
int delete_table(char []);
int insert_row(char [], char [], char []);
int get_row(char [], char []);


//definition section
#define DB "./.db/"
FILE *handle;

//db() function is responsible to interpret the database related commands 
FIELD db(char cmd[]) {
    FIELD retrn;                        //the returning structure identifier
    strcpy(retrn.header, "");           //getting rid of the garabage values
    strcpy(retrn.values, "");

    char exploded[256][256] = {};        
    explode(cmd, ';', exploded);        //exploding the command received with reference to ; 

    if(strcmp(exploded[0], "CREATE TABLE") == 0) {      //if command for creating table is recieved
        int status = create_table(exploded[1], exploded[2], exploded[3]);

        if(status == 2) {
            printf("Undefined data types.\n");
        } else if (status ==1) {
            printf("The table was succefully created.\n");
            strcpy(retrn.header, exploded[2]);          //returning structures with the rows affected details
            strcpy(retrn.values, exploded[3]);

            return retrn;
        } else {
            printf("The table already exists.\n");
        }
    } else if (strcmp(exploded[0], "DELETE TABLE") == 0) {
        if (strcmp(exploded[1], "ALL") == 0) {
            char src[256];
            strcpy(src, DB);
            strcat(src, "tables");

            //create a file where every table names are entered and from the name delete
        } else {
            char tables[256][256] = {};
            explode(exploded[1], ',', tables);
    
            for(int i=0; tables[i][0] != '\0'; i++) {
                int status = delete_table(tables[i]);

                if(!status) {
                    printf("The table was not deleted.\n");
                }
            }
        }
    } else if(strcmp(exploded[0], "INSERT ROW") == 0){
        int status = insert_row(exploded[1], exploded[2], exploded[3]); 

        if(status == 2) {
            printf("The table doesnot exists");
        }
    } else if(strcmp(exploded[0], "GET ROW") == 0) {
        char condition[256] = {};
        
        int start=0;
        for(int i=0; exploded[i][0] != '\0'; ++i) {         //getting the conditions only from the command
            if(strcmp(exploded[i], "WHERE") == 0) {
                start = 1;
                continue;
            }

            if(strcmp(exploded[i], "AND") == 0 || strcmp(exploded[i], "OR") == 0) {
                start = 1;
                continue;
            }

            if(start<=2 && start!=0) {
                strcat(condition, exploded[i]);
                strcat(condition, ",");
                start++;
                continue;
            }

            if(start>2) {
                break;
            }
        }
        condition[strlen(condition)-1] = '\0';              //removing the last comma

        //int status = get_row(exploded[1], condition);
    }else {
        printf("Please check your command and try again.\n");
    }
    return retrn;
}

//function `table_exists()` is used to check whether the table exists or not inside database tables 
int table_exists(char name[]) {
    char src[256] = {};                          //stores the src of the file
    strcat(src, DB);                             //preparing the src
    strcat(src, "tables/");
    strcat(src, name);                                      

    if(access(src, F_OK) == 0) return 1; else return 0;     //returns 1 if file exists
}

//function `create_table()` is used to create a table
int create_table(char name[], char fields[], char datatypes[]) {
    char src[256] = {};
    strcpy(src, DB);
    strcat(src, "tables/");
    strcat(src, name);                      //setting the src

    if(table_exists(name)) {
        return 0;                           //if table already exists
    }

    handle = fopen(src, "w");               //creating a file inside.db/tables
    fprintf(handle, "%s\n", fields);        //printing the first line which is fields
    
    char datas[256][256] = {};
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

//function `delete_table()` is used to delete tables
int delete_table(char name[]) {
    char src[256] = {};
    strcpy(src, DB);            //setting up the src
    strcat(src, "tables/");
    strcat(src, name);

    if(!table_exists(name)) {       //checking if table exists or not
        return 0;
    } else {
        if(remove(src) == 0) return 1; else return 0;       //if exists deleteing the file using remove()
    }
}

//function `insert_row()` is used to insert the row of tables
int insert_row(char name[], char fields[], char values[]) {
    char src[256] = {}, insert[256] = {};
    char header[256] = {}, data[256] = {};
    char e_header[256][256], e_data[256][256], e_fields[256][256], e_val[256][256];

    strcpy(src, DB);
    strcat(src, "tables/");
    strcat(src, name);                  //preparing path of the table

    if(!table_exists(name)) {
        return 2;                       //if table doesnot exists
    }

    handle = fopen(src, "r+");          //opening the file in append mode
    
    int j = 0, k = 0;
    char ch;
    while(1) {                          //getting table header and datatypes
        ch = fgetc(handle);

        if(ch == EOF) break;

        if(ch != '\n') {                //if current position character is not equal to new line  character
            if(k == 0) {
                 header[j] = ch;        //for first line when no \n is encountered update varaible `header`
            } else {
                 data[j] = ch;          //for second line when \n is found once update `data` variable
            }
            j++;                        //next position of header and data variable
        } else {
            k++;                        //if new line is found 
            j = 0;                      //resetting the position
        }

        if(k == 2) break;               //if two lines are fetched breaks the loop
    }

    fseek(handle, 0, SEEK_END);         //seeking the pointer to the end of the  file
    fprintf(handle, "\n");

    explode(header, ',', e_header);     //converting all string varaibles to arrays
    explode(data, ',', e_data);
    explode(fields, ',', e_fields);
    explode(values, ',', e_val);
    
    for(int i=0; e_header[i][0] != '\0'; i++) {             //finding the order in which values are entered
        int found = 0;                                      //use to store wethere the table header value is passed or not
        for(int j=0; e_fields[j][0] != '0'; j++) {
            if(strcmp(e_header[i], e_fields[j]) == 0) {     //if table header and the field value supplied matches
                strcat(insert, e_val[j]);
                
                if(e_header[i+1][0] != '\0') {
                    strcat(insert, ",");                    //if last table field then don't include extra comma , 
                }
                
                found = 1;
            }
        }
        if(!found) {
            strcat(insert, ",");
        }
    }

    fprintf(handle, "%s", insert);              //storing the values in the file

    fclose(handle);
    return 1;
}

//function `update_row()` is used to update an existing row in the table
int get_row(char name[], char condition[]) {
    
    return 1;
}
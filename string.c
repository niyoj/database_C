/******************************************************************************************************
*   Program name: string.c,
*   Author name: NiyojOli,
*   Created Path: /modules/string.c,
*   Created Date: 08 May 2021, 12:01:10 (DD MON YYYY, HH:MM:SS),
*   Description: This  program contains some user define functions.
*******************************************************************************************************/

//function explode() is used to convert a string to array where the separator specifies aftere which character the new array element is to be formed
//Example; explode(string, ';', exploded); converts the  string to array whenever the separator ; is seen and returns its vlue to retrn
int explode(char string[], char separator, char retrn[][256]) {
    int i=0, j=0, k=0;
    
    while(string[i] != '\0') {
        if(string[i] == separator) { 
            k = 0;
            j++;
        } else {
            retrn[j][k] = string[i];
            k++;
        }
        i++;
    }    
}

//function compare_str() is used to check wether the given two strings are same or not. returns 1 of same
int str_same(char str1[], char str2[]) {
    char *p1, *p2;
    
    p1 = str1;
    p2 = str2;
    
    for(; *p1 != '\0'; ++p1) {
        if(*p2 != *p1) {
            return 0;
        }
        ++p2;
    } 

    return 1;
}

//function str_join() is used to concatentate two strings
void str_join(char str1[], char str2[], char joined[]) {
    int i=0;
    for(; str1[i] != '\0'; i++) {
        joined[i] = str1[i];
    }
    for(int j=0; str2[j] != '\0'; j++) {
        joined[i+j] = str2[j];
    }
}
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
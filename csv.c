//
// Created by tgifr on 26.02.17.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "csv.h"


#define MAX_TOKENS 100
int main(){
    return 0;
}
const char * const StandardDelimiter = ";";
List * readCsv(char * readFile){
    List * result = List_new();
    FILE * read;
    if((read = fopen(readFile, "r")) == NULL) {
        printf("Error: can't open file");
        exit(1);
    }
    char temp[200] ;
    char **out;
    while(!feof(read)){
        fgets(temp, 200, read);
        out = NULL;
        int size = getcols(temp, StandardDelimiter, &out);
        Student * new = Student_new(out[0], atoi(out[1]), (float)atof(out[2]));
        List_add(result, new);
    }
    fclose(read);
    return result;
}
void saveCsv(List * list, char * saveFile){
    FILE * save ;
    if((save = fopen(saveFile, "w")) == NULL){
        printf("Error: can't open save file");
        exit(2);
    }
    int length = List_count(list);
    for (int i = 0; i < length; ++i) {
        Student * temp = List_get(list, i);
        fprintf(save, "%s;%i;%f\n", Student_getName(temp), Student_getCourse(temp), Student_getMark(temp));
    }
    fclose(save);
}

int getcols( const char * const line, const char * const delim, char ***out_storage ) {
    const char *start_ptr, *end_ptr, *iter;
    char **out;
    int i;
    int tokens_found = 1, delim_size, line_size;
    int start_idx[MAX_TOKENS], end_idx[MAX_TOKENS];

    if ( *out_storage != NULL )                 return -4;  //This SHOULD be NULL: Not Already Allocated
    if ( !line || !delim )                      return -1;  //NULL pointers Rejected Here
    if ( (delim_size = (int)strlen( delim )) == 0 )  return -2;  //Delimiter not provided

    start_ptr = line;   //Start visiting input. We will distinguish tokens in a single pass, for good performance.
    //Then we are allocating one unified memory region & doing one memory copy.
    while ( ( end_ptr = strstr( start_ptr, delim ) ) ) {
        start_idx[ tokens_found -1 ] = (int)(start_ptr - line);    //Store the Index of current token
        end_idx[ tokens_found - 1 ] = (int)(end_ptr - line); //Store Index of first character that will be replaced with
        //'\0'
        tokens_found++;                                     //Accumulate the count of tokens.
        start_ptr = end_ptr + delim_size;                   //Set pointer to the next c-string within the line
    }

    for ( iter = start_ptr; (*iter!='\0') ; iter++ );

    start_idx[ tokens_found -1 ] = (int)(start_ptr - line);    //Store the Index of current token: of last token here.
    end_idx[ tokens_found -1 ] = (int)(iter - line);           //and the last element that will be replaced with \0

    line_size = (int)(iter - line);    //Saving CPU cycles: Indirectly Count the size of *line without using strlen();

    int size_ptr_region = (1 + tokens_found)*sizeof( char* );   //The size to store pointers to c-strings + 1 (*NULL).
    out = (char**) malloc( (size_t)size_ptr_region + ( line_size + 1 ) + 5 );
    //It reserves a contiguous space for both (char**) pointers AND string region. 5 Bytes for "Out of Range" tests.
    *out_storage = out;     //Update the char** pointer of the caller function.

    for ( i = 0; i < tokens_found; i++ )    //Assign adresses first part of the allocated memory pointers that point to
        out[ i ] = (char*) out + size_ptr_region + start_idx[ i ];  //the second part of the memory, reserved for Data.
    out[ tokens_found ] = (char*) NULL; //[ ptr1, ptr2, ... , ptrN, (char*) NULL, ... ]: We just added the (char*) NULL.
    //Now assign the Data: c-strings. (\0 terminated strings):
    char *str_region = (char*) out + size_ptr_region;   //Region inside allocated memory which contains the String Data.
    memcpy( str_region, line, line_size );   //Copy input with delimiter characters: They will be replaced with \0.

    //Now we should replace: "arg1||arg2||arg3" with "arg1\0|arg2\0|arg3"
    for( i = 0; i < tokens_found; i++) str_region[ end_idx[ i ] ] = '\0';

    return tokens_found;
}
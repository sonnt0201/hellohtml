// file1.h

#ifndef HTTP_HELPER_H
#define HTTP_HELPER_H

#define HTTP_GET 0
#define HTTP_POST 1
#define HTTP_PUT 2
#define HTTP_DELETE 3

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
char *print_request(char *message, int len); // Variable declaration

// Return an INT value referring to request type of a http request
/*
    HTTP_GET 0
    HTTP_POST 1
    HTTP_PUT 2
    HTTP_DELETE 3
*/
int request_type(char *request);
char *create_response(FILE *p_file);
char* param_val_GET(char* request, char* params);
#endif

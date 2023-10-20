/*
    10/2023 by SƠN
    'httphelper' functions' declare

*/

#ifndef HTTP_HELPER_H
#define HTTP_HELPER_H

#define HTTP_GET 0
#define HTTP_POST 1
#define HTTP_PUT 2
#define HTTP_DELETE 3

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Print all the request message
char *print_request(char *message, int len); // Variable declaration

// Return an INT value referring to request type of a http request
/*
    HTTP_GET 0
    HTTP_POST 1
    HTTP_PUT 2
    HTTP_DELETE 3
*/
int request_type(char *request);

// create response to client including html file
char *create_response(char* link);

// get parameter value of 'params' in the request  
char* param_val_GET(char* request, char* params);
#endif

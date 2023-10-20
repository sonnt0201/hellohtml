
/*
    10/2023 by SƠN
    'httphelper' functions' implementations

*/

#include "httphelper.h"
// using namespace std;
char *print_request(
    char *message, int len)
{
    printf("%s", message);
    return message;
}

int request_type(char *request)
{
    if (strstr(request, "GET") == request)
        return HTTP_GET;
    if (strstr(request, "POST") == request)
        return HTTP_POST;
    if (strstr(request, "PUT") == request)
        return HTTP_PUT;
    if (strstr(request, "DELETE") == request)
        return HTTP_DELETE;
}

char *create_response(char *link)
{
    // create header
    char *header = "HTTP/1.1 200 OK\nContent-Type: text/html\n\n";

    // handle html file
    FILE *p_file = fopen(link, "r");
    if (p_file == NULL)
    {
        perror("Error opening HTML file. \n");
        return NULL;
    }
    // file size
    fseek(p_file, 0, SEEK_END);
    long file_size = ftell(p_file);
    fseek(p_file, 0, SEEK_SET);

    // Allocate memory for the response
    char *response = (char *)malloc(strlen(header) + file_size + 1);

    // Check if memory allocation was successful
    if (response == NULL)
    {
        return NULL; // Error handling: return NULL to indicate failure
    }

    // Copy the HTTP header to the response
    strcpy(response, header);

    // Read the HTML file content into the response
    size_t header_length = strlen(header);
    size_t bytes_read = fread(response + header_length, 1, file_size, p_file);

    // Null-terminate the response
    response[header_length + bytes_read] = '\0';

    return response;
}

char *param_val_GET(char *request, char *param)
{

    // check if not GET
    if (request_type(request) != HTTP_GET)
    {
        printf("Wrong request type");
        return NULL;
    }
    printf("param: %s \n\n", param);
    // main function
    char *val_start = strstr(request, param);
    if (val_start == NULL )
    {
        printf("Param %s not found in request. \n", param);
        return NULL;
    }

    // move to '=' char
    val_start += strlen(param) + 1;
    // printf("val_start: %c \n", *val_start);
    // init param_end
    char *val_end = val_start;

    // loop forward until meet '&' or ' '
    while (*val_end != '&' && *val_end != ' ' && *val_end != '\n')
    {
        // printf("%c", *val_end);
        val_end++;
    }
    printf("\n");
    size_t val_len = val_end - val_start;

    // get value
    char *val = (char *)malloc(val_len + 1);
    if (val == NULL)
    {
        printf("Memory allocation failed ! \n");
        return NULL;
    }

    strncpy(val, val_start, val_len);
    val[val_len] = '\0'; // Null-terminate the string
    return val;
}
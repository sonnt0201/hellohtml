/*
    10/2023 by SƠN
    libs testing
    to run test, open terminal in 'libs' folder and run :
    gcc httphelper.c test.c -o test; ./test.exe
*/

#include "httphelper.h"
#include <stdio.h>
#include <string.h>


int main() {
    char message[4098] = "hello library! \n";
    print_request(message, strlen(message));
    char* buffer = "POST /hello.htm HTTP/1.1 \n \n User-Agent: Mozilla/4.0 (compatible; MSIE5.01; Windows NT) \nHost: www.tutorialspoint.com\nAccept-Language: en-us\nAccept-Encoding: gzip, deflate\nConnection: Keep-Alive";
    printf("%d \n",request_type(buffer));
    FILE *html_file = fopen("../web_pages/hello.html","r");
    if (html_file == NULL) {
        perror("Error opening HTML file. \n");
        return 1;
    }
    char* response = create_response(html_file);
    printf("%s", response);
}
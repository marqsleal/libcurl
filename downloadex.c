#include <curl/curl.h> // sudo apt-get install libcurl4-dev
#include <stdio.h>
#include <stdlib.h>

size_t got_data(char *buffer, size_t itemsize, size_t nitems, void* ignorethis)
{
    size_t bytes = itemsize * nitems;
    int line_number = 1;
    printf("New chunk (%zu bytes)\n", bytes);
    printf("%d:\t", line_number);

    for (int i = 0; i < bytes; i++)
    {
        printf("%c", buffer[i]);

        if (buffer[i] == '\n')
        {
            line_number++;
            printf("%d:\t", line_number);
        }
    }

    printf("\n\n");
    return bytes;
}

int main(void)
{
    // API Handler
    CURL *curl = curl_easy_init(); 

    if(!curl)
    {
        fprintf(stderr, "curl init failed\n");
        return EXIT_FAILURE;
    }

    // set options
    curl_easy_setopt(curl, CURLOPT_URL, "ftp://demo:password@test.rebex.net/readme.txt");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, got_data);


    // actions
    CURLcode result = curl_easy_perform(curl);

    if(result != CURLE_OK)
    {
        fprintf(stderr, "download failed: %s\n", curl_easy_strerror(result));
    }

    curl_easy_cleanup(curl);
    return EXIT_SUCCESS;
}
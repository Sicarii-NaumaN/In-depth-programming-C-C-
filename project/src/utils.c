#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "utils.h"

void cases(int choice) {
    FILE *client_book = NULL;
    data client_data = {0};
    switch (choice) {
            case 1:
                add_to_base(client_book, &client_data);
                break;
            case 2:
                read_base(client_book);
                break;
            case 3:
                break;
            default:
                puts("error");
                break;
    }
}
void add_to_base(FILE *client_book, data *client) {
    client_book = fopen("dataset/database.dat", "a+");
    if (client_book == NULL) {
        puts("Not acess");
        return;
    }
    if (scaning(client) == 0) {
        write_to_file(client_book, client);
    }
    fclose(client_book);
}

void read_base(FILE *client_book) {
    client_book = fopen("dataset/database.dat", "r");

     if (client_book == NULL) {
        puts("Not acess");
        return;
    }

    size_t size = 0;
    while (!feof(client_book))
    {
        if (fgetc(client_book) == '\n')
            size++;
    }
    if (size == 0) {
    	puts("Base is empty");
    	fclose(client_book);
    	return;
    }
    size++;
    //rewind(client_book);
    fclose(client_book);
 
    char **result = NULL;
    result = alloc_for_array(result, size);
    if (result == NULL) {
    	puts("Not acess");
    	fclose(client_book);
    	return;
    }
    result = write_to_memory(client_book, result);
    
    char **sort = NULL;
    sort = alloc_for_array(sort, size);
    if (sort == NULL) {
        puts("Not acess");
        fclose(client_book);
        return;
    }
    sort = write_to_memory(client_book, sort);

    int buf1[size];

    for (size_t i = 0; i < size; ++i) {
    	char* str = sort[i];
      	buf1[i] = atoi(strtok(str, " "));
    }
    
    for (size_t i = 0; i < size - 1; ++i) {
      	for (size_t j = 1 + i; j < size; ++j) {
            if (buf1[i] > buf1[j]) {
                char *str = NULL;
                str = result[i];
                result[i] = result[j];
                result[j] = str;
            }
      	}
    }
    printf("%s\n", "There is your visitors book: ");
    for (size_t i = 0; i < size; ++i) {
    	printf("%s\n", result[i]);
    }

    free_alloc(result, size);
    free_alloc(sort, size);
}

void copy_menu() {
    printf("please enter action\n"
           "1 add client;\n"
           "2 show data client;\n"
           "3 exit;\n");
}

int scaning(data *client) {
    while (scanf("%5d%20s%20s%12lf",
           &client->table_number,
           client->name,
           client->surname,
           &client->payments) != -1) {
        return 0;
    }
    return 1;
}
int write_to_file(FILE *visitors_book, data *got_data) {
    int check;
    check = fprintf(visitors_book, "\n%-12d%-15s%-15s%12.2f",
                         got_data->table_number,
                         got_data->name,
                         got_data->surname,
                         got_data->payments);
        
    return check;
}

int free_alloc(char** paragraph, size_t rows) {
    if (paragraph == NULL) {
    	puts("fuck");
        return -1;
    }
    for (size_t i = 0; i < rows; i++) {
        free(paragraph[i]);
    }
    free(paragraph);
    return 0;
}


char** alloc_for_array(char **paragraph, size_t size) {
    paragraph = (char **)malloc(size*sizeof(char *));

    if (paragraph == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < size; i++) {
        paragraph[i] = (char *)malloc(100*sizeof(char));
        if (paragraph[i] == NULL) {
	        for (size_t a = 0; a < i; a++) {
                free(paragraph[a]);
            }
	        free(paragraph);
            return NULL;
        }
    }
    return paragraph;
}

char** write_to_memory(FILE *client_book, char **paragraph) {
	client_book = fopen("dataset/database.dat", "r");

     if (client_book == NULL) {
        puts("Not acess");
        return NULL;
    }

    if (paragraph == NULL) {
    	fclose(client_book);
    	return NULL;
    }
    size_t i = 0;
    while (!feof(client_book)) {
        if (fgets(paragraph[i], 100, client_book) != NULL){
            i++;
   	    }
    }
    rewind(client_book);
    fclose(client_book);
    return paragraph;

}

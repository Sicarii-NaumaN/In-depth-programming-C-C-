#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "utils.h"

#define PATH "../dataset/database.dat"

void cases(int choice) {
    FILE *client_book = NULL;
    data client_data = {0};
    char path[] = PATH;
    switch (choice) {
        case 1:
            add_to_base(client_book, &client_data, path);
            break;
        case 2:
            if (read_base(client_book, path) == EXIT_NORMAL) {
                puts("Base is empty");
            }
            if (read_base(client_book, path) == EXIT_FAILURE) {
                puts("Not access");
            }
            break;
        case 3:
            break;
        default:
            puts("Error");
            break;
    }
}
int add_to_base(FILE *client_book, data *client, const char *path) {
    client_book = fopen(path, "a+");
    if (client_book == NULL) {
        return EXIT_FAILURE;
    }

    if (scanning(client) != 0 || write_to_file(client_book, client) <= 0) {
        puts("Can't add to base");
        fclose(client_book);
        return EXIT_FAILURE;
    }
    fclose(client_book);
    return EXIT_SUCCESS;
}

int read_base(FILE *client_book, const char *path) {
    client_book = fopen(path, "r");

    if (client_book == NULL) {
        return EXIT_FAILURE;
    }

    size_t size = 0;
    while (!feof(client_book)) {
        if (fgetc(client_book) == '\n')
            size++;
    }
    if (size == 0) {
        fclose(client_book);
        return EXIT_NORMAL;
    }

    fclose(client_book);
    char **result = NULL;
    result = alloc_for_array(result, size);
    if (result == NULL) {
        return EXIT_FAILURE;
    }
    result = write_to_memory(client_book, result, PATH);

    char **sort = NULL;
    sort = alloc_for_array(sort, size);
    if (sort == NULL) {
        return EXIT_FAILURE;
    }
    sort = write_to_memory(client_book, sort, PATH);
    if (sort_str(sort, result, size) == EXIT_FAILURE) {
        free_alloc(result, size);
        free_alloc(sort, size);
        return EXIT_FAILURE;
    }

    printf("%s\n", "There is your visitors book: ");
    for (size_t i = 0; i < size; ++i) {
        printf("%s\n", result[i]);
    }

    if (free_alloc(result, size) == -1) {
        return EXIT_FAILURE;
    }
    if (free_alloc(sort, size) == -1) {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

void copy_menu() {
    printf("\nPlease enter action:\n"
           "1 Add client;\n"
           "2 Show data client;\n"
           "3 Exit;\n");
}

int scanning(data *client) {
    while (scanf("%5d%20s%20s%12lf",
           &client->table_number,
           client->name,
           client->surname,
           &client->payments) != -1) {
           return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}
int write_to_file(FILE *visitors_book, data *got_data) {
    int check;
    check = fprintf(visitors_book, "%-12d%-15s%-15s%12.2f\n",
                    got_data->table_number,
                    got_data->name,
                    got_data->surname,
                    got_data->payments);
    return check;
}

int free_alloc(char** paragraph, size_t rows) {
        if (paragraph == NULL) {
            puts("Can't free");
            return EXIT_FAILURE;
        }
        for (size_t i = 0; i < rows; i++) {
           free(paragraph[i]);
        }
        free(paragraph);
        return EXIT_FAILURE;
}


char **alloc_for_array(char **paragraph, size_t size) {
    paragraph = (char **)malloc(size*sizeof(char *));

    if (paragraph == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < size; i++) {
        paragraph[i] = (char *)malloc(58*sizeof(char));
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

char **write_to_memory(FILE *client_book, char **paragraph, const char* path) {
        client_book = fopen(path, "r");

        if (client_book == NULL) {
            puts("Not access");
            return NULL;
        }

        if (paragraph == NULL) {
            fclose(client_book);
            return NULL;
        }
        size_t i = 0;
        while (!feof(client_book)) {
            if (fgets(paragraph[i], 57, client_book) != NULL) {
                i++;
            }
        }
        fclose(client_book);
        return paragraph;
}

int sort_str(char **sort, char** result, size_t size) {
    int *buf1 = (int *) malloc(size * sizeof(int));
    if (buf1 == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < size; ++i) {
        char *str = sort[i];
        buf1[i] = atoi(strtok_r(str, " ", &str));
    }
    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 1 + i; j < size; ++j) {
            if (buf1[i] > buf1[j]) {
                int dig = buf1[j];
                buf1[j] = buf1[i];
                buf1[i] = dig;
                char *str;
                str = result[j];
                result[j] = result[i];
                result[i] = str;
            }
        }
    }
    free(buf1);
    return EXIT_SUCCESS;
}

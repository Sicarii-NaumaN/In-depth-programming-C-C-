#ifndef PROJECT_INCLUDE_UTILS_H_
#define PROJECT_INCLUDE_UTILS_H_
#define EXIT_NORMAL 2
struct restoraunt_visitors{
    int table_number;
    char name[20];
    char surname[20];
    double payments;
};
typedef  struct  restoraunt_visitors data;

int scanning(data *client);
int write_to_file(FILE *client_book, data *got_data);
int free_alloc(char** paragraph, size_t rows);
int sort_str(char **sort, char** result, size_t size);

int read_base(FILE *client_book,const char *path);
int add_to_base(FILE *client_book , data *client,const char *path);

char **alloc_for_array(char **paragraph, size_t size);
char **write_to_memory(FILE *client_book, char **paragraph,const char *path);

void copy_menu();
void cases(int choice);

#endif  //  PROJECT_INCLUDE_UTILS_H_

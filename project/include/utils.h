#ifndef PROJECT_INCLUDE_TASK1
#define PROJECT_INCLUDE_TASK1

struct restoraunt_visitors{
    int table_number;         
    char name[20];         
    char surname[20];
    double payments;
	
};
typedef  struct  restoraunt_visitors data;

int scaning(data *client);
int write_to_file(FILE *client_book, data *got_data);
int free_alloc(char** paragraph, size_t rows);

void read_base(FILE *client_book);
void add_to_base(FILE *client_book , data *client);

char** alloc_for_array(char **paragraph, size_t size);
char** write_to_memory(FILE *client_book, char **paragraph);

void copy_info();
void copy_menu();
void cases(int choice);

#endif  //  PROJECT_INCLUDE_TASK1
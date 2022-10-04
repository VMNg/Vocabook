#ifndef LIST_H
#define LIST_H
#include <string>
class list {
    private:
        record *start;
        std::string file_name;
        int read_file();
        int write_file();
        record* reverse_list(record *);
        void delete_all_records();

    public:
        list();
        list(std::string);
        ~list();
        int add_record(std::string, std::string, std::string, std::string);
        int print_record(std::string);
        int modify_record(std::string, std::string, std::string);
        void print_all_records();
        int delete_record(std::string);
        void reverse_llist();
};
#endif
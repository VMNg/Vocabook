#include <iostream>
#include <fstream>
#include <string>
#include "record.h"
#include "list.h"
#include "voca_book.h"
using namespace std;

list::list() {
    // list default constructor variables
    int records_read = 0;
    // initialize class variables
    start = NULL;
    file_name = "save.txt";

    records_read = read_file();
    // print messages for files
    if (records_read < 0) {
        cout << "'" << file_name << " was not found.\n";
        cout << "Therefore, no records have been added to the list and '" << file_name << "' will be created.\n";
    } else if (records_read == 0) { // else if records_read == 0
        cout << "'" << file_name << "' has been found but is empty.\n";
        cout << "Therefore, no records have been added to the database.\n";
    } else { // else if records_read > 0
        cout << "'" << file_name << "' has been read. " << records_read << " records have been added to the database.\n";
    } // end if records_read < 0
    cout << "--------------------\n";
} // end default list constructor

list::list(string file) {
    // list custom constructor variables
    int records_read = 0;
    // initialize class variables
    start = NULL;
    file_name = file;

    records_read = read_file();
    // print messages for files
    if (records_read < 0) {
        cout << "'" << file_name << " was not found.\n";
        cout << "Therefore, no records have been added to the list and '" << file_name << "' will be created.\n";
    } else if (records_read == 0) { // else if records_read == 0
        cout << "'" << file_name << "' has been found but is empty.\n";
        cout << "Therefore, no records have been added to the database.\n";
    } else { // else if records_read > 0
        cout << "'" << file_name << "' has been read. " << records_read << " records have been added to the database.\n";
    } // end if records_read < 0
    cout << "--------------------\n";
} // end list custom constructor

list::~list() {
    write_file();
    delete_all_records();
} // end list deconstructor

int list::read_file() {
    // read_file variables
    ifstream read_file(file_name.c_str());
    struct record *temp = NULL;
    struct record *index = NULL;
    struct record *previous = NULL;
    int file_char_length = 0;
    int record_count = 0;
    string dummy = "";

    if (!read_file.is_open()) {
        read_file.close();
        return -1;
    } // end if !read_file.is_open()
    read_file.seekg(0, read_file.end); // move read pointer to end of file
    file_char_length = read_file.tellg(); // return file pointer position
    if (file_char_length == 0) {
        read_file.close();
        return 0;
    } // end file_char_length == 0
    read_file.seekg(0, read_file.beg); // reset file pointer to beginning
    do { // do while !read_file.eof()
        // do while temporary variables
        string mean = "";

        temp = new record;
        index = start;
        getline(read_file, temp->name);
        getline(read_file, temp->mean);
        read_file >> temp->day_create;
        // getline(read_file, dummy);
        getline(read_file, temp->kind);
        // getline(read_file, dummy);
        ++record_count;
        while (index != NULL) {
            previous = index;
            index = index->next;
        } // end while index != NULL
        if (previous == NULL) {
            temp->next = start;
            start = temp;
        } else { // else if previous != NULlists
            previous->next = temp;
            temp->next = index;
        } // end if previous == NULL
    } while (!read_file.eof()); // end do while
    read_file.close();
    return record_count; // read_file return - end of function
}

int list::write_file() {
    // write_file variables
    ofstream write_file(file_name.c_str());
    record *index = start;
    int record_count = 0;

    if (start == NULL) {
        cout << "The database is empty. Therefore, no records have been added to file: " << file_name << '\n';
        write_file.close();
        return -1;
    } // end if start == NULL
    do { // do while index != NULL
        write_file << index->name << "\n";
        write_file << index->mean << "\n";
        write_file << index->kind << "\n";
        if (index->next != NULL) {
            // Prints 2 newlines when not at the end of the list to keep the same format from reading
            write_file << index->day_create << "\n\n";
        } else { // else if index->start == NULL
            // Prints 1 newline when at the end of list to keep the same format from reading
            write_file << index->day_create<< "\n";
        } // end if index->next != NULL
        index = index->next;
        ++record_count;
    } while (index != NULL); // end do while
    cout << record_count << " Vocabulary have been recorded to file: " << file_name << "\n";
    write_file.close();
    return 0; // write_file return - end of function
}

void list::delete_all_records() {
    // delete_all_records variables
    struct record *temp = start;
    struct record *index = NULL;
    int records_deleted = 0;

    cout << "--------------------\n";
    if (start != NULL) {
        while (index != NULL) {
            temp = index;
            index = index->next;
            start = index;
            delete temp;
            ++records_deleted;
        } // end while index != NULL
        cout << records_deleted << " Vocabulary removed from the memory.\n";
    } else { // else if start == NULL
        cout << "The Database is empty. Therefore, no Vocabulary have been removed.\n";
    }// end if start != NULL
    cout << "--------------------\n";
    return; // delete_all_records return - end of function
}

int list::add_record(string input_name, string input_mean, string input_kind, string input_day_create) {
    struct record *temp = NULL;
    struct record *index = start;
    struct record *previous = NULL;


    temp = new record;
    temp->name = input_name;
    temp->mean = input_mean;
    temp->day_create = input_day_create;
    temp->kind = input_kind;
    while (index != NULL) {
        previous = index;
        index = index->next;
    } // end while index != NULL
    if (previous == NULL) {
        temp->next = start;
        start = temp;
    } else { // else if previous != NULL
        previous->next = temp;
        temp->next = index;
    } // end if previous == NULL
    cout << "--------------------\n";
    cout << "Record has been added.\n";
    cout << "--------------------\n";
    return 1; // add_record return - end of function
}

int list::print_record(string input_name) {
    struct record *index = start;
    int records_printed = 0;

    #ifdef DEBUG
    {
        debug_function(2, input_name);
    }
    #endif

    cout << "--------------------\n";
    if (start == NULL) {
        cout << "The Database is empty. Therefore, no records of " << input_name << " exist.\n";
        cout << "--------------------\n";
        return -1;
    } // end if start == NULL
    while (index != NULL) {
        if (input_name == index->name) {
            ++records_printed;
            cout << "====================\n";
            cout << "Record #" << records_printed << " of:\n";
            cout << "Name: " << index->name << "\n";
            cout << "mean: " << index->mean << '\n';
            cout << "Year of Birth: " << index->day_create << '\n';
            cout << "Kind: " << index->kind << '\n';
        } // end if input_name == index->name
        index = index->next;
    } // end while index != NULL

    if (records_printed == 0) {
        cout << "No records of " << input_name << " found.\n";
    } else { // else if records_printed > 0
        cout << records_printed << " records of " << input_name << " printed." << '\n';
    } // end if records_printed == 0
    cout << "--------------------\n";
    return 1; // print_record return - end of function
}

int list::modify_record(string input_name, string input_mean, string input_kind) {
    // modify_record variables
    struct record *index = start;
    int records_modified = 0;

    #ifdef DEBUG
    {
        debug_function(3, input_name, input_mean, input_kind);
    }
    #endif

    cout << "--------------------\n";
    if (start == NULL) {
        cout << "The Database is empty. Therefore, no records of " << input_name << " exist.\n";
        cout << "--------------------\n";
        return -1; // modify_record return
    } // end if start == NULL
    while (index != NULL) {
        if (input_name == index->name) {
            index->mean = input_mean;
            index->kind = input_kind;
            ++records_modified;
        } // end if input_name == index->name
        index = index->next;
    } // end while index != NULL
    if (records_modified == 0) {
        cout << "No records of " << input_name << " found.\n";
    } else { // else if records_modified != 0
        cout << records_modified << " records of " << input_name << " records_modified.\n";
    } // end if records_modified == 0
    cout << "--------------------\n";
    return 1; // modify_record return - end of function
}


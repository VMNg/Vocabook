#include <iostream>
#include <string>
#include "record.h"
#include "list.h"
#include "voca_book.h"
using namespace std;

void run_program(){
    list records(get_file_name());
    string input_name = "";
    string input_mean = "";
    string input_kind = "";
    string input_day_create = 0;
    int menu_selection = 0;

    display_commands();
    do{
        menu_selection = get_menu_selection();
        switch (menu_selection) {

            case 1:
            cout << "--------------------\n";
            cout << "Add a new Voca\n";
            input_name = get_name();
            input_mean = get_mean();
            input_kind = get_kind();
            input_day_create = get_create_day();
            records.add_record(input_name, input_mean, input_kind, input_day_create);
            break; 

            case 2:
            cout << "--------------------\n";
            cout << "Print Voca(s)\n";
            input_name = get_name();
            records.print_record(input_name);
            break;

            case 3:
            cout << "--------------------\n";
            cout << "Modify that Voca(s)\n";
            input_name = get_name();
            input_mean = get_mean();
            input_kind = get_kind();
            input_day_create = get_create_day();
            records.modify_record(input_name, input_mean, input_kind);
            break;

            case 4:
            cout << "--------------------\n";
            cout << "Printing Voca...\n";
            records.print_all_records();
            break;

            case 5:
            cout << "--------------------\n";
            cout << "Delete Voca(s) with the same name\n";
            records.delete_record(input_name);
            break;
            
        }
        if (menu_selection != 7) {
            display_commands();
        }
    }while (menu_selection != 7);
    return;
}

void display_commands() {
    cout << "Usage:\n";
    cout << "\t1: Add a new vocabulary into the database.\n";
    cout << "\t2: Print information about a vocabulary using the name as the key. \n";
    cout << "\t3: Modify a vocabulary in the database using the name as the key. \n";
    cout << "\t4: Print all vocabulary in the database.\n";
    cout << "\t5: Delete an existing vocabulary from the database.\n";
    cout << "\t6: Quit the program.\n";
    cout << "What would you like to do? => ENTER A KEY NUMBER\n";
    return; 
}

int get_menu_selection (){
    int selection = 0;
    cin >> selection;
    while(cin.fail()|| selection <1|| selection >6){
        if(cin.fail()){
            cout << "Your inpute war not an integer. Please enter an integer: \n";
            }else if (selection <1 || selection >6){
                cout << "Not valid choice.\n";
                display_commands();
            }
            cin.clear();
            cin.ignore(256,'\n');
            cin >> selection;
        }
        cin.clear();
        return selection;
    }

string get_name(){
    string name = "";
    cin.clear();
    cin.ignore(256,'\n');
    cout << "Please enter a Vocabulary: ";
    getline(cin, name);
    return name;
}

string get_mean(){
    string mean = "";
    cin.ignore(256,'\n');
    cout << "Please enter the meaning of this vocabulary: ";
    getline(cin, mean);
    return mean;
}

string get_kind(){
    string kind = "";
    cout << "Please enter the kind of this vocabulary: ";
    getline(cin, kind);
    return kind;
}

string get_create_day(){
    string day;
    cout << "Please enter the date create of this vocabulary: ";
    getline(cin,day);
    return day;
}

string get_file_name() {

    string file_name = "";
    int count;

    cout << "Please enter your FILE NAME ('.txt' file extension will be added): ";
    getline(cin, file_name);
    file_name += ".txt";
    return file_name; 
}


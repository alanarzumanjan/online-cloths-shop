#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

class User {
private:
    int user_id;
    string user_name;
    string user_surname;
    string user_address;
    string password;

public:
    User() : user_id(0), user_name(""), user_surname(""), user_address(""), password("") {}

    User(int user_id, const string& user_name, const string& user_surname, const string& user_address, const string& password)
        : user_id(user_id), user_name(user_name), user_surname(user_surname), user_address(user_address), password(password) {}

    int getUserId() const {
        return user_id;
    }

    int getMaxUserId() {
        ifstream file("User_database.txt");
        int max_id = 0;
        int stored_id;
        string temp;
        while (getline(file, temp)) { 

            istringstream iss(temp); // Using string stream to parse the line
            if (iss >> stored_id) {

                if (stored_id > max_id) {
                    max_id = stored_id;
                }
            }
        }
        file.close();
        return max_id;
    }

    void registerUser() {
        int max_id = getMaxUserId();
        user_id = max_id + 1;
        cout << "Enter your details" << endl;
        cout << "Name: "; cin >> user_name;
        cout << "Surname: "; cin >> user_surname;
        cout << "Address: "; cin >> user_address;
        cout << "Create a password: "; cin >> password;
        cout << "Your ID is: " << user_id << ". Remember it for login!" << endl;
        saveToFile();
    }

    void saveToFile() {
        ofstream file("User_database.txt", ios::app);
        if (file.is_open()) {
            file << user_id << " " << user_name << " " << user_surname << " " << user_address << " " << password << endl;
            file.close();
        } 
        else {
            cout << "Error opening the database file." << endl;
        }
    }

    void log() {
        cout << "Enter your ID: ";
        cin >> user_id;

        ifstream file("User_database.txt");
        int stored_id;
        string stored_name, stored_surname, stored_address, stored_password;
        bool userFound = false; // Flag to track user presence

        while (file >> stored_id >> stored_name >> stored_surname >> stored_address >> stored_password) {
            if (stored_id == user_id) {
                cout << "Enter your password: ";
                string entered_password;
                cin >> entered_password;

                if (entered_password == stored_password) {
                    cout << "Login successful!" << endl;
                    userFound = true;
                    break; 
                } 
                else {
                    cout << "Incorrect password." << endl;
                    userFound = true;
                    break;
                }
            }
        }
        if (!userFound) {
            cout << "User not found." << endl;
        }
        file.close();
    }

    void register_or_login() {
        int choice;
        cout << "1. Register\n2. Login\nEnter your choice: ";
        cin >> choice;
        if (choice == 1) {
            registerUser();
        } 
        else if (choice == 2) {
            log();
        } 
        else {
            cout << "Invalid choice." << endl;
        }
    }
};

class UserCard: public User
{
private:
    string card_number;
    double bank_account;

public:
    UserCard(string card_number, double bank_account): 
        card_number(card_number), bank_account(bank_account) {}

    void buying(){

    }

};

class Review{
private:
    int review_id;
    int user_id;
    int product_id;
    string comment;
    int rating;

public:
    Review(int review_id, int user_id, int product_id, string comment, int rating): 
        review_id(review_id), user_id(user_id), product_id(product_id), comment(comment),
        rating(rating) {}

    void addReview(int product_id){

    }

    void displayReviews(){

    }
};

void Menu(){
    cout << endl;
    cout << "====> Menu <====" << endl;
    cout << "1. Register / Login" << endl;
    cout << "2. Show and add/remove products to card" << endl;
    cout << "3. Show Card status" << endl;
    cout << "4. Payment" << endl;
    cout << "5. Admin" << endl;
    cout << "6. Exit" << endl;
    cout << "Enter your choice: ";
}

int main() {
    int choice;
    User user;

    do {
        Menu();
        cin >> choice;
        switch (choice) {
            case 1: // Register or Login
                user.register_or_login();
                break;
            case 2: // Show and add products to card
                
                break;
            case 3: // Show Card status
                
                break;
            case 4: // Payment
                
                break;
            case 5: // Admin
                
                break;
            case 6: // Exit
                cout << "Exiting the program." << endl;
                break;
            default:
                cout << "Incorrect choice, please try again." << endl;
        }
    } while (choice != 6);

    return 0;
}
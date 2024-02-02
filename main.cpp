#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

// Main file. Don't change please

using namespace std;

enum{
    Jeans,
    T_shirts,
    Shirts,
    Sweaters,
    Hoodies, 
    Jumpers, 
    Pants, 
    Sweatpants, 
    Coats, 
    Jackets, 
    Fur_coats,
    Shorts,
    Windbreakers,
    Socks,
    Briefs,
    Bras
};

enum{
    Male, // Мужской
    Female, // Женский
    Unisex // Унисекс
};

class User {
private:
    int user_id;
    string user_name;
    string user_surname;
    string user_address;
    string password;

public:
    User() : user_id(0), user_name(""), user_surname(""), user_address(""), password("") {}

    User(int user_id, const string& user_name, const string& user_surname, const string& user_address,
        const string& password):
            user_id(user_id), user_name(user_name),
            user_surname(user_surname), user_address(user_address), password(password) {}

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

    void addReview(){

    }

    void displayReviews(){

    }
};

class Product {
private: 
    
public:
    int product_id;
    string product_name;
    string product_brand;
    string product_size;
    string product_description;
    string product_category;
    string product_gender;
    float product_price;
    int product_quantity;

    Product(int product_id, string product_name, string product_brand, string product_size, string product_description, string product_category,
        string product_gender, float product_price, int product_quantity): 
        product_id(product_id), product_name(product_name), product_brand(product_brand),
        product_size(product_size), product_description(product_description), product_category(product_category),
        product_gender(product_gender), product_price(product_price), product_quantity(product_quantity) {} 
     
    void show_products_and_add_to_cart() {
        cout << "List of Products:" << endl;
        cout << "================" << endl;

        ifstream file("Products_database.txt");

        if (!file.is_open()) {
            cerr << "Error opening the products database file." << endl;
            return;
        }

        int product_id;
        string product_name, product_brand, product_size, product_description;
        int product_category, product_gender;
        float product_price;
        int product_quantity;

        while (file >> product_id >> product_name >> product_brand >> product_size >> product_description >>
            product_category >> product_gender >> product_price >> product_quantity) {

            cout << "Product ID: " << product_id << endl;
            cout << "Name: " << product_name << endl;
            cout << "Brand: " << product_brand << endl;
            cout << "Size: " << product_size << endl;
            cout << "Description: " << product_description << endl;
            cout << "Category: " << product_category << endl;
            cout << "Gender: " << product_gender << endl;
            cout << "Price: $" << product_price << endl;
            cout << "Quantity: " << product_quantity << endl;
            cout << "================" << endl;
        }

        file.close();
        int entered_product_id;
        cout << "Enter ID product to add it to cart: ";
        cin >> entered_product_id;
        add_product_to_cart(entered_product_id);

    }
};

class Cart: public Product 
{
private:
    vector<Product> Products;

public:
    void add_product_to_cart(const Product& new_product) {
        Products.push_back(new_product);
        cout << new_product.product_name << " added to the cart." << endl;
    }

    void remove_product_to_cart(const string& product_name) {
        auto it = remove_if(Products.begin(), Products.end(),
            [&](const Product& Product) { return Product.product_name == product_name; });

        if (it != Products.end()) {
            Products.erase(it, Products.end());
            cout << product_name << " removed from the cart." << endl;
        } 
        else {
            cout << product_name << " not found in the cart." << endl;
        }
    }

    void displayCart() {
        if (Products.empty()) {
            cout << "The shopping cart is empty." << endl;
        } 
        else {
            cout << "Products in the shopping cart:" << endl;
            for (const auto& Product : Products) {
                cout << Product.product_name << " - $" << Product.product_price << " - Quantity: " << Product.product_quantity << endl;
            }
        }
    }
    
};


class Warehouse{

};

class Admin: public Product
{
public:
    
    void product_add_to_shop(){ // via warehouse
        
        cout << "Enter product id: ";
        cin >> product_id;

    }

    void product_delete_to_shop(){ // via warehouse
        cout << "Enter product id: ";
        cin >> product_id;

    }

    void manage_products(){
        int choice;
        do{
            cout << "--> Products manager <--" << endl;
            cout << "1. Add product to shop" << endl;
            cout << "2. Delete product from shop" << endl;
            cout << "3. Exit" << endl;
            cin >> choice;

            switch (choice)
            {
            case 1:
                product_add_to_shop();
                break;
            case 2:
                product_delete_to_shop();
                break;
            case 3:
                break;
            default:
                cout << "Incorrect choice, please try again." << endl << endl;
            }

        }while(choice != 3);
    }
    
    void add_user(){}
    void delete_user(){}
    void modify_user(){}

    void manage_users(){
        int choice;
        do{
            cout << "--> Users manager <--" << endl;
            cout << "1. Add User" << endl;
            cout << "2. Delete User" << endl;
            cout << "3. Modify User" << endl;
            cout << "4. Exit" << endl;
            cin >> choice;

            switch(choice){
                case 1:
                    add_user();
                    break;
                case 2:
                    delete_user();
                    break;
                case 3:
                    modify_user();
                    break;
                case 4:
                    break;
                default:
                    cout << "Incorrect choice, please try again." << endl << endl;  
            }

        }while(choice != 4);
    }

    void view_orders(){}
    void warehouse_update(){}

    void Admin_Functions(){
        int choice;
        do{
            cout << "--> Admin functions <--" << endl;
            cout << "1. Manage Products" << endl;
            cout << "2. Manage Users" << endl;
            cout << "3. View Orders" << endl;
            cout << "4. Warhouse Update" << endl;
            cout << "5. Exit" << endl;
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice)
            {
            case 1:
                manage_products();
                break;
            case 2:
                manage_users();
                break;
            case 3:
                view_orders();
                break;
            case 4:
                warehouse_update();
                break;
            case 5:
                break;
            default:
                cout << "Incorrect choice, please try again." << endl << endl;
            }
        }while(choice != 5);
    }
    
};

void Menu(){
    cout << endl;
    cout << "====> Menu <====" << endl;
    cout << "1. Register / Login" << endl;
    cout << "2. Show and add/remove products to card" << endl;
    cout << "3. Show Card status and add/remove products to card" << endl;
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
            case 2: // Show products and add products to card
                show_products_and_add_to_cart();
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
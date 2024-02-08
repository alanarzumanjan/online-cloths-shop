#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <thread> // Для использования his_thread::sleep_for
#include <chrono> // Для использования schrono::seconds
// Main file. Don't change please

using namespace std;
using namespace this_thread;

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

    string toString() const {
        stringstream ss;
        ss << product_id << " " << product_name << " " << product_price;
        return ss.str();
    }
};

class Inventory {
private:
    vector<Product> products;

public:
    Inventory() {
        loadProducts();
    }

    void loadProducts() {
        ifstream file("Products_database.txt");
        if (!file.is_open()) {
            cerr << "Error opening the products database file." << endl;
            return;
        }

        int id, quantity;
        string name, brand, size, description, category, gender;
        float price;

        products.clear();

        string line;
        while (getline(file, line)) {
            istringstream iss(line);
            
            if (iss >> id >> name >> brand >> size >> quoted(description) >> category >> gender >> price >> quantity) {
                products.emplace_back(id, name, brand, size, description, category, gender, price, quantity);
            }
        }

        file.close();
    }

    bool addProductToCartById(int id, vector<Product>& cart) {
        auto it = find_if(products.begin(), products.end(), [id](const Product& product) {
            return product.product_id == id;
        });

        if (it != products.end()) {
            cart.push_back(*it);
            products.erase(it);
            saveProducts();
            return true;
        }
        return false;
    }

    void saveProducts() {
        ofstream file("Products_database.txt");
        for (const auto& product : products) {
            file << product.toString() << endl;
        }
        file.close();
    }
    // To shop
    void add_product() {
        ifstream readFile("Products_database.txt");
        string line;
        int max_id = 0;
        
        while (getline(readFile, line)) {
            istringstream iss(line);
            int id;
            if (iss >> id) {
                max_id = max(max_id, id);
            }
        }
        readFile.close();

        int id = max_id + 1;
        int quantity;
        string name, brand, size, description, category, gender;
        float price;
        
        cout << "Enter product name: ";
        cin.ignore();
        getline(cin, name);

        cout << "Enter product brand: ";
        getline(cin, brand);

        cout << "Enter product size: ";
        getline(cin, size);

        cout << "Enter product description: ";
        getline(cin, description);

        cout << "Enter product category: ";
        getline(cin, category);

        cout << "Enter product gender (Male/Female/Unisex): ";
        getline(cin, gender);

        cout << "Enter product price: ";
        cin >> price;

        cout << "Enter product quantity: ";
        cin >> quantity;

        ofstream file("Products_database.txt", ios::app);
        if (file.is_open()) {
            file << id << " " 
                << name << " "
                << brand << " "
                << size << " "
                << description << " "
                << category << " "
                << gender << " "
                << price << " " 
                << quantity << endl;
            cout << "Product added successfully." << endl;
        } else {
            cout << "Unable to open the database file." << endl;
        }
    }
    Product parseProductLine(const string& line) {
        
        istringstream iss(line);
        int id; string name; float price;
        
        if (iss >> id >> name >> price) {
            return Product(id, name, );
        }
        return Product(); 
    }
};

class Cart
{
private:

public:
    vector<Product> Products;

    void add_product_to_cart(const Product& new_product) {
        Products.push_back(new_product);
        cout << new_product.product_name << " added to the cart." << endl;
    }

    void show_products() {
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

    }

    void remove_product_to_cart(const int& product_id) {
        auto it = remove_if(Products.begin(), Products.end(),
            [&](const Product& Product) {
                return Product.product_id == product_id; 
                }
            );

        if (it != Products.end()) {
            Products.erase(it, Products.end());
            cout << product_id << " removed from the cart." << endl;
        } 
        else {
            cout << product_id << " not found in the cart." << endl;
        }
    }

    void display_cart() {
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

class Warehouse {
    public:
        // all aboard the breakage-mobile
         vector<Product> products;

         Warehouse();

        void update_warehouse() {
            int choice;
            cout << "1. Add product\n2. Modify product\n3. Delete product\nPlease enter your choice: "; cin >> choice;
            switch (choice) {
                case 3:
                    string product_name;
                    cout << "Enter in the name of the product: "; cin >> product_name;
                    auto it = remove_if(products.begin(), products.end(),
                        [&](const Product& Product) { return Product.product_name == product_name; });

                    if (it != products.end()) {
                        products.erase(it, products.end());
                        cout << product_name << " removed from the cart." << endl;
                    } 
                    else {
                        cout << product_name << " not found in the cart." << endl;
                    }
            }
        }
};

class Warehouse {
    public:
        // all aboard the breakage-mobile
        vector<Product> products;

        Warehouse();

        void update_warehouse() {
            int choice;
            cout << "1. Add product\n2. Modify product\n3. Delete product\nPlease enter your choice: "; cin >> choice;
            switch (choice) {
                case 3:
                    string product_name;
                    cout << "Enter in the name of the product: "; cin >> product_name;
                    auto it = remove_if(products.begin(), products.end(),
                        [&](const Product& Product) { return Product.product_name == product_name; });

                    if (it != products.end()) {
                        products.erase(it, products.end());
                        cout << product_name << " removed from the cart." << endl;
                    } 
                    else {
                        cout << product_name << " not found in the cart." << endl;
                    }
            }
        }
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
    void delete_user(){
        auto it = remove_if(User.begin(), User.end(),
                [&](const User& User) { 
                    return Product.product_name == product_name; });

        if (it != Products.end()) {
            Products.erase(it, Products.end());
            cout << product_name << " removed from the cart." << endl;
        } 
        else {
            cout << product_name << " not found in the cart." << endl;
        }
        }

    void modify_user(){fstream userdb("User_database.txt");
            int id;
            cout << "Enter ID of user: "; cin >> id;
            int stored_id;
            string stored_name, stored_surname, stored_address, stored_password;
            while (userdb >> stored_id ) {
                if (stored_id == id) {
                    int mchoice;
                    cout << "1. Modify name\n2. Modify surname\n3. Modify address\n4. Modify password\n5. Exit\nPlease enter your choice: "; cin >> mchoice;
                    switch(mchoice) {
                        case 1: {
                            // Temporary variables to store modified data
                            string new_name;
                            string temp_line;  // Temporary variable to store the entire line

                            // Create a temporary file to store modified data
                            ofstream tempFile("temp_user_database.txt");

                            // Loop through the userdb file
                            while (userdb >> stored_id >> stored_name >> stored_surname >> stored_address >> stored_password) {
                                if (stored_id == id) {
                                    cout << "Enter a new name: "; cin >> new_name;
                                    // Update only the name
                                    tempFile << stored_id << " " << new_name << " " << stored_surname << " " << stored_address << " " << stored_password << endl;
                                } else {
                                    // Write unchanged data to the temporary file
                                    tempFile << stored_id << " " << stored_name << " " << stored_surname << " " << stored_address << " " << stored_password << endl;
                                }
                            }

                            // Close the original file
                            userdb.close();
                            
                            // Close the temporary file
                            tempFile.close();

                            // Remove the original file
                            remove("User_database.txt");

                            // Rename the temporary file to the original file
                            rename("temp_user_database.txt", "User_database.txt");
                        } case 2: {
                            // Temporary variables to store modified data
                            string new_surname;
                            string temp_line;  // Temporary variable to store the entire line

                            // Create a temporary file to store modified data
                            ofstream tempFile("temp_user_database.txt");

                            // Loop through the userdb file
                            while (userdb >> stored_id >> stored_name >> stored_surname >> stored_address >> stored_password) {
                                if (stored_id == id) {
                                    cout << "Enter a new name: "; cin >> new_surname;
                                    // Update only the name
                                    tempFile << stored_id << " " << stored_name << " " << new_surname << " " << stored_address << " " << stored_password << endl;
                                } else {
                                    // Write unchanged data to the temporary file
                                    tempFile << stored_id << " " << stored_name << " " << stored_surname << " " << stored_address << " " << stored_password << endl;
                                }
                            }

                            // Close the original file
                            userdb.close();
                            
                            // Close the temporary file
                            tempFile.close();

                            // Remove the original file
                            remove("User_database.txt");

                            // Rename the temporary file to the original file
                            rename("temp_user_database.txt", "User_database.txt");
                        } case 3: {
                            
                            string new_address; //temporary variables to store modified data
                            string temp_line;  //temporary variable to store the entire line

                            
                            ofstream tempFile("temp_user_database.txt"); //create a temporary file to store modified data

                            
                            while (userdb >> stored_id >> stored_name >> stored_surname >> stored_address >> stored_password) { //loop through the userdb file
                                if (stored_id == id) {
                                    cout << "Enter a new address: "; cin >> new_address;
                                    //update only the name
                                    tempFile << stored_id << " " << stored_name << " " << stored_surname << " " << new_address << " " << stored_password << endl;
                                } else {
                                    //write unchanged data to the temporary file
                                    tempFile << stored_id << " " << stored_name << " " << stored_surname << " " << stored_address << " " << stored_password << endl;
                                }
                            }

                            
                            userdb.close(); //close the original file
                            tempFile.close(); //close the temporary file

                            
                            remove("User_database.txt"); //remove the original file

                            
                            rename("temp_user_database.txt", "User_database.txt"); //rename the temporary file to the original file
                        } case 4: {
                            // Temporary variables to store modified data
                            string new_password;
                            string temp_line;  // Temporary variable to store the entire line

                            // Create a temporary file to store modified data
                            ofstream tempFile("temp_user_database.txt");

                            // Loop through the userdb file
                            while (userdb >> stored_id >> stored_name >> stored_surname >> stored_address >> stored_password) {
                                if (stored_id == id) {
                                    cout << "Enter a new name: "; cin >> new_password;
                                    // Update only the name
                                    tempFile << stored_id << " " << stored_name << " " << stored_surname << " " << stored_address << " " << new_password << endl;
                                } else {
                                    // Write unchanged data to the temporary file
                                    tempFile << stored_id << " " << stored_name << " " << stored_surname << " " << stored_address << " " << stored_password << endl;
                                }
                            }

                            // Close the original file
                            userdb.close();
                            
                            // Close the temporary file
                            tempFile.close();

                            // Remove the original file
                            remove("User_database.txt");

                            // Rename the temporary file to the original file
                            rename("temp_user_database.txt", "User_database.txt");
                        } case 5:
                            break;
                    }
                }
            }
        }
        }

    void manage_users(){
        fstream userdb("User_database.txt");
        if(userdb.is_open()){
            int choice;
            cout << "1. Add user\n2. Modify user\n3. Delete user\nPlease enter your choice: "; cin >> choice;
            switch (choice) {
                case 1:
                    registerUser();
                case 2:
                    modifyUser();
                case 3:
                    delUser();
                }   
            }
    }

    void view_orders(){}
    void warehouse_update(){Warehouse warehouse;
            warehouse.warehouse_update();
            }

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

class Payment {
    public:
        string payment_type;
        int amount;

        Payment(string pt, int a) : payment_type(pt), amount(a){}

        void process_payment() {
            cout << "Processing payment...";
            sleep_for(3s);
        }
        void validate_transaction() {

        }
        void issue_reciept() {
            cout << "Payment type: " << payment_type << "\nAmount" << amount << endl;
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
    Cart cart;
    Inventory inventory;
    inventory.add_product();
    do {
        Menu();
        cin >> choice;

        switch (choice) {
            case 1: // Register or Login
                user.register_or_login();
                break;
            case 2: // Show products and add products to card
                cart.show_products();
                cout << "Enter product ID to add to cart: ";
                int product_id;
                cin >> product_id;
                if (inventory.addProductToCartById(product_id, cart.Products))
                {
                    cout << "Product added to cart." << endl;
                } 
                else {
                    cout << "Product not found." << endl;
                }
                
                break;
            case 3: // Show Card status 
                cart.display_cart();
                break;
            case 4: // Payment
                
                break;
            case 5: // Admin
                // Admin_Functions();
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
 
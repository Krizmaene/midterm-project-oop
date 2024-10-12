#include <iostream>
#include <string>
#include <cctype>
#include <iomanip>

using namespace std;

const int MAX_ITEMS = 100;

string toUpperCase(string str) {
    for (int i = 0; i < str.length(); i++)
    str[i] = toupper(str[i]);
    return str;
}

bool isAllLetters(string str) {
    for (int i = 0; i < str.length(); i++) {
        if (!isalpha(str[i])) {
            return false;
        }
    }
    return true;
}

class Item {
private:
    string id;
    string name;
    int quantity;
    double price;
    string category;

public:
    Item() {
        id = "";
        name = "";
        quantity = 0;
        price = 0.0;
        category = "";
    }

    Item(string id, string name, int quantity, double price, string category) {
        this->id = id;
        this->name = name;
        this->quantity = quantity;
        this->price = price;
        this->category = category;
    }

    // Getter Setter
    string getID() {
        return id;
    }

    void setID(string id) {
        this->id = id;
    }

    string getName() {
        return name;
    }

    void setName(string name) {
        this->name = name;
    }

    int getQuantity() {
        return quantity;
    }

    void setQuantity(int quantity) {
        this->quantity = quantity;
    }

    double getPrice() {
        return price;
    }

    void setPrice(double price) {
        this->price = price;
    }

    string getCategory() {
        return category;
    }

    void setCategory(string category) {
        this->category = category;
    }

    void displayItem() {
        cout << left << setw(10) << id << left << setw(20) << name << left << setw(10) << quantity << left << setw(10) << fixed << setprecision(2) << price << left << setw(15) << category << endl;
    }
};

// Base Class
class InventoryManagement {
public:
    virtual void addItem() = 0;
    virtual void updateItem() = 0;
    virtual void removeItem() = 0;
    virtual void displayItemsByCategory() = 0;
    virtual void displayAllItems() = 0;
    virtual void searchItem() = 0;
    virtual void sortItem() = 0;
    virtual void displayLowStockItems() = 0;
    virtual void exit() = 0;
};

class Inventory : public InventoryManagement {
private: 
    Item items[MAX_ITEMS];
    int itemCount;

    int findItemIndex(string id) {
        for (int i = 0; i < itemCount; i++) {
            if (items[i].getID() == id) {
                return i;
            }
        }
        return -1;
    }

    // Validate Category
    bool isValidCategory(string category) {
        category = toUpperCase(category);
        return (category == "CLOTHING" || category == "ELECTRONICS" || category == "ENTERTAINMENT");
    }

public:
    Inventory() {
        itemCount = 0;
    }

    // Add Item (category, id, name, quantity, price)
    virtual void addItem() override {
        string category;
        cout << endl;
        cout << "Enter Item Category (Clothing | Electronics | Entertainment): ";
        cin >> category;
        category = toUpperCase(category);

        if (!isValidCategory(category)) {
            cout << endl;
            cout << "Category " << category << " does not exist!" << endl;
            return;
        }

        string id;
        while (true) {
            cout << endl;
            cout << "Enter Item ID (3 letters): ";
            cin >> id;
            id = toUpperCase(id);

            if (id.length() != 3 || !isAllLetters(id)) {
                cout << endl;
                cout << "Invalid input! ID must be 3 letters. Try again." << endl;
            } else {
                if (findItemIndex(id) != -1) {
                    cout << endl;
                    cout << "ID already exists! Try again." << endl;
                } else {
                    break;
                }
            }
        }

        string name;
        cout << "Enter Item Name: ";
        cin.ignore();
        getline(cin, name);
        name = toUpperCase(name);

        int quantity;
        while (true) {
            cout << "Enter Item Quantity: ";
            cin >> quantity;
            
            if (cin.fail() || quantity < 0) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << endl;
                cout << "Invalid Quantity! Please enter a non-negative integer." << endl;
            } else {
                break;
            }
        }

        double price;
        while (true) {
            cout << "Enter Item Price: ";
            cin >> price;

            if (cin.fail() || price < 0) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << endl;
                cout << "Invalid Price! Please enter a non-negative integer." << endl;
            } else {
                break;
            }
        }

        items[itemCount] = Item{id, name, quantity, price, category};
        itemCount++;
        cout << endl;
        cout << "Item added successfully!" << endl;
    }

    // Update Item (id, update quantity or price)
    void updateItem() override {
        string id;
        cout << endl;
        cout << "Enter Item ID: ";
        cin >> id;
        id = toUpperCase(id);

        int index = findItemIndex(id);
        if (index == -1) {
            cout << endl;
            cout << "Item not found!" << endl;
            return;
        }

        string updateChoice;
        cout << "Update Quantity or Price? ";
        cin >> updateChoice;
        updateChoice = toUpperCase(updateChoice);

        if (updateChoice == "QUANTITY") {
            int newQuantity;
            while (true) {
                cout << "Enter NEW Quantity: ";
                cin >> newQuantity;

                if (cin.fail() || newQuantity < 0) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << endl;
                    cout << "Invalid Quantity! Please enter a non-negative integer." << endl;
                } else {
                    break;
                }
            }
            int oldQuantity = items[index].getQuantity();
            items[index].setQuantity(newQuantity);
            cout << endl;
            cout << "Quantity of Item " << items[index].getName() << " is updated from " << oldQuantity << " to " << newQuantity << endl;
        } else if (updateChoice == "PRICE") {
            double newPrice;
            while (true) {
                cout << "Enter NEW Price: ";
                cin >> newPrice;
                
                if (cin.fail() || newPrice < 0) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << endl;
                    cout << "Invalid Price! Please enter a non-negative integer." << endl;
                } else {
                    break;
                }
            }
            double oldPrice = items[index].getPrice();
            items[index].setPrice(newPrice);
            cout << endl;
            cout << "Price of Item " << items[index].getName() << " is updated from " << oldPrice << " to " << newPrice << endl;
        } else {
            cout << endl;
            cout << "Invalid Choice! Please enter 'Quantity' or 'Price'." << endl;
        }
    }

    // Remove Item (id) 
    void removeItem () override {
        string id;
        cout << endl;
        cout << "Enter Item ID: ";
        cin >> id;
        id = toUpperCase(id);

        int index = findItemIndex(id);
        if (index == -1) {
            cout << endl;
            cout << "Item not found!" << endl;
            return;
        }

        cout << endl;
        cout << "Item " << items[index].getName() << " has been removed from the library." << endl;

        for (int i = index; i < itemCount - 1; i++) {
            items[i] = items[i + 1];
        }
        itemCount--;
    }

    // Display Items By Category (category)
    void displayItemsByCategory() override {
        string category;
        cout << endl;
        cout << "Enter Item Category (Clothing | Electronics | Entertainment): ";
        cin >> category;
        category = toUpperCase(category);

        if (!isValidCategory(category)) {
            cout << endl;
            cout << "Category " << category << " does not exist!" << endl;
            return;
        }

        bool found = false;
        cout << endl;
        cout << left << setw(10) << "ID" << left << setw(20) << "NAME" << left << setw(10) << "QUANTITY" << left << setw(10) << "PRICE" << endl;
        cout << "---------------------------------------------------------------------------------------------------------" << endl;
        
        for (int i = 0; i < itemCount; i++) {
            if (items[i].getCategory() == category) {
                items[i].displayItem();
                found = true;
            }
        }

        if (!found) {
            cout << endl;
            cout << "No items found in category." << endl;
        }
    }

    // Display All Items
    void displayAllItems() override {
        if (itemCount == 0) {
            cout << endl;
            cout << "Inventory is empty." << endl;
            return;
        }

        cout << endl;
        cout << left << setw(10) << "ID" << left << setw(20) << "NAME" << left << setw(10) << "QUANTITY" << left << setw(10) << "PRICE" << left << setw(15) << "CATEGORY" << endl;
        cout << "---------------------------------------------------------------------------------------------------------" << endl;

        for (int i = 0; i < itemCount; i++) {
            items[i].displayItem();
        }
    }

    // Search Item (id)
    void searchItem() override {
        string id;
        cout << endl;
        cout << "Enter Item ID: ";
        cin >> id;
        id = toUpperCase(id);

        int index = findItemIndex(id);
        if (index == -1) {
            cout << endl;
            cout << "Item not found!" << endl;
            return;
        }

        cout << endl;
        cout << left << setw(10) << "ID" << left << setw(20) << "NAME" << left << setw(10) << "QUANTITY" << left << setw(10) << "PRICE" << endl;
        cout << "---------------------------------------------------------------------------------------------------------" << endl;

        items[index].displayItem();
    }

    // Sort Item (sort by quantity or price, sort in ascending or descending)
    void sortItem() override {
        if (itemCount == 0) {
            cout << endl;
            cout << "Inventory is empty." << endl;
            return;
        }

        string sortChoice;
        cout << endl;
        cout << "Sort by Quantity or Price? ";
        cin >> sortChoice;
        sortChoice = toUpperCase(sortChoice);

        if (sortChoice != "QUANTITY" && sortChoice != "PRICE") {
            cout << endl;
            cout << "Invalid Choice! Pleace enter 'Quantity' or 'Price'." << endl;
            return;
        }

        string sortOrder;
        cout << "Sort in Ascending or Descending Order? ";
        cin >> sortOrder;
        sortOrder = toUpperCase(sortOrder);

        if (sortOrder != "ASCENDING" && sortOrder != "DESCENDING") {
            cout << endl;
            cout << "Invalid Choice! Please enter 'Ascending' or 'Descending'." << endl; 
            return;
        }

        // Bubble Sort
        for (int i = 0; i < itemCount; i++) {
            for (int j = 0; j < itemCount - i - 1; j++) {
                bool condition = false;
                if (sortChoice == "QUANTITY") {
                    if (sortOrder == "ASCENDING") {
                        if (items[j].getQuantity() > items[j + 1].getQuantity()) {
                            condition = true;
                        }
                    } else {
                        if (items[j].getQuantity() < items[j + 1].getQuantity()) {
                            condition = true;
                        }
                    }
                } else {
                    if (sortOrder == "ASCENDING") {
                        if (items[j].getPrice() > items[j + 1].getPrice()) {
                            condition = true;
                        }
                    } else {
                        if (items[j].getPrice() < items[j + 1].getPrice()) {
                            condition = true;
                        }
                    }
                }

                if (condition) {
                    Item temp = items[j];
                    items[j] = items[j + 1];
                    items[j + 1] = temp;
                }
            }
        }

        cout << endl;
        cout << "Items sorted by " << sortChoice << " in " << sortOrder << " order: " << endl;
        cout << endl;
        cout << left << setw(10) << "ID" << left << setw(20) << "NAME" << left << setw(10) << "QUANTITY" << left << setw(10) << "PRICE" << endl;
        cout << "---------------------------------------------------------------------------------------------------------" << endl;

        for (int i = 0; i < itemCount; i++) {
            items[i].displayItem();
        }
    }

    // Display Low Stock Items
    void displayLowStockItems() override {
        bool found = false;
        cout << endl;
        cout << left << setw(10) << "ID" << left << setw(20) << "NAME" << left << setw(10) << "QUANTITY" << left << setw(10) << "PRICE" << left << setw(15) << "CATEGORY" << endl;
        cout << "---------------------------------------------------------------------------------------------------------" << endl;

        for (int i = 0; i < itemCount; i++) {
            if (items[i].getQuantity() <= 5) {
                items[i].displayItem();
                found = true;
            }
        }

        if (!found) {
            cout << endl;
            cout << "No low stock items found." << endl;
        }
    }

    // Exit
    void exit() override {
        cout << endl;
        cout << "Exiting..." << endl;
    }
};

void displayMenu() {
    cout << endl;
    cout << "M E N U" << endl;
    cout << "1 - Add Item" << endl;
    cout << "2 - Update Item" << endl;
    cout << "3 - Remove Item" << endl;
    cout << "4 - Display Items By Category" << endl;
    cout << "5 - Display All Items" << endl;
    cout << "6 - Search Item" << endl;
    cout << "7 - Sort Item" << endl;
    cout << "8 - Display Low Stock Items" << endl;
    cout << "9 - Exit" << endl;
    cout << endl;
    cout << "Enter your choice: ";
}

int main() {
    Inventory inventory;
    int choice;

    while (true) {
        displayMenu();
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << endl;
            cout << "Invalid Input! Please enter a number between 1 and 9." << endl;
            continue;
        }

        switch (choice) {
            case 1:
                inventory.addItem();
                break;
            case 2: 
                inventory.updateItem();
                break;
            case 3:
                inventory.removeItem();
                break;
            case 4:
                inventory.displayItemsByCategory();
                break;
            case 5:
                inventory.displayAllItems();
                break;
            case 6:
                inventory.searchItem();
                break;
            case 7:
                inventory.sortItem();
                break;
            case 8:
                inventory.displayLowStockItems();
                break;
            case 9:
                inventory.exit();
                return 0;
            default:
                cout << endl;
                cout << "Invalid Choice! Please enter a number between 1 to 9." << endl;
        }
    }

    return 0;
}
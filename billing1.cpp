#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>

using namespace std;

class Product {
public:
    int code;
    string name;
    float price;
    float discount;

    Product() {}
    Product(int c, string n, float p, float d) : code(c), name(n), price(p), discount(d) {}
};

class Shopping {
private:
    vector<Product> products;

public:
    void menu();
    void administrator();
    void buyer();
    void add();
    void edit();
    void remove();
    void list();
    void receipt();
    void loadProducts();
    void saveProducts();
    void displayMenuOptions();
    void displayAdminOptions();
    void displayBuyerOptions();
    int findProductIndex(int code);
};

void Shopping::menu() {
    loadProducts();
    while (true) {
        displayMenuOptions();
        int choice;
        cin >> choice;
        switch (choice) {
            case 1:
                administrator();
                break;
            case 2:
                buyer();
                break;
            case 3:
                saveProducts();
                exit(0);
            default:
                cout << "Please select from the given options\n";
        }
    }
}

void Shopping::administrator() {
    while (true) {
        displayAdminOptions();
        int choice;
        cin >> choice;
        switch (choice) {
            case 1:
                add();
                break;
            case 2:
                edit();
                break;
            case 3:
                remove();
                break;
            case 4:
                return;
            default:
                cout << "Invalid choice!\n";
        }
    }
}

void Shopping::buyer() {
    while (true) {
        displayBuyerOptions();
        int choice;
        cin >> choice;
        switch (choice) {
            case 1:
                receipt();
                break;
            case 2:
                return;
            default:
                cout << "Invalid choice\n";
        }
    }
}

void Shopping::add() {
    int code;
    string name;
    float price, discount;
    cout << "\n\n\tAdd new product";
    cout << "\n\n\tProduct code: ";
    cin >> code;
    cout << "\n\n\tName of the product: ";
    cin >> name;
    cout << "\n\n\tPrice of the product: ";
    cin >> price;
    cout << "\n\n\tDiscount on product: ";
    cin >> discount;

    if (findProductIndex(code) == -1) {
        products.push_back(Product(code, name, price, discount));
        cout << "\n\n\tRecord inserted!\n";
    } else {
        cout << "\n\n\tProduct code already exists. Record not inserted!\n";
    }
}

void Shopping::edit() {
    int code;
    cout << "\n\n\tModify the record";
    cout << "\n\n\tProduct code: ";
    cin >> code;

    int index = findProductIndex(code);
    if (index != -1) {
        cout << "\n\n\tNew product code: ";
        cin >> products[index].code;
        cout << "\n\n\tNew name of the product: ";
        cin >> products[index].name;
        cout << "\n\n\tNew price: ";
        cin >> products[index].price;
        cout << "\n\n\tNew discount: ";
        cin >> products[index].discount;
        cout << "\n\n\tRecord edited!\n";
    } else {
        cout << "\n\n\tRecord not found!\n";
    }
}

void Shopping::remove() {
    int code;
    cout << "\n\n\tDelete product";
    cout << "\n\n\tProduct code: ";
    cin >> code;

    int index = findProductIndex(code);
    if (index != -1) {
        products.erase(products.begin() + index);
        cout << "\n\n\tProduct deleted successfully!\n";
    } else {
        cout << "\n\n\tRecord not found!\n";
    }
}

void Shopping::list() {
    cout << "\n\n|___________________________________________________________\n";
    cout << "ProNo\t\tName\t\tPrice\n";
    cout << "|___________________________________________________________\n";
    for (const auto& product : products) {
        cout << product.code << "\t\t" << product.name << "\t\t" << product.price << "\n";
    }
}

void Shopping::receipt() {
    vector<int> codes;
    vector<int> quantities;
    char choice;
    float total = 0;

    list();
    cout << "\n____________________________\n";
    cout << "\n|    Please place the order  |";
    cout << "\n|____________________________|\n";

    do {
        int code, quantity;
        cout << "\n\nProduct Code: ";
        cin >> code;
        cout << "\nProduct Quantity: ";
        cin >> quantity;

        if (find(codes.begin(), codes.end(), code) == codes.end()) {
            codes.push_back(code);
            quantities.push_back(quantity);
        } else {
            cout << "\n\nDuplicate Product Code. Please try again!\n";
        }

        cout << "\n\nWant to buy another product? Press y for yes and n for no: ";
        cin >> choice;
    } while (choice == 'y');

    cout << "\n\n\t\t\t__________RECEIPT______________\n";
    cout << "Product Num.\tProduct Name\tQuantity\tPrice\tAmount\tAmount with discount\n";

    for (size_t i = 0; i < codes.size(); ++i) {
        int index = findProductIndex(codes[i]);
        if (index != -1) {
            float amount = products[index].price * quantities[i];
            float discountAmount = amount - (amount * products[index].discount / 100);
            total += discountAmount;
            cout << codes[i] << "\t\t" << products[index].name << "\t\t" << quantities[i] << "\t\t" 
                 << products[index].price << "\t" << amount << "\t" << discountAmount << "\n";
        }
    }
    cout << "\n\n----------------------------------------";
    cout << "\n Total Amount: " << total << "\n";
}

void Shopping::loadProducts() {
    ifstream file("database.txt");
    if (file.is_open()) {
        Product product;
        while (file >> product.code >> product.name >> product.price >> product.discount) {
            products.push_back(product);
        }
        file.close();
    }
}

void Shopping::saveProducts() {
    ofstream file("database.txt");
    if (file.is_open()) {
        for (const auto& product : products) {
            file << product.code << " " << product.name << " " << product.price << " " << product.discount << "\n";
        }
        file.close();
    }
}

void Shopping::displayMenuOptions() {
    cout << "\t\t\t\t______________________________________\n";
    cout << "\t\t\t\t                                      \n";
    cout << "\t\t\t\t          Supermarket Main Menu       \n";
    cout << "\t\t\t\t                                      \n";
    cout << "\t\t\t\t______________________________________\n";
    cout << "\t\t\t\t                                      \n";
    cout << "\t\t\t\t|  1) Administrator   |\n";
    cout << "\t\t\t\t|                     |\n";
    cout << "\t\t\t\t|  2) Buyer           |\n";
    cout << "\t\t\t\t|                     |\n";
    cout << "\t\t\t\t|  3) Exit            |\n";
    cout << "\t\t\t\t|                     |\n";
    cout << "\n\t\t\t Please select: ";
}

void Shopping::displayAdminOptions() {
    cout << "\n\n\n\t\t\t Administrator menu";
    cout << "\n\t\t\t|_____1) Add the product_____|";
    cout << "\n\t\t\t|                            |";
    cout << "\n\t\t\t|_____2) Modify the product__|";
    cout << "\n\t\t\t|                            |";
    cout << "\n\t\t\t|_____3) Delete the product__|";
    cout << "\n\t\t\t|                            |";
    cout << "\n\t\t\t|_____4) Back to main menu___|";
    cout << "\n\n\t Please enter your choice: ";
}

void Shopping::displayBuyerOptions() {
    cout << "\t\t\t  Buyer \n";
    cout << "\t\t\t_____________  \n";
    cout << "                     \n";
    cout << "\t\t\t1) Buy product \n";
    cout << "                     \n";
    cout << "\t\t\t2) Go back     \n";
    cout << "\t\t\t Enter your choice: ";
}

int Shopping::findProductIndex(int code) {
    for (size_t i = 0; i < products.size(); ++i) {
        if (products[i].code == code) {
            return i;
        }
    }
    return -1;
}

int main() {
    Shopping shopping;
    shopping.menu();
    return 0;
}

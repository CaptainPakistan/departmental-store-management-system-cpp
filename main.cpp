#include <iostream>
#include <string>
#include <cstring>
#include <fstream>

using namespace std;

const int productLimit = 10;
const int category = 3;

string productNames[category][productLimit];
int productQuantity[category][productLimit];
double productPrice[category][productLimit];

int count = 0;



char decrypt[] = {
'a','b','c','d','e','f','g','h','i','j','k','l','m',
'n','o','p','q','r','s','t','u','v','w','x','y','z',
'A','B','C','D','E','F','G','H','I','J','K','L','M',
'N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
'0','1','2','3','4','5','6','7','8','9',
'!','@','#','$','%','^','&','*','(',')',
'-','_','=','+','[',']','{','}',';',':','\'','"',
',','.','<','>','/','?','\\','|','`','~'
};
const int maxSize = sizeof(decrypt) / sizeof(decrypt[0]);
int getIndex ( char arr[], char x){
for (int i=0; i<maxSize; i++){
  if (arr[i] == x){
return i;}
}
return -1;
}
string encryption(string s){
    for (int i = 0; i < s.size(); i++){
        int ind = getIndex(decrypt, s[i]);
        if (ind >= 0){
            s[i] = decrypt[(ind + 7) % maxSize];
        }
    }
    return s;
}
string decryption(string s){
    for (int i = 0; i < s.size(); i++){
        int ind = getIndex(decrypt, s[i]);
        if (ind >= 0){
            s[i] = decrypt[(ind - 7 + maxSize) % maxSize];
        }
    }
    return s;
}


void adminMenu();
void setProducts();
void saveDataToFile();
void loadDataFromFile();
void menu();


void compactCategory(int cat) {
    int write = 0;

    for (int read = 0; read < productLimit; read++) {
        if (productNames[cat][read] != "Add Product...") {
            if (write != read) {
                productNames[cat][write] = productNames[cat][read];
                productQuantity[cat][write] = productQuantity[cat][read];
                productPrice[cat][write] = productPrice[cat][read];
            }
            write++;
        }
    }

    for (int i = write; i < productLimit; i++) {
        productNames[cat][i] = "Add Product...";
        productQuantity[cat][i] = 0;
        productPrice[cat][i] = 0.0;
    }
}


class Product{
    protected:
    string name; int quantity;double price;
    public:
    Product(){
        name= "NULL";quantity= 0;price= 0.0;
    }
    void setName(string name){
        this->name=name;
    }
   
    void setQuantity(int quantity){
        this->quantity= quantity;
    }
    void setPrice(double price){
        this-> price= price;
    }
    double getPrice(){
        return price;
    }
    string getName(){
        return name;
    }
    int getQuantity(){
        return quantity;
    }
    virtual double finalPrice() = 0;
    virtual ~Product (){
	}

};
class Food: public Product{
    const float gst=15; 
    public:
    float getGst(){
        return gst;
    }
     double finalPrice() {
        return price + (price * (gst/100));
    }
    ~Food(){
	}
  
};
class selfCare: public Product{
    const float gst= 10;
    public:
    float getGst(){
        return gst;
    }
    double finalPrice() {
        return price + (price * (gst/100));
    }
    ~selfCare(){
	}
};
class houseHold: public Product{
    const float gst = 20;
    public:
    double finalPrice() {
        return price + (price * (gst/100));
    }
    float getGst(){
        return gst;
    }
    ~houseHold(){
	}
};

void viewProducts() {
    system("cls");
    
    
    cout << "\n--------------------- Food & Beverages ---------------------\n\n";
    cout << "Name:\t\tQuantity:\tPrice:\n";
    for (int j = 0; j < productLimit; j++)
        cout << productNames[0][j] << "\t\t" << productQuantity[0][j] << "\t\t" << productPrice[0][j] << "\n";

    cout << "\n--------------------- Self Care ---------------------\n\n";
    cout << "Name:\t\tQuantity:\tPrice:\n";
    for (int j = 0; j < productLimit; j++)
        cout << productNames[1][j] << "\t\t" << productQuantity[1][j] << "\t\t" << productPrice[1][j] << "\n";

    cout << "\n--------------------- House Hold ---------------------\n\n";
    cout << "Name:\t\tQuantity:\tPrice:\n";
    for (int j = 0; j < productLimit; j++)
        cout << productNames[2][j] << "\t\t" << productQuantity[2][j] << "\t\t" << productPrice[2][j] << "\n";

    cout<<"\n\nPress '1' to go back to the Admin Panel \nPress '2' to go to the Main Menu\nPress '3' to exit\n\n";
    cout<<"Enter your choice : ";
    int choice;
    cin>>choice;
    
    if(choice==1){
        adminMenu();
    }else if(choice == 2){
        menu();
    }else{
        return;
    }
    
}

void setProducts() {
    system("cls");
    double price; int quantity; string name;
    int productCount;
    int choice;
    int index = 0;

    cout << "------------------------------------------------\n";
    cout << "                   Set Products                 \n";
    cout << "------------------------------------------------\n\n";
    cout << "Categories:\n";
    cout << "1. Food & Beverages\n";
    cout << "2. Self Care\n";
    cout << "3. Household Items\n";
    cout << "4. Exit\n\n";
    cout << "Select your Category [1 / 2 / 3 / 4]: ";
    cin >> choice;

    int cat = choice - 1;
    if (cat < 0 || cat >= category) return;

    compactCategory(cat);

    while (index < productLimit && productNames[cat][index] != "Add Product...")
        index++;

    if (index == productLimit) {
        cout << "You cannot add more products, remove some products to continue\n";
        adminMenu();
    }

    
    if (cat == 0) {
        cout << " \n_____ Food & Beverages _____ \n";
        cout << "You can add " << productLimit - index << " more products\n";
        cout << "How many products do you want to add: ";
        cin >> productCount;
        cout<<endl;
        cin.ignore();
        Food f;
        
        for (int j = index; j < index + productCount && j < productLimit; j++) {
        cout << "Enter Details for product no. " << j + 1 << endl;
        cout << "Name: ";
        getline(cin, name);
        f.setName(name);
        productNames[cat][j] = f.getName();
        cout << "Quantity: ";
        cin >> quantity;
        f.setQuantity(quantity);
        productQuantity[cat][j] = f.getQuantity();
        
        cout << "Price ("<<f.getGst()<<"% GST would be applied to every product in the category) : ";
        cin >> price;
        f.setPrice(price);
        productPrice[cat][j] = f.finalPrice();
        cout << endl;
        cin.ignore();
        
    }
        saveDataToFile();
        cout<<"Product(s) Added Successfully!\n";
        
    }else if (cat == 1){
        cout << "____ Self Care ____ \n";
        cout << "You can add " << productLimit - index << " more products\n";
        cout << "How many products do you want to add: ";
        cin >> productCount;
        cout<<endl;
        cin.ignore();
        selfCare s;
        
        for (int j = index; j < index + productCount && j < productLimit; j++) {
        cout << "Enter Details for product no. " << j + 1 << endl;
        cout << "Name: ";
        getline(cin, name);
        s.setName(name);
        productNames[cat][j] = s.getName();
        cout << "Quantity: ";
        cin >> quantity;
        s.setQuantity(quantity);
        productQuantity[cat][j] = s.getQuantity();
        
        cout << "Price ("<<s.getGst()<<"% GST would be applied to every product in the category) : ";
        cin >> price;
        s.setPrice(price);
        productPrice[cat][j] = s.finalPrice();
        cout << endl;
        cin.ignore();
    }
        saveDataToFile();
        cout<<"Product(s) Added Successfully!\n";
        
    }else if (cat == 2){
        cout << " ____ Household Items ____ \n";
        cout << "You can add " << productLimit - index << " more products\n";
        cout << "How many products do you want to add: ";
        cin >> productCount;
        cout<<endl;
        cin.ignore();
        houseHold h;
        
        for (int j = index; j < index + productCount && j < productLimit; j++) {
        cout << "Enter Details for product no. " << j + 1 << endl;
        cout << "Name: ";
        getline(cin, name);
        h.setName(name);
        productNames[cat][j] = h.getName();
        cout << "Quantity: ";
        cin >> quantity;
        h.setQuantity(quantity);
        productQuantity[cat][j] = h.getQuantity();
        
        cout << "Price ("<<h.getGst()<<"% GST would be applied to every product in the category) : ";
        cin >> price;
        h.setPrice(price);
        productPrice[cat][j] = h.finalPrice();
        cout << endl;
        cin.ignore();
    }
        saveDataToFile();
        cout<<"Product(s) Added Successfully!\n";
        
    }else{
        return;
    }
    
    
    cout << "\n\nPress '1' to go back to the Admin Panel \nPress '2' to go to the Main Menu\nPress '3' to exit\n\n";
    cout<<"Enter your choice : ";
    cin >> choice;
    
    if (choice==1) {
        adminMenu();
    } else if (choice == 2) {
        menu();
    } else {
        return;
    }
}

void removeProducts() {
    int choice;
    cout << "Select Category to remove product from [1-3]: ";
    cin >> choice;
    int cat = choice - 1;
    if (cat < 0 || cat >= category) return;

    compactCategory(cat);

    cout << "\nProducts in this category:\n";
    for (int i = 0; i < productLimit; i++) {
        if (productNames[cat][i] != "Add Product...") {
            cout << i + 1 << ". " << productNames[cat][i] << " | Qty: " << productQuantity[cat][i] << " | Price: " << productPrice[cat][i] << "\n";
        }
    }

    int index;
    cout << "Enter product number to remove: ";
    cin >> index;
    index--; 
    if (index < 0 || index >= productLimit || productNames[cat][index] == "Add Product...") {
        cout << "Invalid selection!\n";
        return;
    }

    productNames[cat][index] = "Add Product...";
    productQuantity[cat][index] = 0;
    productPrice[cat][index] = 0.0;
    
    compactCategory(cat);

    saveDataToFile();
    cout << "Product removed successfully.\n";
    cout<<"\n\nPress '1' to go back to the Admin Panel \nPress '2' to go to the Main Menu\nPress '3' to exit\n\n";
    cout<<"Enter your choice : ";
    cin>>choice;
    
    if(choice==1){
        adminMenu();
    }else if(choice == 2){
        menu();
    }else{
        return;
    }
    
}

void editPrice() {
    int choice;
    cout << "Select Category to edit price [1-3]: ";
    cin >> choice;
    int cat = choice - 1;
    if (cat < 0 || cat >= category) return;

    cout << "\nProducts in this category:\n";
    for (int i = 0; i < productLimit; i++) {
        if (productNames[cat][i] != "Add Product...") {
            cout << i + 1 << ". " << productNames[cat][i] << " | Price: " << productPrice[cat][i] << "\n";
        }
    }

    int index;
    cout << "Enter product number to edit price: ";
    cin >> index;
    index--;
    if (index < 0 || index >= productLimit || productNames[cat][index] == "Add Product...") {
        cout << "Invalid selection!\n";
        return;
    }

    cout << "Enter new price: ";
    cin >> productPrice[cat][index];
    saveDataToFile();
    cout << "Price updated successfully.\n";
    cout<<"\n\nPress '1' to go back to the Admin Panel \nPress '2' to go to the Main Menu\nPress '3' to exit\n\n";
    cout<<"Enter your choice : ";    
    cin>>choice;
    
    if(choice==1){
        adminMenu();
    }else if(choice == 2){
        menu();
    }else{
        return;
    }
}

void editQuantity() {
    int choice;
    cout << "Select Category to edit quantity [1-3]: ";
    cin >> choice;
    int cat = choice - 1;
    if (cat < 0 || cat >= category) return;

    cout << "\nProducts in this category:\n";
    for (int i = 0; i < productLimit; i++) {
        if (productNames[cat][i] != "Add Product...") {
            cout << i + 1 << ". " << productNames[cat][i] << " | Qty: " << productQuantity[cat][i] << "\n";
        }
    }

    int index;
    cout << "Enter product number to edit quantity: ";
    cin >> index;
    index--;
    if (index < 0 || index >= productLimit || productNames[cat][index] == "Add Product...") {
        cout << "Invalid selection!\n";
        return;
    }

    cout << "Enter new quantity: ";
    cin >> productQuantity[cat][index];
    saveDataToFile();
    cout << "Quantity updated successfully.\n";
    cout<<"\n\nPress '1' to go back to the Admin Panel \nPress '2' to go to the Main Menu\nPress '3' to exit\n\n";
    cout<<"Enter your choice : ";
    cin>>choice;
    
    if(choice==1){
        adminMenu();
    }else if(choice == 2){
        menu();
    }else{
        return;
    }
    
}

void adminMenu() {
    system("cls");
    int choice;
    cout << "------------------------------------\n";
    cout << "          MANAGEMENT PANEL\n";
    cout << "------------------------------------\n\n";
    cout << "1. View Inventory\n";
    cout << "2. Add Items\n";
    cout << "3. Remove Items\n";
    cout << "4. Edit Prices\n";
    cout << "5. Edit Quantity\n";
    cout << "6. Main Menu\n";
    cout << "7. Exit\n\n";
    cout << "Enter your choice:";
    cin >> choice;

    if (choice == 1) viewProducts();
    else if (choice == 2) setProducts();
    else if (choice == 3) removeProducts();
    else if (choice == 4) editPrice();
    else if (choice == 5) editQuantity();
    else if (choice == 6) menu();
    else return;
    
}

class Admin {
    string password;
public:
    void setPassword(string pass) {
        password = pass;
    }
    string getPassword() {
        return password;
    }
    ~Admin(){
	}
};

Admin ADMIN;

bool adminPass(string pass) {
    
    return pass == ADMIN.getPassword();
}

void admin() {
    string pass;

    cout << "------------------------------------\n";
    cout << "            ADMIN LOGIN\n";
    cout << "------------------------------------\n\n";

    if (count == 0) {
        cout << "We are logging in for the first time,\n";
        cout << "Enter new Password: ";
        cin >> pass;
        ADMIN.setPassword(pass);
        count++;
        saveDataToFile();
        adminMenu();
    } else {
        cout << "Enter Admin Password: ";
        cin >> pass;
        if (adminPass(pass)) {
            cout << "Login Successful\n";
            adminMenu();
        } else {
            cout << "Wrong Password!\n";
            menu();
        }
    }
}

void menu() {
    system("cls");
    int choice;
    cout << "------------------------------------\n";
    cout << "         Captain Pakistan Mart\n";
    cout << "------------------------------------\n\n";
    cout << "1. Admin Login\n";
    cout << "2. Exit\n";
    cout << "\nEnter your choice: ";
    cin >> choice;

    if (choice == 1) admin();
    else return;
}

void saveDataToFile() {
    ofstream outFile("hello.txt");
    outFile << count << endl;
    outFile <<  encryption(ADMIN.getPassword()) << endl;

    for (int i = 0; i < category; i++)
        for (int j = 0; j < productLimit; j++) {
outFile << encryption(productNames[i][j]) << endl;
outFile << encryption(to_string(productQuantity[i][j])) << endl;
outFile << encryption(to_string(productPrice[i][j])) << endl;
        }
    outFile.close();
}

void loadDataFromFile() {
    string pass;
    ifstream inFile("hello.txt");
    if (!inFile) return;

    inFile >> count;
    inFile.ignore();
    getline(inFile, pass);
    pass = decryption(pass);
    ADMIN.setPassword(pass);

    for (int i = 0; i < category; i++)
        for (int j = 0; j < productLimit; j++) {
            
           string temp;

getline(inFile, productNames[i][j]);
productNames[i][j] = decryption(productNames[i][j]);

getline(inFile, temp);
productQuantity[i][j] = stoi(decryption(temp));

getline(inFile, temp);
productPrice[i][j] = stod(decryption(temp));

        }
    inFile.close();

    for (int i = 0; i < category; i++)
        compactCategory(i);
}

void setDefaults() {
    for (int i = 0; i < category; i++)
        for (int j = 0; j < productLimit; j++) {
            productNames[i][j] = "Add Product...";
            productQuantity[i][j] = 0;
            productPrice[i][j] = 0.0;
        }
    saveDataToFile();
}

int main() {
    loadDataFromFile();
    if (count == 0) 
    { setDefaults(); }
    menu();
}


#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
using namespace std;

class Product {
private:
    int productId;
    string name;
    string category;
    double price;
    int stock;

public:
    Product(int id, string n, string c, double p, int s) {
        productId = id;
        name = n;
        category = c;
        price = p;
        stock = s;
    }

    int getProductId() {
        return productId;
    }

    string getName() {
        return name;
    }

    string getCategory() {
        return category;
    }

    double getPrice() {
        return price;
    }

    int getStock() {
        return stock;
    }

    void setPrice(double p) {
        price = p;
    }

    void setStock(int s) {
        stock = s;
    }

    void displayProduct() {
        cout << "ID: " << productId
             << " | Name: " << name
             << " | Category: " << category
             << " | Price: Rs." << price
             << " | Stock: " << stock << endl;
    }
};


class User {
private:
    int userId;
    string name;
    string username;
    string password;

public:
    User(int id, string n, string u, string p) {
        userId = id;
        name = n;
        username = u;
        password = p;
    }

    int getUserId() {
        return userId;
    }

    string getName() {
        return name;
    }

    string getUsername() {
        return username;
    }

    string getPassword() {
    return password;
    }

    bool checkPassword(string p) {
        return password == p;
    }

    void displayUser() {
        cout << "User ID: " << userId
             << " | Name: " << name
             << " | Username: " << username << endl;
    }
};

class CartItem {
private:
    int productId;
    string productName;
    double price;
    int quantity;

public:
    CartItem(int id, string name, double p, int q) {
        productId = id;
        productName = name;
        price = p;
        quantity = q;
    }

    int getProductId() {
        return productId;
    }

    string getProductName() {
        return productName;
    }

    double getPrice() {
        return price;
    }

    int getQuantity() {
        return quantity;
    }

    void setQuantity(int q) {
        quantity = q;
    }

    double getTotal() {
        return price * quantity;
    }

    void displayCartItem() {
        cout << "ID: " << productId
             << " | " << productName
             << " | Price: Rs." << price
             << " | Quantity: " << quantity
             << " | Total: Rs." << getTotal()
             << endl;
    }
};

class OrderItem {
private:
    int productId;
    string productName;
    double price;
    int quantity;

public:
    OrderItem(int id, string name, double p, int q) {
        productId = id;
        productName = name;
        price = p;
        quantity = q;
    }

    int getProductId() const {
        return productId;
    }

    string getProductName() const {
        return productName;
    }

    double getPrice() const {
        return price;
    }

    int getQuantity() const {
        return quantity;
    }

    double getTotal() {
        return price * quantity;
    }

    void displayOrderItem() {
        cout << "Product ID: " << productId
             << " | " << productName
             << " | Price: Rs." << price
             << " | Quantity: " << quantity
             << " | Total: Rs." << getTotal()
             << endl;
    }
};

class Order {
private:
    int orderId;
    int userId;
    vector<OrderItem> items;
    double totalAmount;
    string status;

public:
    Order(int oid, int uid, vector<OrderItem> orderItems, double total, string s) {
        orderId = oid;
        userId = uid;
        items = orderItems;
        totalAmount = total;
        status = s;
    }

    int getOrderId() {
        return orderId;
    }

    int getUserId() {
        return userId;
    }

    double getTotalAmount() {
        return totalAmount;
    }
    
    const vector<OrderItem>& getItems() {
    return items;
    }

    string getStatus() {
        return status;
    }

    void setStatus(string s) {
        status = s;
    }

    void displayOrder() {
        cout << "\n========== ORDER ==========\n";
        cout << "Order ID: " << orderId << endl;
        cout << "User ID: " << userId << endl;
        cout << "Status: " << status << endl;

        cout << "\nOrder Items:\n";

        for (auto &item : items) {
            item.displayOrderItem();
        }

        cout << "Total Amount: Rs." << totalAmount << endl;
        cout << "===========================\n";
    }
};

class ECommerceSystem {
private:
    vector<Product> products;
    vector<User> users;
    vector<Order> orders;
    vector<CartItem> cart;

    int currentUserId = -1;

public:
    // Product Management
    void addProduct();
    void displayProducts();
    void searchProduct();
    void filterProductsByCategory();
    void sortProductsByPrice();
    void updateProduct();
    void deleteProduct();
    void updateStock();

    // User Management
    void registerUser();
    bool loginUser();

    // Cart & Order Management
    void addToCart();
    void viewCart();
    void removeFromCart();
    void updateCartQuantity();
    void checkout();
    void processPayment();
    void viewOrders();
    void cancelOrder();

    // Admin
    bool adminLogin();
    void adminMenu();
    void customerMenu();
    void viewAllOrders();
    void updateOrderStatus();

    // File Handling
    void saveProducts();
    void loadProducts();
    void saveUsers();
    void loadUsers();
    void saveOrders();
    void loadOrders();
    void loadAllData();

    // Statistics
    void salesStatistics();
};

void ECommerceSystem::addProduct() {
    int id, stock;
    string name, category;
    double price;

    cout << "\nEnter Product ID: ";
    cin >> id;

    // Check whether Product ID already exists
    for (auto &product : products) {
        if (product.getProductId() == id) {
            cout << "\nProduct ID already exists!\n";
            return;
        }
    }

    cout << "Enter Product Name: ";
    cin.ignore();
    getline(cin, name);

    cout << "Enter Category: ";
    getline(cin, category);

    cout << "Enter Price: ";
    cin >> price;

    cout << "Enter Stock: ";
    cin >> stock;

    if (price < 0 || stock < 0) {
        cout << "Invalid price or stock!\n";
        return;
    }

    products.push_back(Product(id, name, category, price, stock));
  
    saveProducts();

    cout << "\nProduct added successfully!\n";
}

void ECommerceSystem::displayProducts() {
    if (products.empty()) {
        cout << "\nNo products available.\n";
        return;
    }

    cout << "\n========== PRODUCT LIST ==========\n";

    for (auto &product : products) {
        product.displayProduct();
    }

    cout << "==================================\n";
}

void ECommerceSystem::searchProduct() {
    if (products.empty()) {
        cout << "\nNo products available.\n";
        return;
    }

    string keyword;

    cout << "\nEnter product name or category to search: ";
    cin.ignore();
    getline(cin, keyword);

    bool found = false;

    for (auto &product : products) {
        if (product.getName().find(keyword) != string::npos ||
            product.getCategory().find(keyword) != string::npos) {

            product.displayProduct();
            found = true;
        }
    }

    if (!found) {
        cout << "\nNo matching product found.\n";
    }
}

void ECommerceSystem::saveProducts() {
    ofstream file("products.txt");

    if (!file) {
        cout << "\nError opening products file!\n";
        return;
    }

    for (auto &product : products) {
        file << product.getProductId() << "|"
             << product.getName() << "|"
             << product.getCategory() << "|"
             << product.getPrice() << "|"
             << product.getStock() << endl;
    }

    file.close();
}

void ECommerceSystem::loadProducts() {
    ifstream file("products.txt");

    if (!file) {
        return;
    }

    products.clear();

    string line;

    while (getline(file, line)) {
        stringstream ss(line);

        string idStr, name, category, priceStr, stockStr;

        getline(ss, idStr, '|');
        getline(ss, name, '|');
        getline(ss, category, '|');
        getline(ss, priceStr, '|');
        getline(ss, stockStr, '|');

        if (!idStr.empty() && !priceStr.empty() && !stockStr.empty()) {
            int id = stoi(idStr);
            double price = stod(priceStr);
            int stock = stoi(stockStr);

            products.push_back(
                Product(id, name, category, price, stock)
            );
        }
    }

    file.close();
}

void ECommerceSystem::saveUsers() {
    ofstream file("users.txt");

    if (!file) {
        cout << "\nError opening users file!\n";
        return;
    }

    for (auto &user : users) {
        file << user.getUserId() << "|"
             << user.getName() << "|"
             << user.getUsername() << "|"
             << user.getPassword() << endl;
    }

    file.close();
}

void ECommerceSystem::loadUsers() {
    ifstream file("users.txt");

    if (!file) {
        return;
    }

    users.clear();

    string line;

    while (getline(file, line)) {
        stringstream ss(line);

        string idStr, name, username, password;

        getline(ss, idStr, '|');
        getline(ss, name, '|');
        getline(ss, username, '|');
        getline(ss, password, '|');

        if (!idStr.empty()) {
            int id = stoi(idStr);

            users.push_back(
                User(id, name, username, password)
            );
        }
    }

    file.close();
}

void ECommerceSystem::saveOrders() {
    ofstream file("orders.txt");

    if (!file) {
        cout << "\nError opening orders file!\n";
        return;
    }

    for (auto &order : orders) {
        file << order.getOrderId() << "|"
             << order.getUserId() << "|"
             << order.getTotalAmount() << "|"
             << order.getStatus() << "|";

        const vector<OrderItem>& items = order.getItems();

        for (auto &item : items) {
            file << item.getProductId() << ","
                 << item.getProductName() << ","
                 << item.getPrice() << ","
                 << item.getQuantity() << ";";
        }

        file << endl;
    }

    file.close();
}

void ECommerceSystem::loadOrders() {
    ifstream file("orders.txt");

    if (!file) {
        return;
    }

    orders.clear();

    string line;

    while (getline(file, line)) {
        stringstream ss(line);

        string orderIdStr, userIdStr, totalStr, status, itemsData;

        getline(ss, orderIdStr, '|');
        getline(ss, userIdStr, '|');
        getline(ss, totalStr, '|');
        getline(ss, status, '|');
        getline(ss, itemsData);

        if (orderIdStr.empty() || userIdStr.empty() || totalStr.empty()) {
            continue;
        }

        int orderId = stoi(orderIdStr);
        int userId = stoi(userIdStr);
        double totalAmount = stod(totalStr);

        vector<OrderItem> orderItems;

        stringstream itemStream(itemsData);
        string itemData;

        while (getline(itemStream, itemData, ';')) {
            if (itemData.empty()) {
                continue;
            }

            stringstream itemSS(itemData);

            string productIdStr;
            string productName;
            string priceStr;
            string quantityStr;

            getline(itemSS, productIdStr, ',');
            getline(itemSS, productName, ',');
            getline(itemSS, priceStr, ',');
            getline(itemSS, quantityStr, ',');

            if (!productIdStr.empty() &&
                !priceStr.empty() &&
                !quantityStr.empty()) {

                int productId = stoi(productIdStr);
                double price = stod(priceStr);
                int quantity = stoi(quantityStr);

                orderItems.push_back(
                    OrderItem(
                        productId,
                        productName,
                        price,
                        quantity
                    )
                );
            }
        }

        Order order(
            orderId,
            userId,
            orderItems,
            totalAmount,
            status
        );

        orders.push_back(order);
    }

    file.close();
}

void ECommerceSystem::filterProductsByCategory() {
    if (products.empty()) {
        cout << "\nNo products available.\n";
        return;
    }

    string category;

    cout << "\nEnter Category: ";
    cin.ignore();
    getline(cin, category);

    bool found = false;

    cout << "\n========== CATEGORY PRODUCTS ==========\n";

    for (auto &product : products) {
        if (product.getCategory() == category) {
            product.displayProduct();
            found = true;
        }
    }

    if (!found) {
        cout << "\nNo products found in this category.\n";
    }

    cout << "=======================================\n";
}

void ECommerceSystem::sortProductsByPrice() {
    if (products.empty()) {
        cout << "\nNo products available.\n";
        return;
    }

    int choice;

    cout << "\n1. Low to High";
    cout << "\n2. High to Low";
    cout << "\nEnter choice: ";
    cin >> choice;

    if (choice == 1) {
        sort(products.begin(), products.end(),
             [](Product &a, Product &b) {
                 return a.getPrice() < b.getPrice();
             });

        cout << "\nProducts sorted by price (Low to High).\n";
    }
    else if (choice == 2) {
        sort(products.begin(), products.end(),
             [](Product &a, Product &b) {
                 return a.getPrice() > b.getPrice();
             });

        cout << "\nProducts sorted by price (High to Low).\n";
    }
    else {
        cout << "\nInvalid choice!\n";
        return;
    }

    displayProducts();
}

void ECommerceSystem::updateProduct() {
    if (products.empty()) {
        cout << "\nNo products available.\n";
        return;
    }

    int id;
    cout << "\nEnter Product ID to update: ";
    cin >> id;

    for (auto &product : products) {
        if (product.getProductId() == id) {
            double newPrice;
            int newStock;

            cout << "Enter new price: ";
            cin >> newPrice;

            cout << "Enter new stock: ";
            cin >> newStock;

            if (newPrice < 0 || newStock < 0) {
                cout << "\nInvalid price or stock!\n";
                return;
            }

            product.setPrice(newPrice);
            product.setStock(newStock);
 
            saveProducts();

            cout << "\nProduct updated successfully!\n";
            return;
        }
    }

    cout << "\nProduct not found!\n";
}

void ECommerceSystem::deleteProduct() {
    if (products.empty()) {
        cout << "\nNo products available.\n";
        return;
    }

    int id;

    cout << "\nEnter Product ID to delete: ";
    cin >> id;

    for (auto it = products.begin(); it != products.end(); ++it) {
        if (it->getProductId() == id) {
            products.erase(it);

            saveProducts();

            cout << "\nProduct deleted successfully!\n";
            return;
        }
    }

    cout << "\nProduct not found!\n";
}

void ECommerceSystem::updateStock() {
    if (products.empty()) {
        cout << "\nNo products available.\n";
        return;
    }

    int id;
    int newStock;

    cout << "\nEnter Product ID: ";
    cin >> id;

    for (auto &product : products) {
        if (product.getProductId() == id) {
            cout << "Current Stock: " << product.getStock() << endl;

            cout << "Enter New Stock: ";
            cin >> newStock;

            if (newStock < 0) {
                cout << "\nInvalid stock!\n";
                return;
            }

            product.setStock(newStock);

            saveProducts();

            cout << "\nStock updated successfully!\n";
            return;
        }
    }

    cout << "\nProduct not found!\n";
}

void ECommerceSystem::addToCart() {
    if (products.empty()) {
        cout << "\nNo products available.\n";
        return;
    }

    int id, quantity;

    cout << "\nEnter Product ID: ";
    cin >> id;

    for (auto &product : products) {
        if (product.getProductId() == id) {

            if (product.getStock() == 0) {
                cout << "\nProduct is out of stock!\n";
                return;
            }

            cout << "Available Stock: " << product.getStock() << endl;
            cout << "Enter Quantity: ";
            cin >> quantity;

            if (quantity <= 0) {
                cout << "\nInvalid quantity!\n";
                return;
            }

            if (quantity > product.getStock()) {
                cout << "\nNot enough stock available!\n";
                return;
            }

            // Check if product is already in cart
            for (auto &item : cart) {
                if (item.getProductId() == id) {

                    int newQuantity = item.getQuantity() + quantity;

                    if (newQuantity > product.getStock()) {
                        cout << "\nRequested quantity exceeds available stock!\n";
                        return;
                    }

                    item.setQuantity(newQuantity);

                    cout << "\nProduct quantity updated in cart!\n";
                    return;
                }
            }

            cart.push_back(
                CartItem(
                    product.getProductId(),
                    product.getName(),
                    product.getPrice(),
                    quantity
                )
            );

            cout << "\nProduct added to cart successfully!\n";
            return;
        }
    }

    cout << "\nProduct not found!\n";
}

void ECommerceSystem::viewCart() {
    if (cart.empty()) {
        cout << "\nYour cart is empty.\n";
        return;
    }

    double grandTotal = 0;

    cout << "\n========== YOUR CART ==========\n";

    for (auto &item : cart) {
        item.displayCartItem();
        grandTotal += item.getTotal();
    }

    cout << "-------------------------------\n";
    cout << "Grand Total: Rs." << grandTotal << endl;
    cout << "===============================\n";
}

void ECommerceSystem::removeFromCart() {
    if (cart.empty()) {
        cout << "\nYour cart is empty.\n";
        return;
    }

    int id;

    cout << "\nEnter Product ID to remove: ";
    cin >> id;

    for (auto it = cart.begin(); it != cart.end(); ++it) {
        if (it->getProductId() == id) {
            cart.erase(it);

            cout << "\nProduct removed from cart successfully!\n";
            return;
        }
    }

    cout << "\nProduct not found in cart!\n";
}

void ECommerceSystem::updateCartQuantity() {
    if (cart.empty()) {
        cout << "\nYour cart is empty.\n";
        return;
    }

    int id, quantity;

    cout << "\nEnter Product ID: ";
    cin >> id;

    for (auto &item : cart) {
        if (item.getProductId() == id) {

            cout << "Enter New Quantity: ";
            cin >> quantity;

            if (quantity <= 0) {
                cout << "\nInvalid quantity!\n";
                return;
            }

            // Check current product stock
            for (auto &product : products) {
                if (product.getProductId() == id) {

                    if (quantity > product.getStock()) {
                        cout << "\nNot enough stock available!\n";
                        return;
                    }

                    item.setQuantity(quantity);

                    cout << "\nCart quantity updated successfully!\n";
                    return;
                }
            }
        }
    }

    cout << "\nProduct not found in cart!\n";
}

void ECommerceSystem::checkout() {
    if (cart.empty()) {
        cout << "\nYour cart is empty.\n";
        return;
    }

    int userId = currentUserId;

    if (currentUserId == -1) {
        cout << "\nPlease login first.\n";
        return;
    }

    vector<OrderItem> orderItems;
    double subtotal = 0;

    for (auto &item : cart) {
        orderItems.push_back(
            OrderItem(
                item.getProductId(),
                item.getProductName(),
                item.getPrice(),
                item.getQuantity()
            )
        );

        subtotal += item.getTotal();
    }

    double discount = 0;

    if (subtotal >= 50000) {
        discount = subtotal * 0.10;
    }
    else if (subtotal >= 20000) {
        discount = subtotal * 0.05;
    }

    double finalAmount = subtotal - discount;

    cout << "\n========== CHECKOUT ==========\n";
    cout << "Subtotal: Rs." << subtotal << endl;
    cout << "Discount: Rs." << discount << endl;
    cout << "Final Amount: Rs." << finalAmount << endl;
    cout << "==============================\n";

    char confirm;

    cout << "Confirm order? (Y/N): ";
    cin >> confirm;

    if (confirm != 'Y' && confirm != 'y') {
        cout << "\nOrder cancelled.\n";
        return;
    }

    int orderId = 1;

    for (auto &order : orders) {
        if (order.getOrderId() >= orderId) {
                orderId = order.getOrderId() + 1;
        }
    }

    orders.push_back(
        Order(
            orderId,
            userId,
            orderItems,
            finalAmount,
            "Pending"
        )
    );

    // Reduce product stock
    for (auto &item : cart) {
        for (auto &product : products) {
            if (product.getProductId() == item.getProductId()) {
                product.setStock(
                    product.getStock() - item.getQuantity()
                );
            }
        }
    }

    cart.clear();

    saveOrders();
    saveProducts();

    cout << "\nOrder placed successfully!\n";
    cout << "Your Order ID: " << orderId << endl;
}

void ECommerceSystem::processPayment() {
    int orderId;
    cout << "\nEnter Order ID: ";
    cin >> orderId;

    for (auto &order : orders) {
        if (order.getOrderId() == orderId) {

            if (order.getUserId() != currentUserId) {
                cout << "\nYou can only process payment for your own orders.\n";
                return;
            }

            if (order.getStatus() != "Pending") {
                cout << "\nPayment cannot be processed for this order.\n";
                return;
            }

            cout << "\n========== PAYMENT ==========\n";
            cout << "Order ID: " << order.getOrderId() << endl;
            cout << "Amount: Rs." << order.getTotalAmount() << endl;
            cout << "=============================\n";

            cout << "1. UPI\n";
            cout << "2. Debit/Credit Card\n";
            cout << "3. Cash on Delivery\n";

            int choice;
            cout << "Choose Payment Method: ";
            cin >> choice;

            if (choice < 1 || choice > 3) {
                cout << "\nInvalid payment method.\n";
                return;
            }

            cout << "\nPayment successful!\n";

            order.setStatus("Confirmed");

            saveOrders();

            cout << "Order confirmed successfully!\n";
            return;
        }
    }

    cout << "\nOrder not found.\n";
}

void ECommerceSystem::viewOrders() {
    if (currentUserId == -1) {
        cout << "\nPlease login first.\n";
        return;
    }

    bool found = false;

    for (auto &order : orders) {
        if (order.getUserId() == currentUserId) {

            if (!found) {
                cout << "\n========== MY ORDERS ==========\n";
                found = true;
            }

            cout << "Order ID: " << order.getOrderId() << endl;
            cout << "Total Amount: Rs." << order.getTotalAmount() << endl;
            cout << "Status: " << order.getStatus() << endl;
            cout << "-------------------------------\n";
        }
    }

    if (!found) {
        cout << "\nNo orders found.\n";
    }
}

void ECommerceSystem::cancelOrder() {
    if (currentUserId == -1) {
        cout << "\nPlease login first.\n";
        return;
    }

    int orderId;
    cout << "\nEnter Order ID to cancel: ";
    cin >> orderId;

    for (auto &order : orders) {
        if (order.getOrderId() == orderId) {

            if (order.getUserId() != currentUserId) {
                cout << "\nYou can only cancel your own orders.\n";
                return;
            }

            if (order.getStatus() != "Pending") {
                cout << "\nOnly pending orders can be cancelled.\n";
                return;
            }

            for (auto &item : order.getItems()) {
                for (auto &product : products) {
                    if (product.getProductId() == item.getProductId()) {
                        product.setStock(
                            product.getStock() + item.getQuantity()
                        );
                    }
                }
            }

            order.setStatus("Cancelled");

            saveOrders();
            saveProducts();

            cout << "\nOrder cancelled successfully!\n";
            return;
        }
    }
    
    cout << "\nOrder not found.\n";
}

void ECommerceSystem::viewAllOrders() {
    if (orders.empty()) {
        cout << "\nNo orders available.\n";
        return;
    }

    cout << "\n========== ALL ORDERS ==========\n";

    for (auto &order : orders) {
        order.displayOrder();
    }

    cout << "================================\n";
}

void ECommerceSystem::updateOrderStatus() {
    if (orders.empty()) {
        cout << "\nNo orders available.\n";
        return;
    }

    int orderId;
    string newStatus;

    cout << "\nEnter Order ID: ";
    cin >> orderId;

    for (auto &order : orders) {
        if (order.getOrderId() == orderId) {

            cout << "\nCurrent Status: "
                 << order.getStatus() << endl;

            cout << "Enter New Status: ";
            cin >> newStatus;

            if (newStatus != "Pending" &&
                newStatus != "Confirmed" &&
                newStatus != "Shipped" &&
                newStatus != "Delivered" &&
                newStatus != "Cancelled") {

                cout << "\nInvalid order status!\n";
                return;
            }

            order.setStatus(newStatus);

            saveOrders();

            cout << "\nOrder status updated successfully!\n";
            return;
        }
    }

    cout << "\nOrder not found!\n";
}

void ECommerceSystem::adminMenu() {
    int choice;

    do {
        cout << "\n========== ADMIN MENU ==========\n";
        cout << "1. Add Product\n";
        cout << "2. Display Products\n";
        cout << "3. Search Product\n";
        cout << "4. Filter Products by Category\n";
        cout << "5. Sort Products by Price\n";
        cout << "6. Update Product\n";
        cout << "7. Delete Product\n";
        cout << "8. Update Stock\n";
        cout << "9. View Orders\n";
        cout << "10. Update Order Status\n";
        cout << "11. Sales Statistics\n";
        cout << "0. Logout\n";
        cout << "================================\n";

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addProduct();
                break;

            case 2:
                displayProducts();
                break;

            case 3:
                searchProduct();
                break;

            case 4:
                filterProductsByCategory();
                break;

            case 5:
                sortProductsByPrice();
                break;

            case 6:
                updateProduct();
                break;

            case 7:
                deleteProduct();
                break;

            case 8:
                updateStock();
                break;

            case 9:
                viewAllOrders();
                break;

            case 10:
                updateOrderStatus();
                break;

            case 11:
                salesStatistics();
                break;

            case 0:
                cout << "\nAdmin logged out successfully.\n";
                break;

            default:
                cout << "\nInvalid choice. Please try again.\n";
        }

    } while (choice != 0);
}

void ECommerceSystem::customerMenu() {
    int choice;

    do {
        cout << "\n========= CUSTOMER MENU =========\n";
        cout << "1. Display Products\n";
        cout << "2. Search Product\n";
        cout << "3. Filter Products by Category\n";
        cout << "4. Sort Products by Price\n";
        cout << "5. Add to Cart\n";
        cout << "6. View Cart\n";
        cout << "7. Remove from Cart\n";
        cout << "8. Update Cart Quantity\n";
        cout << "9. Checkout\n";
        cout << "10. Process Payment\n";
        cout << "11. View Orders\n";
        cout << "12. Cancel Order\n";
        cout << "0. Logout\n";
        cout << "=================================\n";

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                displayProducts();
                break;

            case 2:
                searchProduct();
                break;

            case 3:
                filterProductsByCategory();
                break;

            case 4:
                sortProductsByPrice();
                break;

            case 5:
                addToCart();
                break;

            case 6:
                viewCart();
                break;

            case 7:
                removeFromCart();
                break;

            case 8:
                updateCartQuantity();
                break;

            case 9:
                checkout();
                break;

            case 10:
                processPayment();
                break;

            case 11:
                viewOrders();
                break;

            case 12:
                cancelOrder();
                break;

            case 0:
                cart.clear();
                currentUserId = -1;
                cout << "\nCustomer logged out successfully.\n";
                break;

            default:
                cout << "\nInvalid choice. Please try again.\n";
        }

    } while (choice != 0);
}

void ECommerceSystem::salesStatistics() {
    if (orders.empty()) {
        cout << "\nNo orders available.\n";
        return;
    }

    int totalOrders = orders.size();
    int deliveredOrders = 0;
    int cancelledOrders = 0;
    double totalSales = 0;

    for (auto &order : orders) {
        if (order.getStatus() == "Delivered") {
            deliveredOrders++;
            totalSales += order.getTotalAmount();
        }
        else if (order.getStatus() == "Cancelled") {
            cancelledOrders++;
        }
    }

    cout << "\n========== SALES STATISTICS ==========\n";
    cout << "Total Orders: " << totalOrders << endl;
    cout << "Delivered Orders: " << deliveredOrders << endl;
    cout << "Cancelled Orders: " << cancelledOrders << endl;
    cout << "Total Sales: Rs." << totalSales << endl;
    cout << "======================================\n";
}

void ECommerceSystem::registerUser() {
    int id;
    string name, username, password;

    cout << "\nEnter User ID: ";
    cin >> id;

    cout << "Enter Name: ";
    cin.ignore();
    getline(cin, name);

    cout << "Enter Username: ";
    cin >> username;

    // Check whether User ID already exists
    for (auto &user : users) {
        if (user.getUserId() == id) {
            cout << "\nUser ID already exists!\n";
            return;
        }
    }
    
    // Check whether username already exists
    for (auto &user : users) {
        if (user.getUsername() == username) {
            cout << "\nUsername already exists!\n";
            return;
        }
    }

    cout << "Enter Password: ";
    cin >> password;

    users.push_back(User(id, name, username, password));

    saveUsers();

    cout << "\nRegistration successful!\n";
}

bool ECommerceSystem::loginUser() {
    int userId;
    string username, password;

    cout << "\n========== USER LOGIN ==========\n";

    cout << "Enter User ID: ";
    cin >> userId;

    cout << "Enter Username: ";
    cin >> username;

    cout << "Enter Password: ";
    cin >> password;

    for (auto &user : users) {
        if (user.getUserId() == userId &&
            user.getUsername() == username &&
            user.getPassword() == password) {

            currentUserId = userId;

            cout << "\nLogin successful!\n";
            cout << "Welcome, " << username << "!\n";

            return true;
        }
    }

    cout << "\nInvalid User ID, Username or Password.\n";
    return false;
}

bool ECommerceSystem::adminLogin() {
    string username, password;

    cout << "\n========== ADMIN LOGIN ==========\n";

    cout << "Enter Admin Username: ";
    cin >> username;

    cout << "Enter Admin Password: ";
    cin >> password;

    if (username == "admin" && password == "admin123") {
        cout << "\nAdmin login successful!\n";
        cout << "Welcome, Admin!\n";
        return true;
    }

    cout << "\nInvalid Admin Username or Password.\n";
    return false;
}

void ECommerceSystem::loadAllData() {
    loadProducts();
    loadUsers();
    loadOrders();
}

int main() {
    ECommerceSystem system;

    system.loadAllData();

    int choice;

    do {
        cout << "\n========== E-COMMERCE MANAGEMENT SYSTEM ==========\n";
        cout << "1. Customer Registration\n";
        cout << "2. Customer Login\n";
        cout << "3. Admin Login\n";
        cout << "0. Exit\n";
        cout << "===================================================\n";

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {

            case 1:
                system.registerUser();
                break;

            case 2:
                if (system.loginUser()) {
                    system.customerMenu();
                }
                break;

            case 3:
                if (system.adminLogin()) {
                    system.adminMenu();
                }
                break;

            case 0:
                cout << "\nThank you for using E-Commerce Management System!\n";
                break;

            default:
                cout << "\nInvalid choice. Please try again.\n";
        }

    } while (choice != 0);

    return 0;
}
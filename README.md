# E-Commerce Management System

A console-based **E-Commerce Management System** developed in C++ using Object-Oriented Programming (OOP), STL, file handling, searching, sorting, and input validation.

## Features

### Customer Module

* Customer Registration
* Customer Login and Logout
* Display Products
* Search Products by Name or Category
* Filter Products by Category
* Sort Products by Price

  * Low to High
  * High to Low
* Add Products to Cart
* View Cart
* Update Cart Quantity
* Remove Products from Cart
* Checkout
* Discount Calculation
* Payment Processing

  * UPI
  * Debit/Credit Card
  * Cash on Delivery
* View Order History
* Cancel Pending Orders

### Admin Module

* Admin Login
* Add New Products
* Display All Products
* Search Products
* Filter Products by Category
* Sort Products by Price
* Update Product Details
* Delete Products
* Update Product Stock
* View All Orders
* Update Order Status
* View Sales Statistics

## Technologies Used

* **Language:** C++
* **Programming Concepts:** Object-Oriented Programming
* **STL:** Vector, Sorting and Searching
* **File Handling:** Text File Storage
* **Compiler:** G++ / C++17

## OOP Concepts Used

The project demonstrates the following OOP concepts:

* Classes and Objects
* Encapsulation
* Constructors
* Member Functions
* Data Abstraction
* Object Interaction

## Main Classes

The system is organized into the following major classes:

* `Product`
* `User`
* `CartItem`
* `OrderItem`
* `Order`
* `ECommerceSystem`

## Data Storage

The application stores data using text files:

```text
products.txt
users.txt
orders.txt
```

This allows product, customer, and order information to persist between program executions.

## Project Structure

```text
E-Commerce-Management-System/
│
├── main.cpp
├── products.txt
├── users.txt
├── orders.txt
├── .gitignore
└── README.md
```

## How to Run

### 1. Clone the Repository

```bash
git clone <repository-url>
```

### 2. Open the Project Folder

```bash
cd E-Commerce-Management-System
```

### 3. Compile the Program

```bash
g++ -std=c++17 main.cpp -o ecommerce
```

### 4. Run the Program

On Windows:

```bash
ecommerce.exe
```

Or:

```bash
.\ecommerce.exe
```

## Admin Login

For demonstration/testing:

```text
Username: admin
Password: admin123
```

## Example Workflow

### Customer

```text
Register → Login → Browse Products → Add to Cart
→ Checkout → Payment → View Orders
```

### Admin

```text
Login → Manage Products → Manage Stock
→ View Orders → Update Order Status
→ View Sales Statistics
```

## Validation and Error Handling

The system includes validation for:

* Duplicate Product IDs
* Duplicate User IDs
* Duplicate Usernames
* Invalid Product Price
* Invalid Stock
* Invalid Product IDs
* Invalid Order IDs
* Insufficient Product Stock
* Empty Cart Checkout
* Unauthorized Order Payment
* Invalid Order Cancellation
* Invalid Menu Choices

## Future Improvements

Possible future enhancements include:

* GUI-based interface
* Database integration using MySQL
* Product images
* Customer address management
* Online payment gateway integration
* Product reviews and ratings
* Advanced sales reports
* Password encryption
* Role-based authentication

## Author

**Shivesh Kumar**

BCA Student

## Project Purpose

This project was developed as a practical implementation of C++ programming concepts, Object-Oriented Programming, STL, file handling, searching, sorting, and basic e-commerce workflow management.

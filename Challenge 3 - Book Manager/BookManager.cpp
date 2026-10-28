#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

class Book { // Create a class to store book information
public:
    string title;
    string author;
    int pages;
    string id;
    bool borrowed;
};

void displayBook(const Book& book) { // Function to display book details
    cout << "\nTitle: " << book.title << endl;
    cout << "Author: " << book.author << endl;
    cout << "Pages: " << book.pages << endl;
    cout << "ID: " << book.id << endl;
    cout << "Status: "
         << (book.borrowed ? "Borrowed" : "Available") << endl;
}

int findBook(const vector<Book>& books, string id) { // Function to find a book by its ID

    for (int i = 0; i < static_cast<int>(books.size()); i++) { // Check each book in the vector
        if (books[i].id == id) {
            return i;
        }
    }

    return -1; // Return -1 if the book is not found
}

int main() {

    ifstream file("bookData.txt"); // Open the file containing the books

    if (!file.is_open()) { // Check if the file opened correctly
        cout << "Error opening bookData.txt!" << endl;
        return 1;
    }

    vector<Book> books; // Create a vector to store the books
    string line;

    while (getline(file, line)) { // Read each line from the file

        stringstream ss(line); // Separate the information in each line
        Book book;
        string pagesText, borrowedText;

        if (getline(ss, book.title, ',') && // Read the book details separated by commas
            getline(ss, book.author, ',') &&
            getline(ss, pagesText, ',') &&
            getline(ss, book.id, ',') &&
            getline(ss, borrowedText)) {

            book.pages = stoi(pagesText); // Convert pages to a number

            book.borrowed = (borrowedText == "true"); // Check if the book is borrowed

            books.push_back(book); // Add the book to the vector
        }
    }

    file.close(); // Close the file

    int choice = 0;
    string id;

    while (choice != 5) { // Keep showing the menu until the user exits

        cout << "\n===== BOOK MANAGER =====" << endl; // Display the main menu
        cout << "1. View all books" << endl;
        cout << "2. Search book by ID" << endl;
        cout << "3. Borrow a book" << endl;
        cout << "4. Return a book" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";

        if (!(cin >> choice)) { // Check if the menu choice is valid
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid choice!" << endl;
            continue;
        }

        if (choice == 1) { // Option 1: Display all books
            for (const Book& book : books) {
                displayBook(book);
            }
        }

        else if (choice >= 2 && choice <= 4) { // Options 2, 3 and 4 need a book ID
            cout << "Enter book ID: ";
            cin >> id;

            int index = findBook(books, id); // Search for the book

            if (index == -1) { // Check if the book exists
                cout << "Book not found!" << endl;
            }

            else if (choice == 2) { // Option 2: Display one book
                displayBook(books[index]);
            }

            else if (choice == 3) { // Option 3: Borrow a book

                if (books[index].borrowed) { // Check if the book is already borrowed
                    cout << "Book is already borrowed!" << endl;
                }
                else {
                    books[index].borrowed = true;
                    cout << "Book borrowed successfully!" << endl;
                }
            }

            else if (choice == 4) { // Option 4: Return a book

                if (!books[index].borrowed) { // Check if the book is already available
                    cout << "Book is already available!" << endl;
                }
                else {
                    books[index].borrowed = false;
                    cout << "Book returned successfully!" << endl;
                }
            }
        }

        else if (choice == 5) { // Option 5: Exit the program
            cout << "Goodbye!" << endl;
        }

        else { // Show an error for an incorrect option
            cout << "Invalid choice!" << endl;
        }
    }

    return 0;
}
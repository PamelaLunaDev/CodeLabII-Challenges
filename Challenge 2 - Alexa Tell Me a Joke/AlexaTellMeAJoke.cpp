#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>
using namespace std;

int main() {

    ifstream file("randomJokes.txt"); // Open the file containing the jokes

    if (!file.is_open()) { // Check if the file opened correctly
        cout << "Error opening file!" << endl;
        return 1;
    }

    vector<string> jokes; // Create a vector to store the jokes
    string line;

    while (getline(file, line)) { // Read each line from the file
        if (line.find('?') != string::npos) { // Add lines containing a question mark
            jokes.push_back(line);
        }
    }

    file.close(); // Close the file

    if (jokes.empty()) { // Check if any jokes were found
        cout << "No jokes found!" << endl;
        return 1;
    }

    random_device rd; // Set up the random number generator
    mt19937 generator(rd());

    uniform_int_distribution<int> distribution(0, jokes.size() - 1); // Choose a random joke from the vector

    string command;

    cout << "Alexa Joke Generator" << endl; // Display the program title and instructions
    cout << "Type 'Alexa, tell me a joke' or 'quit'." << endl;

    while (true) { // Keep the program running until the user quits

        cout << "\nEnter command: (Alexa, tell me a joke or quit) "; // Ask the user to enter a command

        if (!getline(cin, command)) {
            break;
        }

        if (command == "quit") { // Exit the program if the user types quit
            cout << "Goodbye!" << endl;
            break;
        }

        if (command == "Alexa, tell me a joke") { // Check if the user requests a joke

            int index = distribution(generator); // Select a random joke
            string joke = jokes[index];

            size_t position = joke.find('?'); // Find the question mark in the joke

            string setup = joke.substr(0, position + 1); // Separate the question and the answer
            string punchline = joke.substr(position + 1);

            cout << "\n" << setup << endl; // Display the first part of the joke
            cout << "Press Enter to see the answer...";

            if (!getline(cin, command)) { // Wait for the user to press Enter
                break;
            }

            cout << punchline << endl; // Display the punchline
        }
        else {

            cout << "Invalid command. Try again." << endl; // Show a message for an incorrect command
        }
    }

    return 0;
}
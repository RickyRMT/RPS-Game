// Creator: RickyRMT
//----------------------------------
// Project: Rock, Paper, Scissors Game
#include <iostream>
#include <string>
#include <random>
#include <algorithm>

using namespace std;

class Game {
private:
    string choices[3] = {"rock", "paper", "scissors"};
    int playerScore;
    int robotScore;
    int roundsToWin;

public:
    Game() : playerScore(0), robotScore(0) {}

    void play() {
        intro();
        setRoundsToWin();

        cout << "First to " << roundsToWin << " wins!" << endl;

        while (playerScore < roundsToWin && robotScore < roundsToWin) {
            string playerChoice = getPlayerChoice();
            if (playerChoice == "done") break;

            string robotChoice = rpsGenerator();
            outputAnswer(playerChoice, robotChoice);
        }

        declareWinner();
        displayStatistics();
    }

private:
    static void intro(){ cout << "Welcome to Rock, Paper, Scissors!" << endl; }

    void setRoundsToWin() {
        cout << "Enter number of rounds to win (3, 5, or 7): ";
        cin >> roundsToWin;

        // Input validation for roundsToWin
        while (roundsToWin != 3 && roundsToWin != 5 && roundsToWin != 7) {
            cout << "Invalid choice. Please select 3, 5, or 7: ";
            cin >> roundsToWin;

            // Clear the input buffer if a non-integer is entered
            if (cin.fail()) {
                cin.clear(); // Clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                roundsToWin = 0; // Reset roundsToWin to ensure re-prompt
            }
        }
    }

    static string getPlayerChoice() {
        string choice;
        while (true) {
            cout << "Please enter your choice: 'rock', 'paper', 'scissors' or 'done' to quit: ";
            cin >> choice;
            transform(choice.begin(), choice.end(), choice.begin(), ::tolower);

            // Input validation
            if (choice == "rock" || choice == "paper" || choice == "scissors" || choice == "done") {
                return choice;
            } else {
                cout << "Invalid input. Please try again." << endl;
            }
        }
    }

    string rpsGenerator() {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> distribution(0, 2);
        return choices[distribution(gen)];
    }

    void outputAnswer(const string& playerChoice, const string& robotChoice) {
        cout << "User has chosen: " << playerChoice << endl;
        cout << "Robot has chosen: " << robotChoice << endl;

        if (playerChoice == robotChoice) {
            cout << "It's a draw!" << endl;
        } else if ((playerChoice == "rock" && robotChoice == "scissors") ||
                   (playerChoice == "paper" && robotChoice == "rock") ||
                   (playerChoice == "scissors" && robotChoice == "paper")) {
            cout << "User wins this round!" << endl;
            playerScore++;
        } else {
            cout << "Robot wins this round!" << endl;
            robotScore++;
        }

        cout << "Current Score -> User: " << playerScore << " | Robot: " << robotScore << endl;
        cout << "----------------------------------------------" << endl;
    }

    void declareWinner() const {
        cout << "----------------------------------------------" << endl;
        if (playerScore > robotScore) {
            cout << "Congratulations! You are the overall winner!" << endl;
        } else if (robotScore > playerScore) {
            cout << "Robot wins the game! Better luck next time!" << endl;
        } else {
            cout << "The game ended in a tie!" << endl;
        }
        cout << "----------------------------------------------" << endl;
    }

    void displayStatistics() const {
        cout << "Final Score -> User: " << playerScore << " | Robot: " << robotScore << endl << endl;
        cout << "Thank you for playing!" << endl;
        cout << "project made by: RickyRMT" << endl;
    }
};

int main() {
    Game game;
    game.play();
    return 0;
}

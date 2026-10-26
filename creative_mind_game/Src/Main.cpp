#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include <unordered_map>
#include <algorithm>
#include <limits>

using namespace std;

struct User {
    string username;
    string password;
    int score;
    User* next;
    User(string u, string p) : username(u), password(p), score(0), next(nullptr) {}
};

class UserList {
private:
    User* head;
public:
    UserList() : head(nullptr) {}

    bool addUser(string username, string password) {
        if (findUser(username) != nullptr) return false; 
        User* newUser = new User(username, password);
        newUser->next = head;
        head = newUser;
        return true;
    }

    User* findUser(string username) {
        User* temp = head;
        while (temp) {
            if (temp->username == username) return temp;
            temp = temp->next;
        }
        return nullptr;
    }

    void displayScores() {
        vector<User*> users;
        User* temp = head;
        while (temp) {
            users.push_back(temp);
            temp = temp->next;
        }
        sort(users.begin(), users.end(), [](User* a, User* b){ return a->score > b->score; });
        cout << "\n---- Scoreboard ----\n";
        for (auto u : users) {
            cout << u->username << " : " << u->score << endl;
        }
    }
};

string generateRandomNumber(int length, bool allowRepeat) {
    string result = "";
    srand(time(0));
    while ((int)result.length() < length) {
        char digit = '0' + rand() % 10;
        if (!allowRepeat && result.find(digit) != string::npos) continue;
        result += digit;
    }
    return result;
}

pair<int,int> compareNumbers(const string &secret, const string &guess) {
    int correctPos = 0, correctDigit = 0;
    string tempSecret = secret;
    string tempGuess = guess;

    // Check correct positions
    for (int i = 0; i < secret.size(); ++i) {
        if (tempGuess[i] == tempSecret[i]) {
            correctPos++;
            tempSecret[i] = tempGuess[i] = '*'; 
        }
    }

    for (int i = 0; i < tempGuess.size(); ++i) {
        if (tempGuess[i] != '*') {
            size_t pos = tempSecret.find(tempGuess[i]);
            if (pos != string::npos) {
                correctDigit++;
                tempSecret[pos] = '*';
            }
        }
    }
    return {correctPos, correctDigit};
}

int calculateScore(int length, bool repeatAllowed, int tries, int timeTaken, bool historyShown) {
    int base = length * 10;
    if (repeatAllowed) base += 5;
    int score = base + (historyShown ? 5 : 0) + max(0, 50 - tries*4 - timeTaken/5);
    return score;
}

int main() {
    UserList users;
    int choice;
    int gameLength = 4;
    bool repeatAllowed = false;
    bool showHistory = false;

    do {
        cout << "\n--- Fekre Bakar Game Menu ---\n";
        cout << "1. Register User\n";
        cout << "2. Game Settings\n";
        cout << "3. Play Game\n";
        cout << "4. View Scores\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            string u, p;
            cout << "Enter username: "; cin >> u;
            cout << "Enter password: "; cin >> p;
            if (users.addUser(u, p)) cout << "User registered successfully.\n";
            else cout << "Username already exists.\n";
        } 
        else if (choice == 2) {
            cout << "Enter number length (4-9): "; cin >> gameLength;
            cout << "Allow repeated digits? (1-yes, 0-no): "; cin >> repeatAllowed;
            cout << "Show guess history? (1-yes, 0-no): "; cin >> showHistory;
        } 
        else if (choice == 3) {
            string u, p;
            cout << "Enter username: "; cin >> u;
            cout << "Enter password: "; cin >> p;
            User* player = users.findUser(u);
            if (!player || player->password != p) {
                cout << "Invalid username or password.\n";
                continue;
            }

            string secret = generateRandomNumber(gameLength, repeatAllowed);
            vector<string> history;
            int tries = 0;
            int maxTries = 12;
            int timePerDigit = repeatAllowed ? 7 : 10;
            int totalTime = gameLength * timePerDigit;
            string guess;

            cout << "Game started! You have " << totalTime << " seconds.\n";

            while (tries < maxTries) {
                cout << "\nAttempt " << (tries+1) << ": Enter your guess: ";
                cin >> guess;
                if (guess.size() != secret.size()) {
                    cout << "Invalid input length. Must be " << secret.size() << " digits.\n";
                    continue;
                }
                tries++;
                auto [correctPos, correctDigit] = compareNumbers(secret, guess);
                cout << "Correct position: " << correctPos << ", Correct digit (wrong place): " << correctDigit << "\n";
                if (showHistory) history.push_back(guess);
                if (correctPos == secret.size()) {
                    cout << "Congratulations! You guessed the number.\n";
                    break;
                }
            }

            int score = calculateScore(gameLength, repeatAllowed, tries, totalTime, showHistory);
            player->score = score;
            cout << "Your score: " << score << "\n";
            if (showHistory) {
                cout << "Guess history: ";
                for (auto h : history) cout << h << " ";
                cout << "\n";
            }
        } 
        else if (choice == 4) {
            users.displayScores();
        }

    } while (choice != 5);

    cout << "Exiting program...\n";
    return 0;
}

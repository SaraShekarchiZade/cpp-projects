#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>

using namespace std;

struct Node {
    string word;
    Node* next;
};

class LinkedList {
public:
    Node* head;

    LinkedList() { head = nullptr; }

    void append(const string& w) {
        Node* newNode = new Node{w, nullptr};
        if (!head) {
            head = newNode;
        } else {
            Node* temp = head;
            while (temp->next) temp = temp->next;
            temp->next = newNode;
        }
    }

    vector<string> toVector() {
        vector<string> words;
        Node* temp = head;
        while (temp) {
            words.push_back(temp->word);
            temp = temp->next;
        }
        return words;
    }
};

LinkedList readFileToList(const string& filename) {
    LinkedList list;
    ifstream file(filename);
    if (!file) {
        cerr << "Error opening file: " << filename << endl;
        return list;
    }
    string word;
    while (file >> word) {
        list.append(word);
    }
    file.close();
    return list;
}

double calculateAccuracy(const vector<string>& pattern, const vector<string>& typed) {
    int correct = 0;
    int minSize = min(pattern.size(), typed.size());
    for (int i = 0; i < minSize; i++) {
        if (pattern[i] == typed[i]) correct++;
    }
    return (double)correct / pattern.size() * 100;
}

vector<string> getIncorrectWords(const vector<string>& pattern, const vector<string>& typed) {
    vector<string> wrong;
    int minSize = min(pattern.size(), typed.size());
    for (int i = 0; i < minSize; i++) {
        if (pattern[i] != typed[i]) wrong.push_back(typed[i]);
    }
    for (int i = minSize; i < typed.size(); i++) {
        wrong.push_back(typed[i]);
    }
    return wrong;
}

struct User {
    int id;
    LinkedList typedWords;
    double timeSeconds;
};

int main() {
    vector<User> users;

    int n;
    cout << "Enter number of users: ";
    cin >> n;
    for (int i = 0; i < n; i++) {
        User u;
        cout << "Enter user ID: ";
        cin >> u.id;
        cout << "Enter typing time in seconds: ";
        cin >> u.timeSeconds;

        string filename;
        cout << "Enter typed text filename for user " << u.id << ": ";
        cin >> filename;

        u.typedWords = readFileToList(filename);
        users.push_back(u);
    }

    LinkedList pattern = readFileToList("pattern.txt");
    vector<string> patternWords = pattern.toVector();

 
    cout << fixed << setprecision(2);
    vector<pair<int, double>> speeds;

    int maxErrors = -1;
    int worstUserIndex = -1;

    for (int i = 0; i < users.size(); i++) {
        vector<string> typed = users[i].typedWords.toVector();
        double accuracy = calculateAccuracy(patternWords, typed);
        cout << "User " << users[i].id << " accuracy: " << accuracy << "%\n";

        int correctWords = (int)(accuracy / 100.0 * patternWords.size());
        double speed = correctWords / users[i].timeSeconds;
        speeds.push_back({users[i].id, speed});

        vector<string> wrongWords = getIncorrectWords(patternWords, typed);
        if (wrongWords.size() > maxErrors) {
            maxErrors = (int)wrongWords.size();
            worstUserIndex = i;
        }
    }

    sort(speeds.begin(), speeds.end(), [](auto &a, auto &b){ return a.second < b.second; });
    cout << "\nTyping speeds (words/sec) sorted:\n";
    for (auto &p : speeds) {
        cout << "User " << p.first << ": " << p.second << "\n";
    }

    // print  mistakes
    if (worstUserIndex != -1) {
        vector<string> wrongWords = getIncorrectWords(patternWords, users[worstUserIndex].typedWords.toVector());
        cout << "\nUser with most mistakes: " << users[worstUserIndex].id << "\nWrong words:\n";
        for (auto &w : wrongWords) cout << w << " ";
        cout << endl;
    }

    return 0;
}

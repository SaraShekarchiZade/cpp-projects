#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <ctime>
#include <queue>
#include <algorithm>

using namespace std;

// Message priority map
unordered_map<string, int> messagePriority = {
    {"Text", 5},
    {"Image", 4},
    {"Audio", 3},
    {"Video", 2}
};

// ------------------- Message Class -------------------
class Message {
public:
    int desId;
    int sourceId;
    string type;
    string contentId;
    int volume;
    time_t sendTime;
    time_t receiveTime;
    int status; // 1=unsent, 2=sent, 3=seen

    Message(int d, int s, string t, string c, int v, time_t st, time_t rt, int stt)
        : desId(d), sourceId(s), type(t), contentId(c), volume(v), sendTime(st), receiveTime(rt), status(stt) {}

    int getPriority() const { return messagePriority[type]; }
};

// ------------------- Template Queue Class -------------------
template <typename T>
class Queue {
protected:
    vector<T> data;
public:
    void enqueue(T item) { data.push_back(item); }
    T dequeue() {
        if (data.empty()) throw runtime_error("Queue is empty!");
        T item = data.front();
        data.erase(data.begin());
        return item;
    }
    bool empty() { return data.empty(); }
};

// ------------------- MaxPriorityQueue -------------------
template <typename T>
class MaxPriorityQueue : public Queue<T> {
public:
    T dequeue() {
        if (this->data.empty()) throw runtime_error("Queue is empty!");
        auto it = max_element(this->data.begin(), this->data.end(), [](const T &a, const T &b) {
            if (a.getPriority() == b.getPriority())
                return a.sendTime > b.sendTime; // older message first
            return a.getPriority() < b.getPriority();
        });
        T item = *it;
        this->data.erase(it);
        return item;
    }
};

// ------------------- File Handling -------------------
vector<Message> loadMessagesFromFile(const string &filename) {
    vector<Message> messages;
    ifstream fin(filename);
    string line;
    while (getline(fin, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string token;

        int desId, sourceId, volume, status;
        string type, contentId;
        time_t sendTime, receiveTime;

        getline(ss, token, '|'); desId = stoi(token);
        getline(ss, token, ','); sourceId = stoi(token);
        getline(ss, type, ','); getline(ss, contentId, ',');
        getline(ss, token, ','); volume = stoi(token);
        getline(ss, token, '|'); sendTime = stol(token);
        getline(ss, token, ','); receiveTime = stol(token);
        getline(ss, token, ','); status = stoi(token);

        messages.emplace_back(desId, sourceId, type, contentId, volume, sendTime, receiveTime, status);
    }
    return messages;
}

void saveMessageToFile(const string &filename, const Message &msg) {
    ofstream fout(filename, ios::app);
    fout << msg.desId << "|"
         << msg.sourceId << "," << msg.type << "," << msg.contentId << "," << msg.volume << "," << msg.sendTime << "|"
         << msg.receiveTime << "," << msg.status << "\n";
}

// ------------------- Priority Sending Simulation -------------------
void sendMessages(MaxPriorityQueue<Message> &mpq, const string &destFile) {
    while (!mpq.empty()) {
        Message msg = mpq.dequeue();
        int seconds = max(1, msg.volume / 500); // 500 bytes/sec
        time_t now = time(0);
        msg.sendTime = now;
        msg.receiveTime = now + seconds;
        msg.status = 2; // sent
        saveMessageToFile(destFile, msg);
        cout << "Sent message: " << msg.contentId << " to user " << msg.desId << endl;
    }
}

// ------------------- Statistics -------------------
void showStats(const vector<Message> &messages) {
    unordered_map<int, int> volumeMap;
    unordered_map<int, int> countMap;

    for (const auto &msg : messages) {
        if (msg.status == 2 || msg.status == 3) {
            int key = msg.sourceId * 1000 + msg.desId; // unique per pair
            volumeMap[key] += msg.volume;
            countMap[key]++;
        }
    }

    cout << "\n--- Message Volume Between Users ---\n";
    for (const auto &p : volumeMap)
        cout << "User Pair [" << p.first / 1000 << " -> " << p.first % 1000 << "]: " << p.second << " bytes\n";

    cout << "\n--- Message Count Between Users ---\n";
    for (const auto &p : countMap)
        cout << "User Pair [" << p.first / 1000 << " -> " << p.first % 1000 << "]: " << p.second << " messages\n";
}

int main() {
    MaxPriorityQueue<Message> mpq;

    // Load messages from a user file
    vector<Message> messages = loadMessagesFromFile("user1.txt");
    for (auto &msg : messages) {
        if (msg.status == 1) // unsent
            mpq.enqueue(msg);
    }

    int choice;
    do {
        cout << "\n1) Send pending messages\n2) Show statistics\n0) Exit\nChoice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                sendMessages(mpq, "user1.txt");
                break;
            case 2:
                showStats(messages);
                break;
            case 0:
                break;
            default:
                cout << "Invalid choice!\n";
        }
    } while (choice != 0);

    return 0;
}

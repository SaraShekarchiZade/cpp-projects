#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
using namespace std;

struct Parents {
    vector<string> queens;
    vector<string> workers;
};

// Function to read parents from file
Parents readParents(const string &filename) {
    ifstream fin(filename);
    Parents p;
    int qCount, wCount;
    fin >> qCount >> wCount;
    string s;
    getline(fin, s); // consume newline
    for(int i = 0; i < qCount; ++i) {
        getline(fin, s);
        p.queens.push_back(s);
    }
    for(int i = 0; i < wCount; ++i) {
        getline(fin, s);
        p.workers.push_back(s);
    }
    return p;
}

// Check if worker substring matches queen prefix
vector<string> generateChildren(const Parents &p, const string &worker) {
    vector<string> children;
    for (const auto &queen : p.queens) {
        int minLen = min(worker.size(), queen.size());
        for (int len = 1; len <= minLen; ++len) {
            if (worker.substr(worker.size()-len) == queen.substr(0,len)) {
                children.push_back(queen.substr(0,len));
            }
        }
    }
    return children;
}

int main() {
    Parents p = readParents("txt.parents");
    vector<string> inputQueue;
    string s;
    int n;
    cin >> n;
    getline(cin, s); // consume newline
    for(int i = 0; i < n; ++i) {
        getline(cin, s);
        inputQueue.push_back(s);
    }

    vector<string> validChildren;

    for(const auto &ant : inputQueue) {
        bool isChild = false;
        for(const auto &worker : p.workers) {
            vector<string> gen = generateChildren(p, worker);
            if(find(gen.begin(), gen.end(), ant) != gen.end()) {
                isChild = true;
                break;
            }
        }
        if(isChild) validChildren.push_back(ant);
    }

    // Save order to file
    ofstream fout("order", ios::binary);
    for(const auto &child : validChildren) {
        uint16_t len = child.size();
        fout.write((char*)&len, sizeof(len));
        fout.write(child.c_str(), len);
    }
    fout.close();

    return 0;
}

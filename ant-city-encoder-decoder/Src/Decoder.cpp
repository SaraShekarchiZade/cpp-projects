#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
using namespace std;

int main() {
    ifstream fin("order", ios::binary);
    string s;
    while(fin.peek() != EOF) {
        uint16_t len;
        fin.read((char*)&len, sizeof(len));
        char buffer[256];
        fin.read(buffer, len);
        buffer[len] = '\0';
        cout << buffer << endl;
    }
    fin.close();
    return 0;
}

#include <iostream>
#include <queue>
#include <vector>
#include <string>
using namespace std;


class Song {
public:
    char category;   // S, P, K, M
    int requests;    
    int duration;  
    Song() {}
    Song(char c, int r, int d) : category(c), requests(r), duration(d) {}
};


struct CompareSongs {
    bool operator()(Song a, Song b) {
        return a.requests < b.requests; 
    }
};


int main() {

   
    queue<Song> inputQueue;


    inputQueue.push(Song('S', 8, 90));
    inputQueue.push(Song('P', 6, 120));
    inputQueue.push(Song('K', 2, 180));
    inputQueue.push(Song('M', 5, 300));
    inputQueue.push(Song('S', 4, 150));
    inputQueue.push(Song('P', 7, 200));
    inputQueue.push(Song('K', 6, 240));
    inputQueue.push(Song('M', 9, 210));


    queue<Song> traditional, pop, classic, local;

    while (!inputQueue.empty()) {
        Song s = inputQueue.front();
        inputQueue.pop();

        switch (s.category) {
            case 'S': traditional.push(s); break;
            case 'P': pop.push(s); break;
            case 'K': classic.push(s); break;
            case 'M': local.push(s); break;
        }
    }


    priority_queue<Song, vector<Song>, CompareSongs> playQueue;

    auto moveToHeap = [&](queue<Song>& q) {
        while (!q.empty()) {
            playQueue.push(q.front());
            q.pop();
        }
    };

    moveToHeap(traditional);
    moveToHeap(pop);
    moveToHeap(classic);
    moveToHeap(local);


    int totalTime = 3600;
    int usedTime = 0;

    int timeS = 0, timeP = 0, timeK = 0, timeM = 0;
    int satS = 0, satP = 0, satK = 0, satM = 0;

 
    while (!playQueue.empty() && usedTime < totalTime) {
        Song s = playQueue.top();
        playQueue.pop();

        if (usedTime + s.duration <= totalTime) {
            usedTime += s.duration;

            switch (s.category) {
                case 'S': timeS += s.duration; satS += s.requests; break;
                case 'P': timeP += s.duration; satP += s.requests; break;
                case 'K': timeK += s.duration; satK += s.requests; break;
                case 'M': timeM += s.duration; satM += s.requests; break;
            }
        }
    }


    cout << "\n====== Night Ahangi Program Report ======\n";

    cout << "\nTraditional (S):"
         << "\n  Play Time: " << timeS << " sec"
         << "\n  Satisfaction: " << satS
         << "\n  Percentage: " << (timeS * 100.0 / totalTime) << "%\n";

    cout << "\nPop (P):"
         << "\n  Play Time: " << timeP << " sec"
         << "\n  Satisfaction: " << satP
         << "\n  Percentage: " << (timeP * 100.0 / totalTime) << "%\n";

    cout << "\nClassic (K):"
         << "\n  Play Time: " << timeK << " sec"
         << "\n  Satisfaction: " << satK
         << "\n  Percentage: " << (timeK * 100.0 / totalTime) << "%\n";

    cout << "\nLocal (M):"
         << "\n  Play Time: " << timeM << " sec"
         << "\n  Satisfaction: " << satM
         << "\n  Percentage: " << (timeM * 100.0 / totalTime) << "%\n";

    cout << "\nTotal Used Time: " << usedTime << " sec\n";

    return 0;
}

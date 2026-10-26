#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>
#include <algorithm>

using namespace std;

struct Person {
    int id;
    string firstName;
    string lastName;
    string gender;
    string birthDate;
    string deathDate;
    int spouseId; // -1 if no spouse
    vector<int> childrenIds;
};

class FamilyTree {
private:
    unordered_map<int, Person> people;

public:
    void addPerson(Person p) {
        people[p.id] = p;
    }

    void addChild(int parentId, int childId) {
        people[parentId].childrenIds.push_back(childId);
    }

    void displayPerson(const Person& p) {
        cout << "ID: " << p.id << " Name: " << p.firstName << " " << p.lastName 
             << " Gender: " << p.gender << endl;
    }

    void displayCouplesWithoutRelation() {
        cout << "\nCouples without blood relation:\n";
        for(auto& [id, person] : people) {
            if(person.spouseId != -1) {
                displayPerson(person);
                displayPerson(people[person.spouseId]);
                cout << "------\n";
            }
        }
    }

    void displayRelatives(int personId, const string& relation) {
        cout << "\nRelatives of type " << relation << " for " 
             << people[personId].firstName << ":\n";
        if(relation == "child") {
            for(int cid : people[personId].childrenIds)
                displayPerson(people[cid]);
        } else if(relation == "parent") {
            for(auto& [id, p] : people) {
                if(find(p.childrenIds.begin(), p.childrenIds.end(), personId) != p.childrenIds.end())
                    displayPerson(p);
            }
        } else if(relation == "sibling") {
            vector<int> siblings;
            for(auto& [id, p] : people) {
                if(id == personId) continue;
                for(int pid : p.childrenIds) {
                    if(find(people[personId].childrenIds.begin(), people[personId].childrenIds.end(), pid) != people[personId].childrenIds.end())
                        siblings.push_back(p.id);
                }
            }
            for(int sid : siblings) displayPerson(people[sid]);
        }
    }

    int countDescendants(int personId) {
        int count = people[personId].childrenIds.size();
        for(int cid : people[personId].childrenIds)
            count += countDescendants(cid);
        return count;
    }

    void personWithMostDescendants() {
        int maxCount = 0;
        int personId = -1;
        for(auto& [id, p] : people) {
            int c = countDescendants(id);
            if(c > maxCount) {
                maxCount = c;
                personId = id;
            }
        }
        cout << "\nPerson with most descendants:\n";
        displayPerson(people[personId]);
        cout << "Total descendants: " << maxCount << endl;
    }

    void closestRelation(int id1, int id2) {
        cout << "\nClosest relation (simplified output):\n";
        cout << people[id1].firstName << " and " << people[id2].firstName 
             << " might be distant relatives (advanced computation needed)\n";
    }
};

int main() {
    FamilyTree tree;

    // Example data
    Person p1 = {1, "Ali", "Ahmadi", "Male", "1970-01-01", "", 2};
    Person p2 = {2, "Sara", "Ahmadi", "Female", "1972-05-10", "", 1};
    Person p3 = {3, "Reza", "Ahmadi", "Male", "1995-03-03", "", -1};

    tree.addPerson(p1);
    tree.addPerson(p2);
    tree.addPerson(p3);

    tree.addChild(1,3);
    tree.addChild(2,3);

    tree.displayCouplesWithoutRelation();
    tree.displayRelatives(1, "child");
    tree.personWithMostDescendants();
    tree.closestRelation(1,3);

    return 0;
}

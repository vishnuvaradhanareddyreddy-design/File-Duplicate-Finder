#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <iomanip>
using namespace std;

struct File {
    int id;
    string name, path, hash;
    double size;
};

struct Group {
    string hash;
    vector<File> files;
    double saved;
};

// Compare duplicate groups
bool compare(Group a, Group b) {
    if (a.files.size() != b.files.size())
        return a.files.size() > b.files.size();

    return a.saved > b.saved;
}

int main() {
    int n;

    cout << "===== FILE DUPLICATE FINDER =====\n";
    cout << "Enter number of files (minimum 20): ";
    cin >> n;

    if (n < 20) {
        cout << "Please enter at least 20 files!\n";
        return 0;
    }

    vector<File> files(n);

    unordered_map<string, vector<File>> mp;

    // Input files
    cout << "\nEnter ID Name Path Size Hash:\n";

    for (int i = 0; i < n; i++) {
        cin >> files[i].id
            >> files[i].name
            >> files[i].path
            >> files[i].size
            >> files[i].hash;

        mp[files[i].hash].push_back(files[i]);
    }

    // Display file table
    cout << "\n===== FILE TABLE =====\n";

    cout << left << setw(8) << "ID"
         << setw(18) << "Name"
         << setw(18) << "Path"
         << setw(12) << "Size"
         << "Hash\n";

    for (auto f : files) {
        cout << left << setw(8) << f.id
             << setw(18) << f.name
             << setw(18) << f.path
             << setw(12) << f.size
             << f.hash << "\n";
    }

    // Find duplicate groups
    vector<Group> groups;
    double totalSaved = 0;

    for (auto entry : mp) {
        if (entry.second.size() > 1) {

            Group g;
            g.hash = entry.first;
            g.files = entry.second;
            g.saved = 0;

            // Keep one file and remove extra copies
            for (int i = 1; i < g.files.size(); i++) {
                g.saved += g.files[i].size;
            }

            totalSaved += g.saved;
            groups.push_back(g);
        }
    }

    // Display duplicates
    cout << "\n===== DUPLICATE FILES =====\n";

    if (groups.empty())
        cout << "No duplicates found!\n";

    for (auto g : groups) {
        cout << "\nHash: " << g.hash << "\n";

        for (auto f : g.files) {
            cout << f.name << " | "
                 << f.path << " | "
                 << f.size << " MB\n";
        }

        cout << "Files count: " << g.files.size() << "\n";
        cout << "Storage saved: " << g.saved << " MB\n";
    }

    // Sort groups
    sort(groups.begin(), groups.end(), compare);

    cout << "\n===== SORTED DUPLICATE GROUPS =====\n";

    for (auto g : groups) {
        cout << g.hash
             << " | Count: " << g.files.size()
             << " | Saved: " << g.saved << " MB\n";
    }

    // Final summary
    cout << "\n===== STORAGE SUMMARY =====\n";

    cout << "Total files: " << n << "\n";
    cout << "Duplicate groups: " << groups.size() << "\n";

    cout << fixed << setprecision(2);
    cout << "Total storage saved: "
         << totalSaved << " MB\n";

    cout << "\n===== PROJECT COMPLETED =====\n";

    return 0;
}
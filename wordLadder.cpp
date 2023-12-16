#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <queue>
using namespace std;

/*Description: The wordLadder function is designed to find the shortest word ladder between two given words 
(source and target), with the constraint that the words involved are exactly 5 letters long. 
A word ladder is a sequence of words where each adjacent pair of words differs by exactly one character.
This implementation ensures that the word ladder is found within a reasonable time frame by using breadth-first 
search and unordered maps for efficient storage and retrieval of graph-related information. */

vector<string> V; // words from wordlist05.txt
unordered_map<string, vector<string>> neighbors; // adjacency list
unordered_map<string, int> distance; // distance from source
unordered_map<string, string> predecessor; // predecessor in the shortest path

// Function to check if two words differ by exactly one character
bool isOneCharApart(const string& word1, const string& word2) {
    int diffCount = 0;
    for (size_t i = 0; i < word1.size(); ++i) {
        if (word1[i] != word2[i]) {
            if (++diffCount > 1) {
                return false;
            }
        }
    }
    return diffCount == 1;
}

// Breadth-First Search
void bfs(const string& start) {
    queue<string> q;
    q.push(start);
    ::distance[start] = 0;

    while (!q.empty()) {
        string current = q.front();
        q.pop();

        for (const string& neighbor : neighbors[current]) {
            if (::distance.find(neighbor) == ::distance.end()) {
                ::distance[neighbor] = ::distance[current] + 1;
                predecessor[neighbor] = current;
                q.push(neighbor);
            }
        }
    }
}

void wordLadder(string s, string t, int &steps, vector<string> &p) {
    // Read words from wordlist05.txt
    ifstream infile("wordlist05.txt");
    string word;
    while (infile >> word) {
        V.push_back(word);
    }
    infile.close();

    // Build the adjacency list
    for (size_t i = 0; i < V.size(); ++i) {
        for (size_t j = i + 1; j < V.size(); ++j) {
            if (isOneCharApart(V[i], V[j])) {
                neighbors[V[i]].push_back(V[j]);
                neighbors[V[j]].push_back(V[i]);
            }
        }
    }

    // Initialize data structures
    ::distance.clear();
    predecessor.clear();

    // Perform BFS
    bfs(s);

    // Reconstruct the path
    steps = ::distance[t];
    if (steps > 0) {
        string current = t;
        while (current != s) {
            p.insert(p.begin(), current);
            current = predecessor[current];
        }
        p.insert(p.begin(), s);
    }
}

/*int main(void) {
    int steps = 0;
    string s, t;
    vector<string> path;

    cout << "Source: ";
    cin >> s;

    cout << "Target: ";
    cin >> t;

    wordLadder(s, t, steps, path);

    if (steps == 0) {
        cout << "No path!\n";
    } else {
        cout << "Steps: " << steps << "\n\n";
        for (const string& word : path) {
            cout << word << endl;
        }
    }
    return 0;
}*/
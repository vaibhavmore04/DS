#include <iostream>
#include <string>
using namespace std;

const int MAX = 10;

class FlightGraph {
    int n; // number of cities
    string cities[MAX];
    int adjMatrix[MAX][MAX]; // matrix to store flight costs

public:
    void createGraph() {
        cout << "Enter number of cities (max " << MAX << "): ";
        cin >> n;

        cout << "Enter names of " << n << " cities:\n";
        for (int i = 0; i < n; i++) {
            cin >> cities[i];
        }

        // Initialize matrix to 0 (no flights)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                adjMatrix[i][j] = 0;

        int flights;
        cout << "Enter number of flights: ";
        cin >> flights;

        for (int i = 0; i < flights; i++) {
            string src, dest;
            int cost;
            cout << "Enter source city, destination city, and cost: ";
            cin >> src >> dest >> cost;

            int u = getIndex(src);
            int v = getIndex(dest);

            if (u != -1 && v != -1) {
                adjMatrix[u][v] = cost;
            } else {
                cout << "Invalid city name!\n";
            }
        }
    }

    int getIndex(string name) {
        for (int i = 0; i < n; i++) {
            if (cities[i] == name)
                return i;
        }
        return -1;
    }

    void displayMatrix() {
        cout << "\nAdjacency Matrix (Flight Cost):\n    ";
        for (int i = 0; i < n; i++)
            cout << cities[i] << "\t";
        cout << "\n";

        for (int i = 0; i < n; i++) {
            cout << cities[i] << " ";
            for (int j = 0; j < n; j++) {
                cout << "\t" << adjMatrix[i][j];
            }
            cout << "\n";
        }
    }

    void checkConnection() {
        string src, dest;
        cout << "Enter source and destination city: ";
        cin >> src >> dest;

        int u = getIndex(src);
        int v = getIndex(dest);

        if (u != -1 && v != -1 && adjMatrix[u][v] > 0) {
            cout << "Flight exists with cost: " << adjMatrix[u][v] << "\n";
        } else {
            cout << "No direct flight found.\n";
        }
    }
};

int main() {
    FlightGraph graph;
    int choice;

    do {
        cout << "\n--- Flight Management ---\n";
        cout << "1. Create Graph\n";
        cout << "2. Display Adjacency Matrix\n";
        cout << "3. Check Flight Connection\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: graph.createGraph(); break;
            case 2: graph.displayMatrix(); break;
            case 3: graph.checkConnection(); break;
            case 0: cout << "Exiting...\n"; break;
            default: cout << "Invalid option.\n";
        }
    } while (choice != 0);

    return 0;
}


/*--- Flight Management ---
1. Create Graph
2. Display Adjacency Matrix
3. Check Flight Connection
0. Exit
Enter choice: 1
Enter number of cities (max 10): 3
Enter names of 3 cities:
Pune
Mumbai
Delhi
Enter number of flights: 3
Enter source city, destination city, and cost: Pune Mumbai 500
Enter source city, destination city, and cost: Mumbai Delhi 1000
Enter source city, destination city, and cost: Pune Delhi 1500
*/
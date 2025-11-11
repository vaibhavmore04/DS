#include <bits/stdc++.h>
using namespace std;

class Heap {
public:
    vector<int> maxHeap = {0}; // 1-indexed for easy parent-child calculation
    vector<int> minHeap = {0};
    int nmax = 0;
    int nmin = 0;

    // -------- Insert Stock Price --------
    void insertPrice(int price) {
        insertMax(price);
        insertMin(price);
    }

    // -------- Insert into Max Heap --------
    void insertMax(int data) {
        maxHeap.push_back(data);
        nmax++;
        reheapUpMax(nmax);
    }

    // -------- Insert into Min Heap --------
    void insertMin(int data) {
        minHeap.push_back(data);
        nmin++;
        reheapUpMin(nmin);
    }

    // -------- Reheap Up for Max --------
    void reheapUpMax(int n) {
        while (n > 1) {
            int parent = n / 2;
            if (maxHeap[parent] < maxHeap[n]) {
                swap(maxHeap[parent], maxHeap[n]);
                n = parent;
            } else break;
        }
    }

    // -------- Reheap Up for Min --------
    void reheapUpMin(int n) {
        while (n > 1) {
            int parent = n / 2;
            if (minHeap[parent] > minHeap[n]) {
                swap(minHeap[parent], minHeap[n]);
                n = parent;
            } else break;
        }
    }

    // -------- Reheap Down for Max --------
    void reheapDownMax(int i, int n) {
        while (true) {
            int lc = 2 * i, rc = 2 * i + 1, largest = i;
            if (lc <= n && maxHeap[lc] > maxHeap[largest]) largest = lc;
            if (rc <= n && maxHeap[rc] > maxHeap[largest]) largest = rc;
            if (largest != i) {
                swap(maxHeap[i], maxHeap[largest]);
                i = largest;
            } else break;
        }
    }

    // -------- Reheap Down for Min --------
    void reheapDownMin(int i, int n) {
        while (true) {
            int lc = 2 * i, rc = 2 * i + 1, smallest = i;
            if (lc <= n && minHeap[lc] < minHeap[smallest]) smallest = lc;
            if (rc <= n && minHeap[rc] < minHeap[smallest]) smallest = rc;
            if (smallest != i) {
                swap(minHeap[i], minHeap[smallest]);
                i = smallest;
            } else break;
        }
    }

    // -------- Display Max & Min Stock Price --------
    void displayMaxMin() {
        if (nmax == 0) {
            cout << "No stock prices recorded.\n";
            return;
        }
        cout << "Maximum (Highest) Stock Price: " << maxHeap[1] << endl;
        cout << "Minimum (Lowest) Stock Price: " << minHeap[1] << endl;
    }

    // -------- Delete Topmost (Maximum) Price --------
    void deleteMax() {
        if (nmax == 0) {
            cout << "Heap is empty.\n";
            return;
        }
        cout << "Deleting maximum price: " << maxHeap[1] << endl;
        maxHeap[1] = maxHeap[nmax];
        maxHeap.pop_back();
        nmax--;
        reheapDownMax(1, nmax);
    }

    // -------- Display All Prices in Ascending Order --------
    void displayAscending() {
        if (nmax == 0) {
            cout << "No prices to display.\n";
            return;
        }
        vector<int> temp = maxHeap;
        int tempn = nmax;
        while (tempn > 1) {
            swap(temp[1], temp[tempn]);
            tempn--;
            reheapDownMax(1, tempn);
        }
        cout << "Prices in Ascending Order: ";
        for (int i = 1; i <= nmax; i++) cout << temp[i] << " ";
        cout << endl;
    }

    // -------- Display All Prices in Descending Order --------
    void displayDescending() {
        if (nmin == 0) {
            cout << "No prices to display.\n";
            return;
        }
        vector<int> temp = minHeap;
        int tempn = nmin;
        while (tempn > 1) {
            swap(temp[1], temp[tempn]);
            tempn--;
            reheapDownMin(1, tempn);
        }
        cout << "Prices in Descending Order: ";
        for (int i = 1; i <= nmin; i++) cout << temp[i] << " ";
        cout << endl;
    }
};

// -------- MAIN FUNCTION --------
int main() {
    Heap h;
    int choice, price;

    while (true) {
        cout << "\n--- STOCK PRICE MANAGEMENT ---\n";
        cout << "1. Insert Daily Stock Price\n";
        cout << "2. Display Maximum and Minimum Price\n";
        cout << "3. Delete Maximum (Topmost) Price\n";
        cout << "4. Display All Prices (Ascending)\n";
        cout << "5. Display All Prices (Descending)\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter stock price: ";
                cin >> price;
                h.insertPrice(price);
                break;

            case 2:
                h.displayMaxMin();
                break;

            case 3:
                h.deleteMax();
                break;

            case 4:
                h.displayAscending();
                break;

            case 5:
                h.displayDescending();
                break;

            case 6:
                cout << "Exiting program.\n";
                return 0;

            default:
                cout << "Invalid choice! Try again.\n";
        }
    }
}
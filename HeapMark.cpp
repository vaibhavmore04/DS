#include <iostream>
#include <vector>
using namespace std;

class Heap {
private:
    vector<int> marks; 
    int n;

public:
    Heap() {
        n = 0;
    }

    void inputMarks() {
        cout << "Enter number of students: ";
        cin >> n;
        marks.resize(n);
        cout << "Enter marks of students: ";
        for (int i = 0; i < n; i++) {
            cin >> marks[i];
        }
    }

    void maxHeap(vector<int> &arr, int n, int i) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && arr[left] > arr[largest])
            largest = left;

        if (right < n && arr[right] > arr[largest])
            largest = right;

        if (largest != i) {
            swap(arr[i], arr[largest]);
            maxHeap(arr, n, largest);
        }
    }

    void minHeap(vector<int> &arr, int n, int i) {
        int smallest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && arr[left] < arr[smallest])
            smallest = left;

        if (right < n && arr[right] < arr[smallest])
            smallest = right;

        if (smallest != i) {
            swap(arr[i], arr[smallest]);
            minHeap(arr, n, smallest);
        }
    }

    void findMaxMark() {
        vector<int> arr = marks;
        for (int i = n / 2 - 1; i >= 0; i--)
            maxHeap(arr, n, i);
        cout << "Maximum mark: " << arr[0] << endl;
    }

    void findMinMark() {
        vector<int> arr = marks;
        for (int i = n / 2 - 1; i >= 0; i--)
            minHeap(arr, n, i);
        cout << "Minimum mark: " << arr[0] << endl;
    }
};

int main() {
    Heap h;
    int choice;

    do {
        cout << "\n---- MENU ----\n";
        cout << "1. Enter Marks\n";
        cout << "2. Find Maximum Mark\n";
        cout << "3. Find Minimum Mark\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            h.inputMarks();
            break;
        case 2:
            h.findMaxMark();
            break;
        case 3:
            h.findMinMark();
            break;
        case 4:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice!\n";
        }
    } while (choice != 4);

    return 0;
}

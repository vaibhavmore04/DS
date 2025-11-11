#include <iostream>
using namespace std;

class JobHeap {
    int maxHeap[50], minHeap[50], jobs[50];
    int nMax, nMin, total;

public:
    JobHeap() {
        nMax = nMin = total = 0;
    } 

    void insertJob(int priority) {
        // Insert in Max Heap
        maxHeap[++nMax] = priority;
        int i = nMax;
        while (i > 1 && maxHeap[i / 2] < maxHeap[i]) {
            swap(maxHeap[i / 2], maxHeap[i]);
            i /= 2;
        }

        // Insert in Min Heap
        minHeap[++nMin] = priority;
        i = nMin;
        while (i > 1 && minHeap[i / 2] > minHeap[i]) {
            swap(minHeap[i / 2], minHeap[i]);
            i /= 2;
        }

        // Store in jobs array
        jobs[total++] = priority;
    }

    void showPriority() {
        if (nMax == 0) {
            cout << "No jobs available.\n";
            return;
        }
        cout << "Highest priority job: " << maxHeap[1] << endl;
        cout << "Lowest priority job: " << minHeap[1] << endl;
    }

    void deleteHighest() {
        if (nMax == 0) {
            cout << "No jobs available.\n";
            return;
        }

        int high = maxHeap[1];
        cout << "Deleted job with highest priority: " << high << endl;

        // Remove root and reheapify (iterative)
        maxHeap[1] = maxHeap[nMax--];
        int i = 1;
        while (true) {
            int left = 2 * i, right = 2 * i + 1, largest = i;
            if (left <= nMax && maxHeap[left] > maxHeap[largest])
                largest = left;
            if (right <= nMax && maxHeap[right] > maxHeap[largest])
                largest = right;
            if (largest != i) {
                swap(maxHeap[i], maxHeap[largest]);
                i = largest;
            } else
                break;
        }

        // Also remove from jobs array
        for (int j = 0; j < total; j++) {
            if (jobs[j] == high) {
                for (int k = j; k < total - 1; k++)
                    jobs[k] = jobs[k + 1];
                total--;
                break;
            }
        }
    }

    void displayJobs() {
        if (total == 0) {
            cout << "No jobs available.\n";
            return;
        }

        // Sort jobs array in descending order
        for (int i = 0; i < total - 1; i++) {
            for (int j = i + 1; j < total; j++) {
                if (jobs[i] < jobs[j])
                    swap(jobs[i], jobs[j]);
            }
        }

        cout << "Jobs in descending order of priority: ";
        for (int i = 0; i < total; i++)
            cout << jobs[i] << " ";
        cout << endl;
    }
};

int main() {
    JobHeap job;
    int choice, priority;

    do {
        cout << "\n----- JOB PRIORITY MENU -----\n";
        cout << "1. Insert new job with priority\n";
        cout << "2. Display highest and lowest priority jobs\n";
        cout << "3. Delete job with highest priority\n";
        cout << "4. Display all jobs (sorted)\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter job priority: ";
                cin >> priority;
                job.insertJob(priority);
                break;

            case 2:
                job.showPriority();
                break;

            case 3:
                job.deleteHighest();
                break;

            case 4:
                job.displayJobs();
                break;

            case 5:
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid choice.\n";
        }
    } while (choice != 5);

    return 0;
}

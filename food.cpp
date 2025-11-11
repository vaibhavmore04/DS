#include <bits/stdc++.h>
using namespace std;

struct Package {
    int benefit;   // importance or value
    int weight;
    int index;     // package number
};

// Comparator function to sort packages by benefit/weight ratio (descending order)
bool cmp(Package a, Package b) {
    double r1 = (double)a.benefit / a.weight;
    double r2 = (double)b.benefit / b.weight;
    return r1 > r2;
}

double fractionalKnapsack(int capacity, Package arr[], int n) {
    sort(arr, arr + n, cmp); // sort by ratio

    double totalBenefit = 0.0;
    int totalWeightUsed = 0;

    cout << "\nSelected Packages:\n";
    cout << "------------------------------------\n";
    cout << "Package\tWeight\tBenefit\tFraction\n";

    for (int i = 0; i < n; i++) {
        if (arr[i].weight <= capacity) {
            // Take the whole package
            capacity -= arr[i].weight;
            totalBenefit += arr[i].benefit;
            totalWeightUsed += arr[i].weight;
            cout << arr[i].index << "\t" << arr[i].weight << "\t" << arr[i].benefit << "\t1.0\n";
        } 
        else {
            // Take a fraction of the package
            double fraction = (double)capacity / arr[i].weight;
            totalBenefit += arr[i].benefit * fraction;
            totalWeightUsed += capacity;
            cout << arr[i].index << "\t" << arr[i].weight << "\t" << arr[i].benefit << "\t" << fixed << setprecision(2) << fraction << "\n";
            break; // truck is full
        }
    }

    cout << "------------------------------------\n";
    cout << "Total Truck Weight Used: " << totalWeightUsed << endl;
    cout << "Total Benefit Obtained: " << totalBenefit << endl;

    return totalBenefit;
}

int main() {
    int n, capacity;
    cout << "Enter number of packages: ";
    cin >> n;

    cout << "Enter truck capacity: ";
    cin >> capacity;

    Package arr[100];
    for (int i = 0; i < n; i++) {
        cout << "Enter weight and benefit of package " << (i + 1) << ": ";
        cin >> arr[i].weight >> arr[i].benefit;
        arr[i].index = i + 1;
    }

    fractionalKnapsack(capacity, arr, n);

    return 0;
}
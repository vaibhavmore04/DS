
#include <iostream>
using namespace std;

struct Item {
    int weight;
    int profit;
    double ratio;
};

// Sorting by Profit/Weight ratio
void sortItemsByRatio(Item items[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (items[j].ratio > items[i].ratio) {
                Item temp = items[i];
                items[i] = items[j];
                items[j] = temp;
            }
        }
    }
}

// Sorting by Profit
void sortItemsByProfit(Item items[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (items[j].profit > items[i].profit) {
                Item temp = items[i];
                items[i] = items[j];
                items[j] = temp;
            }
        }
    }
}

// Sorting by Weight
void sortItemsByWeight(Item items[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (items[j].weight < items[i].weight) {
                Item temp = items[i];
                items[i] = items[j];
                items[j] = temp;
            }
        }
    }
}

int main() {
    int n, capacity, choice;

    cout << "Enter number of items: ";
    cin >> n;

    Item items[n];
    cout << "Enter weight and profit of each item:\n";
    for (int i = 0; i < n; i++) {
        cin >> items[i].weight >> items[i].profit;
        items[i].ratio = (double)items[i].profit / items[i].weight;
    }

    cout << "Enter capacity of knapsack: ";
    cin >> capacity;

    while (true) {
        cout << "\nSelect the method for knapsack problem:\n";
        cout << "1. Max Profit (Sort by Profit)\n";
        cout << "2. Min Weight (Sort by Weight)\n";
        cout << "3. Profit/Weight Ratio (Sort by Ratio)\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                sortItemsByProfit(items, n);
                cout << "\nMethod used: Max Profit First\n";
                break;
            case 2:
                sortItemsByWeight(items, n);
                cout << "\nMethod used: Min Weight First\n";
                break;
            case 3:
                sortItemsByRatio(items, n);
                cout << "\nMethod used: Max Profit/Weight Ratio First\n";
                break;
            case 4:
                cout << "Exiting...\n";
                return 0;
            default:
                cout << "Invalid choice! Please try again.\n";
                continue;
        }

        double totalProfit = 0.0;
        int currentWeight = 0;

        cout << "----------------------------------------------------------\n";
        cout << "Item\tWeight\tProfit\tProfit/Weight\tTaken Weight\tProfit Earned\n";
        cout << "----------------------------------------------------------\n";

        for (int i = 0; i < n; i++) {
            if (currentWeight + items[i].weight <= capacity) {
                currentWeight += items[i].weight;
                totalProfit += items[i].profit;
                cout << "Item " << i + 1 << "\t"
                     << items[i].weight << "\t"
                     << items[i].profit << "\t"
                     << items[i].ratio << "\t\t"
                     << items[i].weight << "\t\t"
                     << items[i].profit << endl;
            } else {
                int remain = capacity - currentWeight;
                totalProfit += items[i].ratio * remain;
                cout << "Item " << i + 1 << "\t"
                     << items[i].weight << "\t"
                     << items[i].profit << "\t"
                     << items[i].ratio << "\t\t"
                     << remain << "\t\t"
                     << items[i].ratio * remain << endl;
                break;
            }
        }

        cout << "----------------------------------------------------------\n";
        cout << "\nMaximum profit is: " << totalProfit << endl;
    }

    return 0;
}


/*Enter number of items: 3
Enter weight and profit of each item:
10 60
20 100
30 120
Enter capacity of knapsack: 50

Select the method for knapsack problem:
1. Max Profit (Sort by Profit)
2. Min Weight (Sort by Weight)
3. Profit/Weight Ratio (Sort by Ratio)
4. Exit
Enter your choice: 3

Method used: Max Profit/Weight Ratio First
----------------------------------------------------------
Item    Weight  Profit  Profit/Weight   Taken Weight   Profit Earned
----------------------------------------------------------
Item 1  10      60      6               10             60
Item 2  20      100     5               20             100
Item 3  30      120     4               20             80
----------------------------------------------------------

Maximum profit is: 240
*/
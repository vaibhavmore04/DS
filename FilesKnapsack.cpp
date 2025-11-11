#include <iostream>
using namespace std;

int main()
{
    int n, S;
    cout << "Enter number of files: ";
    cin >> n;
    cout << "Enter total storage capacity (in GB): ";
    cin >> S;

    int size[100], importance[100];

    for (int i = 0; i < n; i++)
    {
        cout << "Enter size (in GB) and importance of file " << (i + 1) << ": ";
        cin >> size[i] >> importance[i];
    }

    int dp[101][1001]; // dp[i][s] → max importance using first i files and capacity s

    // Step 1: Build DP Table
    for (int i = 0; i <= n; i++)
    {
        for (int s = 0; s <= S; s++)
        {
            if (i == 0 || s == 0)
                dp[i][s] = 0;
            else if (size[i - 1] <= s)
                dp[i][s] = max(dp[i - 1][s], dp[i - 1][s - size[i - 1]] + importance[i - 1]);
            else
                dp[i][s] = dp[i - 1][s];
        }
    }

    cout << "\nMaximum Total Importance = " << dp[n][S] << endl;

    // Step 2: Backtrack to find selected files
    int totalSize = 0;
    cout << "\nFiles selected: ";
    int w = S;
    for (int i = n; i > 0 && w > 0; i--)
    {
        if (dp[i][w] != dp[i - 1][w])
        {
            cout << "File" << i << " ";
            totalSize += size[i - 1];
            w -= size[i - 1];
        }
    }

    cout << "\nTotal size used = " << totalSize << " GB" << endl;

    // Optional: Print DP table (for understanding)
    cout << "\nDP Table:\n";
    for (int i = 0; i <= n; i++)
    {
        for (int s = 0; s <= S; s++)
        {
            cout << dp[i][s] << "\t";
        }
        cout << endl;
    }

    return 0;
}
/*
Line-by-line explanation

#include <iostream>

Brings in standard I/O functions (cin, cout).

using namespace std;

Avoids writing std:: before cin/cout.

int main() { ... }

Program entry point.

int n, S;

n = number of files (items).

S = total storage capacity in GB (knapsack capacity).

cout << "Enter number of files: "; cin >> n;

Prompt and read number of files.

cout << "Enter total storage capacity (in GB): "; cin >> S;

Prompt and read capacity.

int size[100], importance[100];

Arrays to hold each file’s size and importance. (100 is a safe fixed upper bound in this program.)

for (int i = 0; i < n; i++) { ... cin >> size[i] >> importance[i]; }

For each file i (0-based), read size[i] and importance[i].

Example prompt: Enter size (in GB) and importance of file 1: 2 100

int dp[101][1001];

DP table: dp[i][s] = maximum importance achievable using the first i files with capacity s.

We allocate 101 x 1001 to support up to 100 items and capacity up to 1000 (adjust if needed).

for (int i = 0; i <= n; i++) { for (int s = 0; s <= S; s++) { ... } }

Fill the DP table row by row.

i iterates from 0..n (0 means “no items considered”).

s iterates all capacities from 0..S.

if (i == 0 || s == 0) dp[i][s] = 0;

Base cases:

With 0 items or 0 capacity, maximum importance is 0.

else if (size[i - 1] <= s) dp[i][s] = max(dp[i - 1][s], dp[i - 1][s - size[i - 1]] + importance[i - 1]);

If the i-th file (index i-1) fits in current capacity s:

Option A: skip it → dp[i-1][s].

Option B: take it → dp[i-1][s - size[i-1]] + importance[i-1].

Choose the better of the two.

else dp[i][s] = dp[i - 1][s];

If file i doesn’t fit (size[i-1] > s), we must skip it.

cout << "\n📦 Maximum Total Importance = " << dp[n][S] << endl;

After filling, dp[n][S] is the optimal importance score.

Backtracking to find selected files:

int totalSize = 0;
cout << "\n🗂️ Files selected: ";
int w = S;
for (int i = n; i > 0 && w > 0; i--) {
    if (dp[i][w] != dp[i - 1][w]) {
        cout << "File" << i << " ";
        totalSize += size[i - 1];
        w -= size[i - 1];
    }
}


Start with capacity w = S and iterate i from n down to 1.

If dp[i][w] != dp[i-1][w], it means item i was included in the optimal solution for capacity w.

Print File i, add its size to totalSize, and reduce w by that size to continue backtracking.

This recovers the chosen files.

cout << "\n💾 Total size used = " << totalSize << " GB" << endl;

Print total storage used by selected files.

Optional printing of the whole DP table (helps visualize):

for (int i = 0; i <= n; i++) {
    for (int s = 0; s <= S; s++) cout << dp[i][s] << "\t";
    cout << endl;
}


return 0; — normal program termination.

Concrete example (step-by-step)

Use this sample input (common example):

n = 3
S = 5
Files:
1) size = 1, importance = 60
2) size = 2, importance = 100
3) size = 3, importance = 120

Fill DP table explanation

We build dp rows i=0..3 and columns s=0..5.

Row i=0: all zeros (no items).

Row i=1 (only file1 available, size=1, imp=60):

s=0 → dp[1][0]=0

s=1 → can take file1 → max( dp[0][1]=0, dp[0][0]+60=60 ) = 60

s=2..5 → can still only take file1 (no other items) → dp[1][s] = 60

Row i=2 (files 1..2 available; file2 size=2, imp=100):

s=0 → 0

s=1 → file2 doesn't fit (2>1) → dp[2][1] = dp[1][1] = 60

s=2 → file2 fits:

skip: dp[1][2] = 60

take: dp[1][2-2] + 100 = dp[1][0] + 100 = 100 → choose 100
→ dp[2][2] = 100

s=3 → file2 fits:

skip: dp[1][3] = 60

take: dp[1][1] + 100 = 60 + 100 = 160 -> choose 160
→ dp[2][3] = 160

s=4: take → dp[1][2]+100 = 60+100=160 -> dp[2][4]=160

s=5: dp[2][5]=160

Row i=3 (files 1..3; file3 size=3, imp=120):

s=0 → 0

s=1 → dp[3][1]=dp[2][1]=60

s=2 → dp[3][2]=dp[2][2]=100

s=3 → file3 fits:

skip: dp[2][3]=160

take: dp[2][0]+120=120
→ choose 160 (skip) → dp[3][3]=160

s=4 → file3 fits:

skip: dp[2][4]=160

take: dp[2][1]+120 = 60+120=180 -> choose 180 → dp[3][4]=180

s=5 → file3 fits:

skip: dp[2][5]=160

take: dp[2][2]+120 = 100+120=220 -> choose 220 → dp[3][5]=220

So final answer: dp[3][5] = 220.

DP table (rows i, columns s=0..5)
i\s:   0   1   2    3    4    5
--------------------------------
0      0   0   0    0    0    0
1      0  60  60   60   60   60
2      0  60 100  160  160  160
3      0  60 100  160  180  220

Backtracking (to identify which files)

Start with w = S = 5, i = 3:

dp[3][5] = 220 vs dp[2][5] = 160 → different ⇒ file 3 included.

Print File3, totalSize += size[2] (3), w = 5 - 3 = 2.

Now i = 2, w = 2: compare dp[2][2] = 100 vs dp[1][2] = 60 → different ⇒ file 2 included.

Print File2, totalSize += size[1] (2), w = 2 - 2 = 0.

w is now 0 so stop.

Selected files: File3 and File2. Total size = 3 + 2 = 5 GB. Total importance = 220.

Time & Space Complexity

Time complexity: O(n × S) — two nested loops filling dp table of size (n+1) × (S+1).

Space complexity: O(n × S) for the dp table. (You can optimize space to O(S) with a 1D array and backward iteration if you only need the max value, but backtracking selected items becomes harder.)
*/
#include<bits/stdc++.h>
using namespace std;

class heap{
public:
    vector<int> maxheap = {0};   // 1-indexed
    vector<int> minheap = {0};   // 1-indexed
    int nmax;
    int nmin;

    heap(){
        nmax = 0;
        nmin = 0;
    }

    void insertmax(int &n,int data);
    void insertmin(int &n,int data);
    void reheapupmax(int n);
    void reheapdownmax(int i,int n);
    void reheapupmin(int n);
    void reheapdownmin(int i,int n);
    void deletemax(int n);  // now uses COPY of n
    void deletemin(int n);  // now uses COPY of n
    void asc();
    void desc();
};

//---------------- INSERT MAX ----------------
void heap::insertmax(int &n,int data){
    maxheap.push_back(data);
    n++;
    reheapupmax(n);
}

//---------------- REHEAP UP (MAX) ------------
void heap::reheapupmax(int n){
    while(n > 1){
        int parent = n/2;
        if(maxheap[parent] < maxheap[n]){
            swap(maxheap[parent], maxheap[n]);
            n = parent;
        } else return;
    }
}

//---------------- INSERT MIN ----------------
void heap::insertmin(int &n,int data){
    minheap.push_back(data);
    n++;
    reheapupmin(n);
}

//---------------- REHEAP UP (MIN) ------------
void heap::reheapupmin(int n){
    while(n > 1){
        int parent = n/2;
        if(minheap[parent] > minheap[n]){
            swap(minheap[parent], minheap[n]);
            n = parent;
        } else return;
    }
}

//---------------- REHEAP DOWN (MAX) ----------
void heap::reheapdownmax(int i,int n){
    while(i <= n){
        int lc = 2*i, rc = 2*i+1, largest = i;

        if(lc <= n && maxheap[lc] > maxheap[largest]) largest = lc;
        if(rc <= n && maxheap[rc] > maxheap[largest]) largest = rc;

        if(largest != i){
            swap(maxheap[i], maxheap[largest]);
            i = largest;
        } else return;
    }
}

//---------------- REHEAP DOWN (MIN) ----------
void heap::reheapdownmin(int i,int n){
    while(i <= n){
        int lc = 2*i, rc = 2*i+1, smallest = i;

        if(lc <= n && minheap[lc] < minheap[smallest]) smallest = lc;
        if(rc <= n && minheap[rc] < minheap[smallest]) smallest = rc;

        if(smallest != i){
            swap(minheap[i], minheap[smallest]);
            i = smallest;
        } else return;
    }
}

//---------------- HEAPSORT USING TEMP SIZE (MAX -> ASC) ----------
void heap::deletemax(int n){   // using copied n (heap remains intact!)
    while(n > 1){
        swap(maxheap[1], maxheap[n]);
        n--;
        reheapdownmax(1, n);
    }
}

//---------------- HEAPSORT USING TEMP SIZE (MIN -> DESC) ----------
void heap::deletemin(int n){   // using copied n (heap remains intact!)
    while(n > 1){
        swap(minheap[1], minheap[n]);
        n--;
        reheapdownmin(1, n);
    }
}

//---------------- DISPLAY ASCENDING -----------
void heap::asc(){
    int tempn = nmax;
    deletemax(tempn);  // sort copy
    for(int i = 1; i <= nmax; i++)
        cout << maxheap[i] << " ";
    cout << endl;
}


//---------------- DISPLAY DESCENDING ----------
void heap::desc(){
    int tempn = nmin;
    deletemin(tempn); // sort copy
    for(int i = 1; i <= nmin; i++)
        cout << minheap[i] << " ";
    cout << endl;
}

//---------------- MENU ----------------
int main(){
    heap h;
    int choice, data;

    while(true){
        cout << "\n----- MENU -----\n";
        cout << "1. Insert into Max Heap\n";
        cout << "2. Insert into Min Heap\n";
        cout << "3. Display Asc (Max Heap Sorted)\n";
        cout << "4. Display Desc (Min Heap Sorted)\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice){
            case 1:
                cout << "Enter element: ";
                cin >> data;
                h.insertmax(h.nmax, data);
                break;

            case 2:
                cout << "Enter element: ";
                cin >> data;
                h.insertmin(h.nmin, data);
                break;

            case 3:
                h.asc();
                break;

            case 4:
                h.desc();
                break;

            case 5:
                return 0;

            default:
                cout << "Invalid choice.\n";
        }
    }
}
/*
Nice program — clean and educational. I’ll walk through it line-by-line, explain what each part does, and then show a concrete example (inserting some marks and showing asc() / desc() outputs). I’ll finish with a short algorithm analysis (time/space complexity and important notes).

1) Header + using
#include<bits/stdc++.h>
using namespace std;


#include <bits/stdc++.h> pulls in most standard headers (convenient for competitive/learning code).

using namespace std; avoids writing std:: everywhere.

2) Class declaration: fields & constructor
class heap{
public:
    vector<int> maxheap = {0};   // 1-indexed
    vector<int> minheap = {0};   // 1-indexed
    int nmax;
    int nmin;

    heap(){
        nmax = 0;
        nmin = 0;
    }

    // method declarations...
};


Two vectors store heaps: maxheap for the max-heap and minheap for the min-heap.

Both vectors are initialized with one element {0} so the heaps are 1-indexed (root at index 1).

nmax and nmin track the number of elements in each heap.

Default constructor sets both counts to 0.

3) Method declarations

The class declares functions for:

insertion (insertmax, insertmin)

reheap/up and reheap/down for both heaps

deletemax and deletemin which perform heap-sort on a copied size

asc() and desc() to print sorted orders

4) insertmax
void heap::insertmax(int &n,int data){
    maxheap.push_back(data);
    n++;
    reheapupmax(n);
}


Appends data to maxheap.

Increments the passed-in size n (you pass h.nmax so the class field is updated).

Calls reheapupmax(n) to restore the max-heap property by moving the newly inserted element up.

5) reheapupmax (restore max-heap by moving upward)
void heap::reheapupmax(int n){
    while(n > 1){
        int parent = n/2;
        if(maxheap[parent] < maxheap[n]){
            swap(maxheap[parent], maxheap[n]);
            n = parent;
        } else return;
    }
}


While node is not root, compare with parent.

If child > parent, swap (bubble up) and continue.

Stops when heap property satisfied or root reached.

This is the standard insertion fix-up for max-heap. Complexity O(log n).

6) insertmin & reheapupmin (mirror for min-heap)
void heap::insertmin(int &n,int data){
    minheap.push_back(data);
    n++;
    reheapupmin(n);
}

void heap::reheapupmin(int n){
    while(n > 1){
        int parent = n/2;
        if(minheap[parent] > minheap[n]){
            swap(minheap[parent], minheap[n]);
            n = parent;
        } else return;
    }
}


Same idea but for min-heap: bubble up when child < parent.

7) reheapdownmax (restore max-heap by moving down)
void heap::reheapdownmax(int i,int n){
    while(i <= n){
        int lc = 2*i, rc = 2*i+1, largest = i;

        if(lc <= n && maxheap[lc] > maxheap[largest]) largest = lc;
        if(rc <= n && maxheap[rc] > maxheap[largest]) largest = rc;

        if(largest != i){
            swap(maxheap[i], maxheap[largest]);
            i = largest;
        } else return;
    }
}


At index i, find the largest among i, left child, right child.

If a child is larger, swap and continue downwards.

This is used after removing (or swapping) the root to restore heap property. Complexity O(log n).

8) reheapdownmin (mirror for min-heap)
void heap::reheapdownmin(int i,int n){
    while(i <= n){
        int lc = 2*i, rc = 2*i+1, smallest = i;

        if(lc <= n && minheap[lc] < minheap[smallest]) smallest = lc;
        if(rc <= n && minheap[rc] < minheap[smallest]) smallest = rc;

        if(smallest != i){
            swap(minheap[i], minheap[smallest]);
            i = smallest;
        } else return;
    }
}


Standard down-heap for min-heap.

9) deletemax — heapsort on a COPY of size
void heap::deletemax(int n){   // using copied n (heap remains intact!)
    while(n > 1){
        swap(maxheap[1], maxheap[n]);
        n--;
        reheapdownmax(1, n);
    }
}


This performs the classic in-place heap sort using the max-heap array:

Swap root (max) with last element of the current heap.

Decrease effective heap size (n--).

Reheap down from root to reestablish max-heap on the reduced prefix.

Important: parameter n is passed by value, so you sort only the prefix implied by that copy. The maxheap array contents become sorted ascending within positions 1..nmax, but nmax remains unchanged outside the function — actual heap metadata stays intact from caller perspective.

10) deletemin — heapsort (min-heap -> descending)
void heap::deletemin(int n){   // using copied n (heap remains intact!)
    while(n > 1){
        swap(minheap[1], minheap[n]);
        n--;
        reheapdownmin(1, n);
    }
}


Same idea for min-heap; after this, positions 1..nmin in minheap are sorted in descending order.

11) asc() — print ascending order from maxheap
void heap::asc(){
    int tempn = nmax;
    deletemax(tempn);  // sort copy
    for(int i = 1; i <= nmax; i++)
        cout << maxheap[i] << " ";
    cout << endl;
}


Copies current size into tempn.

Calls deletemax(tempn) so the array prefix 1..nmax becomes sorted ascending.

Prints elements from 1 to nmax (ascending order).

Because deletemax used a copy of n, nmax (the class field) and the logical heap structure remains unchanged with regard to nmax value — but note the actual maxheap[] vector content is rearranged to sorted order inside the function call. (The comment says “heap remains intact!” meaning counts remain, but the array elements are permuted.)

12) desc() — print descending order from minheap
void heap::desc(){
    int tempn = nmin;
    deletemin(tempn); // sort copy
    for(int i = 1; i <= nmin; i++)
        cout << minheap[i] << " ";
    cout << endl;
}


Same logic for minheap, printing descending list of elements.

13) Menu (main)
int main(){
    heap h;
    int choice, data;

    while(true){
        cout << "\n----- MENU -----\n";
        cout << "1. Insert into Max Heap\n";
        cout << "2. Insert into Min Heap\n";
        cout << "3. Display Asc (Max Heap Sorted)\n";
        cout << "4. Display Desc (Min Heap Sorted)\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice){
            case 1:
                cout << "Enter element: ";
                cin >> data;
                h.insertmax(h.nmax, data);
                break;

            case 2:
                cout << "Enter element: ";
                cin >> data;
                h.insertmin(h.nmin, data);
                break;

            case 3:
                h.asc();
                break;

            case 4:
                h.desc();
                break;

            case 5:
                return 0;

            default:
                cout << "Invalid choice.\n";
        }
    }
}


Repeated menu loop:

Option 1: insert into max-heap (h.insertmax(h.nmax, data);) — h.nmax is passed by reference so it updates the object's nmax.

Option 2: insert into min-heap.

Option 3: print ascending order from max-heap.

Option 4: print descending order from min-heap.

Option 5: exit.

Example (concrete walkthrough)

Suppose teacher enters marks: 50, 30, 20, 10, 15 into the max-heap (option 1 five times). We will also enter the same values into min-heap for demonstration.

Insert sequence into max-heap (brief):

Insert 50: maxheap = [0,50], nmax=1

Insert 30: maxheap = [0,50,30], nmax=2 (30 < 50 → no swap)

Insert 20: maxheap = [0,50,30,20], nmax=3

Insert 10: maxheap = [0,50,30,20,10], nmax=4

Insert 15: maxheap = [0,50,30,20,10,15], nmax=5
(after reheap ups the structure remains a valid max-heap with root 50)

Call h.asc():

tempn = 5

deletemax(5) performs:

swap maxheap[1] (50) with maxheap[5] (15): array becomes [0,15,30,20,10,50] and n=4

reheapdownmax(1,4) -> root 15 swaps with 30 -> [0,30,15,20,10,50] then further fix so prefix 1..4 is a max-heap

next swap root with position 4, n=3, reheapdown, and so on...

After loop, elements in positions 1..5 will be: 10 15 20 30 50 (ascending).

asc() prints: 10 15 20 30 50

If you inserted the same values into minheap and call desc() you’ll get 50 30 20 15 10.

Note: After asc() the values in maxheap will be permuted to ascending — the numerical content at indexes changed. The nmax integer value remains unchanged.

Algorithm Analysis

Operations & complexity

insertmax / insertmin: O(log n) per insert (due to reheapup).

reheapdown used in deletemax/deletemin: O(log n) each call.

deletemax(tempn) performs ≈ n swaps + n reheapdowns → overall O(n log n) (this is heap sort).

asc() and desc() therefore cost O(n log n) to sort + O(n) to print.

Space: O(n) for the arrays (vectors). Extra space negligible because sort is in-place.

Correctness notes / subtle points

Vectors are 1-indexed by introducing a dummy 0 element at index 0 — so valid child/parent arithmetic is left = 2*i, parent = i/2.

deletemax and deletemin take n by value — the caller’s nmax / nmin values are not changed. However the vector contents are rearranged to a sorted order in-place; if you need to preserve the original heap order (structure), you would need to copy the entire vector before heapsort.

The comment // using copied n (heap remains intact!) is slightly misleading: the numeric n remains but the array gets permuted. If you want both n and the heap array unchanged, copy the vector too.

Possible improvement

If you want asc() to not disturb maxheap array at all, do:

vector<int> tmp = maxheap;
int tmpn = nmax;
// perform deletemax on tmp using tmpn (adapt functions or write an overload)


or implement a non-destructive extraction (pop max repeatedly into a separate output vector)

Complexity Analysis of the Heap Program

The heap operations in your program are standard — and their complexity depends mainly on the height of the heap.
For a heap with n elements, the height is O(log n).

Let’s break it down operation by operation 👇

🟢 1. Insertion (insertmax, insertmin)
maxheap.push_back(data);
reheapupmax(n);

➤ Explanation:

Appending an element → O(1)

reheapup (bubble-up) swaps with parent nodes until heap property restored → at most height of heap times → O(log n)

✅ Time Complexity:

O(log n) per insertion

✅ Space Complexity:

O(1) extra (uses same heap array)

🟣 2. Reheap Down (reheapdownmax, reheapdownmin)

Used after deletion or during sorting.

➤ Explanation:

Each swap moves the element one level down the heap.
Maximum number of levels = height = log n.

✅ Time Complexity:

O(log n)

✅ Space Complexity:

O(1) (in-place swaps, no extra storage)

🔵 3. DeleteMax / DeleteMin (Heapsort Logic)
void heap::deletemax(int n){
    while(n > 1){
        swap(maxheap[1], maxheap[n]);
        n--;
        reheapdownmax(1, n);
    }
}

➤ Explanation:

Loop runs (n − 1) times.

Each loop iteration does one swap (O(1)) and one reheapdownmax (O(log n)).

✅ Time Complexity:

O(n × log n)

(because n times each O(log n))

✅ Space Complexity:

O(1) extra (sort done in-place in same heap array)

🟠 4. asc() / desc() Functions
void heap::asc(){
    int tempn = nmax;
    deletemax(tempn);
    for(int i = 1; i <= nmax; i++)
        cout << maxheap[i] << " ";
}

➤ Explanation:

Calls deletemax() → O(n log n)

Then prints all elements → O(n)

✅ Total Time Complexity:

O(n log n + n) ≈ O(n log n)

✅ Space Complexity:

O(1) (no new heap created — uses same one)

🧮 5. Overall Complexity Summary Table
Operation	Description	Time Complexity	Space Complexity
insertmax() / insertmin()	Insert one element	O(log n)	O(1)
reheapup / reheapdown	Adjust heap	O(log n)	O(1)
deletemax() / deletemin()	Heap sort	O(n log n)	O(1)
asc() / desc()	Sort + Display	O(n log n)	O(1)
Overall Program	Building + Sorting Heaps	O(n log n)	O(n) (heap storage)
🧠 Intuitive Understanding

Building the heap (inserting all n elements one by one) → n × O(log n) = O(n log n)

Sorting (heap sort) → O(n log n)

Hence, the entire program (insert + sort) is O(n log n) time, and it uses O(n) space to store marks.

💡 Example Recap

If the teacher enters 5 marks:
50, 30, 20, 10, 15

Operation	Work Done	Time (roughly)
5 insertions	5 × log 5 ≈ 12 comparisons	O(log n) each
Sorting (asc)	5 × log 5 ≈ 12 more	O(n log n)
Printing	5 prints	O(n)

So, total operations ≈ 24 comparisons/swaps → very efficient even for large n.

🏁 Final Summary

✅ Time Complexity:

Build heap: O(n log n)

Sort (deletemax / deletemin): O(n log n)

Overall: O(n log n)

✅ Space Complexity:

Heap storage: O(n)

Extra temporary space: O(1) (in-place sorting)
*/
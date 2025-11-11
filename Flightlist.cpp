#include <iostream>
#include <string>
using namespace std;

int adj[10][10];

class node{
public:
    string city;
    int cost;
    node* next;

    node(){
        cost = 0;
        next = NULL;
    }
};    

class graph{
public:
    node* head[5];
    int n;

    graph(){
        n = 0;
        for(int i = 0; i < 5; i++){
            head[i] = NULL;
        }
    }

    void create();
    void addedge(int u, int v, int cost);
    void display();
    bool isconnected(int u,int v);
};

void graph::create(){
    cout<<"Enter number of cities(max 5): ";
    cin>>n;
    cin.ignore();

    // Initialize adjacency matrix
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            adj[i][j] = 0;
        }
    }                  

    cout<<"Enter city names:\n";
    for(int i=0;i<n;i++){
        string cityname;
        cout<<"City "<<i+1<<": ";
        getline(cin,cityname);

        node* newnode = new node();
        newnode->city = cityname;
        head[i] = newnode;
    }
}

void graph::addedge(int u, int v, int cost){
    // Add v to u’s adjacency list
    node* newnode = new node();
    newnode->city = head[v]->city;
    newnode->cost = cost;

    node* temp = head[u];
    while(temp->next != NULL){
        temp = temp->next;
    }
    temp->next = newnode;

    // Directed graph: Only one direction
    adj[u][v] = cost;
}

void graph::display(){
    cout<<"\nAdjacency List Representation:\n";
    for(int i=0;i<n;i++){
        node* temp = head[i];
        cout<<temp->city<<" -> ";
        temp = temp->next;

        while(temp != NULL){
            cout<<temp->city<<"("<<temp->cost<<") -> ";
            temp = temp->next;
        }
        cout<<"NULL\n";
    }

    cout<<"\nAdjacency Matrix Representation:\n  ";
    for(int i=0;i<n;i++){
        cout<<head[i]->city<<" ";
    }
    cout<<endl;

    for(int i=0;i<n;i++){
        cout<<head[i]->city<<" ";
        for(int j=0;j<n;j++){
            cout<<adj[i][j]<<" ";
        }
        cout<<endl;
    }
}

bool graph::isconnected(int u,int v){
    return adj[u][v] != 0;
}

int main(){
    graph g;
    g.create();
    int choice;

    do{
        cout<<"\nMenu:\n1. Add Flight Path\n2. Display Graph\n3. Check Connection\n4. Exit\nEnter your choice: ";
        cin>>choice;

        switch(choice){
            case 1:{
                int u,v,cost;
                cout<<"Enter source city index (0 to "<<g.n-1<<"): ";
                cin>>u;
                cout<<"Enter destination city index (0 to "<<g.n-1<<"): ";
                cin>>v;
                cout<<"Enter cost (time/fuel): ";
                cin>>cost;
                g.addedge(u,v,cost);
                break;
            }
            case 2:
                g.display();
                break;

            case 3:{
                int u,v;
                cout<<"Enter source city index (0 to "<<g.n-1<<"): ";
                cin>>u;
                cout<<"Enter destination city index (0 to "<<g.n-1<<"): ";
                cin>>v;
                if(g.isconnected(u,v))
                    cout<<"Cities are connected through a flight path.\n";
                else
                    cout<<"No direct flight path exists.\n";
                break;
            }

            case 4:
                cout<<"Exiting...\n";
                break;

            default:
                cout<<"Invalid choice. Try again.\n";
        }
    }while(choice != 4);

    return 0;
}
#include <bits/stdc++.h>
using namespace std;


/*
    Iterative-Deepening Search

    *IDS combines advantages of both DFS and BFS
    *BFS maintains queue resulting in high memory consumption, but IDS don't require extra queue
    *Takes less time due to memory reusage

*/

/*
INPUT:
     6
     6
     1 2
     1 3
     2 4
     2 5
     3 6
     3 7
     6
     2
*/

/*

 OUTPUT:
                        IDS
Number of edges: 6
Number of vertices: 6
Enter the edges: 1st, 2nd = 1 2
Enter the edges: 1st, 2nd = 1 3
Enter the edges: 1st, 2nd = 2 4
Enter the edges: 1st, 2nd = 2 5
Enter the edges: 1st, 2nd = 3 6
Enter the edges: 1st, 2nd = 3 7
Enter the goal: 6
Level 0:  1->
Level 1:  1-> 2-> 3->
Level 2:  1-> 2-> 4-> 5-> 3->6
*/
int goal,X,Y;
int visited[100];


vector<vector<int> >a(100); // adjacency list

bool IDS(int p, int limit)
{

    if(p+1 == goal){
    cout << p+1 << endl;
    return true;
    // returns true if goal found
    }
     int q;
    if(visited[p] == 0){
    visited[p]=1;
    printf(" %d->",p+1); // new node visited and printed in output
    }
    if(limit > 0){  // if limit = 0, get back
    for(q=0; q<a[p].size(); q++)
    {
        int k = a[p][q];

        if(visited[k]==0){
           if( IDS(k, limit-1)) // if goal is found return true
            return true;
        }
    }
    }

   return false; // if goal is not found return false

}
int main()
{
    int p,q,x1,x2;
    cout << "\t\t\tIDS\n";
    cout << "Number of edges: ";
    cin >> Y;
    cout << "Number of vertices: ";
    cin >>X;

    //creating edges :
    for(p=0; p<Y; p++)
    {
        cout << "Enter the edges: 1st, 2nd = ";
        cin >> x1 >> x2;

        a[x1-1].push_back(x2-1);
        a[x2-1].push_back(x1-1); // for each node, adjacent nodes are listed
    }

    cout << "Enter the goal: ";
    cin >> goal;

    for(int i=0; ;i++){ // iteration continues until node found
            for(int j=0;j<20;j++){
                visited[j] = 0; // visit array cleared after each iteration
            }
        cout << "Level " << i << ": ";
       if(IDS(0, i)){
        break; // won't iterate any more levels if goal found
       }

       cout << endl;
    }
    return 0;
}

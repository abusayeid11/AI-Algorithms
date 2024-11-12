#include <bits/stdc++.h>
using namespace std;

/*
  Depth-Limited Search VS Depth-First Search

  * Same as DFS with limitation on level
  * DFS can stuck into endless loop, DLS solves this problem
  * More efficient in time and memory usage

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
Number of edges: 6
Number of vertices: 6
Enter edge: 1st, 2nd = 1 2
Enter edge: 1st, 2nd = 1 3
Enter edge: 1st, 2nd = 2 4
Enter edge: 1st, 2nd = 2 5
Enter edge: 1st, 2nd = 3 6
Enter edge: 1st, 2nd = 3 7
Enter the goal: 6
Enter limit: 2
 1-> 2-> 4-> 5-> 3-> 6
*/


int goal,X,Y;

int visited[100];
bool check = false;

vector<vector<int> >a(100); // adjacency list

void DLS(int p, int limit)
{

    if(p+1 == goal){
    cout << " " << p+1 << endl;
    check = true;
    // DLS ends after reaching goal
    }

   if(!check){ // goal not found
     int q;
    if(visited[p] == 0){
    visited[p]=1;
    printf(" %d->",p+1);// new node visited and printed in output
    }

    if(limit > 0){ // if limit ends get back
    for(q=0; q<a[p].size(); q++)
     {
        int k = a[p][q];

        if(visited[k]==0)
            DLS(k, limit-1); // going into next level, limit reduces
      }
    }
   }

}
int main()
{
    int p,q,x1,x2;
    cout << "\t\t\tDLS\n";
    cout << "Number of edges: ";
    cin >> Y;
    cout << "Number of vertices: ";
    cin >>X;

    //making edges :
    for(p=0; p<Y; p++)
    {
        cout << "Enter edge: 1st, 2nd = ";
        cin >> x1 >> x2;

        a[x1-1].push_back(x2-1);
        a[x2-1].push_back(x1-1); // for each node, adjacent nodes are listed
    }

    cout << "Enter the goal: ";
    cin >> goal;

    int limit;
     cout << "Enter limit: ";
    cin >> limit;

    DLS(0, limit); // DLS starts

    return 0;
}

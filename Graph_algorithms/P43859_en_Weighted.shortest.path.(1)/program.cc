#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
using namespace std;

typedef pair<double,int> Arc;
typedef vector<vector<Arc> > Graf;

//#define inf 1.0/0.0

void llegeix_graf(int m, Graf &G) {
  for(int i=0; i<m; ++i) {
    int u;
    Arc a;
    cin >> u >> a.second >> a.first;
    G[u].push_back(a);
  }
}

void dist_x_y(const Graf &G, int x, int y, vector<double> &D) {
  D[x]=0;
  vector<bool> S(G.size(),false);
  priority_queue<Arc,vector<Arc>,greater<Arc> > Q;
  Q.push(Arc(0,x));
  
  while(not Q.empty() and not S[y]) {
    int u = Q.top().second;
    Q.pop();
    if(not S[u]) {
      S[u] = true;
      if(not S[y]) {
        for(int i=0; i<G[u].size(); ++i) {
          int v = G[u][i].second;
          double c = G[u][i].first;
          if(D[v] > D[u] + c) {
            D[v] = D[u] + c;
            Q.push(Arc(D[v],v));
            
          }
        }
      }
    }
  }
}

int main() {
  int n,m;
  while (cin >> n >> m) {
    Graf G(n);
    llegeix_graf(m,G);
    int x,y;
    cin >> x >> y;
    
    vector<double> D(n,HUGE_VAL);
    dist_x_y(G,x,y,D);
    if(D[y] < HUGE_VAL)
      cout << D[y] << endl;
    else
      cout << "no path from " << x << " to " << y << endl;
    
  }
  
  
}

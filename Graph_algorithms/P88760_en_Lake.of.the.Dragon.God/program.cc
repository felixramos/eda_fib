#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
using namespace std;

typedef struct {
    double x, y, r;
} Roca;

typedef vector<vector<int> > Graf;

void llegeix_roques(vector<Roca> &R) {
    int n = R.size();
    for(int i=0; i<n; ++i)
        cin >> R[i].x >> R[i].y >> R[i].r;
}

double distancia(const Roca &r1, const Roca &r2) {
    double a = r1.x - r2.x;
    double b = r1.y - r2.y;
    return sqrt(a*a + b*b) - (r1.r + r2.r);
}

void construye_graf(const vector<Roca> &R, double d, Graf &G) {
    int n = G.size();
    for(int i=0; i<n; ++i) {
        int j=i+1;
        for(j; j<n; ++j) {
            if(distancia(R[i],R[j]) <= d) {
                G[i].push_back(j);
                G[j].push_back(i);
            }
        }
    }
}

int calcula_nsalts(const Graf &G) {
    int n = G.size();
    queue<pair<int,int> > Q;
    vector<bool> enc(n,false);
    
    Q.push(make_pair(0,0));
    enc[0] = true;
    
    while(not Q.empty()) {
        int u = Q.front().first;
        int du = Q.front().second;
        Q.pop();
        if(u == n-1) return du;
        int m = G[u].size();
        for(int v=0; v<m; ++v) {
            if(not enc[G[u][v]]) {
                Q.push(make_pair(G[u][v],du+1));
                enc[G[u][v]] = true;
            }
        }
    }
    return -1;
}

int main() {
    int n; double d;
    while(cin >> n >> d) {
        vector<Roca> R(n);
        llegeix_roques(R);
        
        Graf G(n);
        construye_graf(R, d, G);
        
        int nsalts = calcula_nsalts(G);
        if(nsalts != -1) cout << nsalts << endl;
        else cout << "Xof!" << endl;
    }
}
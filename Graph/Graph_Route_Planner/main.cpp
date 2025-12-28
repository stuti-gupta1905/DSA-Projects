#include <bits/stdc++.h>
using namespace std;

class Graph{
public:    
    int V;
    list<pair<int,int>> *l;
    map<pair<int,int>, bool> blocked;

    Graph(int V){
        this->V=V;
        l=new list<pair<int,int>> [V];
    }

    void addEdge(int u, int v, int wt){
        l[u].push_back({v,wt});
        l[v].push_back({u,wt});
        blocked[{u,v}]=false; 
        blocked[{v,u}]=false; 
    }

    void blockRoad(int u, int v){
        blocked[{u,v}]=true;
        blocked[{v,u}]=true;
    }

    vector<int> dijkstra(int src, int dest){
        vector<int> dist(V, INT_MAX);
        vector<int> parent(V,-1);
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq; //stores //dist[v],v

        dist[src]=0;
        pq.push({0,src});

        while(!pq.empty()){
            int u=pq.top().second;
            int d=pq.top().first;
            pq.pop();

            if(d>dist[u]){
                continue;
            }

            for(auto e : l[u]){
                int v=e.first;
                int wt=e.second;
                if(blocked[{u,v}]){
                    continue;
                }
                if(dist[u]!=INT_MAX && dist[v]>dist[u]+wt){
                    dist[v]=dist[u]+wt;
                    parent[v]=u;
                    pq.push({dist[v],v});
                }
            }
        }

        // Impossible path
        if(dist[dest]==INT_MAX){
            return {};
        }

        //Path Reconstruction
        vector<int> path;
        for(int v=dest; v!=-1; v=parent[v]){
            path.push_back(v);
        }
        reverse(path.begin(),path.end());

        return path;
    }

    void bfsHelper(int src, vector<bool>& vis){
        queue<int> q;

        q.push(src);
        vis[src]=true;

        while(!q.empty()){
            int u=q.front();
            q.pop();
            cout<<u<<" ";

            for(auto e : l[u]){
                int v=e.first;
                if(!vis[v]){
                    vis[v]=true;
                    q.push(v);
                }
            }
        }
    }
    void bfs(int src){
        vector<bool> vis(V,false);
        bfsHelper(src,vis);
        for(int i=0; i<V; i++){ //handle disconnected nodes
            if(!vis[i]){
                bfsHelper(i,vis);
            }
        }
        cout<<endl;
    }

    void dfsHelper(int src, vector<bool>& vis){
        cout<<src<<" ";
        vis[src]=true;
        for(auto e : l[src]){
            int v=e.first;
            if(!vis[v]){
                dfsHelper(v,vis);
            }
        }
    }
    void dfs(int src){
        vector<bool> vis(V, false);
        dfsHelper(src,vis);
        for(int i=0; i<V; i++){
            if(!vis[i]){
                dfsHelper(i,vis);
            }
        }
        cout<<endl;
    }
};

// Implementation example
int main(){
    Graph g(6);

    // 0-Varanasi 1-Delhi 2-Mumbai 3-Banglore 4-Indore 5-Hydrabad
    g.addEdge(0,1,871); //src, dest, distance in kilometers
    g.addEdge(0,1,871);
}
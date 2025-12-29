#include <bits/stdc++.h>
using namespace std;

class Graph{
public:    
    int V;
    list<pair<int,int>> *l;
    map<pair<int,int>, bool> blocked;
    unordered_map<string,int> cityTold;
    vector<string> idToCity;

    Graph(int V){
        this->V=V;
        l=new list<pair<int,int>> [V];
        idToCity.resize(V);
    }

    void addEdge(int u, int v, int wt){
        l[u].push_back({v,wt});
        l[v].push_back({u,wt});
        blocked[{u,v}]=false; 
        blocked[{v,u}]=false; 
    }

    void addCity(int id, string city){
        cityTold[city]=id;
        idToCity[id]=city;
    }

    void blockRoad(int u, int v){
        blocked[{u,v}]=true;
        blocked[{v,u}]=true;
    }

    pair<int, vector<int>> dijkstra(int src, int dest){
        vector<long long> dist(V, INT_MAX);
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
            return {INT_MAX, {}};
        }

        //Path Reconstruction
        vector<int> path;
        for(int v=dest; v!=-1; v=parent[v]){
            path.push_back(v);
        }
        reverse(path.begin(),path.end());

        return {dist[dest],path};
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

    g.addCity(0,"Varanasi");
    g.addCity(1,"Delhi");
    g.addCity(2,"Mumbai");
    g.addCity(3,"Banglore");
    g.addCity(4,"Indore");
    g.addCity(5,"Hydrabad");

    g.addEdge(0,1,871); //src, dest, distance in kilometers
    g.addEdge(1,2,1387);
    g.addEdge(1,4,774);
    g.addEdge(2,3,1001);
    g.addEdge(3,4,1357);
    g.addEdge(2,4,604);
    g.addEdge(2,5,713);

    cout<<"Normal Route : Varanasi -> Indore"<<endl;
    auto path=g.dijkstra(0,4);
    if(path.second.empty()){
        cout<<"No route available!"<<endl;
    }
    else{
        for(int val : path.second){
            cout<<g.idToCity[val]<<" ";
        }
        cout<<"\nTotal distance (km): "<<path.first<<endl;
    }

    cout<<"Blocking road : Delhi -> Indore"<<endl;
    g.blockRoad(1,4);

    cout<<"Redirected route : Varanasi -> Indore"<<endl;
    path=g.dijkstra(0,4);
    if(path.second.empty()){
        cout<<"No route available!"<<endl;
    }
    else{
        for(int val : path.second){
            cout<<g.idToCity[val]<<" ";
        }
        cout<<"\nTotal distance (km): "<<path.first<<endl;
    }

    cout<<"Full route through bfs and dfs respectively"<<endl;
    g.bfs(0);
    g.dfs(0);

    return 0;
}
#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include<list>
const int INF = 1e9;
using namespace std;


// Helper function to initialize the graph with edges and weights
void addEdge(unordered_map<int,list<pair<int,int>>>&adj, int u, int v, int w) {
    adj[u].push_back(make_pair(v, w));
    adj[v].push_back(make_pair(u, w)); // For undirected graph
}

vector<int> dijkstra(unordered_map<int,list<pair<int,int>>>&adj, int source) {
    int vertices = adj.size();
    vector<int> dist(vertices);
    for(int i=0;i<vertices;i++)
        dist[i]=INF;
        
    dist[source] = 0; 

    set<pair<int,int>>st;
   st.insert(make_pair(0, source));

    while (!st.empty()) {
        auto top=*(st.begin());
        int topDist=top.first;
        int topNode=top.second;
        st.erase(st.begin());

        for (auto neighbour : adj[topNode]) {
            if (topDist + neighbour.second < dist[neighbour.first]){
                auto record=st.find(make_pair(dist[neighbour.first],neighbour.first));
                if(record!=st.end()){
                    st.erase(record);
                }
                dist[neighbour.first] =topDist + neighbour.second;
                st.insert(make_pair(dist[neighbour.first], neighbour.first));
            }
        }
    }

    return dist;
}

int main() {
    int vertices, edges;
    cout << "Enter the number of vertices and edges: ";
    cin >> vertices >> edges;

    unordered_map<int,list<pair<int,int>>>adj;

    cout << "Enter the edges (u v) and weights: " << endl;
    for (int i = 0; i < edges; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        addEdge(adj, u, v, w);
    }

    int source, destination;
    cout << "Enter the source and destination: ";
    cin >> source >> destination;

    vector<int> shortestDistances = dijkstra(adj, source);

    if (shortestDistances[destination] == INF) {
        cout << "No path found between source and destination." << endl;
    } else {
        cout << "Shortest distance from source to destination: " << shortestDistances[destination] << endl;
    }

    return 0;
}

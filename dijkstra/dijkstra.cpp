#include <iostream>
#include <fstream>
#include <limits.h>

#define inf INT_MAX

using namespace std;

template <class H> class Graph{

  private:
    H** K;
    int** adj;
    int n,len;
    int* dist;
    bool* visit;

    int findIndex(H x){
      for(int i=0;i<len;i++)
        if(K[i] && *K[i] == x) return i;
      return -1;
    }

    int minDistance(){
      int min_index;
      int min = inf;
      for (int i=0;i<len;i++)
        if(visit[i] == false && dist[i] <= min){
          min = dist[i];
          min_index = i;
        }
      return min_index;
    }

  public:

    Graph(int dim){
      n = dim;
      len = 0;
      dist = new int[n];
      visit = new bool[n];

      K = new H*[n];
      for(int i=0;i<n;i++)
        K[i] = NULL;

      adj = new int*[n];
      for(int i=0;i<n;i++){
        adj[i] = new int[n];
        for(int j=0;j<n;j++)
          adj[i][j] = -1;
      }
    }

    Graph<H>* addNode(H x){
      if(findIndex(x) >= 0) return this;
      if(len == n) return this;
      K[len++] = new H(x);
      return this;
    }

    Graph<H>* addEdge(H x, H y, int weight){
      int i = findIndex(x);
      int j = findIndex(y);
      if(i<0 || j<0) return this;
      if(adj[i][j] == -1)
        adj[i][j] = weight;
      return this;
    }

    void Dijkstra(H sorgente, H destinazione, ofstream& out){
      for(int i=0;i<len;i++){
        dist[i] = inf;
        visit[i] = false;
      }
      dist[findIndex(sorgente)] = 0;
      for(int i=0;i<len;i++){
        int u = minDistance();
        visit[u] = true;

        for(int v=0;v<len;v++)
          if(visit[v] == false && adj[u][v] >= 0 && dist[u] != inf && dist[u] + adj[u][v] < dist[v])
            dist[v] = dist[u] + adj[u][v];
      }

      if(dist[findIndex(destinazione)] == inf) out << "inf." << endl;
      else out << dist[findIndex(destinazione)] << endl;
    }
};

int main(){
  ifstream input;
  ofstream output;
  input.open("input.txt");
  output.open("output.txt");

  int n,m;
  string type;
  for(int i=0;i<100;i++){
    input >> n >> m >> type;
    if(type == "int"){
      Graph<int>* g = new Graph<int>(n);
      for(int j=0;j<n;j++){
        int in; input >> in;
        g->addNode(in);
      }
      for(int j=0;j<m;j++){
        char tmp; input >> tmp;
        int f; input >> f;
        int s; input >> s;
        int w; input >> w;
        input >> tmp;
        g->addEdge(f,s,w);
      }
      int sorgente; input >> sorgente;
      int destinazione; input >> destinazione;
      g->Dijkstra(sorgente,destinazione,output);
    }
    if(type=="double"){
      Graph<double>* g = new Graph<double>(n);
      for(int j=0;j<n;j++){
        double in; input >> in;
        g->addNode(in/10);
      }
      for(int j=0;j<m;j++){
        char tmp; input >> tmp;
        double f; input >> f;
        double s; input >> s;
        int w; input >> w;
        input >> tmp;
        g->addEdge(f,s,w);
      }
      double sorgente; input >> sorgente;
      double destinazione; input >> destinazione;
      g->Dijkstra(sorgente,destinazione,output);
    }
  }
}

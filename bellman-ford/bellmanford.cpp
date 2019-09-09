#include <iostream>
#include <fstream>
#include <limits.h>

using namespace std;

template <class H> class Graph{
  private:
    H** K;
    int** adj;
    int n,len;

    int findIndex(H x){
      for (int i=0;i<len;i++)
        if(K[i] && *K[i]==x) return i;
      return -1;
    }

  public:
    Graph(int dim){
      n = dim;
      len = 0;
      K = new H*[n];
      for(int i=0;i<n;i++)
        K[i] = NULL;

      adj = new int*[n];
      for (int i=0;i<n;i++){
        adj[i] = new int[n];
        for(int j=0;j<n;j++)
          adj[i][j] = INT_MIN;
      }
    }

    Graph<H>* addNode(H x){
      if(len==n) return this;
      if(findIndex(x)>=0) return this;
      K[len++] = new H(x);
      return this;
    }

    Graph<H>* addEdge(H x, H y, int weight){
      int i = findIndex(x);
      int j = findIndex(y);
      if(i<0 || j<0) return this;
      if(adj[i][j] == INT_MIN)
        adj[i][j] = weight;
      return this;
    }

    void BellmanFord(H sorgente, H destinazione, ofstream& out){
      int* dist = new int[len];
      for (int i=0;i<len;i++)
        dist[i] = INT_MAX;
      dist[findIndex(sorgente)] = 0;

      for (int k=0;k<len-1;k++)
        for(int i=0;i<len;i++)
          for(int j=0;j<len;j++)
            if(adj[i][j]!=INT_MIN){
              int weight = adj[i][j];
              if(dist[i] != INT_MAX && dist[i] + weight < dist[j])
                dist[j] = dist[i] + weight;
            }


      for (int k=0;k<len-1;k++)
        for(int i=0;i<len;i++)
          for(int j=0;j<len;j++)
            if(adj[i][j]!=INT_MIN){
              int weight = adj[i][j];
              if(dist[i] != INT_MAX && dist[i] + weight < dist[j]){
                out << "undef." << endl;
                return;
              }
            }

      if(dist[findIndex(destinazione)]==INT_MAX) out << "inf." << endl;
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

  for (int i=0;i<100;i++){
    input >> n >> m >> type;
    if(type=="int"){
      Graph<int>* g = new Graph<int>(n);
      for (int j=0;j<n;j++){
        int in; input >> in;
        g->addNode(in);
      }
      for(int j=0;j<m;j++){
        char tmp; input >> tmp;
        int f; input >> f;
        int s; input >> s;
        int p; input >> p;
        input >> tmp;
        g->addEdge(f,s,p);
      }
      int sorgente; input >> sorgente;
      int destinazione; input >> destinazione;
      g->BellmanFord(sorgente,destinazione,output);
  }
  if(type=="double"){
    Graph<double>* g = new Graph<double>(n);
    for (int j=0;j<n;j++){
      double in; input >> in;
      g->addNode(in);
    }
    for(int j=0;j<m;j++){
      char tmp; input >> tmp;
      double f; input >> f;
      double s; input >> s;
      int p; input >> p;
      input >> tmp;
      g->addEdge(f,s,p);
    }
    double sorgente; input >> sorgente;
    double destinazione; input >> destinazione;
    g->BellmanFord(sorgente,destinazione,output);
  }
 }
}

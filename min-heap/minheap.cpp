#include <iostream>
#include <fstream>
#include <limits.h>

using namespace std;

template <class H> class MinHeap{

  private:
    H* array;
    int len,heapsize;
    int heapifynumber;

    int left(int i){ return 2*(i+1)-1; }
    int right(int i){ return 2*(i+1); }
    int parent(int i){
      if(i==0) return 0;
      return ((i+1)/2)-1;
    }


    void scambia(int i, int j){
      H tmp = array[i];
      array[i] = array[j];
      array[j] = tmp;
    }

    void heapify(int i){
      if(i>=len) return;
      heapifynumber++;
      int l = left(i);
      int r = right(i);
      int smallest = i;
      if(l<len && array[l]<array[smallest]) smallest = l;
      if(r<len && array[r]<array[smallest]) smallest = r;
      if(smallest!=i){
        scambia(i,smallest);
        heapify(smallest);
      }
    }

  public:

      MinHeap<H>(int dim){
        heapsize = dim;
        array = new H[heapsize];
        len = 0;
        heapifynumber = 0;
      }

      H* extract(){
        if(heapsize==0) return NULL;
        scambia(0,len-1);
        len--;
        heapify(0);
        return new H(array[len]);
      }

      MinHeap<H>* enqueue(H x){
        if(len == heapsize) return this;
        int i = len;
        array[len++] = x;
        while(array[i]<array[parent(i)]){
          scambia(i,parent(i));
          i = parent(i);
        }
        return this;
      }

      void print(ofstream & out){
        out << heapifynumber << " ";
        for(int i=0;i<len;i++)
          out << array[i] << " ";
        out << endl;
      }
};

int main(){
  ifstream input;
  ofstream output;
  input.open("input.txt");
  output.open("output.txt");

  string type;
  int n;

  for(int i=0;i<100;i++){
    input >> type >> n;
    if(type=="int"|| type=="bool"){
      MinHeap<int>* mh = new MinHeap<int>(n);
      for(int j=0;j<n;j++){
        char tmp; input >> tmp; input >> tmp;
        if(tmp==':'){
          int k; input >> k;
          mh->enqueue(k);
        }
        else{
          string s; input >> s;
          mh->extract();
        }
      }
      mh->print(output);
    }
    if(type=="double"){
      MinHeap<double>* mh = new MinHeap<double>(n);
      for(int j=0;j<n;j++){
        char tmp; input >> tmp; input >> tmp;
        if(tmp==':'){
          double k; input >> k;
          mh->enqueue(k);
        }
        else{
          string s; input >> s;
          mh->extract();
        }
      }
      mh->print(output);
    }
    if(type=="char"){
      MinHeap<char>* mh = new MinHeap<char>(n);
      for(int j=0;j<n;j++){
        char tmp; input >> tmp; input >> tmp;
        if(tmp==':'){
          char k; input >> k;
          mh->enqueue(k);
        }
        else{
          string s; input >> s;
          mh->extract();
        }
      }
      mh->print(output);
    }
  }
}

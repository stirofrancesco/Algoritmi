#include <iostream>
#include <fstream>

using namespace std;

template<class H> class MaxHeap{

  private:
    H* array;
    int heapsize;
    int len;
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
      int highest = i;
      int l = left(i);
      int r = right(i);
      if(l<len && array[l]>array[highest]) highest = l;
      if(r<len && array[r]>array[highest]) highest = r;
      if(highest!=i){
        scambia(i,highest);
        heapify(highest);
      }
    }

  public:
    MaxHeap(int n){
      array = new H[n];
      heapsize = n;
      len = 0;
      heapifynumber = 0;
    }

    H* extract(){
      if(len==0) return NULL;
      scambia(0,len-1);
      len--;
      heapify(0);
      return new H(array[len]);
    }

    MaxHeap<H>* enqueue(H x){
      if(len==heapsize) return this;
      int i = len;
      array[len++] = x;
      while(array[i]>array[parent(i)]){
        scambia(i,parent(i));
        i = parent(i);
      }
      return this;
   }

  void print(ofstream& out){
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

  int n;
  string type;

  for(int i=0;i<100;i++){
    input >> type >> n;
    if(type == "int" || type == "bool"){
      MaxHeap<int>* mh = new MaxHeap<int>(n);
      for(int j=0;j<n;j++){
        char tmp; input >> tmp; input >> tmp;
        if(tmp == ':'){
          int k; input >> k;
          mh->enqueue(k);
        }
        else{
          mh->extract();
          string s; input >> s;
        }
      }
      mh->print(output);
    }
    if(type == "double"){
      MaxHeap<double>* mh = new MaxHeap<double>(n);
      for(int j=0;j<n;j++){
        char tmp; input >> tmp; input >> tmp;
        if(tmp == ':'){
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
    if(type == "char"){
      MaxHeap<char>* mh = new MaxHeap<char>(n);
      for(int j=0;j<n;j++){
        char tmp; input >> tmp; input >> tmp;
        if(tmp == ':'){
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

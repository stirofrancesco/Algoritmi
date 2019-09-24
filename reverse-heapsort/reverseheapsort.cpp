#include <iostream>
#include <fstream>
#include <limits.h>

using namespace std;

template <class H> class MinHeap{

  private:
    H* array;
    int heapsize;
    int heapifynumber;

    int left(int i){ return 2*(i+1)-1; }
    int right(int i){ return 2*(i+1); }

    void scambia(int i, int j){
      H tmp = array[i];
      array[i] = array[j];
      array[j] = tmp;
    }

    void heapify(int i){
      if(i>=heapsize) return;
      heapifynumber++;
      int l = left(i);
      int r = right(i);
      int smallest = i;
      if(l<heapsize && array[l]<array[smallest]) smallest = l;
      if(r<heapsize && array[r]<array[smallest]) smallest = r;
      if(smallest!=i){
        scambia(smallest,i);
        heapify(smallest);
      }
    }

    void buildHeap(){
      for(int i=heapsize/2-1;i>=0;i--)
        heapify(i);
    }

  public:

    MinHeap<H>(H* V, int n){
      array = V;
      heapsize = n;
      heapifynumber = 0;
      buildHeap();
    }

    H* extract(){
      if(heapsize==0) return NULL;
      scambia(0,heapsize-1);
      heapsize--;
      heapify(0);
      return new H(array[heapsize]);
    }

    int getHeapifyNumber(){ return heapifynumber; }
};

template <class H>
void revHeapSort(H* array, int n, ofstream& out){
  MinHeap<H>* mh = new MinHeap<H>(array,n);
  for(int i=0;i<n;i++)
    mh->extract();

  // Stampa
  out << mh->getHeapifyNumber() << " ";
  for(int i=0;i<n;i++)
    out << array[i] << " ";
  out << endl;
}


int main(){
  ifstream input;
  ofstream output;
  input.open("input.txt");
  output.open("output.txt");

  string type;
  int n;

  for(int i=0;i<100;i++){
    input >> type >> n;
    if(type == "int" || type=="bool"){
      int* array = new int[n];
      for(int j=0;j<n;j++)
        input >> array[j];
      revHeapSort(array,n,output);
    }
    if(type == "double"){
      double* array = new double[n];
      for(int j=0;j<n;j++)
        input >> array[j];
      revHeapSort(array,n,output);
    }
    if(type == "char"){
      char* array = new char[n];
      for(int j=0;j<n;j++)
        input >> array[j];
      revHeapSort(array,n,output);
    }
  }
}

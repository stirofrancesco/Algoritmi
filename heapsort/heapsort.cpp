#include <iostream>
#include <fstream>

using namespace std;

template <class H> class MaxHeap{

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
      int highest = i;
      if(l<heapsize && array[l]>array[highest]) highest = l;
      if(r<heapsize && array[r]>array[highest]) highest = r;
      if(highest!=i){
        scambia(highest,i);
        heapify(highest);
      }
    }

    void buildHeap(){
      for(int i=(heapsize/2)-1;i>=0;i--)
        heapify(i);
    }

  public:

    MaxHeap(H* V, int n){
      heapifynumber = 0;
      array = V;
      heapsize = n;
      buildHeap();
    }

    H* extract(){
      scambia(0,heapsize-1);
      heapsize--;
      heapify(0);
      return new H(array[heapsize]);
    }

    int HeapSort(){
      int k = heapsize;
      for(int i=0;i<k;i++)
        extract();
      return heapifynumber;
    }
};



int main(){
  ifstream input;
  ofstream output;
  input.open("input.txt");
  output.open("output.txt");

  string type;
  int n;

  for (int i=0;i<100;i++){
    input >> type >> n;
    if(type=="int" || type=="bool"){
      int* array = new int[n];
      for (int j=0;j<n;j++)
        input >> array[j];
      MaxHeap<int>* mh = new MaxHeap<int>(array,n);
      output << mh->HeapSort() << " ";
      for (int j=0;j<n;j++)
        output << array[j] << " ";
      output << endl;
    }
    if(type=="double"){
      double* array = new double[n];
      for (int j=0;j<n;j++)
        input >> array[j];
      MaxHeap<double>* mh = new MaxHeap<double>(array,n);
      output << mh->HeapSort() << " ";
      for (int j=0;j<n;j++)
        output << array[j] << " ";
      output << endl;
    }
    if(type=="char"){
      char* array = new char[n];
      for (int j=0;j<n;j++)
        input >> array[j];
      MaxHeap<char>* mh = new MaxHeap<char>(array,n);
      output << mh->HeapSort() << " ";
      for (int j=0;j<n;j++)
        output << array[j] << " ";
      output << endl;
    }
  }
}

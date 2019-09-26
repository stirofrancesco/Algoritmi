#include <iostream>
#include <fstream>

using namespace std;

template <class H> class Coppia{

  private:
    H first;
    H second;

  public:
    Coppia(H first, H second){
      this->first = first;
      this->second = second;
    }

    H getFirst(){ return first; }
    H getSecond(){ return second; }

    bool operator >(Coppia& c){
      if(first!=c.getFirst()) return first>c.getFirst();
      else return second > c.getSecond();
    }
};

template <class H> class MaxHeap{

  private:
    H** array;
    int heapsize;
    int heapifynumber;

    int left(int i){ return 2*(i+1)-1; }
    int right(int i){ return 2*(i+1); }

    void scambia(int i, int j){
      H* tmp = array[i];
      array[i] = array[j];
      array[j] = tmp;
    }

    void heapify(int i){
      if(i>=heapsize) return;
      heapifynumber++;
      int l = left(i);
      int r = right(i);
      int highest = i;
      if(l<heapsize && *array[l]>*array[highest]) highest = l;
      if(r<heapsize && *array[r]>*array[highest]) highest = r;
      if(highest!=i){
        scambia(i,highest);
        heapify(highest);
      }
    }

    void buildHeap(){
      for(int i=heapsize/2-1;i>=0;i--)
        heapify(i);
    }

  public:

    MaxHeap<H>(H** V, int n){
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
      return new H(*array[heapsize]);
    }

    int getHeapifyNumber(){ return heapifynumber; }
};


template<class H>
void heapSort(Coppia<H>** V, int n, ofstream& out){
  MaxHeap< Coppia<H> >* mh = new MaxHeap< Coppia<H> >(V,n);
  for(int i=0;i<n;i++)
    mh->extract();
 // STAMPA
  out << mh->getHeapifyNumber() << " ";
  for(int i=0;i<n;i++)
    out << "(" << V[i]->getFirst() << "," << V[i]->getSecond() << ")" << " ";
  out << endl;
}


int main(){
  ifstream input;
  ofstream output;
  input.open("input.txt");
  output.open("output.txt");

  string type;
  int n;

  for (int i=0;i<100;i++){
    input >> type >> n;
    if(type == "int" || type == "bool"){
      Coppia<int>** array = new Coppia<int>*[n];
      for(int j=0;j<n;j++){
        char tmp; input >> tmp;
        int f; input >> f;
        int s; input >> s;
        input >> tmp;
        array[j] = new Coppia<int>(f,s);
      }
      heapSort(array,n,output);
    }
    if(type == "double"){
      Coppia<double>** array = new Coppia<double>*[n];
      for(int j=0;j<n;j++){
        char tmp; input >> tmp;
        double f; input >> f;
        double s; input >> s;
        input >> tmp;
        array[j] = new Coppia<double>(f,s);
      }
      heapSort(array,n,output);
    }
    if(type == "char"){
      Coppia<char>** array = new Coppia<char>*[n];
      for(int j=0;j<n;j++){
        char tmp; input >> tmp;
        char f; input >> f;
        char s; input >> s;
        input >> tmp;
        array[j] = new Coppia<char>(f,s);
      }
      heapSort(array,n,output);
    }
  }
}

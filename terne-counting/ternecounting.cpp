#include <iostream>
#include <fstream>

using namespace std;

template<class H> class Coppia{

  private:
    H first;
    H second;
    H third;

  public:
    Coppia(H first, H second, H third){
      this->first = first;
      this->second = second;
      this->third = third;
    }

    H getFirst(){ return first; }
    H getSecond(){ return second; }
    H getThird(){ return third; }

    void print(ofstream& out){
      out << "(" << first << "," << second << "," << third << ")" << " ";
    }

    bool operator < (Coppia& c){ return first < c.getFirst(); }
    bool operator > (Coppia& c){ return !(*this<c); }
    H operator - (Coppia& c){ return first-c.getFirst(); }
};


template <class H>
void CountingSort(Coppia<H>** V, int n, ofstream& out){

  Coppia<int>** A = new Coppia<int>*[n];
  for(int i=0;i<n;i++) A[i] = new Coppia<int>(V[i]->getFirst()*10,V[i]->getSecond()*10,V[i]->getThird()*10);

  Coppia<int> max = *A[0];
  Coppia<int> min = *A[0];
  for(int i=1;i<n;i++){
    if(*A[i]<min) min = *A[i];
    if(*A[i]>max) max = *A[i];
  }
  int range = max-min+1;
  int* C = new int[range];
  Coppia<H>** B = new Coppia<H>*[n];

  for(int i=0;i<range;i++)
    C[i] = 0;
  for(int i=0;i<n;i++)
    C[*A[i]-min]++;
  for(int i=1;i<range;i++)
    C[i]+=C[i-1];
  for(int i=n-1;i>=0;i--){
    B[C[*A[i]-min]-1] = new Coppia<double>(A[i]->getFirst()/10.0,A[i]->getSecond()/10.0,A[i]->getThird()/10.0);
    C[*A[i]-min]--;
  }

  for(int i=0;i<range;i++)
    out << C[i] << " ";
  for(int i=0;i<n;i++)
    B[i]->print(out);
  out << endl;
}

int main(){
  ifstream input;
  ofstream output;
  input.open("input.txt");
  output.open("output.txt");

  int n;

  for(int i=0;i<100;i++){
    input >> n;
    Coppia<double>** array = new Coppia<double>*[n];
    for(int j=0;j<n;j++){
      char tmp; input >> tmp;
      double f; input >> f;
      double s; input >> s;
      double t; input >> t;
      input >> tmp;
      array[j] = new Coppia<double>(f,s,t);
    }
    CountingSort(array,n,output);
  }
}

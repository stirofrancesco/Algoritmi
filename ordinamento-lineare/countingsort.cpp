#include <iostream>
#include <fstream>

using namespace std;

template <class H>
void CountingSort(H* A, int n, ofstream& out){
  H max = A[0];
  H min = A[0];
  for(int i=1;i<n;i++){
    if(A[i]<min) min = A[i];
    if(A[i]>max) max = A[i];
  }
  int range = max-min+1;
  int* C = new int[range];
  H* B = new H[n];

  for(int i=0;i<range;i++)
    C[i] = 0;
  for(int i=0;i<n;i++)
    C[A[i]-min]++;
  for(int i=1;i<range;i++)
    C[i]+=C[i-1];
  for(int i=n-1;i>=0;i--){
    B[C[A[i]-min]-1] = A[i];
    C[A[i]-min]--;
  }

  for(int i=0;i<range;i++)
    out << C[i] << " ";
  for(int i=0;i<n;i++)
    out << B[i] << " ";
  out << endl;
}

template <class H>
void CountingSortD(H* V, int n, ofstream& out){
  int* A = new int[n];
  for(int i=0;i<n;i++) A[i] = V[i]*10;
  int max = A[0];
  int min = A[0];
  for(int i=1;i<n;i++){
    if(A[i]<min) min = A[i];
    if(A[i]>max) max = A[i];
  }
  int range = max-min+1;
  int* C = new int[range];
  H* B = new H[n];

  for(int i=0;i<range;i++)
    C[i] = 0;
  for(int i=0;i<n;i++)
    C[A[i]-min]++;
  for(int i=1;i<range;i++)
    C[i]+=C[i-1];
  for(int i=n-1;i>=0;i--){
    B[C[A[i]-min]-1] = A[i]/10.0;
    C[A[i]-min]--;
  }

  for(int i=0;i<range;i++)
    out << C[i] << " ";
  for(int i=0;i<n;i++)
    out << B[i] << " ";
  out << endl;
}

int main(){
  ifstream input;
  ofstream output;
  input.open("input.txt");
  output.open("output.txt");

  int n;
  string type;

  for(int i=0;i<100;i++){
    input >> type >> n;
    if(type=="int" || type=="bool"){
      int* array = new int[n];
      for(int j=0;j<n;j++)
        input >> array[j];
      CountingSort(array,n,output);
    }
    if(type=="double"){
      double* array = new double[n];
      for(int j=0;j<n;j++){
        input >> array[j];
      }
      CountingSortD(array,n,output);
    }
    if(type=="char"){
      char* array = new char[n];
      for(int j=0;j<n;j++)
        input >> array[j];
      CountingSort(array,n,output);
    }
  }
}

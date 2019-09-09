#include <iostream>
#include <fstream>

using namespace std;

template <class H>
void CountingSort(H* A, int n, ofstream& out){
  H min = A[0];
  H max = A[0];
  for(int i=0;i<n;i++){
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

  for(int i=0;i<n;i++)
    A[i] = B[i];

  // Stampa array C

  for (int i=0;i<range;i++)
    out << C[i] << " ";
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
      int* array = new int[n];
      for(int j=0;j<n;j++)
        input >> array[j];
      CountingSort(array,n,output);
      for(int j=0;j<n;j++)
        output << array[j] << " ";
      output << endl;
    }
    if(type == "char"){
      char* array = new char[n];
      for(int j=0;j<n;j++)
        input >> array[j];
      CountingSort(array,n,output);
      for(int j=0;j<n;j++)
        output << array[j] << " ";
      output << endl;
    }
    if(type == "double"){
      int* array = new int[n];
      for(int j=0;j<n;j++){
        double k; input >> k; k*=10;
        array[j]= k;
      }
      CountingSort(array,n,output);
      for(int j=0;j<n;j++)
        output << (double)array[j]/10 << " ";
      output << endl;
    }
  }
}

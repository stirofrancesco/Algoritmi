#include <iostream>
#include <fstream>

using namespace std;

// Versione non stabile

void CountingSort(int* A, int n, ofstream& out){
  int max = A[0];
  int min = A[0];
  for (int i=0;i<n;i++){
    if(A[i]>max)
      max = A[i];
    if(A[i]<min)
      min = A[i];
  }

  int range = max-min+1;
  int* B = new int[n];
  int* C = new int[range];

  for (int i=0;i<range;i++)
    C[i] = 0;
  for(int i=0;i<n;i++)
    C[A[i]-min]++;
  for(int i=1;i<range;i++)
    C[i]+=C[i-1];
  for(int i=0;i<n;i++){
    B[C[A[i]-min]-1] = A[i];
    C[A[i]-min]--;
  }
  for (int i=0;i<n;i++)
    A[i] = B[i];

  // Stampa

  for (int i=0;i<range;i++)
    out << C[i] << " ";
  for(int i=0;i<n;i++)
    out << A[i] << " ";
  out << endl;

  return;
}




int main(){
  ifstream input;
  ofstream output;
  input.open("input.txt");
  output.open("output.txt");

  int n;

  for (int i=0;i<100;i++){
    input >> n;
    int* array = new int[n];
    for (int j=0;j<n;j++)
      input >> array[j];
    CountingSort(array,n,output);
  }
}

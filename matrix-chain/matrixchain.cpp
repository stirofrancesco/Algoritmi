#include <iostream>
#include <fstream>
#include <limits.h>

using namespace std;

int matrix_chain(int* p, int n){
  int m[n][n];
  for(int i=1;i<n;i++)
    m[i][i] = 0;

  for(int delta=2;delta<n;delta++)
    for(int i=1;i<n-delta+1;i++){
      int j = i+delta-1;
      m[i][j] = INT_MAX;
      for(int k=i;k<j;k++){
        int q = m[i][k]+m[k+1][j]+p[i-1]*p[k]*p[j];
        if(q<m[i][j])
          m[i][j]=q;
      }
    }
  return m[1][n-1];
}

int main(){
  ifstream input;
  ofstream output;
  input.open("input.txt");
  output.open("output.txt");

  int n;

  for (int i=0;i<100;i++){
    input >> n;
    int* array = new int[n+1];
    char tmp;
    int f,s;
    for(int j=0;j<n;j++){
      input >> tmp;
      input >> f; input >> tmp;
      input >> s; input >> tmp;
      array[j] = f;
    }
    array[n] = s;
    output << matrix_chain(array,n+1) << endl;
  }
}

#include <iostream>
#include <fstream>

using namespace std;

int resto(int* tagli, int n, int r){

  int* table = new int[r+1];
  table[0] = 0;
  for (int i=1;i<=r;i++) table[i] = r+1;

  for (int i=1;i<=r;i++)
    for(int j=0;j<n;j++)
      if(i-tagli[j]>=0)
        table[i] = min(table[i],1+table[i-tagli[j]]);
  return table[r];
}

/*ALTERNATIVA

int resto(int* tagli, int n, int r){
  int* table = new int[r+1];
  table[0] = 0;
  for(int i=1;i<=r;i++) table[i] = r+1;

  for(int i=1;i<=r;i++)
    for(int j=0;j<n;j++){
      if(i-tagli[j]>=0 && 1+table[i-tagli[j]]<table[i])
        table[i] = 1+table[i-tagli[j]];
    }
  return table[r];
}

*/


int main(){
  ifstream input;
  ofstream output;
  input.open("input.txt");
  output.open("output.txt");

  int r,n;

  for (int i=0;i<100;i++){
    input >> r >> n;
    int* array = new int[n];
    for(int j=0;j<n;j++)
      input >> array[j];

    output << resto(array,n,r) << endl;
  }
}

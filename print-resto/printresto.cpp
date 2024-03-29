#include <iostream>
#include <fstream>
#include <limits.h>

using namespace std;

void scambia(int* array, int i, int j){
  int tmp = array[i];
  array[i] = array[j];
  array[j] = tmp;
}

void sort(int* array, int n){
  for(int i=0;i<n;i++)
    for(int j=i+1;j<n;j++)
      if(array[i]>array[j])
        scambia(array,i,j);
}

void printresto(int* tagli, int n, int r, ofstream& out){
  int* table = new int[r+1];
  int* s = new int[r+1];
  table[0] = 0;
  s[0] = 0;
  for(int i=1;i<=r;i++){
    table[i] = r+1;
    s[i] = 0;
  }

  for(int i=1;i<=r;i++)
    for(int j=0;j<n;j++){
      if(i-tagli[j]>=0 && 1+table[i-tagli[j]]<table[i]){
        table[i] = 1+table[i-tagli[j]];
        s[i] = j;
      }
    }

  int* coin = new int[table[r]];
  int k = r;
  int i = 0;

  while(k>0){
    coin[i++] = tagli[s[k]];
    k = k-tagli[s[k]];
  }

  sort(coin,table[r]);
  // Stampa
  out << table[r] << " ";
  for(int i=0;i<table[r];i++)
    out << coin[i] << " ";
  out << endl;
}

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
    printresto(array,n,r,output);
  }
}

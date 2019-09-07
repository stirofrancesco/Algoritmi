#include <iostream>
#include <fstream>

using namespace std;

void scambia(int* V, int i, int j){
  int tmp = V[i];
  V[i] = V[j];
  V[j] = tmp;
}

void sort(int* V, int n){
  for (int i=0;i<n;i++)
    for(int j=i+1;j<n;j++)
      if(V[i]<V[j])
        scambia(V,i,j);
}

int knapsack(int* V, int n, int p){
  sort(V,n);
  int maximal_value = 0;
  for(int i=0;i<p;i++)
    maximal_value+=V[i];

  return maximal_value;
}


int main(){

  ifstream input;
  ofstream output;
  input.open("input.txt");
  output.open("output.txt");

  int n,p;

  for (int i=0;i<100;i++){
    input >> n >> p;
    int* array = new int[n];
    for(int j=0;j<n;j++)
      input >> array[j];

    output << knapsack(array,n,p) << endl;
  }
}

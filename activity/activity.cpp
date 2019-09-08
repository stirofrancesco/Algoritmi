#include <iostream>
#include <fstream>

using namespace std;

class Activity{
  private:
    int start;
    int end;
    int duration;

  public:
    Activity(int start, int end){
      this->start = start;
      this->end = end;
      duration = (end-start);
    }

    int getStart(){ return start; }
    int getEnd(){ return end; }
    int getProfit(){ return duration; }
};


void scambia(Activity** V, int i, int j){
  Activity* tmp = V[i];
  V[i] = V[j];
  V[j] = tmp;
}

void sort(Activity** V, int n){
  for (int i=0;i<n;i++)
    for(int j=i+1;j<n;j++)
      if(V[i]->getEnd()>V[j]->getEnd())
        scambia(V,i,j);
}

int latestNonConflict(Activity** V, int i){

  for (int j=i-1;j>=0;j--)
    if(V[j]->getEnd()<=V[i]->getStart())
      return j;
  return -1;
}

int activity_selector(Activity** V, int n){
  sort(V,n);
  int* table = new int[n];
  table[0] = V[0]->getProfit();

  for(int i=1;i<n;i++){
    int total_profit = V[i]->getProfit();
    int l = latestNonConflict(V,i);
    if(l!=-1)
      total_profit+=table[l];

    table[i] = max(total_profit,table[i-1]);
  }
  return table[n-1];
}


int main(){

  ifstream input;
  ofstream output;
  input.open("input.txt");
  output.open("output.txt");

  int n;

  for (int i=0;i<100;i++){
    input >> n;
    Activity** array = new Activity*[n];
    for(int j=0;j<n;j++){
      char tmp; input >> tmp;
      int f; input >> f;
      int s; input >> s;
      input >> tmp;
      array[j] = new Activity(f,s);
    }
    output << activity_selector(array,n) << endl;
  }
}

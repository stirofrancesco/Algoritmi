#include <iostream>
#include <fstream>

using namespace std;

class Activity{
  private:
    int start;
    int end;

  public:
    Activity(int start, int end){
      this->start = start;
      this->end = end;
    }

    int getStart(){ return start; }
    int getEnd(){ return end; }
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

int greedy_activity(Activity** V, int n){
  sort(V,n);
  int counter = 1;
  Activity* activity = V[0];
  for(int i=1;i<n;i++)
    if(V[i]->getStart()>=activity->getEnd()){
      counter++;
      activity = V[i];
    }
  return counter;
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
      int first; input >> first;
      int second; input >> second;
      input >> tmp;
      array[j] = new Activity(first,second);
    }
    output << greedy_activity(array,n) << endl;
  }
}

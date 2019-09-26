#include <iostream>
#include <fstream>

using namespace std;

void reverse(string &x){
  for(int i=0;i<x.length()/2;i++){
    char tmp = x[i];
    x[i] = x[x.length()-1-i];
    x[x.length()-1-i] = tmp;
  }
}

string printlcs(string x, string y, int len1, int len2){
  int m[len1+1][len2+1];
  for(int i=0;i<=len1;i++)
    for(int j=0;j<=len2;j++){
      if(i==0 || j==0) m[i][j] = 0;
      else if(x[i-1]==y[j-1]) m[i][j] = m[i-1][j-1]+1;
      else m[i][j] = max(m[i][j-1],m[i-1][j]);
    }

//  int max = m[len1][len2];
  int i = len1;
  int j = len2;
  string lcs = "";

  while(i>0 && j>0){
    if(x[i-1]==y[j-1]){
      lcs += x[i-1];
      i--; j--;
    }
    else{
      if(m[i][j-1]>=m[i-1][j]) j--;
      else i--;
    }
  }
  reverse(lcs);
  return lcs;
}

int main(){
  ifstream input;
  ofstream output;
  input.open("input.txt");
  output.open("output.txt");

  string x,y;
  int l1,l2;

  for (int i=0;i<100;i++){
    input >> l1 >> l2 >> x >> y;
    output << printlcs(x,y,l1,l2) << endl;
  }
}

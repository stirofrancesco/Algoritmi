#include <iostream>
#include <fstream>

using namespace std;

int editDistance(string x, string y, int len1, int len2){
  int m[len1+1][len2+1];
  for(int i = 0; i <= len1; ++i) {
    for(int j = 0; j <= len2; ++j) {
      if(i == 0) {
        m[i][j] = j;
      } else if(j == 0) {
        m[i][j] = i;
      } else if(x[i-1] == y[j-1]) {
        m[i][j] = m[i-1][j-1];
      } else {
        m[i][j] = 1 + min(
          m[i-1][j],
          min(m[i][j-1], m[i-1][j-1])
        );
      }
    }
  }
  return m[len1][len2];
}


int main(){
  ifstream input;
  ofstream output;
  input.open("input.txt");
  output.open("output.txt");

  int len1,len2;
  string x,y;
  for (int i=0; i < 100; ++i){
    input >> len1 >> len2 >> x >> y;
    output << editDistance(x, y, len1, len2) << endl;
  }
}

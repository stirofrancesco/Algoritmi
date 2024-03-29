#include <iostream>
#include <fstream>

using namespace std;

int lcs(string x, string y, int len1, int len2){
  int m[len1+1][len2+1];

  for(int i=0;i<=len1;i++)
    for(int j=0;j<=len2;j++){
      if(i==0||j==0)
        m[i][j]=0;
      else if(x[i-1]==y[j-1]) m[i][j] = m[i-1][j-1]+1;
      else m[i][j] = max(m[i-1][j],m[i][j-1]);
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
  for (int i=0;i<100;i++){
    input >> len1 >> len2 >> x >> y;
    output << lcs(x,y,len1,len2) << endl;
  }
}

#include<iostream>
#include <sstream>
#include<vector>
#include<algorithm>
#include<string>
#include<fstream>
using namespace std;

int factorial(int n) {
  return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n;
}

const int Max_Degree = 9;
const int STOP = 10000;
const int Permutation_number = factorial(Max_Degree);
char Sample_In[] = "sample.in";
char Permutation_list[] = "permutation_list.txt";
char rmst_length[] = "./rmst_length -p -l < sample.in";

class Verify {
 public:
  Verify();
  bool Permutation_generate(char which[]);
  bool get_length();
  /*** DATA ***/
  vector<int> permutation_sequence;
  int count;
};

Verify::Verify() {
  for (int i = 1; i <= Max_Degree; i++) {
    permutation_sequence.push_back(i);
  }
  count = 0;
}
bool Verify::Permutation_generate(char which[]) {
  ofstream Print_permutation(Permutation_list, ios::out | ios::trunc);
  if (!Print_permutation) {
    cout << endl << endl << "*** Openning permutation_list.txt error! ***" << endl << endl;
    exit(1);
  }
  count = 0;
  int test = 0;
  do {
    test++;

    for (vector<int>::iterator iter = permutation_sequence.begin(); iter != permutation_sequence.end(); iter++) {
      Print_permutation << *iter;
    }
    Print_permutation << endl;
    count++;
    ofstream Read_Sample(Sample_In, ios::out | ios::trunc);
    if (!Read_Sample) {
      cout << endl << endl << "*** Openning sample.in error! ***" << endl << endl;
      exit(1);
    }
    Read_Sample << Max_Degree << endl;
    int j = 1;
    for (vector<int>::iterator iter = permutation_sequence.begin(); iter != permutation_sequence.end(); iter++) {
      Read_Sample << *iter << " " << j << endl;
      j++;
    }
    system(which);
    Read_Sample.close();
    
    //if(test == STOP) return true;

  }	while (next_permutation(permutation_sequence.begin(), permutation_sequence.end()));
  Print_permutation.close();
  if (count != Permutation_number) {
    cout << endl << "* count != Permutation_number *" << endl;
    exit(0);
  }
}
bool Verify::get_length() {
  Permutation_generate(rmst_length);
  return true;
}

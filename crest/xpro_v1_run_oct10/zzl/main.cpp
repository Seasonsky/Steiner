#include "Def.h"
#include "Verify.h"
int main() {
  cout << endl << "++++++++++++++++++++++++ BEGIN OF PROGRAM ++++++++++++++++++++++++" << endl;
  clock_t begin = clock();
  Verify verify;
  verify.Permutation_generate();

  clock_t end = clock();
  double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
  cout << endl << "------ PRINTING ------" << endl;
  cout << endl << "Time elapsed= " << elapsed_secs << endl;
  cout << endl << "------ PRINTING ------" << endl;
  cout << endl << "++++++++++++++++++++++++ END OF PROGRAM ++++++++++++++++++++++++" << endl;
  return 0;
}

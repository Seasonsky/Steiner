#include <iostream>
using namespace std;
#include "rmst.h"

int main() {

  cout << endl << "########## Begin of Program ##########" << endl;

  Plane plane;
  RMST rmst(plane);

  rmst.travel_trees();

  rmst.output_trees(plane);

  cout << endl << "########### End of Program ###########" << endl;

  cout << endl;
  return 0;
}

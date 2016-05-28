#include <iostream>
using namespace std;
#include "rmst.h"

int main() {

  cout << endl << "########## Begin of Program ##########" << endl;
  
  Utilities util;
  Plane plane;
  cout << plane.terminals;
  RMST rmst(plane);

  rmst.travel_trees();

  util.output_tree_queue(plane,rmst);

  cout << endl << "########### End of Program ###########" << endl;

  cout << endl;
  return 0;
}

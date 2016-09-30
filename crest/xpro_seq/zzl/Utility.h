#include "Def.h"
#include "Atom.h"

class Utility {
 public:

  // Permutation<->String
  string permutation2string(vector<int> sequence);
  vector<int> string2permutation(string line);

  // Printing
  void print_vector(vector<int> sequence);
  void print_vector(vector<vector<int> > sequences);
  void print_vector_string(vector<string>);
  void print_vector_atom(vector<Atom> atoms);
  void print_vector_atom(vector<vector<Atom> > atoms);
  
};
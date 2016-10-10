#include "Def.h"
#include "Calculation.h"
#include "Utility.h"
#include "Table.h"

class Verify {

 public:

  Verify();
  bool Permutation_generate();
  bool Permutation_process();

  void linear_divide();

  void sort_atoms();

  vector<int> modeling_district_powv(vector<Atom> district_atom);
  void mapping_powv_stream(); 

  void quantify_real_distance();
  void fill_permutation_powvs();
  vector<int> retrieve_permutation(const string& str);
  void fill_permutation_districts();

  int compute_powv_length(vector<int>& powvs, int iter, vector<int>& real_distance);
  vector<int> compute_district_lengths(vector<int>& powvs, vector<int>& real_distance);
  void compute_permutation_lengths();
  void compute_permutation_minimal_length();

  /*** DATA ***/
  vector<int> Permutation_sequence;
  vector<vector<int> > Permutation_district_location; 
  vector<Atom> Permutation_array_unsorted; 
  vector<Atom> Permutation_array_sorted;
  vector<vector<Atom> > Permutation_districts;
  vector<string> Permutation_powv_stream; 
  vector<vector<int> > Permutation_POWVs; 
  vector<vector<int> > Permutation_real_distance;
  vector<vector<int> > Permutation_district_lengths;
  vector<int> Permutation_lengths;
  unsigned int District_number;
  int Permutation_minimal_length;
  unsigned int Count;

  Table table_list;
  const unsigned int Degree = 20;
  const unsigned int District_Length = 6;
  unsigned int Permutation_number;
  unsigned int STOP = 100000;
  
};

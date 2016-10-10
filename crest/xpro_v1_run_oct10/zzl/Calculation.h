#include "Def.h"

class Calculation {
 public:
  int factorial(int n);
  int compute_distance_two(int x1, int x2, int y1, int y2);
  int compute_district_distance(vector<int>& powv, int powv_size);
  vector<int> compose_powv_distance(vector<int> district);
  bool find_str(const string& strng, const string& str);
  int linear_divide_number(unsigned int degree, unsigned int district_length);
  int get_length(string str);
  string extract_powvs_string(string str, int permutation_length);
};

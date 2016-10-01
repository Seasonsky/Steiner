#include "Calculation.h"

int Calculation::factorial(int n) {
  return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n;
}

int Calculation::compute_distance_two(int x1, int x2, int y1, int y2) {
  return std::abs(x1-x2) + std::abs(y1-y2);
}

bool Calculation::find_str(const string& strng, const string& str) {
  for (int i = 0; i < str.size(); i++) {
    if (str[i] != strng[i]) return false;
  }
  return true;
}

int Calculation::linear_divide_number(unsigned int degree, unsigned int district_length) {
  if(district_length >= degree) {
    cout << endl << "*** district_length cannot be >= Degree ***" << endl;
    exit(-1);
  }
  if((float) degree / (float) district_length > 0) {
     return degree / district_length + 1 + degree;
  } else return degree / district_length + degree;
}

int Calculation::compute_district_distance(vector<int>& powv, int powv_size) {
  int size = powv.size();
  if(size != powv_size) {
    cout << endl << "*** powv.size ***" << endl;
    exit(-1);
  } else {
    return 0; //compute_real_distance(powv);
  }
}
vector<int> Calculation::compose_powv_distance(vector<int> district) {
  int size = district.size();
  vector<int> powv_distance;
  for(int i = 1; i < size; i++) {
    powv_distance.push_back(district[i] - district[i-1]);
  }
  return powv_distance;
}
string Calculation::extract_powvs_string(string str, int permutation_length) {
  string strng;
  int size = str.length();
  for(int i = permutation_length + 2; i < size; i++) {
    strng.push_back(str[i]);
  }
  return strng;
}
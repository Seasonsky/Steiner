#include "Verify.h"

Verify::Verify() {
  District_number = 0;
  Count = 0;
  Calculation cal;
  Permutation_number = cal.factorial(Degree);
  for (int i = 1; i <= Degree; i++) {
    Permutation_sequence.push_back(i);
  }
}

void Verify::linear_divide() {
  Atom atom;
  vector<int> district_loaction;
  vector<int> permutation = Permutation_sequence;
  int span = District_Length - 1;
  int number = permutation.size();
  int k = 0;
  int district_number = 0;
  int iter = 0;
  Permutation_district_location.clear();
  Permutation_array_unsorted.clear();
  for(int i = 0; i < number && i + span < number; i += span) {
    k = 0;
    district_number++;
    district_loaction.clear();
    for(int j = i; j <= i + span; j++) {
      k++;
      atom.location = permutation[j];
      district_loaction.push_back(atom.location);
      atom.order = k;
      atom.district = district_number;
      Permutation_array_unsorted.push_back(atom);
    }
    Permutation_district_location.push_back(district_loaction);
    iter = i;
  }
  if(iter+span == number-1) {
    District_number = district_number;
    return;
  }
  k = 0;
  district_number++;
  district_loaction.clear();
  for(int i = iter+span; i < number; i++) {
    k++;
    atom.location = permutation[i];
    district_loaction.push_back(atom.location);
    atom.order = k;
    atom.district = district_number;
    Permutation_array_unsorted.push_back(atom);
  }
  Permutation_district_location.push_back(district_loaction);
  District_number = district_number;
  return;
}

void  Verify::sort_atoms() {
  Permutation_array_sorted.clear();
  int size = Permutation_array_unsorted.size();
  Atom atom;
  for(int i = 0; i < size; i++) {
    Permutation_array_sorted.push_back(atom);
  }
  int Counting[Degree+1];
  for(int i = 0; i < Degree+1; i++) {
    Counting[i] = 0;
  }
  for(int i = 0; i < size; i++) {
    Counting[Permutation_array_unsorted[i].location]++;
  }
  for(int i = 1; i < Degree+1; i++) {
    Counting[i] = Counting[i-1] + Counting[i];
  }
  for(int i = size - 1; i >= 0; i--) {
    Permutation_array_sorted[Counting[Permutation_array_unsorted[i].location]-1] 
    = Permutation_array_unsorted[i];
    Counting[Permutation_array_unsorted[i].location]--;
  }
}

void Verify::mapping_powv_stream() {
  Permutation_powv_stream.clear();
  string str;
  Utility util;
  for(int i= 0; i < District_number; i++) {
    str = util.permutation2string(modeling_district_powv(Permutation_districts[i]));
    Permutation_powv_stream.push_back(str);
  }
  return;
}

vector<int> Verify::modeling_district_powv(vector<Atom> district_atom) {
  vector<int> powv;
  Atom atom;
  int size = district_atom.size();
  for(int i = 0; i < size; i++) {
    powv.push_back(0);
  }
    for(int i = 0; i < size; i++) {
    atom = district_atom[i];
    powv[atom.order-1] = i+1;
    }
    return powv;
}

void Verify::fill_permutation_districts() {
  Permutation_districts.clear();
  int size = Permutation_array_sorted.size();
  Atom atom;
  for(int i = 0; i < District_number; i++) {
    vector<Atom> atoms;
    Permutation_districts.push_back(atoms);
  }
  
  for(int i = 0; i < size; i++) {
    atom = Permutation_array_sorted[i];
    Permutation_districts[atom.district-1].push_back(atom);
  }
  return;
}

void Verify::quantify_real_distance() {
  int size_i = Permutation_districts.size();
  int size_j = 0;
  Permutation_real_distance.clear();
  vector<int> distance;
  for(int i = 0; i < size_i; i++) {
    size_j = Permutation_districts[i].size();
    distance.clear();
    for(int j = 1; j < size_j; j++) {
      distance.push_back(Permutation_districts[i][j].location - Permutation_districts[i][j-1].location);
    }
    Permutation_real_distance.push_back(distance);
  }
}

vector<int> Verify::retrieve_permutation(const string& str) {
  if(str.length() < 2) {
    cout << endl << "permutation.size should be >= 2" << endl;
    exit(-1);
  } else if(str.length() > 7) {
    cout << endl << "permutation.size should be <= 7" << endl;
    exit(-1);
  }
  string strng;
  Calculation cal;
  Utility util;
  unsigned int index = str.length() - 2;
  int size = table_list.tables[index].size();
  for(int i = 0; i < size; i++) {
    strng = table_list.tables[index][i];
    if(cal.find_str(strng, str)) {
      return util.string2permutation(cal.extract_powvs_string(strng, str.length()));
    }
  }
  cout << "*** Cannot find the permutation: " << str << endl;
  exit(-1);
}

void Verify::fill_permutation_powvs() {
  Permutation_POWVs.clear();
  int size = Permutation_powv_stream.size();
  vector<int> powv;
  for(int i = 0; i < size; i++) {
    Permutation_POWVs.push_back(retrieve_permutation(Permutation_powv_stream[i]));
  }
  return;
}

int Verify::compute_powv_length(vector<int>& powvs, int iter, vector<int>& real_distance) {
   int powv_size = 2 * real_distance.size();
   int half_size = real_distance.size();
   int start = iter * powv_size;
   int end = iter * powv_size + half_size;
   int sum = 0;
   for(int i = start; i < end; i++) {
     sum += powvs[i];
   }
   start = iter * powv_size + half_size;
   end = (iter +1) * powv_size;
   for(int i = start; i < end; i++) {
     sum = sum + powvs[i] * real_distance[i-start];
   }
   return sum;
}

vector<int> Verify::compute_district_lengths(vector<int>& powvs, vector<int>& real_distance) {
  int size = powvs.size();
  int powv_size = 2 * real_distance.size();
  int powv_number = size / powv_size;
  vector<int> lengths;
  for(int i = 0; i < powv_number; i++) {
    lengths.push_back(compute_powv_length(powvs, i, real_distance));
  }
  return lengths;
}

void Verify::compute_permutation_lengths() {
  Permutation_lengths.clear();
  Permutation_district_lengths.clear();
  //vector<int> temp;
  for(int i = 0; i < District_number; i++) {
    //Permutation_lengths.push_back(compute_district_lengths(Permutation_POWVs[i], Permutation_real_distance[i]));
    Permutation_district_lengths.push_back(
      compute_district_lengths(Permutation_POWVs[i], Permutation_real_distance[i])
      );
    vector<int>::iterator iter = std::min_element(std::begin(Permutation_district_lengths[i]), std::end(Permutation_district_lengths[i]));
    Permutation_lengths.push_back(*iter); 
  }
}

void Verify::compute_permutation_minimal_length() {
  int size = Permutation_lengths.size();
  Permutation_minimal_length = 0;
  for(int i = 0; i < size; i++) {
    Permutation_minimal_length += Permutation_lengths[i];
  }
}

bool Verify::Permutation_examine() {
  table_list.routine();
  
  if(Permutation_districts.size() != District_number) {
    cout << endl << "*** Permutation_districts.size() != District_number ***" << endl;
    exit(-1);
  }

  if(Permutation_district_location.size() != District_number) {
    cout << endl << "*** Permutation_district_location != District_number ***" << endl;
    exit(-1);
  }
  if(Permutation_powv_stream.size() != District_number) {
    cout << endl << "*** Permutation_powv_stream.size() != District_number ***" << endl;
    exit(-1);
  }
  if(Permutation_real_distance.size() != District_number) {
    cout << endl << "*** Permutation_real_distance.size() != District_number ***" << endl;
    exit(-1);
  }

  cout << endl;
  Permutation_dump();
  cout << endl;
}

bool Verify::Permutation_generate() {
  vector<string> permutation_stream;
  char Permutation_list[] = "permutation_list.txt";
  vector<Atom> atoms;
  int test = 0;
  ofstream Print_permutation(Permutation_list, ios::out | ios::trunc);
  if (!Print_permutation) {
    cout << endl << endl << "*** Openning permutation_list.txt error! ***" << endl << endl;
    exit(1);
  }
  Utility util;
  Calculation cal;
  int iter = -1;
  do {
    test++;
    iter++;
    for (vector<int>::iterator iter = Permutation_sequence.begin(); iter != Permutation_sequence.end(); iter++) {
      Print_permutation << *iter;
    }
    Print_permutation << endl;

    Permutation_process();

    //cout << Permutation_minimal_length << endl;

    Permutation_examine();

    if(test == STOP) return true; 
    Count++;
  }	while (next_permutation(Permutation_sequence.begin(), Permutation_sequence.end()));
  Print_permutation.close();
  
  if (Count != Permutation_number) {
    cout << endl << "* Count != Permutation_number *" << endl;
    exit(0);
  }
  return true;
}

bool Verify::Permutation_process() {

  linear_divide();
  sort_atoms();
  fill_permutation_districts();
  mapping_powv_stream();
  fill_permutation_powvs();

  quantify_real_distance();
  compute_permutation_lengths();
  compute_permutation_minimal_length();

  return true;
}

void Verify::Permutation_dump() {
  Utility util;
  cout << endl << "--- Permutation_dump ---";
  cout << endl << "Permutation_sequence= ";
  util.print_vector(Permutation_sequence);
  cout << endl << "Permutation_array::unsorted= ";
  util.print_vector_atom(Permutation_array_unsorted);

  cout << endl << "Permutation_array::sorted= ";
  util.print_vector_atom(Permutation_array_sorted);

  cout << endl << "Permutation_district_location= ";
  util.print_vector(Permutation_district_location);

  cout << endl << "Permutaion_disticts= ";
  util.print_vector_atom(Permutation_districts);

  cout << endl << "Permutation_powv_stream= ";
  util.print_vector_string(Permutation_powv_stream);

  cout << endl << "Permutation_POWVs= ";
  util.print_vector(Permutation_POWVs);

  cout << endl << "Permutation_real_distance= ";
  util.print_vector(Permutation_real_distance);

  cout << endl << "Permutation_district_lengths= ";
  util.print_vector(Permutation_district_lengths);

  cout << endl << "Permutation_lengths= ";
  util.print_vector(Permutation_lengths);

  cout << endl << "Permutation_minimal_length= ";
  cout << Permutation_minimal_length << endl;

  cout << endl << "### Permutation_dump ###";
}

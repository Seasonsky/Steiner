#include "Utility.h"
const char ZERO = '0';

// Permutation<->String
string Utility::permutation2string(vector<int> sequence) {
  string str;
  for (int i = 0; i < sequence.size(); i++) {
    str.push_back(sequence[i] + ZERO);
  }
  return str;
}
vector<int> Utility::string2permutation(string line) {
  vector<int> permutation;
  for (int i = 0; i < line.size(); i++) {
    permutation.push_back(line[i] - ZERO);
  }
  return permutation;
}

// Printing
void Utility::print_vector(vector<int> sequence) {
  int size = sequence.size(); 
  for (int i = 0; i < size; i++) {
    cout << sequence[i] << ' ';
  }
}
void Utility::print_vector(vector<vector<int> > sequences) {
  int size_i = sequences.size();
  for(int i = 0; i < size_i; i++) {
    print_vector(sequences[i]);
    cout << "  ";
  }
}
void Utility::print_vector_string(vector<string> stream) {
  int size = stream.size();
  for(int i = 0; i < size; i++) {
    cout << stream[i] << "  ";
    //cout << stream[i] << endl;
  } 
}
void Utility::print_vector_atom(vector<Atom> atoms) {
  int size = atoms.size();
  for(int i = 0; i < size; i++) {
    cout << atoms[i].location << " " << atoms[i].order << " " << atoms[i].district << "  ";
  }
}
void Utility::print_vector_atom(vector<vector<Atom> > atoms) {
  int size_i = atoms.size();
  for(int i = 0; i < size_i; i++) {
    print_vector_atom(atoms[i]);
    cout << "  "; 
  }
}
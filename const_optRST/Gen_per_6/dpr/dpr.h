#include<iostream>
#include<vector>
using namespace std;

class DATA {
 public:
 DATA();
 void read_data();
 void print_table(const unsigned int which);
 void compare();
 vector<string> powv;
 vector<string> opt;
 vector<unsigned int> permutation_sequence;

string permutation2string(vector<unsigned int> sequence);
vector<unsigned int> string2permutation(string line);
void print_vector(vector<unsigned int> sequence);
void print_vector(vector<vector<unsigned int> > sequences);
void print_vector_string(vector<string> stream);
bool find_subset(string permutation, string record);
vector<string> retrieve_permutation(string permutation, vector<string> table);
unsigned int per_sharp(string record);
bool control_group(vector<string> powv, vector<string> opt);
};

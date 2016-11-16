#include "dpr.h"
#include<algorithm>
#include <fstream>
const unsigned int DEGREE = 6;
const unsigned int EXCL = 33;
const unsigned int CHU = 1;
const unsigned int ME = 2;
char powv_6[] = "POINTS/POWVs_6.dat";
char powv_7[] = "POINTS/POWVs_7.dat";
char per_6[] = "TERMINALS/PER_6.dat";
char per_7[] = "TERMINALS/PER_7.dat";
const char ZERO = '0';
const unsigned int STOP = 3;

void DATA::compare() {
  read_data();
  string permutation;
  vector<string> powv_permutation;
  vector<string> opt_permutation;
  unsigned int test = 0;
  do {
   test++;
// --------------------------
    permutation = permutation2string(permutation_sequence);
    powv_permutation = retrieve_permutation(permutation, powv);
    opt_permutation = retrieve_permutation(permutation, opt);
    if(powv_permutation.size()!=opt_permutation.size()) {
       cout << endl <<"!!! powv.size()!=opt_permutation.size() !!!" << endl;
       exit(-1);
    }
    if(!control_group(powv_permutation, opt_permutation)) {
       cout << endl <<"!!! powv !!!"<< endl;
       exit(-1);
    }
// --------------------------
    //if(test==STOP) exit(-1);
  } while (next_permutation(permutation_sequence.begin(), permutation_sequence.end()));

}

DATA::DATA() {

  for (unsigned int i = 1; i <= DEGREE; i++) {
    permutation_sequence.push_back(i);
  }

}

void DATA::read_data() {

  string line;
  ifstream Read_POWVs;


      Read_POWVs.open(powv_6);

      //Read_POWVs.open(powv_7);

    while (!Read_POWVs.eof()) {
    line.clear();
    Read_POWVs >> line;
    powv.push_back(line);
    } 
    powv.pop_back(); // for removing the last element
    Read_POWVs.close();


  ifstream Read_opt;

      Read_opt.open(per_6);

      //Read_POWVs.open(powv_7);

    while (!Read_opt.eof()) {
    line.clear();
    Read_opt >> line;
    opt.push_back(line);
    } 
    opt.pop_back(); // for removing the last element
    Read_opt.close();

}

void DATA::print_table(const unsigned int which) {

   if(which==CHU) {
     for(unsigned int i=0; i<powv.size(); i++) cout <<powv[i]<<endl;

   } else if(which==ME) {

     for(unsigned int i=0; i<opt.size(); i++) cout <<opt[i]<<endl;
   }

}

bool DATA::control_group(vector<string> powv, vector<string> opt) {

    string powv_string, opt_string;
    bool single = false;
    if(powv.size()!=opt.size()) {
      cout << endl <<"!!! powv.size()!=opt.size() !!!"<<endl;
      exit(-1);
    }
    for(int i=0; i<powv.size(); i++) {
      if(powv[i].size()!=opt[i].size()) {
         cout << endl <<"!!! powv.size()!=opt.size() !!!"<<endl;
         exit(-1);
      }
      powv_string = powv[i];
      single = false;
      for(int j=0; j<opt.size(); j++) {
        opt_string = opt[j];
        if(powv_string==opt_string) {
          single = true; 
          break;
        }
      }
      if(single==false) {

        cout << endl <<"!!! powv_control_group !!!"<<endl;
        cout <<endl<<"powv=";
        print_vector_string(powv);
        cout<<endl<<"opt=";
        print_vector_string(opt);
        return false;
      }
    }
   return true;
}


vector<string> DATA::retrieve_permutation(string permutation, vector<string> table) {

  unsigned int count = 0;
  vector<string> stream;
   for(int i=0; i<table.size(); i++) {

      if(find_subset(permutation, table[i])) {

         count = per_sharp(table[i]);
         for(int j=i+1; j<=count+i; j++) {

            stream.push_back(table[j]);
         }
         return stream;
      }
   }

   cout << endl <<"!!! Cannot find the permutation !!!"<<endl;
   exit(-1);

}

unsigned int DATA::per_sharp(string record) {

   for(int i=0; i<record.size(); i++) {

      if(record[i]==':') return record[i+1]-EXCL;
   }

}

bool DATA::find_subset(string permutation, string record) {

   for(int i=0; i<permutation.size(); i++) {

      if(permutation[i]!=record[i]) return false;
   }

   return true;

}

string DATA::permutation2string(vector<unsigned int> sequence) {
  string str;
  for (unsigned int i = 0; i < sequence.size(); i++) {
    str.push_back(sequence[i] + ZERO);
  }
  return str;
}
vector<unsigned int> DATA::string2permutation(string line) {
  vector<unsigned int> permutation;
  for (unsigned int i = 0; i < line.size(); i++) {
    permutation.push_back(line[i] - ZERO);
  }
  return permutation;
}

// Printing
void DATA::print_vector(vector<unsigned int> sequence) {
  unsigned int size = sequence.size(); 
  for (unsigned int i = 0; i < size; i++) {
    cout << sequence[i] << ' ';
  }
}
void DATA::print_vector(vector<vector<unsigned int> > sequences) {
  unsigned int size_i = sequences.size();
  for(unsigned int i = 0; i < size_i; i++) {
    print_vector(sequences[i]);
    cout << "  ";
  }
}
void DATA::print_vector_string(vector<string> stream) {
  unsigned int size = stream.size();
  for(unsigned int i = 0; i < size; i++) {
    cout << stream[i] << "  ";
    //cout << stream[i] << endl;
  } 
}

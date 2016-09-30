#include "Table.h"
#include "Calculation.h"
#include "Utility.h"

char p2[] = "POINTS/P2.dat";
char p3[] = "POINTS/P3.dat";
char p4[] = "POINTS/P4.dat";
char p5[] = "POINTS/P5.dat";
char p6[] = "POINTS/P6.dat";
char p7[] = "POINTS/P7.dat";

Table::Table() {
  ifstream Read_POWVs;
  string line;
  vector<string> table;
  for(int i = 2; i <= 7; i++) {
    table.clear();
    switch (i) {
    case 2:
      Read_POWVs.open(p2);
      break;
    case 3:
      Read_POWVs.open(p3);
      break;
    case 4:
      Read_POWVs.open(p4);
      break;
    case 5:
      Read_POWVs.open(p5);
      break;
    case 6:
      Read_POWVs.open(p6);
      break;
    case 7:
      Read_POWVs.open(p7);
      break;
    default:
      {
        cout << endl << "*Cannot open POWVs files*" << endl;
        exit(1);
      }
    }
    while (!Read_POWVs.eof()) {
    line.clear();
    Read_POWVs >> line;
    table.push_back(line);
    } 
    table.pop_back(); // for removing the last element
    tables.push_back(table);
    Read_POWVs.close();
  }
  size = tables.size();
}

void Table::routine() {
  if(size != (7-2+1)) {
    cout << "*** Table.size() ***" << endl;
    exit(1);
  }
  Utility util;
  Calculation cal;
  for(int i = 0; i < size; i++) {
    if(tables[i].size() != cal.factorial(i+2)) {
      cout << "*** Talbe[" << i << "].size() ***" << endl;
      exit(1);
    }
  }
  /*
  for(int i = 0; i < size; i++) {
    util.print_vector_string(tables[i]);
    cout << endl;
  } 
  */
}

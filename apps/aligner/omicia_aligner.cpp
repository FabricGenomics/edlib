/*
 * omicia_aligner.cpp
 * bases on aligner.cpp
 * to run in the Fabric Genomics Inc. environment
 *
 * input sequences will be read over STDIN
 * output (via STDOUT) of the alignment is in cigar format only
 *
 */

#include <unistd.h>
#include <cstdio>
#include <string>
#include <sstream>
#include <iostream>
#include <stdio.h>
#include "edlib.h"

using namespace std;

int main() {
  string line;
  getline(cin, line);
  
  istringstream iss(line);
  string reference = "";
  string query = "";
  
  iss >> reference;
  iss >> query;

  // printf("query: %s\n", query.c_str());
  // printf("reference: %s\n", reference.c_str()); 
  EdlibAlignResult result = edlibAlign(query.c_str(), query.length(), reference.c_str(), reference.length(), edlibNewAlignConfig(42, EDLIB_MODE_HW, EDLIB_TASK_PATH));
  // printf("distance %d\n", result.editDistance);
  char* cigar = edlibAlignmentToCigar(result.alignment, result.alignmentLength, EDLIB_CIGAR_EXTENDED);
  printf("%s\n", cigar);
  free(cigar);
  edlibFreeAlignResult(result);
}


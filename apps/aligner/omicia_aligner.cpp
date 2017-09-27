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
#include "edlib.h"


using namespace std;

int main() {
    string line;
    string stdin_content;
    string reference, query;
    stdin_content = "";


    int numBestSeqs = 0;
    int kArg = -1;


    while (getline(cin, line)) {
        if (line.length() == 0)
            break;
        stdin_content += line;

    }
    istringstream iss(stdin_content);
    iss >> reference;
    iss >> query;

    EdlibAlignResult result = edlibAlign(query.c_str(), query.length(), reference.c_str(), reference.length(),
                                         edlibNewAlignConfig(-1, EDLIB_MODE_NW, EDLIB_TASK_PATH, NULL, 0));

    // printf("distance %d\n", result.editDistance);
    char *cigar = edlibAlignmentToCigar(result.alignment, result.alignmentLength, EDLIB_CIGAR_EXTENDED);

//        cout << reference << endl;
//        cout << query << endl;

    printf("%s\n", cigar);
    free(cigar);
    edlibFreeAlignResult(result);
}

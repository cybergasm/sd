/*
 * CfgFile.cpp
 *
 *  Created on: May 1, 2012
 *      Author: emint
 */

#include "CfgFile.h"

#include <iostream>
#include <fstream>
CfgFile::CfgFile(string fileName) :
  cfgFileName(fileName) {
  ifstream cfgFile(cfgFileName.c_str(), ios::in);

  string currentPair;

  if (cfgFile.is_open()) {
    while (cfgFile.good()) {
      getline(cfgFile, currentPair);
      unsigned int delimPos = currentPair.find(":");

      //a comment or invalid string
      if (currentPair[0] == '#' || delimPos == string::npos || delimPos == 0) {
        continue;
      }

      string key = currentPair.substr(0, delimPos);
      string value = currentPair.substr(delimPos + 1, currentPair.length() - 1);

      //If either is empty we cry
      if (key == "" || value == "") {
        continue;
      }

      set<string>& values = parsedFile[key];
      values.insert(value);
    }
  } else {
    cerr << "Error reading file: " << fileName << endl;
  }
}

CfgFile::~CfgFile() {
  // TODO Auto-generated destructor stub
}

set<string> CfgFile::get(string key) const {
  if (parsedFile.find(key) == parsedFile.end()) {
    return set<string>();
  }
  return parsedFile.find(key)->second;
}

const map<string, set<string> >& CfgFile::getAllPairs() {
  return parsedFile;
}

void CfgFile::printFile() {

  for (map<string, set<string> >::iterator fileIterator = parsedFile.begin(); fileIterator
      != parsedFile.end(); ++fileIterator) {
    cout << "Values for " << fileIterator->first << ": " << endl;
    set<string> values = fileIterator->second;

    for (set<string>::iterator valueIter = values.begin(); valueIter
        != values.end(); ++valueIter) {
      cout << *valueIter << endl;
    }
  }
}

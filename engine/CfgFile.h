/*
 * CfgFile.h
 *
 *  Class which reads a file of <key, value> pairs in 'key:value' format. Accessed by calling get(key)
 *  which returns a set of found values for that key or null.
 *
 *  Created on: May 1, 2012
 *      Author: emint
 */

#ifndef CFGFILE_H_
#define CFGFILE_H_

#include <string>
#include <map>
#include <set>

using namespace std;

class CfgFile {
  public:
    CfgFile(string fileName);
    virtual ~CfgFile();

    /**
     * Prints out the parsed file to stdout
     */
    void printFile();

    /**
     * Returns value associated with key
     */
    set<string> get(string key) const;

    /**
     * Returns all key value pairs. Note that this is returned
     * as a reference in case there are many such pairs.
     */
    const map<string, set<string> >& getAllPairs();

  private:
    string cfgFileName;
    map<string, set<string> > parsedFile;

};

#endif /* CFGFILE_H_ */

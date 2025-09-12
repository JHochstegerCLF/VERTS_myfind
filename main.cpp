// C++ Program to illustrate the use of filesystem classes
// and features
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <assert.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// for simplicity
using namespace std;
using namespace std::filesystem;

// converts a string to lower case
string toLowerCase(const string &str) {
    string result = str;
    transform(result.begin(), result.end(), result.begin(), static_cast<int(*)(int)>(tolower));
    return result;
}

void searchFolder(const path& path, const string& key, const bool recursive,const bool caseInsensitive) {
    // verify that path is a existing path and directory
    if(exists(path) &&
        is_directory(path)) {
        string tempKey = key;
        // iterate over every entry of the current directory defined in @path
        for(const auto& entry : directory_iterator(path)) {
            string tempFilename = entry.path().filename().string();
            // if case insensitive, make tempKey and tempFilename to lower case
            if(caseInsensitive) {
                tempKey = toLowerCase(tempKey);
                tempFilename = toLowerCase(tempFilename);
            }
            // If the file was found it gets saved
            if(tempFilename == tempKey) {
                cout << entry.path().string() << endl; // TODO: somehow return the found path to parent
            }
            // Recursive call if recursive flag is set and if entry is a directory
            if(recursive && is_directory(entry)) {
                searchFolder(entry.path().string(), key, recursive, caseInsensitive);
            }
        }
    }
}


void test() {
    path directorypath = "./ebene1";

    cout << "--- Search for G.txt case sensitive ---" << endl;
    searchFolder(directorypath, "G.txt", true, false);

    cout << "--- Search for G.txt case insensitive ---" << endl;
    searchFolder(directorypath, "G.txt", true, true);

    cout << "--- Search for folder case insensitive ---" << endl;
    searchFolder(directorypath, "ebene2.1", true, true);

    cout << "--- Search for dasisteintest.txt case insensitive ---" << endl;
    searchFolder(directorypath, "dasisteintest.txt", true, true);

    directorypath = "./ebene1/ebene2.0/ebene3.1";
    cout << "--- Search for A.txt case sensitive ---" << endl;
    searchFolder(directorypath, "A.txt", false, false);

    cout << "--- Search for a.txt case insensitive ---" << endl;
    searchFolder(directorypath, "a.txt", false, true);

    cout << "---" << endl;
}


int main(int argc, char *argv[]) {

  int c;
  char *dateiname;
  char *programm_name;
  unsigned short Counter_Option_f = 0;
  unsigned short Counter_Option_h = 0;
  unsigned short Counter_Option_v = 0;
  while ((c = getopt(argc, argv, "Ri")) != EOF) {
    switch (c) {
    case '?':
      std::cout << "This is getting out of hand!";
      exit(1);
      /* Das break ist nach exit() eigentlich nicht mehr notwendig. */
      break;
    case 'R':
      cout << "R!";
      break;
    case 'i':
      cout << "i!";
      break;
    default:
      /* assert() dient nur zu Debugzwecken und sollte nur dort eingesetzt sein,
         wo etwas sicher niemals passieren darf. 0 ist in C immer gleich
         "logisch falsch". */
      assert(0);
    }
  }
  for (int i = 1; i < argc; i++) {
    std::string cla = "-";
    std::string arg = argv[i];
    if (arg.find(cla) == std::string::npos) {
      std::cout << "Argument " << i << ": " << argv[i] << std::endl;
    }
  }

  return 0;
}

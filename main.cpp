// C++ Program to illustrate the use of filesystem classes
// and features
#include <algorithm>
#include <assert.h>
#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <iterator>
#include <mutex>
#include <ostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// for simplicity
using namespace std;
using namespace std::filesystem;

// converts a string to lower case
string toLowerCase(const string &str) {
  string result = str;
  transform(result.begin(), result.end(), result.begin(),
            static_cast<int (*)(int)>(tolower));
  return result;
}

void searchFolder(const path &path, const string &key, const bool recursive,
                  const bool caseInsensitive, mutex &print) {
  // verify that path is a existing path and directory
  if (exists(path) && is_directory(path)) {
    string tempKey = key;
    // iterate over every entry of the current directory defined in @path
    for (const auto &entry : directory_iterator(path)) {
      string tempFilename = entry.path().filename().string();
      // if case insensitive, make tempKey and tempFilename to lower case
      if (caseInsensitive) {
        tempKey = toLowerCase(tempKey);
        tempFilename = toLowerCase(tempFilename);
      }
      // If the file was found it gets saved
      if (tempFilename == tempKey) {
        print.lock();
        cout << getpid() << ": " << key << ": " << entry.path().string() << endl;
        print.unlock();
      }
      // Recursive call if recursive flag is set and if entry is a directory
      if (recursive && is_directory(entry)) {
        searchFolder(entry.path().string(), key, recursive, caseInsensitive, print);
      }
    }
  }
}

int main(int argc, char *argv[]) {

  int c;
  bool recursive = false;
  bool insensitive = false;
  mutex print;
  // Command Line Argument Detection
  while ((c = getopt(argc, argv, "Ri")) != EOF) {
    switch (c) {
    case '?':
      cout << "Not a valid argument: " << c << endl;
      exit(1);
    case 'R': // Recusive Search
      recursive = true;
      break;
    case 'i': // case-insensitive Search
      insensitive = true;
      break;
    default:
      assert(0);
    }
  }
  path folder; // The search path
  for (int i = 1; i < argc; i++) {
    string cla = "-";
    string arg = argv[i];
    if (arg.find(cla) == string::npos) { // Checks if the argument is a commandline argument (-<argument>)
      string argument(argv[i]); // Converts to string
      if (empty(folder)) { // If its the first argument its the path
        folder = path(argument);
        continue;
      } else {
        pid_t c_pid = fork(); // Creates Fork for the search

        if (c_pid == -1) { // If -1 error
          perror("fork");
          exit(EXIT_FAILURE);
        } else if (c_pid == 0) { // If child process call function and break out of for loop
          searchFolder(folder, argument, recursive, insensitive, print);
          break;
        }
      }
    }
  }
  while (wait(NULL) > 0); // Wait for all child processes

  return 0;
}

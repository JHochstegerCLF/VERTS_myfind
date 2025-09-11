// C++ Program to illustrate the use of filesystem classes
// and features
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>

// for simplicity
using namespace std;
using namespace std::filesystem;

// converts a string to lower case
string toLowerCase(const string &str) {
    string result = str;
    transform(result.begin(), result.end(), result.begin(), static_cast<int(*)(int)>(tolower));
    return result;
}

void searchRecursive(const path& path, const string& key, const bool caseInsensitive) {
    if(exists(path) &&
        is_directory(path)) {
        // If case insensitive, convert both strings (key & entry.path()) to lowerCase using toLowerCase()
        if(caseInsensitive) {
            string keyLower = toLowerCase(key);
            for (const auto& entry : directory_iterator(path)) {
                string filenameLower = toLowerCase(entry.path().filename().string());
                if(is_directory(entry)) {
                    searchRecursive(entry.path().string(), key, caseInsensitive);
                }else if (filenameLower == keyLower) {
                    cout << entry.path().string() << endl;
                }
            }
            // if not case insensitive don't convert
        }else {
            for(const auto& entry : directory_iterator(path)) {
                if(is_directory(entry)) {
                    searchRecursive(entry.path().string(), key, caseInsensitive);
                }else if(entry.path().filename().string() == key) {
                    cout << entry.path().string() << endl;
                    // save entry somehow and search deeper!
                }
            }
        }
    }
}

void searchFolder(const path& path,const string& key, bool caseInsensitive) {
    if(exists(path) &&
        is_directory(path)) {
        if(caseInsensitive) {
            string keyLower = toLowerCase(key);
            for (const auto& entry : directory_iterator(path)) {
                string filenameLower = toLowerCase(entry.path().filename().string());
                if(filenameLower == keyLower) {
                    cout << entry.path().string() << endl;
                }
            }
        }else {
            for (const auto& entry : directory_iterator(path)) {
                if(entry.path().filename().string() == key) {
                    cout << entry.path().string() << endl;
                }
            }
        }
    }
}

int main()
{
    path directorypath = "./ebene1";
    searchRecursive(directorypath, "G.txt", false);
    cout << "---" << endl;
    searchRecursive(directorypath, "h.txt", true);
    cout << "---" << endl;
    searchRecursive(directorypath, "dasisteintest.txt", true);
    cout << "---" << endl;

    directorypath = "./ebene1/ebene2.0/ebene3.0";
    searchFolder(directorypath, "A.txt", false);
    cout << "---" << endl;
    searchFolder(directorypath, "a.txt", true);
    cout << "---" << endl;
    return 0;
}
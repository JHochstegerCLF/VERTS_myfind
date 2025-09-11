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

void searchFolderRecursive(const path& path, const string& key, const bool caseInsensitive) {
    // verify that path is a existing path and directory
    if(exists(path) &&
        is_directory(path)) {
        // If case insensitive, convert both strings (key & entry.path()) to lowerCase using toLowerCase()
        if(caseInsensitive) {
            string keyLower = toLowerCase(key);
            // iterate over every entry of the current directory defined in @path
            for (const auto& entry : directory_iterator(path)) {
                string filenameLower = toLowerCase(entry.path().filename().string());
                // If the file was found it gets saved
                if (filenameLower == keyLower) {
                    cout << entry.path().string() << endl;
                }
                // Recursive call if entry is a directory
                if(is_directory(entry)) {
                    searchFolderRecursive(entry.path().string(), key, caseInsensitive);
                }
            }
            // if not case insensitive don't convert
        }else {
            // iterate over every entry of the current directory defined in @path
            for(const auto& entry : directory_iterator(path)) {
                // If the file was found it gets saved
                if(entry.path().filename().string() == key) {
                    cout << entry.path().string() << endl;
                    // save entry somehow and search deeper!
                }
                // Recursive call if entry is a directory
                if(is_directory(entry)) {
                    searchFolderRecursive(entry.path().string(), key, caseInsensitive);
                }
            }
        }
    }
}

void searchFolder(const path& path,const string& key, bool caseInsensitive) {
    if(exists(path) &&
        is_directory(path)) {
        // case insensitive
        if(caseInsensitive) {
            string keyLower = toLowerCase(key);
            // iterate over every entry of the current directory defined in @path
            for (const auto& entry : directory_iterator(path)) {
                string filenameLower = toLowerCase(entry.path().filename().string());
                // If the file was found it gets saved
                if(filenameLower == keyLower) {
                    cout << entry.path().string() << endl;
                }
            }
            // case sensitive
        }else {
            // iterate over every entry of the current directory defined in @path
            for (const auto& entry : directory_iterator(path)) {
                if(entry.path().filename().string() == key) {
                    cout << entry.path().string() << endl;
                }
            }
        }
    }
}

void test() {
    path directorypath = "./ebene1";

    cout << "--- Search for G.txt case sensitive ---" << endl;
    searchFolderRecursive(directorypath, "G.txt", false);

    cout << "--- Search for G.txt case insensitive ---" << endl;
    searchFolderRecursive(directorypath, "G.txt", true);

    cout << "--- Search for folder case insensitive ---" << endl;
    searchFolderRecursive(directorypath, "ebene2.1", true);

    cout << "--- Search for dasisteintest.txt case insensitive ---" << endl;
    searchFolderRecursive(directorypath, "dasisteintest.txt", true);

    cout << "--- Search for A.txt case sensitive ---" << endl;
    searchFolder(directorypath, "A.txt", false);

    cout << "--- Search for a.txt case insensitive ---" << endl;
    searchFolder(directorypath, "a.txt", true);

    cout << "---" << endl;
}

int main()
{
    test();
    return 0;
}
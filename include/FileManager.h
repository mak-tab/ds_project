#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "Library.h"
#include <string>

class FileManager {
private:
    string filename;

public:
    FileManager(string file);
    void saveBooks(Library& lib);
    void loadBooks(Library& lib);
};

#endif
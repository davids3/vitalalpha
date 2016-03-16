#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <sstream>

class fileManager//class for managing files
{
    public:
        fileManager();
        ~fileManager();

        void loadContent(const char* filename,
            std::vector< std::vector<std::string> > &attributes,
            std::vector< std::vector<std::string> > &contents);

        void loadContent(const char* filename,
            std::vector< std::vector<std::string> > &attributes,
            std::vector< std::vector<std::string> > &contents, std::string id);

        void loadMap(const char* filename, std::vector< std::vector<int> >& mapVector);

    protected:
    private:
        std::vector<std::string> tempAttributes;
        std::vector<std::string> tempContents;

        bool idFound;
        int state;
};

#endif // FILEMANAGER_H

#include "fileManager.h"

fileManager::fileManager()
{
    //ctor
}

fileManager::~fileManager()
{
    //dtor
}

enum loadState { ATTRIBUTES, CONTENTS };

void fileManager::loadContent(const char* filename,
    std::vector< std::vector<std::string> > &attributes,
    std::vector< std::vector<std::string> > &contents)
{
    //clears the attributes and contents in case the fileManager was called before
    attributes.clear();
    contents.clear();

    //the below algorithm interprets a text file to determine attributes and contents
    //more details are in the overloaded module below
    std::ifstream openfile(filename);
    if(openfile.is_open())
    {
        while(!openfile.eof())
        {
            std::string line;
            std::getline(openfile, line);
            line.erase(std::remove(line.begin(), line.end(),' '), line.end());

            if(line.find("Load=") != std::string::npos)
            {
                state = ATTRIBUTES;
                line.erase(0, line.find('=') + 1);
                tempAttributes.clear();
            }
            else
            {
                state = CONTENTS;
                tempContents.clear();
            }

            line.erase(std::remove(line.begin(), line.end(), '['), line.end());

            std::stringstream str(line);

            while(str)
            {
                std::getline(str, line, ']');
                if(line != "")
                {
                    if(state == ATTRIBUTES)
                        tempAttributes.push_back(line);
                    else
                        tempContents.push_back(line);
                }
            }
            if(state == CONTENTS && tempContents.size() > 0)
            {
                attributes.push_back(tempAttributes);
                contents.push_back(tempContents);
            }
        }
    }
    else
    {

    }
}

void fileManager::loadContent(const char* filename,
    std::vector< std::vector<std::string> > &attributes,
    std::vector< std::vector<std::string> > &contents, std::string id)
{
    attributes.clear();//for when loadcontents is opened more then once
    contents.clear();

    idFound = false;

    std::ifstream openfile(filename);//opens the file
    if(openfile.is_open())
    {
        while(!openfile.eof())//open file NOT at end of file
        {
            std::string line;//temp line contents
            std::getline(openfile, line);//gets contents of file and puts it in line
            line.erase(std::remove(line.begin(), line.end(),' '), line.end());//removes all spaces in line
            std::replace(line.begin(), line.end(), '_', ' ');//replaces underscores with spaces

            if(line.find("Start=[" + id + "]") != std::string::npos)//if the required id is found within the start brackets
            {
                idFound=true;
                continue; //repeats back to start of while loop
            }
            else if(line.find("End=") != std::string::npos && line.find(id) != std::string::npos)
            {
                idFound = false;
                break;
            }

            if(idFound)
            {
                if(line.find("Load=") != std::string::npos)
                {
                    state = ATTRIBUTES;
                    line.erase(0, line.find('=') + 1);//removes "Load=["
                    tempAttributes.clear();
                }
                else
                {
                    state = CONTENTS;
                    tempContents.clear();
                }

                line.erase(std::remove(line.begin(), line.end(), '['), line.end());//removes opening brackets

                std::stringstream str(line);//loads line into str (Position]Axis]Animation]Align])

                while(str)
                {
                    std::getline(str, line, ']');//gets the line up to the first ] sign
                    if(line != "")
                    {
                        if(state == ATTRIBUTES)
                            tempAttributes.push_back(line);
                        else
                            tempContents.push_back(line);
                    }
                }
                if(state == CONTENTS && tempContents.size() > 0)
                {
                    attributes.push_back(tempAttributes);
                    contents.push_back(tempContents);
                }
            }
        }
    }
    else
    {

    }
}

void fileManager::loadMap(const char* filename, std::vector< std::vector<int> >& mapVector)
{
    //loads the map contents
    std::ifstream openfile(filename);
    std::vector <int> tempVector;

    std::string line;

    if(openfile.is_open())
    {
        while (!openfile.eof())
        {
            std::getline(openfile, line);

            std::string tempLine = line.erase(line.find_last_not_of(" ") + 1);
            int space = tempLine.find_first_of(" ");
            if(space == 0)
                tempLine = tempLine.erase(0, space + 1);
            std::stringstream str(tempLine);

            while(!str.eof())
            {
                std::string value;
                getline(str, value, ',');
                if(value.length() > 0)
                    tempVector.push_back(atoi(value.c_str()));
            }
            mapVector.push_back(tempVector);
            tempVector.clear();
        }
    }
    tempVector.clear();
}

//
//

#ifndef INC_320_ASSIGNMENT_1_INSULTGENERATOR_H
#define INC_320_ASSIGNMENT_1_INSULTGENERATOR_H
#include <string>
#include <vector>

using namespace std;

class InsultGenerator {
public:
    InsultGenerator();
    void initialize();
    string talkToMe();
    vector<string> generate(int numberOfInputs);
    void generateAndSave(string file, int numResults);
private: //make the vectors private so other things can't access them. don't want privacy leak
    vector<string> rawData;
    vector<string> column1;
    vector<string> column2;
    vector<string> column3;
};

//class for file exception, throws the error message when you try to read an invalid file
class FileException
{
public:
    FileException(const string& m);
    string& what();
private:        //strings are mutable in C++, need to privatize them
    string message;
};

//class for out of bounds, throws the associated error message when you try feeding in a wrong
//amount of inputs (or in this case, insults)
class NumInsultsOutOfBounds
{
public:
    NumInsultsOutOfBounds(const string& m);
    string& what();
private:
    string message;

};


#endif //INC_320_ASSIGNMENT_1_INSULTGENERATOR_H

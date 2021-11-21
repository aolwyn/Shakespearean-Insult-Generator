//#include "library.h"
#include <stdlib.h>
#include <string>
#include <vector>
#include <time.h>
#include <fstream>
#include <iostream>
#include <algorithm>
#include "insultgenerator_19ahb.h"

//sort using <algorithm> or <sort> ??? both work
using namespace std;



InsultGenerator::InsultGenerator() {}


//goal: generate and save between 1 - 10000 insults.
//classes: file exception, NumInsultsOutOfBounds,
//main is InsultGenerator

/*Stuff:
 * initialize() - load all source phrases from txt file into the attributes
 * talkToMe() - returns a single insult, generated at random
 * generate(int __) - generates requested number of unique insults, returns vector of strings
 * generateAndSave() - generates the requested # of insults & saves them to the filename supplied in alphabetical order
 */

//error class for invalid file
FileException::FileException(const string& m) : message(m) {}

string& FileException::what()  {
    return message;
}

//error class for insult outside of bounds
NumInsultsOutOfBounds::NumInsultsOutOfBounds(const string& m) : message(m) {}

string& NumInsultsOutOfBounds::what() {
    return message;
}




void  InsultGenerator::initialize()
{
    string line;
    ifstream fileIn("../InsultsSource.txt"); //attempt to read in the files from source
    if(fileIn.fail()) //fail check, if you can't read in files print an error message
    {
        throw FileException("Not a valid file.");
        return; //wont actually return anything (void,) but was getting a random error for some reason without it
    }//close reading failure check

    //while(!fileIn.eof()) //while not at end of file, alternate way of doing this
    while(fileIn >> line) //while there's stuff to still read in
    {
        //fileIn >> line; //read in data into a string
        rawData.push_back(line); //push above string into the vector that hold all inputs
    }//end while(!fileInAgain.eof())

    for( int i = 0; i < rawData.size(); i+=3) //separate the three words into their individual columns.
    {
        column1.push_back(rawData[i]);
        column2.push_back(rawData[i+1]);
        column3.push_back(rawData[i+2]);
    }//close for loop

    fileIn.close(); //close file after finished tasks
}//close initialize()


string  InsultGenerator::talkToMe()
{

    int word1 = rand() % column1.size(); //take random elements from within the range
    int word2 = rand() % column2.size();
    int word3 = rand() % column3.size();

    string insult = "Thou " + column1[word1] + " " + column2[word2] + column3[word3] + " !"; //put the full sentence together
    return insult; //return the result

}//close talkToMe()

vector<string> InsultGenerator::generate(int numberOfInputs)
{
    srand(time(0)); //need this otherwise you just get the same random thing from rand() each time?
    if (numberOfInputs < 1 || numberOfInputs > 10000) //out of bounds check
    {
        throw NumInsultsOutOfBounds("Not a valid number. Choose a number between 1 and 10,000.");
        return vector<string>();
    }//close if exception check

    vector<string>generatedInsults; //new vector for the generated things
    for(int i = 0; i< numberOfInputs; i++)
    {
        generatedInsults.push_back(talkToMe()); //send insults to the new vector while not at requested amount
    }//end for loop

    vector<string>  returnedInsults( generatedInsults.begin(), generatedInsults.end()); //for returning, this vector is to be sorted
    sort(returnedInsults.begin(), returnedInsults.end()); //function for sorting. this will sort everything from start -> end alphabetically
    return returnedInsults; // return the sorted, generated insults

}//close generate()

void InsultGenerator::generateAndSave(string file, int numResults) {

    if(numResults < 0 || numResults > 10000) //insult out of bounds check
    {
        throw NumInsultsOutOfBounds("Not a valid number. Choose a number between 1 and 10,000.");
    }//close if

    vector<string> insultsToGive; //create temporary vector for insults
    insultsToGive = generate(numResults); //feed in wanted # of insults
    ofstream outputFile(file);  //create the output file thing
    for(const auto &a : insultsToGive) outputFile << a <<"\n"; //read into file the stuff generated

}//close generateAndSave()


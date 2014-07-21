/**
 * This is a script to generate random xml files to provide world data
 * @author Thomas Rückert
 */

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <cstdlib>
#include <string>
#include <cstring>
using namespace std;

int main(int argc, char *argv[])
{
    cout << "Starting to create files" << endl;
    for (int files = 1; files < argc; files++) {
        ofstream myfile;
        string filename = argv[files];
        filename += ".xml";
        char * filenameChar = new char[filename.length()];
        strcpy(filenameChar,filename.c_str());
        myfile.open (filenameChar);
        cout << "Creating " << filenameChar << endl;
        myfile << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << endl << "<" << argv[files] << ">" << endl;
        for (int i = 0; i < 20; i++) {
            myfile << "<pos" << i << ">" << (rand() % 100)/3 << "</pos" << i << ">" << endl;
        }
        myfile << "</" << argv[files] << ">";
        myfile.close();
    }
    cout << "Done creating" << endl;
    return 0;
}

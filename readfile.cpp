#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int main(void){

    // create an ifstream object to open and accrss the file
    ifstream file;

    // open the file
    file.open("file.txt");

    // exit with an error message and status if the file fails to open
    if(file.fail()){
        cout<<"file failed to open."<<endl;
        return 1;
    }

    // create a stringstream object to help read the file contents
    stringstream buffer;

    // read entire contents of the file into the stringstream buffer
    buffer << file.rdbuf();

    // create the string to store the file contents
    string file_contents;

    // get the string from the stringstream object, store it into the file_contents string
    file_contents = buffer.str();

    cout << file_contents;

    // close the file
    file.close();

    return 0;
}
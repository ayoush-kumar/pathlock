#include <iostream>
#include <fstream>
#include <sstream>
#include <map>


using namespace std;

int main(){
    // store the name of the file to be opened
    string filename;

    // ifstream file object is used to access the file
    ifstream file;

    cout<< "Enter the file name to open (must include .txt or other format of file eq. input.txt)" << endl;
    cin >> filename;

    file.open(filename);

    if(file.fail()){
        cout<< "file failed to open."<< endl;
        return 1;
    }

    string line;
    map<string, int> m;
    while(!file.eof()){
        getline(file, line);

        istringstream iss(line);
        string name;
        int age;

        if( iss >> name >> age){
            m[name] = age;
        }
    }

    file.close();

    // display the data present in the map m
    // for( auto &it : m){
    //     cout<<it.first<<" : "<<it.second<<endl;
    // }


    ofstream outputFile("output.txt");
    if(outputFile.is_open()){
        for(const auto& entry : m){
            outputFile<<entry.first<<" "<<entry.second<<endl;
        }

        cout<<"Data written to 'outputFile.txt'. "<<endl;
        outputFile.close();
    }else{
        cerr<<"unable to open the file"<<endl;
    }

    int x;
    bool flag = false;
    cout<<"Enter a age"<<endl;
    cin>>x;
    for(const auto& it : m){
        if(it.second == x){
            cout<<it.first<<endl;
            flag = true;
        }
    }
    if(flag == false){
        cout<<"user with age "<<x<<" does'nt exsits"<<endl;
    }
   

    return 0;
}

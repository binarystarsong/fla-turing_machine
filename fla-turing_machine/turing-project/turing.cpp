#include <iostream>
#include <string>
#include "turingmachine.h"
#include "input.h"
using namespace std;
bool verbose=1;
string filename;
string input;
bool judge(int argc, char* argv[]){
    bool flag = 0;
    string arg;
    for(int i = 1; i < argc; i++){
        arg = argv[i];
        if(arg[0] == '-'){
            if(arg == "-h" || arg == "--help"){
                cout << "usage: turing [-v|--verbose] [-h|--help] <tm> <input>" << endl;
                exit(0);
            }
            else if(arg == "-v" || arg == "--verbose"){
                flag=1;
            }
            else{
                cerr << "turing: unknown option argument \"" << arg << "\"." <<endl;
                cerr << "Use \"turing --help\" for a complete list of options." << endl;
                exit(-1);
            }
        }
        else{
            if(filename.length() == 0){
                filename = arg;
            }
            else if(input.length() == 0){
                input = arg;
            }
            else{
                cerr << "turing: unknown command \"" << arg << "\"." <<endl;
                cerr << "Use \"turing --help\" for a complete list of options." << endl;
                exit(-1);
            }
        }
    }
    if(filename.length() == 0){
        cerr << "turing: missing argument." <<endl;
        cerr << "Use \"turing --help\" for a complete list of options." << endl;
        exit(-1);
    }
    return flag;
}
int main(int argc, char* argv[]){
    verbose=judge(argc,argv);
    TuringMachine a=readtxt(filename);
    /*cout<<"readout"<<endl;
    cout<<a.blank<<endl;
    cout<<a.start<<endl;
    cout<<a.tapenum<<endl;
    for(int i=0;i<a.state.size();i++){
        cout<<a.state[i]<<" ";
    }
    cout<<endl;
    for(int i=0;i<a.input.size();i++){
        cout<<a.input[i]<<" ";
    }
    cout<<endl;
    for(int i=0;i<a.tapestate.size();i++){
        cout<<a.tapestate[i]<<" ";
    }
    cout<<endl;
    for(int i=0;i<a.delta.size();i++){
        cout<<a.delta[i].curState<<" ";
        for(int j=0;j<a.delta[i].oldSymbol.size();j++) cout<<a.delta[i].oldSymbol[j]<<" ";
        for(int j=0;j<a.delta[i].newSymbol.size();j++) cout<<a.delta[i].newSymbol[j]<<" ";
        for(int j=0;j<a.delta[i].direction.size();j++) cout<<a.delta[i].direction[j]<<" ";
        cout<<a.delta[i].newState<<" ";
        cout<<endl;
    }
    */
    if(verbose) dealinput_verbose(a,input);
    else dealinput(a,input);
}
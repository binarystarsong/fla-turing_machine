#include <iostream>
#include "turingmachine.h"
TuringMachine readtxt(string filename){
    TuringMachine turing;
    fstream file;
    file.open(filename,ios::in);
    if(!file.is_open()) cerr<<"cannot open the file"<<endl;
    else{
        string buf;
        while(getline(file,buf)){
            if(buf[0]==';'||buf.length()==0) continue;
            char line[1024];
            int m=0;
            for(int i=0;i<1024;i++){
                if(buf[i]!=' ') {
                    line[m]=buf[i]; 
                    m++;
                }
            }
            //cerr<<m<<"m"<<endl;
            if(line[0]=='#'){
                if(strlen(line)<4){
                    cerr << "syntax error" << endl;
                    exit(-1);
                }
                if(line[1]=='Q'){
                    if(line[2] != '='  || line[3] != '{' || line[strlen(line) - 1] != '}'){
                        cerr << "syntax error" << endl;
                        exit(-1);
                    }
                    else{
                        string str;
                        for(int j=4;j<strlen(line) ;j++){
                            if(line[j]==','||j==strlen(line)-1) {
                                turing.state.push_back(str);
                                str.clear();
                            }
                            else if((line[j] >= '0'&& line[j] <= '9') || (line[j] >= 'a' && line[j] <='z') || (line[j] >= 'A' && line[j] <='Z') || line[j] == '_') str+=line[j];
                            else{
                                cerr << "syntax error" << endl;
                                cerr<<str<<endl;
                                exit(-1);
                            }
                        }
                    }
                }
                else if(line[1]=='S'){
                    if(line[2] != '='  || line[3] != '{' || line[strlen(line)  - 1] != '}'){
                        cerr << "syntax error" << endl;
                        exit(-1);
                    }
                    else{
                        for(int j=4;j<strlen(line)-1;j++){
                            if(line[j] != ',' && line[j] != ';' && line[j] != '{' && line[j] != '}' && line[j] != '*' && line[j] != '_') {
                                if(j==strlen(line)-2) turing.input.push_back(line[j]);
                                else if(line[j+1]==',') {
                                    turing.input.push_back(line[j]);
                                    j++;
                                }
                                else{
                                    cerr << "syntax error" << endl;
                                    cerr<<line[j]<<endl;
                                    exit(-1);
                                }
                            }
                            else{
                                cerr << "syntax error" << endl;
                                cerr<<line[j]<<endl;
                                exit(-1);
                            }
                        }
                    }
                }
                else if(line[1]=='G'){
                    if(line[2] != '='  || line[3] != '{' || line[strlen(line)  - 1] != '}'){
                        cerr << "syntax error" << endl;
                        exit(-1);
                    }
                    else{
                        for(int j=4;j<strlen(line)-1;j++){
                            if(line[j] != ',' && line[j] != ';' && line[j] != '{' && line[j] != '}' && line[j] != '*') {
                                if(j==strlen(line)-2) turing.tapestate.push_back(line[j]);
                                else if(line[j+1]==',') {
                                    turing.tapestate.push_back(line[j]);
                                    j++;
                                }
                                else{
                                    cerr << "syntax error" << endl;
                                    cerr<<line[j]<<endl;
                                    exit(-1);
                                }
                            }
                            else{
                                cerr << "syntax error" << endl;
                                cerr<<line[j]<<endl;
                                exit(-1);
                            }
                        }
                    }
                }
                else if(line[1]=='q'&&line[2]=='0'){
                    if(line[3]!='='&&strlen(line)<4){
                        cerr << "syntax error" << endl;
                        exit(-1);
                    }
                    else{
                        for(int i=4;i<strlen(line);i++) turing.start+=line[i];
                    }
                }
                else if(line[1]=='B'){
                    if(line[2]!='='){
                        cerr << "syntax error" << endl;
                        exit(-1);
                    }
                    else{
                        for(int i=3;i<strlen(line);i++) turing.blank+=line[i];
                    }
                }
                else if(line[1]=='F'){
                    if(line[2] != '='  || line[3] != '{' || line[strlen(line) - 1] != '}'){
                        cerr << "syntax error" << endl;
                        exit(-1);
                    }
                    else{
                        string str;
                        for(int j=4;j<strlen(line) ;j++){
                            if(line[j]==','||j==strlen(line)-1) {
                                turing.finalstate.push_back(str);
                                str.clear();
                            }
                            else if((line[j] >= '0'&& line[j] <= '9') || (line[j] >= 'a' && line[j] <='z') || (line[j] >= 'A' && line[j] <='Z') || line[j] == '_') str+=line[j];
                            else{
                                cerr << "syntax error" << endl;
                                cerr<<str<<endl;
                                exit(-1);
                            }
                        }
                    }
                }
                else if(line[1]=='N'){
                    string num;
                    int n;
                    if(line[2]!='='){
                        cerr << "syntax error" << endl;
                        exit(-1);
                    }
                    else{
                        for(int i=3;i<strlen(line);i++){
                            if(line[i]>='0'&&line[i]<='9') num+=line[i];
                            else{
                                cerr << "syntax error" << endl;
                                exit(-1);
                            }
                        }
                        sscanf(num.c_str(), "%d", &n);
                        turing.tapenum=n;
                    }
                }
                
            }
            else if(buf[0]!=';'&&buf[0]!=' '){
                    stringstream ss(buf);
                    string s;
                    TransitionFunction tf;
                    ss>>s;
                    if(find(turing.state.begin(), turing.state.end(),s) == turing.state.end()){
                        cerr << "syntax error" << endl;
                        cerr<<s<<endl;
                        exit(-1);
                    }
                    tf.curState=s;
                    ss>>s;
                    for(int i=0;i<s.length();i++){
                        char m=s[i];
                        if(find(turing.tapestate.begin(), turing.tapestate.end(), m) == turing.tapestate.end()&&m!='*'){
                            cerr << "syntax error" << endl;
                            exit(-1);
                        }
                        tf.oldSymbol.push_back(m);
                    }
                    ss>>s;
                    for(int i=0;i<s.length();i++){
                        char m=s[i];
                        if(find(turing.tapestate.begin(), turing.tapestate.end(), m) == turing.tapestate.end()&&m!='*'){
                            cerr << "syntax error" << endl;
                            exit(-1);
                        }
                        tf.newSymbol.push_back(m);
                    }
                    ss>>s;
                    for(int i=0;i<s.length();i++){
                        char m=s[i];
                        if(m=='r')  tf.direction.push_back(1);
                        else if(m=='l') tf.direction.push_back(-1);
                        else if(m=='*') tf.direction.push_back(0);
                        else{
                            cerr<<m;
                            cerr << "syntax error" << endl;
                            exit(-1);
                        }   
                        
                    }
                    ss>>s;
                    if(find(turing.state.begin(), turing.state.end(), s) == turing.state.end()){
                        cerr << "syntax error" << endl;
                        exit(-1);
                    }
                    tf.newState=s;
                    turing.delta.push_back(tf);
                }
            else{
                cerr<<"syntax error"<<endl;
                exit(-1);
            }
        }
    }
    return turing;
}


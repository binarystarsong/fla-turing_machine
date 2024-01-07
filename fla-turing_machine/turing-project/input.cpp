#include <iostream>
#include "input.h"
#include "turingmachine.h"
using namespace std;
void dealinput(TuringMachine turing,string input){
    map<int,char> tape;
    string curstate=turing.start;
    for(int i=0;i<input.length();i++){
        if(find(turing.input.begin(),turing.input.end(), input[i]) ==turing.input.end()){
            cerr<<"illegal input string"<<endl;
            exit(-1);
        }
        tape.insert(pair<int, char>(i, input[i]));
    }
    vector<map<int, char>> tapes;
    tapes.push_back(tape);
    for(int i = 1; i < turing.tapenum; i++){
            tape.clear();
            tape.insert(pair <int, char> (0, '_'));
            tapes.push_back(tape);
    }
    vector<int> indexs(turing.tapenum,0);
    int num=0;
    while(1){
        for(int i = 0; i < turing.tapenum; i++) {
            if(tapes[i].find(indexs[i])==tapes[i].end()) {
                tapes[i].insert(pair<int, char>(indexs[i], '_'));
            }
        }
        if(find(turing.finalstate.begin(), turing.finalstate.end(), curstate) != turing.finalstate.end()) break;
        bool judge=true;
        for(int i=0;i<turing.delta.size();i++){
            judge=true;
            if(curstate!=turing.delta[i].curState) {
                judge=false;
                continue;
            }
            for(int j=0;j<turing.tapenum;j++){
                if(turing.delta[i].oldSymbol[j]=='*'&&tapes[j][indexs[j]]!='_') continue;
                if(j>=turing.tapenum) break;
                if(tapes[j][indexs[j]]!=turing.delta[i].oldSymbol[j]){
                    judge=false;
                    break;
                }
            }
            if(judge==true){
                for(int j=0;j<turing.tapenum;j++){
                    if(turing.delta[i].newSymbol[j]!='*') tapes[j][indexs[j]]=turing.delta[i].newSymbol[j];
                    indexs[j]+=turing.delta[i].direction[j];
                }
                curstate=turing.delta[i].newState;
                break;
            }
        }
        
        if(judge==false){
            cout<<"(UNACCEPTED)"<<" ";
            auto it=tapes[0].begin();
            bool flag=false;
            string res;
            for(;it!=tapes[0].end();it++){
            if(it->second!='_'){
               flag=true;
                res+=it->second;
            }
            else if(flag){
                res+=it->second;
            }
        }
            for(int j=res.size()-1;j>=0;j--){
                if(res[j]=='_') res.pop_back();
                else break;
            }
            cout<<res<<endl;
            return;
        }
    }
    auto it=tapes[0].begin();
    bool flag=false;
    string res;
    for(;it!=tapes[0].end();it++){
        if(it->second!='_'){
           flag=true;
            res+=it->second;
        }
        else if(flag){
            res+=it->second;
        }
    }
    for(int j=res.size()-1;j>=0;j--){
        if(res[j]=='_') res.pop_back();
        else break;
    }
    cout<<"(ACCEPTED)"<<"  ";
    cout<<res<<endl;        
    
}
void dealinput_verbose(TuringMachine turing,string input){
    map<int,char> tape;
    string curstate=turing.start;
    for(int i=0;i<input.length();i++){
        if(find(turing.input.begin(),turing.input.end(), input[i]) ==turing.input.end()){
            cerr << "Input: " << input << endl;
            cerr << "==================== ERR ====================" << endl;
            cerr << "\'" << input[i] << "\' was not declared in the set of input symbols" << endl;
            cerr << "Input: " << input << endl;
            cerr << "       ";
            for(int j = 0; j < i; j++){
                cerr << " ";
            }
            cerr << "^" << endl;
            cerr << "==================== END ====================" << endl;
            exit(-1);
        }
        tape.insert(pair<int, char>(i, input[i]));
    }
    if(input=="") tape.insert(pair<int,char>(0,'_'));
    cout << "Input: " << input << endl;
    cout << "==================== RUN ====================" << endl;
    
    vector<map<int, char>> tapes;
    tapes.push_back(tape);
    for(int i = 1; i < turing.tapenum; i++){
            tape.clear();
            tape.insert(pair <int, char> (0, '_'));
            tapes.push_back(tape);
    }
    vector<int> indexs(turing.tapenum,0);
    int num=0;
    while(1){
        //for(int i=0;i<tapes[1].size();i++) cout<<tapes[1][i]<<"a"<<" ";
        //for(int i=0;i<tapes[0].size();i++) cout<<tapes[0][i]<<"a"<<" ";
        string ans;
        for(int i = 0; i < turing.tapenum; i++) {
            //cout<<tapes[i].size()<<" "<<indexs[i]<<" "<<i<<endl;
            if(tapes[i].find(indexs[i])==tapes[i].end()) {
                tapes[i].insert(pair<int, char>(indexs[i], '_'));
            }
        }
        cout<<"Step"<<"   "<<":"<<" "<<num<<endl;
        num++;
        //if(num==10) break;
        cout<<"State"<<"  "<<":"<<" "<<curstate<<endl;        
        if(find(turing.finalstate.begin(), turing.finalstate.end(), curstate) != turing.finalstate.end()) cout<<"Acc"<<"    "<<":"<<" "<<"Yes"<<endl;
        else cout<<"Acc"<<"    "<<":"<<" "<<"No"<<endl;
        for(int i = 0; i < turing.tapenum; i++){
            vector<int> indexcharge;
            auto it=tapes[i].begin();
            bool flag=false;
            string res;
            //cout<<it->first<<endl;
            for(;it!=tapes[i].end();it++){
                //cout<<"indexs"<<i<<" "<<indexs[i]<<endl;
                if(it->second!='_'){
                   flag=true;
                   res+=it->second;
                   indexcharge.push_back(it->first);
                }
                else if(it->first==indexs[i]){
                    flag=true;
                    res+=it->second;
                    indexcharge.push_back(it->first);
                }
                else if(flag){
                    res+=it->second;
                    indexcharge.push_back(it->first);
                }
            }
            //cout<<res<<endl;
            for(int j=res.size()-1;j>=0;j--){
                if(res[j]=='_'&&indexs[i]!=indexcharge[j]) {
                    res.pop_back();
                    indexcharge.pop_back();
                }
                else break;
            }
            if(i>=10) cout<<"Index"<<i<<": ";
            else cout << "Index" << i << " "<<": ";
            for(int j=0;j<indexcharge.size();j++){
                cout<<abs(indexcharge[j])<<" ";
            }
            cout<<endl;
            if(i>=10) cout<<"Tape"<<i<<" "<<": ";
            else cout << "Tape" << i << "  "<<": ";
            for(int j=0;j<res.size();j++){
                if(indexcharge[j]>=10||indexcharge[j]<=-10) cout<<res[j]<<"  ";
                else cout<<res[j]<<" ";
            }
            cout<<endl;
            if(i>=10) cout<<"Head"<<i<<" "<<": ";
            else cout << "Head" << i << "  "<<":";
            int bla=0;
            for(int j=0;j<indexcharge.size();j++){
                if((indexcharge[j]>=10||indexcharge[j]<=-10)&&indexs[i]>indexcharge[j]) bla+=3;
                else if(indexs[i]>indexcharge[j]) bla+=2;
                else if(indexs[i]==indexcharge[j]) bla+=1;
                else break;
            }
            for(int j=0;j<bla;j++) cout<<" ";
            cout<<'^'<<endl;
            if(i==0){
                ans.clear();
                for(int j=res.size()-1;j>=0;j--){
                    if(res[j]=='_') {
                        res.pop_back();
                }
                    else break;
                }
                bool add=false;
                for(int j=0;j<res.size();j++){
                    if(res[j]!='_') {
                        ans+=res[j];
                        add=true;
                    }
                    else if(add) ans+=res[j];
                }
            }
        }
        cout<<"---------------------------------------------"<<endl;
        if(find(turing.finalstate.begin(), turing.finalstate.end(), curstate) != turing.finalstate.end()) {
            cout<<"ACCEPTED"<<endl;
            cout<<"Result: "<<ans<<endl;
            break;
        }
        bool judge=true;
        //for(int i=0;i<tapes[1].size();i++) cout<<tapes[1][i]<<"a"<<" ";
        //cout<<endl;
        for(int i=0;i<turing.delta.size();i++){
            judge=true;
            if(curstate!=turing.delta[i].curState) {
                judge=false;
                continue;
            }
            for(int j=0;j<turing.tapenum;j++){
                if(turing.delta[i].oldSymbol[j]=='*'&&tapes[j][indexs[j]]!='_') continue;
                if(j>=turing.tapenum) break;
                if(tapes[j][indexs[j]]!=turing.delta[i].oldSymbol[j]){
                    judge=false;
                    break;
                }
            }
            if(judge==true){
                for(int j=0;j<turing.tapenum;j++){
                    if(turing.delta[i].newSymbol[j]!='*') tapes[j][indexs[j]]=turing.delta[i].newSymbol[j];
                    indexs[j]+=turing.delta[i].direction[j];
                }
                curstate=turing.delta[i].newState;
                break;
            }
        }
        if(judge==false) {
            cout<<"UNACCEPTED"<<endl;
            cout<<"Result: "<<ans<<endl;
            break;
        }
    }
    cout<<"==================== END ===================="<<endl;
}



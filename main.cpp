#include <iostream>
#include<string>
#include<deque>
#include<fstream>
#include<algorithm>
#include<climits>
using namespace std;
int GetPriority(const string &str){
        int Hash=-1;
        for(int i=(int)str.size()-1;i>=0;i--)
            if(str[i]=='#'){Hash=i;break;}
        if(Hash==-1 or Hash==(int)str.size()-1 or !isdigit(str[Hash+1]) )
            return INT_MAX;
        return str[Hash+1]-'0';

}
deque<string>  ReadFile(const string &path){
    deque<string> todos;
    ifstream fin(path.c_str());
    if(fin.fail()){
        cout<<"Error, can't open file\n";
        return todos;
    }
    string todo;

    while(getline(fin, todo)){
        if(!todo.empty() and todo[0]!='\0')
            todos.emplace_back(todo);
    }
    fin.close();
    return todos;
}
void UpdateFile(const string &path, const deque<string> &todos){
        ofstream fout(path);

        if(fout.fail()){
            cout<<"Can't open file\n";
            return;
        }
        for(const auto &todo: todos)
           fout<<todo<<"\n";


        fout.close();

}
bool cmp(const string &str1, const string &str2){

        return  GetPriority(str1)<=GetPriority(str2);
}

int main() {
    deque<string> Todos= ReadFile("../ToDo.txt");
    sort(Todos.begin(), Todos.end(), cmp);
    UpdateFile("../ToDo.txt", Todos);


    return 0;
}

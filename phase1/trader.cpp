#include "receiver.h"
#include <vector>
#include <string>

using namespace std;

template <typename KeyType, typename ValueType>
class MyUnorderedMap {
private:
    struct Entry {
        KeyType key;
        ValueType value;
        bool occupied;

        Entry() : occupied(false) {}
    };

    std::vector<Entry> table;

    size_t hash(const KeyType& key) {
        return std::hash<KeyType>{}(key) % table.size();
    }

    size_t findEmptySlot(const KeyType& key) {
        size_t index = hash(key);
        while (table[index].occupied) {
            if (table[index].key == key) {
                return index;
            }
            index = (index + 1) % table.size(); // Linear probing
        }
        return index;
    }

    void resize() {
        // This is a simplified implementation, and we are not resizing the table here.
        // A production-quality unordered map would resize the table to maintain a low load factor.
    }

public:
    MyUnorderedMap(size_t initialSize = 100) {
        table.resize(initialSize);
    }

    void insert(const KeyType& key, const ValueType& value) {
        resize();
        size_t index = findEmptySlot(key);
        table[index].key = key;
        table[index].value = value;
        table[index].occupied = true;
    }

    ValueType& operator[](const KeyType& key) {
        size_t index = findEmptySlot(key);
        if (!table[index].occupied) {
            table[index].key = key;
            table[index].value = ValueType();
            table[index].occupied = true;
        }
        return table[index].value;
    }
};

vector<string> splitt(string s)
{
    string tmp="";
    vector<string> ans;
    for(char& c: s)
    {
    if(int(c) == 13){//cout<<"CARRIGE RETURN SAALA";
    continue;}
        else if(c!=' ')
        {
            tmp+=c;
        }

        else
        {
            ans.push_back(tmp);
            tmp="";
        }
    }
    ans.push_back(tmp);
    return ans;
}

vector<string> splitn(string s)
{
    string tmp="";
    vector<string> ans;
    for(auto c: s)
    {
        if(c!='#')
        {
            tmp+=c;
        }
        //else if(c == '\r'){cout<<"chutiya";continue;}
        else
        {
            ans.push_back(tmp);
            tmp="";
        }
    }
    return ans;
}
    

string processor(string &stocking, MyUnorderedMap<string,int> &order_book){
    string ans="No Trade\r";
    //cout << "yes im here";
    vector<string> order=splitt(stocking);
    //return "_"+order[0]+"*";
    
    //cout<< "splitting done";
    //cout <<"\r test:"<< order[0] <<" "<< order[1] <<order[2];
    //cout << order_book[order[0]];
    if(order_book[order[0]]==0)
    {
        //cout <<"order 1 is:"<< order[1]<<endl;
        order_book[order[0]]=stoi(order[1]);
        //bool flag =(order[0]=="ASML");
        //cout <<"flag is"<< flag;
        //cout << " changed to :" <<order_book["ASML"];
        if(order[2] == "b"){
            ans = order[0]+ " " + order[1]+ " s\r";
            return ans;
        }
        else{
            ans = order[0]+ " " + order[1]+ " b\r";
            return ans;
        }
    }
    if(order[2] == "b"){
        if(stoi(order[1]) > order_book[order[0]]){
            ans = order[0]+ " " + order[1]+ " s\r";
            order_book[order[0]]= stoi(order[1]);
            }
    }
    else {
        if(stoi(order[1]) < order_book[order[0]]){
            ans = order[0]+ " " + order[1]+ " b\r";
            order_book[order[0]]= stoi(order[1]);
            }
    }
    return ans;
}
int main(int argc, char **argv) {

    if(strcmp(argv[1],"1")==0){
    MyUnorderedMap<string,int> order_book;
    Receiver rcv;
    // sleep(4);
    std::string message = rcv.readIML();
    //cout<<message;
    bool characterExists = 0;


    while(!characterExists){
    characterExists = message.find('$') != std::string::npos;
    vector<string> ans;
    //while(message != "$"){
    ans = splitn(message);
    int s= ans.size();
    //cout << "been here";
    for(int i=0; i<s;i++){
        cout << processor(ans[i],order_book);
        // cout << ans[i];
        //cout << int(ans[i][0]);
        //cout << "New value:" <<order_book["ASML"];

    }
    //cout  << message;
    if(!characterExists) message = rcv.readIML();
    else break;
    }
    }
    else if(strcmp(argv[1],"2")==0){
        cout<<"argument is 2";
    }
    //cout<<message << "second time";
    //ans.clear();
    
    //cout<<characterExists;
    
    //   if(message[0] == '$'){cout << "end";}
    //}
    // ans = splitn(message);
    // s= ans.size();
    // for(int i=0; i<s;i++){
    //     cout << processor(ans[i],order_book);
    //     //cout << int(ans[i][0]);
    //     //cout << "New value:" <<order_book["ASML"];

    // }
    
    return 0;
}

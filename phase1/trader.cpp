#include "receiver.h"
#include <vector>
#include <string>
#include<unordered_map>

using namespace std;

// Murmur2 hash function
size_t _Hash_bytes(const char* buf, size_t len, size_t seed) {
    const size_t m = 0x5bd1e995;
    size_t hash = seed ^ len;
    while (len >= 4) {
        size_t k = *((const size_t*)buf);
        k *= m; k ^= k >> 24; k *= m;
        hash *= m; hash ^= k;
        buf += 4; len -= 4;
    }
    size_t k;
    switch (len) {
        case 3: k = buf[2]; hash ^= k << 16;
        case 2: k = buf[1]; hash ^= k << 8;
        case 1: k = buf[0]; hash ^= k; hash *= m;
    }
    hash ^= hash >> 13; hash *= m; hash ^= hash >> 15;
    return hash;
}

class MyMap {
public:
    MyMap() : buckets(100) {} // Choose an initial size for the hash table.


    int& operator[](const std::string& key) {
        size_t hash = _Hash_bytes(key.c_str(), key.length(), 0);
        size_t index = hash % buckets.size();
        for (auto& pair : buckets[index]) {
            if (pair.first == key) {
                return pair.second;
            }
        }
        buckets[index].emplace_back(key, 0);
        return buckets[index].back().second;
    }
    // Insert a key-value pair into the map.
    void insert(const std::string& key, int value) {
        size_t hash = _Hash_bytes(key.c_str(), key.length(), 0);
        size_t index = hash % buckets.size();
        for (auto& pair : buckets[index]) {
            if (pair.first == key) {
                // Key already exists; update the value.
                pair.second = value;
                return;
            }
        }
        buckets[index].emplace_back(key, value);
    }

    // Search for a key and return its value.
    int find(const std::string& key) {
        size_t hash = _Hash_bytes(key.c_str(), key.length(), 0);
        size_t index = hash % buckets.size();
        for (const auto& pair : buckets[index]) {
            if (pair.first == key) {
                return pair.second;
            }
        }
        return -1; // Key not found.
    }

private:
    std::vector<std::vector<std::pair<std::string, int>>> buckets;
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
        else if(c == '\r'){cout<<"chutiya";continue;}
        else
        {
            ans.push_back(tmp);
            tmp="";
        }
    }
    return ans;
}
    

string processor(string &stocking, MyMap &order_book){
    string ans="No Trade\n";
    //cout << "yes im here";
    vector<string> order=splitt(stocking);
    //return "_"+order[0]+"*";
    
    //cout<< "splitting done";
    //cout <<"\n test:"<< order[0] <<" "<< order[1] <<order[2];
    //cout << order_book[order[0]];
    if(order_book[order[0]]==0)
    {
        //cout <<"order 1 is:"<< order[1]<<"\n";
        order_book[order[0]]=stoi(order[1]);
        //bool flag =(order[0]=="ASML");
        //cout <<"flag is"<< flag;
        //cout << " changed to :" <<order_book["ASML"];
        if(order[2] == "b"){
            ans = order[0]+ " " + order[1]+ " s\n";
            return ans;
        }
        else{
            ans = order[0]+ " " + order[1]+ " s\n";
            return ans;
        }
    }
    if(order[2] == "b"){
        if(stoi(order[1]) > order_book[order[0]]){
            ans = order[0]+ " " + order[1]+ " s\n";
            order_book[order[0]]= stoi(order[1]);
            }
    }
    else {
        if(stoi(order[1]) < order_book[order[0]]){
            ans = order[0]+ " " + order[1]+ " b\n";
            order_book[order[0]]= stoi(order[1]);
            }
    }
    return ans;
}
int main() {

    MyMap order_book;
    Receiver rcv;
    // sleep(4);
    std::string message = rcv.readIML();
    //cout<<message;
    vector<string> ans;
    ans = splitn(message);
    int s= ans.size();
    for(int i=0; i<s;i++){
        cout << processor(ans[i],order_book);
        //cout << int(ans[i][0]);
        //cout << "New value:" <<order_book["ASML"];

    }
    //cout << processor(ans[0],order_book);
    // vector<string> s1 = splitt(ans[0]);
    // for (auto c: s1){
    //     cout <<"splitline"<< c;
    // }
    // std::string line;
    // cout <<R
    // size_t start = 0;
    // size_t end = message.find('\n');
    // while (end != std::string::npos) {
    //     line = message.substr(start, end - start);
    //     lines.push_back(line);
    //     start = end + 1;
    //     end = message.find('\n', start);
    // }
    
    // // Add the last line (if any)
    // line = message.substr(start, end);
    // lines.push_back(line);
    // cout<<lines.size()<<" is the size";
    // // Now 'lines' contains the individual lines
    // for (const std::string& s : lines) {
    //     std::cout << s <<"is it done"<< std::endl;
    // }
    
    return 0;
}

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
    if(int(c) == 13) continue;
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
        if(c!='#') tmp+=c;
        else
        {
            ans.push_back(tmp);
            tmp="";
        }
    }
    return ans;
}
    

string processor(string &stocking, MyUnorderedMap<string,std::vector<int>> &order_book){
    string ans="No Trade\r";
    vector<string> order=splitt(stocking);

    string stock = order[0];
    int bid = stoi(order[1]);

    if(order_book[stock].size()==0)
    {
        order_book[stock].push_back(0);
        order_book[stock].push_back(0);
        order_book[stock].push_back(bid);

        if(order[2] == "b"){
            ans = order[0]+ " " + order[1]+ " s\r";
            //ans = ans+"new trade buy";
            return ans;
        }

        else{
            ans = order[0]+ " " + order[1]+ " b\r";
            //ans+="new trade sell";
            return ans;
        }

    }

    if(order[2] == "b"){

        if(order_book[stock][0] != 0 && bid <= order_book[stock][0]){
        // ans+="dead by skill issue";
            return ans;
        } // bad buy order dies instantly

        if(order_book[stock][1] != 0 && bid == order_book[stock][1]) {       // equal (alive) buy and sell orders cancel each other
            order_book[stock][0] = 0; 
            order_book[stock][1] = 0;
            // ans+="dead by ko";
            return ans;
            }

        if(bid > order_book[stock][2]){
            ans = order[0]+ " " + order[1]+ " s\r";
            order_book[stock][2]= bid;
            order_book[stock][0]= 0;
            // ans+="sold";
            return ans;
            }
        else{
            order_book[stock][0] = bid;
            // ans+="bad luck";
            return ans;
        }

    }

    else {

        if(order_book[stock][1] != 0 && bid >= order_book[stock][1]){
        // ans+="dead by skill issue";
            return ans;
        } // bad sell order dies instantly

        if(order_book[stock][0] != 0 && bid == order_book[stock][0]) {       // equal (alive) buy and sell orders cancel each other
            order_book[stock][0] = 0; 
            order_book[stock][1] = 0;
            // ans+="dead by ko";
            return ans;
            }

        if(bid < order_book[stock][2]){
            ans = order[0]+ " " + order[1]+ " b\r";
            order_book[stock][2]= bid;
            order_book[stock][1]= 0;
            // ans+="bought";
            return ans;
            }
        else{
            order_book[stock][1] = bid;
            // ans+="bad luck";
            return ans;
        }

    }

    return ans;
}
int main(int argc, char **argv) {

    if(strcmp(argv[1],"1")==0){
    MyUnorderedMap<string,vector<int>> order_book;
    Receiver rcv;
    // sleep(4);
    std::string message = rcv.readIML();
    //cout<<message;


    bool characterExists = 0;

    while(!characterExists){
    characterExists = message.find('$') != std::string::npos;
    vector<string> ans;
    ans = splitn(message);
    int s= ans.size();
    
    for(int i=0; i<s;i++){
        cout << processor(ans[i],order_book);
        // cout << ans[i];
    }

    if(!characterExists) message = rcv.readIML();
    else break;

    }
    }


    else if(strcmp(argv[1],"2")==0){
        cout<<"argument is 2";
    }
    
    return 0;
}

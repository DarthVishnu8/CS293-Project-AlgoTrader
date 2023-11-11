#include "receiver.h"
#include <vector>
#include <string>
#include <unordered_set>
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

MyUnorderedMap<string,int> inputProcessing(string inp, std::vector<string>& stocks, int n, std::vector<int>& price){
    vector<string> elements = splitt(inp);
    // vector<int> row;
    int s = elements.size();
    //cout << elements[s-2] << " is the price";
    price.push_back(stoi(elements[s-2]));
    string order_type = elements[s-1];
    MyUnorderedMap<string,int> line;
    for (int i=0; i < s/2 -1; i++){

        if(order_type == "b"){
            auto it = std::find(stocks.begin(), stocks.end(), elements[2*i]);
            if(it != stocks.end())
            {
                // cout << "found";
                int index = it-stocks.begin();
                line[elements[2*i]] = stoi(elements[2*i+1]);
            }
            else{
                // cout <<elements[2*i]<< " NF";

                line[elements[2*i]] = stoi(elements[2*i+1]);
                stocks.push_back(elements[2*i]);
            }
        }

        else{
            auto it = std::find(stocks.begin(), stocks.end(), elements[2*i]);
            if(it != stocks.end())
            {
                int index = it-stocks.begin();
                line[elements[2*i]] = stoi(elements[2*i+1]) * -1;
            }
            else{
                line[elements[2*i]] = stoi(elements[2*i+1]) * -1;
                stocks.push_back(elements[2*i]);
            }
        }

    }
    return line;
}



void kiloprocessor(std::vector<std::vector<int>> &subs,vector<string> stocks, MyUnorderedMap<int, MyUnorderedMap<string,int> >& matrix){

    for (int i=0; i<subs.size(); i++){
            // cout << "Analyzing subset: ";
            // for (auto f:subs[i]){cout <<f<<" ";}
            if(subs[i].size()==0){
                subs.erase(std::remove_if(subs.begin(), subs.end(), [](const std::vector<int>& subset) {
                    return subset.empty();
                }), subs.end());--i;
                // cout << "removed empty subset\n";
                continue;
                }
            for (auto c: stocks){
                int s = 0;
                for(auto j : subs[i]){
                    // cout << j << " is the no in subset";
                    s += matrix[j][c];
                    // cout << "added " << matrix[j][c];
                }
                // cout << "sum for "<<c<< " is "<<s<<"\n";
                if(s != 0){
                    //for (auto f:subs[i]){cout <<f<<" ";}
                    subs.erase(subs.begin()+i);
                    --i;
                // cout << "deleted\n";
                break;
                }
                // else{
                //     //for (auto f:subs[i]){cout <<f;}
                //     cout << " passed " << c<<endl;
                // }
                // cout << "sum is "<<s;
            }
            // for (auto c: subs){
            //     cout << "remaining subsets: ";
            //         for (auto d: c){
            //             std::cout << d<<" ";
            //         }
            //         std::cout << "\n";
            //     }
        }
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

std::vector<std::vector<int>> generateSubsets(vector<int> set) {
    int n = set.size();
    std::vector<std::vector<int>> subs;
    
    // Generate subsets without the last element
    for (int i = 0; i < (1 << (n - 1)); ++i) {
        std::vector<int> subset;

        for (int j = 0; j < n - 1; ++j) {
            if ((i & (1 << j)) != 0) {
                subset.push_back(set[j]);
            }
        }
        subs.push_back(subset);
    }

    // Append the last element to each subset
    int lastElementIndex = n - 1;
    for (auto &subset : subs) {
        subset.push_back(set[lastElementIndex]);
    }

    return subs;
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

            MyUnorderedMap<int, MyUnorderedMap<string,int> > matrix;
            
            vector<string> stocks;
        Receiver rcv;
        // sleep(4);
        std::string message = rcv.readIML();
        // cout << message;
        // rcv.terminate();
        vector<string> splitlines;
        splitlines = splitn(message);
        vector<int> prices;
        vector<int> profits;
        int count = 0;
        int finalprofit = 0;
        vector<vector<int>> paisa;
        vector<int> orders;
        for (auto c: splitlines){
            orders.push_back(count);
            for (auto c: orders){cout << c<<" ";}
            matrix[count] = inputProcessing(c, stocks,count,prices);
            std::vector<std::vector<int>> subs = generateSubsets(orders);
            kiloprocessor(subs, stocks, matrix);
            cout<< subs.size()<<endl;
            if(subs.size()==0){count++;continue;cout <<"No arbitrage found\n";}
            int maxp = 0;
            vector<int> plines;
            for (int i=0; i<subs.size(); i++){
                int p = 0;
                for (auto j : subs[i]){
                    p += prices[j];
                }
                if(p > maxp) {maxp = p;plines = subs[i];}
            }
            cout << "max profit is "<<maxp << " in ";
            for (auto c: plines){
                cout << c <<" ";
            }
            if(maxp > 0){
                paisa.push_back(plines);
                finalprofit += maxp;
            }
            count++;
            // cout<<"stocks till now:";
            // for(auto c: stocks){cout <<c;}
            // cout <<"\n";
        }
        // for (int i = 0; i<3;i++){
        //     for(auto c:stocks){
        //         cout << c << ": "<<matrix[i][c]<<". ";
        //     }
        //     cout <<"\n";
        // }

        



    //      PRINT GENERATED SUBSETS
    //
    //     for (auto c: subs){
    //     for (auto d: c){
    //         std::cout << d<<" ";
    //     }
    //     std::cout << "\n";
    // }
    return 0;

    }
    
    return 0;
}

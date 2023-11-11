#include "market.h"
#include <vector>
#include <fstream>

using namespace std;

market::market(int argc, char** argv)
{
	
}

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

std::vector<std::string> takeInput()
{
    std::ifstream inputFile;
    inputFile.open("testoutput.txt");


    std::vector<std::string> orderList;

    bool i=0;

    // Read from the file
    std::string line;
    while (std::getline(inputFile, line)) {
        if(i==0)
        {i=1; continue;}

        if(line[0]=='@' || line[0]=='!')
        continue;
        

        orderList.push_back(line);
    }



    // Close the file
    inputFile.close();


    return orderList;
}

vector<vector<string>> splitBySpaceToGetItems(vector<string> orders)
{

    vector<vector<string>> ans;
    for(auto order: orders)
    {
        order+=' ';
        vector<string> tmp;
        string t="";
        for(auto c: order)
        {
            if(c==' ')
            {tmp.push_back(t); t="";}

            else{
                t+=c;
            }
        }
          ans.push_back(tmp);
          tmp.clear();

    }
    return ans;
}



MyUnorderedMap<string,vector<string>> processBuy(vector<vector<string>> orders)
{
    MyUnorderedMap<string,vector<string>> ans;
    for(auto c: orders)
    {
        if(c[2][0]=='B')
        ans[c[2]].push_back()
    }
    return ans;
}

vector<vector<string>> processSell(vector<vector<string>> orders)
{
    vector<vector<string>> ans;
    for(auto c: orders)
    {
        if(c[2][0]=='S')
        ans.push_back(c);
    }
    return ans;
}


void market::start()
{

    std::vector<std::string> orderList=takeInput();

    MyUnorderedMap<vector<string>, vector<int>> tradeInfo;                // this will contain a map for the trades that actually happened string[0]=Buyer, string[1]=Seller, string[2]=stockName, int[0]=#shares, int[1]=cost/share
    int totalAmountTransferred=0;
    int numberOfTrades=0;
    int numberofShares=0;
    vector<vector<string>> orderListItems=splitBySpaceToGetItems(orderList); // This function returns a vector of string vectors which contains the individual information regarding all orders
    vector<vector<string>> buyOrderItems=processBuy(orderListItems);
    vector<vector<string>> sellOrderItems=processSell(orderListItems);

}

// My thought. Start iterating from the start of the vector containing the order list. If an order has expired make that vector entry null. Then within another loop, iterate over all the other remaining orders other than the one already in outer loop. Within the inner loop check whether the orders are compatible. If they are not compatible, move on. If they are compatible, store appropriate information within the tradeInfo map

// compatible check algorithm: check if one is buy and other sell. If not, return false. else return true. Next check if order with buy has price >= sell. If yes return true, else return false.

// expired check algorithm: current order being checked (outer loop order) originate time - prev order originate time > prev order time to live => expired and not compatible else both orders are alive wrt to each other.

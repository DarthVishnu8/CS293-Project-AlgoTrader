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

int stringcmp(string s1, string s2)  // this function returns 0 if strings are equal, -1 if first string is smaller, 1 if second string is smaller
{
    int index=0;
    while(true)
    {
        if(s1[index]=='\0' && s2[index]=='\0')
        return 0;

        if(s1[index]=='\0' && s2[index]!='\0')
        return -1;

        if(s1[index]!='\0' && s2[index]=='\0')
        return 1;

        if(int(s1[index]) < int(s2[index]))
        return -1;

        if(int(s1[index]) > int(s2[index]))
        return 1;


        index++;
    }
}

int parent(int x)
{
    return (x-1)/2;
}

int left(int x)
{
    return 2*x+1;
}

int right(int x)
{
    return 2*x+2;
}

void deleteBuyMostPriorityElement(MyUnorderedMap<string,vector<vector<string>>> &ans,string stock)
{
    int indexLen=ans[stock].size()-1;
    ans[stock][0]= ans[stock][indexLen];
    ans[stock].pop_back();
    heapifyMax(ans,stock,0);
}

void deleteSellMostPriorityElement(MyUnorderedMap<string,vector<vector<string>>> &ans,string stock)
{
    int indexLen=ans[stock].size()-1;
    ans[stock][0]= ans[stock][indexLen];
    ans[stock].pop_back();
    heapifyMin(ans,stock,0);
}

void mySwap(MyUnorderedMap<string,vector<vector<string>>> &ans,string stock,int i, int j)
{
    vector<string> tmp=ans[stock][i];
    ans[stock][i]=ans[stock][j];
    ans[stock][j]=tmp;
}

// price starts with the character $ (linear combinations possible so cannot hardcode the index) will change this later. For now we have hardcoded the price index

void heapifyMax(MyUnorderedMap<string,vector<vector<string>>> &ans,string stock,int i)
{
    int c;
    int indexLen=ans[stock].size()-1;
    if(right(i)<indexLen)       // right does not exist
    {
        if(left(i)<indexLen)    // neither left nor right exists if true
        {
            c=i;
        }

        else if (ans[stock][i][4] > ans[stock][left(i)][4])       // if price of stock[i] > stock[left(i)]
        {
            c=i;
        }
        
        else if (ans[stock][i][4] < ans[stock][left(i)][4])      // if price of stock[i] < stock[left(i)]
        {
            c=left(i);
        }

        else{
            if(ans[stock][i][0] < ans[stock][left(i)][0])       // prioritise by time if price same
            c=i;

            else if(ans[stock][i][0] > ans[stock][left(i)][0])
            c=left(i);

            else{
                if(stringcmp(ans[stock][i][1],ans[stock][left(i)][1])<0)      // prioritise alphabetically if time also same
                c=i;

                else c=left(i);
            }
        }

    }

    else{
        if(ans[stock][i][4] > ans[stock][left(i)][4])
        {
            if(ans[stock][i][4] > ans[stock][right(i)][4])
            c=i;

            else if(ans[stock][i][4] < ans[stock][right(i)][4])
            c=right(i);

            else{
            if(ans[stock][i][0] < ans[stock][right(i)][0])       // prioritise by time if price same
            c=i;

            else if(ans[stock][i][0] > ans[stock][right(i)][0])
            c=right(i);

            else{
                if(stringcmp(ans[stock][i][1],ans[stock][right(i)][1])<0)      // prioritise alphabetically if time also same
                c=i;

                else c=right(i);
            }
        }
        }

        else if(ans[stock][i][4] == ans[stock][left(i)][4])
        {
            if(ans[stock][i][0] < ans[stock][left(i)][0])       // prioritise by time if price same
            c=i;

            else if(ans[stock][i][0] > ans[stock][left(i)][0])
            c=left(i);

            else{
                if(stringcmp(ans[stock][i][1],ans[stock][left(i)][1])<0)      // prioritise alphabetically if time also same
                c=i;

                else c=left(i);
            }
        }

        else{
            if(ans[stock][left(i)][4] > ans[stock][right(i)][4])
            c=left(i);

            else if(ans[stock][left(i)][4] < ans[stock][right(i)][4])
            c=right(i);

            else{
            if(ans[stock][left(i)][0] < ans[stock][right(i)][0])       // prioritise by time if price same
            c=left(i);

            else if(ans[stock][left(i)][0] > ans[stock][right(i)][0])
            c=right(i);

            else{
                if(stringcmp(ans[stock][left(i)][1],ans[stock][right(i)][1])<0)      // prioritise alphabetically if time also same
                c=left(i);

                else c=right(i);
            }
        }
        }
    }

    if(c==i) return;

    mySwap(ans,stock,i,c);

    heapifyMax(ans,stock,c);

}

void heapifyMin(MyUnorderedMap<string,vector<vector<string>>> &ans,string stock,int i)
{
        int c;
    int indexLen=ans[stock].size()-1;
    if(right(i)<indexLen)       // right does not exist
    {
        if(left(i)<indexLen)    // neither left nor right exists if true
        {
            c=i;
        }

        else if (ans[stock][i][4] < ans[stock][left(i)][4])       // if price of stock[i] > stock[left(i)]
        {
            c=i;
        }
        
        else if (ans[stock][i][4] > ans[stock][left(i)][4])      // if price of stock[i] < stock[left(i)]
        {
            c=left(i);
        }

        else{
            if(ans[stock][i][0] < ans[stock][left(i)][0])       // prioritise by time if price same
            c=i;

            else if(ans[stock][i][0] > ans[stock][left(i)][0])
            c=left(i);

            else{
                if(stringcmp(ans[stock][i][1],ans[stock][left(i)][1])<0)      // prioritise alphabetically if time also same
                c=i;

                else c=left(i);
            }
        }

    }

    else{
        if(ans[stock][i][4] < ans[stock][left(i)][4])
        {
            if(ans[stock][i][4] < ans[stock][right(i)][4])
            c=i;

            else if(ans[stock][i][4] > ans[stock][right(i)][4])
            c=right(i);

            else{
            if(ans[stock][i][0] < ans[stock][right(i)][0])       // prioritise by time if price same
            c=i;

            else if(ans[stock][i][0] > ans[stock][right(i)][0])
            c=right(i);

            else{
                if(stringcmp(ans[stock][i][1],ans[stock][right(i)][1])<0)      // prioritise alphabetically if time also same
                c=i;

                else c=right(i);
            }
        }
        }

        else if(ans[stock][i][4] == ans[stock][left(i)][4])
        {
            if(ans[stock][i][0] < ans[stock][left(i)][0])       // prioritise by time if price same
            c=i;

            else if(ans[stock][i][0] > ans[stock][left(i)][0])
            c=left(i);

            else{
                if(stringcmp(ans[stock][i][1],ans[stock][left(i)][1])<0)      // prioritise alphabetically if time also same
                c=i;

                else c=left(i);
            }
        }

        else{
            if(ans[stock][left(i)][4] < ans[stock][right(i)][4])
            c=left(i);

            else if(ans[stock][left(i)][4] > ans[stock][right(i)][4])
            c=right(i);

            else{
            if(ans[stock][left(i)][0] < ans[stock][right(i)][0])       // prioritise by time if price same
            c=left(i);

            else if(ans[stock][left(i)][0] > ans[stock][right(i)][0])
            c=right(i);

            else{
                if(stringcmp(ans[stock][left(i)][1],ans[stock][right(i)][1])<0)      // prioritise alphabetically if time also same
                c=left(i);

                else c=right(i);
            }
        }
        }
    }

    if(c==i) return;

    mySwap(ans,stock,i,c);

    heapifyMax(ans,stock,c);
}

void makeHeapMax(MyUnorderedMap<string,vector<vector<string>>> &ans, vector<string> c,string stock)              // creates a max heap
{
    ans[stock].push_back(c);
    for(int i=ans[stock].size()-1;i>=0;i--)
    heapifyMax(ans,stock,i);
}

void makeHeapMin(MyUnorderedMap<string,vector<vector<string>>> &ans, vector<string> c,string stock)             // creates a min heap
{
    ans[stock].push_back(c);
    for(int i=ans[stock].size()-1;i>=0;i--)
    heapifyMin(ans,stock,i);
}


MyUnorderedMap<string,vector<vector<string>>> processBuy(vector<vector<string>> orders)
{
    MyUnorderedMap<string,vector<vector<string>>> ans;
    for(auto c: orders)
    {
        if(c[2][0]=='B')
        makeHeapMax(ans,c,c[3]);
    }
    return ans;
}

MyUnorderedMap<string,vector<vector<string>>> processSell(vector<vector<string>> orders)
{
    MyUnorderedMap<string,vector<vector<string>>> ans;
    for(auto c: orders)
    {
        if(c[2][0]=='S')
        makeHeapMin(ans,c,c[3]);
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
    MyUnorderedMap<string,vector<vector<string>>> buyOrderItems=processBuy(orderListItems);
    MyUnorderedMap<string,vector<vector<string>>> sellOrderItems=processSell(orderListItems);

}

// My thought. Start iterating from the start of the vector containing the order list. If an order has expired make that vector entry null. Then within another loop, iterate over all the other remaining orders other than the one already in outer loop. Within the inner loop check whether the orders are compatible. If they are not compatible, move on. If they are compatible, store appropriate information within the tradeInfo map

// compatible check algorithm: check if one is buy and other sell. If not, return false. else return true. Next check if order with buy has price >= sell. If yes return true, else return false.

// expired check algorithm: current order being checked (outer loop order) originate time - prev order originate time > prev order time to live => expired and not compatible else both orders are alive wrt to each other.

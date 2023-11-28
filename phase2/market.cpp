#include "market.h"
#include <vector>
#include <fstream>
#include<iostream>
#include<climits>
using namespace std;

int timme=0;

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

    auto begin() const {
        return table.begin();
    }

    auto end() const {
        return table.end();
    }

    void insert(const KeyType& key, const ValueType& value) {
        resize();
        size_t index = findEmptySlot(key);
        table[index].key = key;
        table[index].value = value;
        table[index].occupied = true;
    }

    std::vector<KeyType> keys() const {
        std::vector<KeyType> result;
        for (const auto& entry : table) {
            if (entry.occupied) {
                result.push_back(entry.key);
            }
        }
        return result;
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

bool mincompare(const vector<string>& a, const vector<string>& b) {
    int index = 4; // Sorting based on the 4th index (0-indexed)

    if (a[index] != b[index]) {
        return stoi(a[index]) > stoi(b[index]); // Sort by 4th index in descending order
    } else {
        int sumA = (a[6] != "-1") ? stoi(a[0]) + stoi(a[6]) : INT_MAX;
        int sumB = (b[6] != "-1") ? stoi(b[0]) + stoi(b[6]) : INT_MAX;

        if (sumA != sumB) {
            return sumA > sumB; // Sort by the lower sum of 0th and last index if last index is not -1
        } else {
            return a[1] > b[1]; // Sort alphabetically by the 1st index (KarGoExpress)
        }
    }
}

void mininsertIntoHeap(vector<vector<string>>& arr, vector<string> element) {
    arr.push_back(element);
    int index = arr.size() - 1;
    while (index > 0 && mincompare(arr[(index - 1) / 2], arr[index])) {
        swap(arr[index], arr[(index - 1) / 2]);
        index = (index - 1) / 2;
    }
}

bool maxcompare(const vector<string>& a, const vector<string>& b) {
    int index = 4; // Sorting based on the 4th index (0-indexed)

    if (a[index] != b[index]) {
        return stoi(a[index]) < stoi(b[index]); // Sort by 4th index in descending order
    } else {
        int sumA = (a[6] != "-1") ? stoi(a[0]) + stoi(a[6]) : INT_MAX;
        int sumB = (b[6] != "-1") ? stoi(b[0]) + stoi(b[6]) : INT_MAX;

        if (sumA != sumB) {
            return sumA > sumB; // Sort by the lower sum of 0th and last index if last index is not -1
        } else {
            
                return a[1] > b[1]; // Sort alphabetically by the 1st index (KarGoExpress)
        }
    }
}
void minheapify(vector<vector<string>>& arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && mincompare(arr[left], arr[largest])) {
        largest = left;
    }

    if (right < n && mincompare(arr[right], arr[largest])) {
        largest = right;
    }

    if (largest != i) {
        swap(arr[i], arr[largest]);
        minheapify(arr, n, largest);
    }
}

void maxheapify(vector<vector<string>>& arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && maxcompare(arr[left], arr[largest])) {
        largest = left;
    }

    if (right < n && maxcompare(arr[right], arr[largest])) {
        largest = right;
    }

    if (largest != i) {
        swap(arr[i], arr[largest]);
        maxheapify(arr, n, largest);
    }
}

vector<string> deletemax(vector<vector<string>>& arr) {
    if (arr.empty()) {
        return {};
    }

    vector<string> minElement = arr[0];
    arr[0] = arr.back();
    arr.pop_back();

    minheapify(arr, arr.size(), 0);

    return minElement;
}

vector<string> deletemin(vector<vector<string>>& arr) {
    if (arr.empty()) {
        return {};
    }

    vector<string> minElement = arr[0];
    arr[0] = arr.back();
    arr.pop_back();

    maxheapify(arr, arr.size(), 0);

    return minElement;
}


void maxinsertIntoHeap(vector<vector<string>>& arr, vector<string> element) {
    arr.push_back(element);
    int index = arr.size() - 1;
    while (index > 0 && maxcompare(arr[(index - 1) / 2], arr[index])) {
        swap(arr[index], arr[(index - 1) / 2]);
        index = (index - 1) / 2;
    }
}

std::vector<std::string> takeInput()
{
    std::ifstream inputFile;
    inputFile.open("lolol.txt");


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
            if(c == '#'|| c=='$')
            continue;
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

market::market(int argc, char** argv)
{
	
}

void market::start()
{
    std::vector<std::string> orderList=takeInput();
    MyUnorderedMap<string, vector<vector<string>>> orderBook;
    MyUnorderedMap<string, vector<int>> tradeinfo;
    vector<vector<string>> orderListItems=splitBySpaceToGetItems(orderList);
    int totalAmountTransferred=0;
    int numberOfTrades=0;
    int numberofShares=0;
    for(auto l: orderListItems){
        // cout << "time is:"<<timme<<endl;
        if(timme != stoi(l[0]))
        {
            // check expiry
            timme = stoi(l[0]);
            std::vector<std::string> mapKeys = orderBook.keys();
            for (const auto& key : mapKeys) {

                for(int f=0;f<orderBook[key].size();++f){
                    if(orderBook[key][f][2] == "BUY"){
                        if(stoi(orderBook[key][f][6]) != -1 && stoi(orderBook[key][f][0])+stoi(orderBook[key][f][6]) < timme){
                        // cout << "found expired buy order\n";
                            swap(orderBook[key][f],orderBook[key][orderBook[key].size()-1]);
                            orderBook[key].pop_back();
                            minheapify(orderBook[key], orderBook[key].size(), f);
                        }
                    }
                    else{
                        if(stoi(orderBook[key][f][6]) != -1 && stoi(orderBook[key][f][0])+stoi(orderBook[key][f][6]) < timme){
                        // cout << "found expired sell order\n";
                            swap(orderBook[key][f],orderBook[key][orderBook[key].size()-1]);
                            orderBook[key].pop_back();
                            maxheapify(orderBook[key], orderBook[key].size(), f);
                        }
                    }
                }
            }
        }
        
        string probe = l[3]+l[2];
        string pcomp;
        if(l[2] == "BUY"){
            pcomp = l[3]+"SELL";
            while(orderBook[pcomp].size() != 0 && stoi(orderBook[pcomp][0][4]) <= stoi(l[4]) ){   // complementary heap exists and valid trade exists
                // cout << "valid trade exists for " << probe <<"\n";
                // update quantities
                numberOfTrades++;
                int q = min(stoi(orderBook[pcomp][0][5]), stoi(l[5]));
                numberofShares += q;
                totalAmountTransferred += q*stoi(orderBook[pcomp][0][4]);
                cout << l[1] << " puchased "<< q<<" share of "<< l[3] << " from "<< orderBook[pcomp][0][1] <<" for $" << orderBook[pcomp][0][4]<<"/share"<<"\n";
                l[5] = to_string(stoi(l[5])-q);
                // cout << "Decreased "<<l[1]<<"'s "<<l[3] << " by " << q<<"\n";
                orderBook[pcomp][0][5] = to_string(stoi(orderBook[pcomp][0][5])-q);
                // cout << "Decreased "<<orderBook[pcomp][0][1]<<"'s "<<orderBook[pcomp][0][3] << " by " << q<<"\n";
                // if newline quantity is over then continue to next line
                if(stoi(orderBook[pcomp][0][5]) == 0){
                    deletemax(orderBook[pcomp]);
                    // cout <<orderBook[pcomp][0][1] << " is out of "<<l[3]<< " stocks\n";
                }
                if(stoi(l[5]) == 0){
                    // cout <<l[1] << " is out of "<<l[3]<< " stocks\n";
                    break;
                }  
                // if heap quantity is over deletemax
            }
            if(stoi(l[5]) > 0){
                maxinsertIntoHeap(orderBook[probe],l);
                // cout << "Inserted "<<l[5] <<" of "<< l[3]<<" stocks in name of "<<l[1]<<"\n";
            }
        }
        else{
            pcomp = l[3]+"BUY";
            while(orderBook[pcomp].size() != 0 && stoi(orderBook[pcomp][0][4]) >= stoi(l[4])){   // complementary heap exists and valid trade exists
                // cout << "valid trade exists for " << probe <<"\n";
                // update quantities
                numberOfTrades++;
                int q = min(stoi(orderBook[pcomp][0][5]), stoi(l[5]));
                numberofShares += q;
                totalAmountTransferred += q*stoi(orderBook[pcomp][0][4]);
                cout << orderBook[pcomp][0][1] << " puchased "<< q<<" share of "<< l[3] << " from "<< l[1] <<" for $" << orderBook[pcomp][0][4]<<"/share"<<"\n";
                l[5] = to_string(stoi(l[5])-q);
                // cout << "Decreased "<<l[1]<<"'s "<<l[3] << " by " << q<<"\n";

                // cout << "Decreased "<<orderBook[pcomp][0][1]<<"'s "<<orderBook[pcomp][0][3] << " by " << q<<"\n";
                orderBook[pcomp][0][5] = to_string(stoi(orderBook[pcomp][0][5])-q);
                // if newline quantity is over then continue to next line
                if(stoi(orderBook[pcomp][0][5]) == 0){
                    deletemin(orderBook[pcomp]);
                    // cout <<orderBook[pcomp][0][1] << " is out of "<<l[3]<< " stocks\n";

                }
                if(stoi(l[5]) == 0){
                    // cout <<l[1] << " is out of "<<l[3]<< " stocks\n";
                    break;
                }  
                // if heap quantity is over deletemax
            }
            if(stoi(l[5]) > 0){
                mininsertIntoHeap(orderBook[probe],l);
                // cout << "Inserted "<<l[5] <<" of "<< l[3]<<" stocks in name of "<<l[1]<<"\n";

            }
        } 
        // cout << probe<<"\n";
        // cout << "\n";
        // cout << "Printing orderbook for "<<probe<<"\n";
        // for ( auto f: orderBook[probe])
        //     {
        //         for(auto g: f){
        //             cout << g<<" ";
        //         }
        //         cout << "\n";
        //     }
        //     cout << "\n";
    }
    cout << "\n";
    cout << "---End of Day--- \n";
    cout << "Total Amount of Money Transferred: $"<< totalAmountTransferred<<"\n";
    cout << "Number of Completed Trades: "<< numberOfTrades<<"\n";
    cout << "Number of Shares Traded: "<< numberofShares;
}

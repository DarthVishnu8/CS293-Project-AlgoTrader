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
    // Check if resizing is necessary based on load factor
    if (table.size() >= 0.75 * table.capacity()) {
        // Double the size of the table
        table.resize(table.size() * 2);

        // Rehash existing elements after resizing (not optimal but simple)
        for (size_t i = 0; i < table.size(); ++i) {
            if (table[i].occupied) {
                size_t newIndex = findEmptySlot(table[i].key);
                if (newIndex != i) {
                    // Move the element to its new position
                    table[newIndex] = std::move(table[i]);
                    table[i].occupied = false;  // Clear the old position
                }
            }
        }
    }
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
    bool operator==(const MyUnorderedMap& other) const {
    if (table.size() != other.table.size()) {
        return false;
    }

    for (size_t i = 0; i < table.size(); ++i) {
        if ((table[i].occupied && table[i].value != 0) !=
            (other.table[i].occupied && other.table[i].value != 0)) {
            return false;
        }

        if (table[i].occupied && table[i].value != 0 &&
            (table[i].key != other.table[i].key || table[i].value != other.table[i].value)) {
            return false;
        }
    }

    return true;
}

bool operator!=(const MyUnorderedMap& other) const {
    return !(*this == other);
}

    void printMap() const {
        std::cout << "Map Contents:\n";
        for (const Entry& entry : table) {
            if (entry.occupied) {
                std::cout << entry.key << ": " << entry.value << "\n";
            }
        }
        std::cout << "End of Map\n";
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
// PART 2 INPUT PROCESSING
MyUnorderedMap<string,int> inputProcessing(string& inp, std::vector<string>& stocks, int n, std::vector<int>& price, bool* flag){
    vector<string> elements = splitt(inp);
    // vector<int> row;
    int s = elements.size();
    //cout << elements[s-2] << " is the price";
    string order_type = elements[s-1];
    MyUnorderedMap<string,int> line;
    
    if(order_type=="b"){
            price.push_back(stoi(elements[s-2]));
            *flag = 0;
    }
    else{        
            price.push_back(-1*stoi(elements[s-2]));
            *flag = 1;
    }
    for (int i=0; i < s/2 -1; i++){

        if(order_type == "b"){
            auto it = std::find(stocks.begin(), stocks.end(), elements[2*i]);
            elements[s-1] = "s#";
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
            elements[s-1] = "b#";
            auto it = std::find(stocks.begin(), stocks.end(), elements[2*i]);
            if(it != stocks.end())
            {
                int index = it-stocks.begin();
                line[elements[2*i]] = stoi(elements[2*i+1]);
            }
            else{
                line[elements[2*i]] = stoi(elements[2*i+1]);
                stocks.push_back(elements[2*i]);
            }
        }

    }
    inp = "";
    for (auto d: elements){
        if(d != "b#" || d!= "s#")
        {
        inp += d;
        inp += " ";
        }
        else inp += d;
    }

    return line;
}

// PART 3 INPUT PROCESSING
MyUnorderedMap<string,int> inputProcessingAgain(string& inp, std::vector<string>& stocks, int n, std::vector<int>& price, bool* flag, vector<int>& quantity){
    vector<string> elements = splitt(inp);
    // vector<int> row;
    int s = elements.size();
    //cout << elements[s-2] << " is the price";
    string order_type = elements[s-1];
    MyUnorderedMap<string,int> line;
    quantity.push_back(stoi(elements[s-2]));
    if(order_type=="b"){
            price.push_back(stoi(elements[s-3]));
            *flag = 0;
    }
    else{        
            price.push_back(-1*stoi(elements[s-3]));
            *flag = 1;
    }
    for (int i=0; i < (s-3)/2; i++){

        if(order_type == "b"){
            auto it = std::find(stocks.begin(), stocks.end(), elements[2*i]);
            elements[s-1] = "s#";
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
            elements[s-1] = "b#";
            auto it = std::find(stocks.begin(), stocks.end(), elements[2*i]);
            if(it != stocks.end())
            {
                int index = it-stocks.begin();
                line[elements[2*i]] = stoi(elements[2*i+1]);
            }
            else{
                line[elements[2*i]] = stoi(elements[2*i+1]);
                stocks.push_back(elements[2*i]);
            }
        }

    }
    inp = "";
    for (auto d: elements){
        if(d != "b#" || d!= "s#")
        {
        inp += d;
        inp += " ";
        }
        else inp += d;
    }

    return line;
}


void kiloprocessor(std::vector<std::vector<int>> &subs,vector<string> stocks, MyUnorderedMap<int, MyUnorderedMap<string,int> >& matrix, MyUnorderedMap<int,bool>& Sign){

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
                    if (!Sign[j]) s += matrix[j][c];
                    else s -= matrix[j][c];
                    // cout << "added " << matrix[j][c];
                }
                // cout << "sum for "<<c<< " is "<<s<<"\n";
                if(s != 0){
                    //for (auto f:subs[i]){cout <<f<<" ";}
                    subs.erase(subs.begin()+i);
                    --i;
                // cout << "deleted by "<<c<<"\n";
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

    // PART 1 CODE -----------------------------------------------------------------------------


    if(strcmp(argv[1],"1")==0){
    MyUnorderedMap<string,vector<int>> order_book;
    Receiver rcv;
    // sleep(4);
    std::string message = rcv.readIML();
    // cout<<message;


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

    // PART 2 CODE -----------------------------------------------------------------------------


    else if(strcmp(argv[1],"2")==0){

        MyUnorderedMap<int, MyUnorderedMap<string,int> > matrix;
        MyUnorderedMap<int,bool> Sign;
        vector<string> stocks;
        Receiver rcv;
        // sleep(4);
        std::string message = rcv.readIML();
        // cout << message;
        // rcv.terminate();
        vector<string> splitlines;
        vector<int> prices;
        int count = 0;
        int finalprofit = 0;
        vector<int> orders;
        bool characterExists = 0;

    while(!characterExists){
    characterExists = message.find('$') != std::string::npos;
        splitlines = splitn(message);
        for (auto &c: splitlines){
            bool* flag = new bool;
            MyUnorderedMap<string,int> temp = inputProcessing(c, stocks,count,prices, flag); //temporary processing;
            // matrix[count] = inputProcessing(c, stocks,count,prices, flag);
            Sign[count] = *flag;
            if(orders.size()==0){
                orders.push_back(count);    // if no orders present directly add
               //cout << "empty book\n";
            }
            else{
                for(auto x : orders){       // otherwise iterate over previous orders
                //cout << "Checking "<<x<<endl;
                // matrix[x].printMap();
                // temp.printMap();
                if(matrix[x] == temp) {
                    if(Sign[x] == *flag){   // if order type is same (bb) or (ss), check price
                        //cout << "Match found\n";
                            if(prices[count] <= prices[x]){
                                count++;
                                // cout <<"Buyissue:No Trade\n";
                                cout <<"No Trade\n"; 
                                continue;}
                            else{
                                orders.erase(std::remove(orders.begin(), orders.end(), x), orders.end());   
                            }
                    }
                    else{                   // if order type is different compare price
                        if(prices[count] + prices[x] == 0){
                            orders.erase(std::remove(orders.begin(), orders.end(), x), orders.end());
                            count++;
                            //cout <<"Cancelled:No Trade\n";
                            cout <<"No Trade\n";

                             continue;
                        }
                    }
                }
                // if(matrix[x] == temp && flag != Sign[x]) cout << "different type";                            // check if similar order structure is present
                }
                orders.push_back(count);                            // check if order type is same
            }
            matrix[count] = temp;
            delete flag;

            // orders.push_back(count);
            // matrix[count]= inputProcessing(c, stocks,count,prices,flag);
            // Sign[count] = *flag;

            //for (auto c: orders){cout << c<<" ";}
            std::vector<std::vector<int>> subs = generateSubsets(orders);
            kiloprocessor(subs, stocks, matrix, Sign);
            //cout<< subs.size()<<endl;
            if(subs.size()==0){count++;
            // cout <<"Nocomb:No Trade\n";
            cout <<"No Trade\n";
            continue;}
            int maxp = 0;
            vector<int> plines;
            for (int i=0; i<subs.size(); i++){
                int p = 0;
                for (auto j : subs[i]){
                    p += prices[j];
                }
                if(p > maxp) {maxp = p;plines = subs[i];}
            }
            // cout << "prices are: \n";
            // for (auto c: prices){
            //     cout << c <<". ";
            // }
            // cout <<endl;
        //     cout<<"orders till now:";
        //     for(auto c: orders){cout <<c<<". ";}
        //     cout <<"\n";
        // for (int i = 0; i<count;i++){
        //     for(auto c:stocks){
        //         cout << c << ": "<<matrix[i][c]<<". ";
        //     }
        //     cout <<"\n";
        // }
            if(maxp > 0){
                finalprofit += maxp;
                for (auto it = plines.rbegin(); it != plines.rend(); ++it) {
                    std::cout << splitlines[*it]<<"\n";
                }

                for(auto k:plines){
                    orders.erase(std::remove(orders.begin(), orders.end(), k), orders.end());
                }
            }
            else{
                count++;
                // cout <<"Loss:No Trade\n";
                cout <<"No Trade\n";
                continue;
            }
            count++;
        }
if(!characterExists) message = rcv.readIML();
    else break;

    }
        // if(matrix[1] == matrix[2]){cout << "3 and 5 are same";}
        cout << finalprofit;

        



    //      PRINT GENERATED SUBSETS
    //
    //     for (auto c: subs){
    //     for (auto d: c){
    //         std::cout << d<<" ";
    //     }
    //     std::cout << "\n";
    // }
    }

    // PART 3 CODE -----------------------------------------------------------------------------

    else if(strcmp(argv[1],"3")==0){
        bool characterExists = 0;
        MyUnorderedMap<int, MyUnorderedMap<string,int> > matrix;
        MyUnorderedMap<int,bool> Sign;
        vector<int> quantity;
        vector<string> stocks;
        Receiver rcv;
        // sleep(4);
        std::string message = rcv.readIML();
        // cout << message;
        // rcv.terminate();
        vector<string> splitlines;
        vector<int> prices;
        int count = 0;
        int finalprofit = 0;
        vector<int> orders;
        while(!characterExists){
            characterExists = message.find('$') != std::string::npos;
            splitlines = splitn(message);
            for (auto &c: splitlines){
                bool* flag = new bool;
                MyUnorderedMap<string,int> temp = inputProcessingAgain(c, stocks,count,prices, flag, quantity); //temporary processing;
                // matrix[count] = inputProcessing(c, stocks,count,prices, flag);
                Sign[count] = *flag;
                if(orders.size()==0){
                    orders.push_back(count);    // if no orders present directly add
                //cout << "empty book\n";
                }
                else{
                    for(auto x : orders){       // otherwise iterate over previous orders
                    //cout << "Checking "<<x<<endl;
                    // matrix[x].printMap();
                    // temp.printMap();
                    if(matrix[x] == temp) {
                        
                        if(Sign[x] != *flag){                   // if order type is different compare price
                            if(prices[count] + prices[x] == 0){
                                if(quantity[x] > quantity[count]){
                                    quantity[x] -= quantity[count];
                                count++;
                                //cout <<"Cancelled:No Trade\n";
                                cout <<"No Trade\n";

                                continue;
                                }
                                else if(quantity[x] == quantity[count]){
                                    orders.erase(std::remove(orders.begin(), orders.end(), x), orders.end());
                                    count++;
                                //cout <<"Cancelled:No Trade\n";
                                cout <<"No Trade\n";

                                continue;
                                }
                                else{
                                    orders.erase(std::remove(orders.begin(), orders.end(), x), orders.end());
                                    quantity[count] -= quantity[x];
                                }
                            }
                        }
                        else{
                            if(prices[count] == prices[x]){
                                quantity[x] += quantity[count];
                                count ++;
                                cout << "No Trade\n";
                                continue;
                            }
                        }
                    }
                    // if(matrix[x] == temp && flag != Sign[x]) cout << "different type";                            // check if similar order structure is present
                    }
                    orders.push_back(count);                            // check if order type is same
                }
                matrix[count] = temp;
                delete flag;
                // orders.push_back(count);
                // matrix[count]= inputProcessing(c, stocks,count,prices,flag);
                // Sign[count] = *flag;

                //for (auto c: orders){cout << c<<" ";}
                std::vector<std::vector<int>> subs = generateSubsets(orders);
                kiloprocessor(subs, stocks, matrix, Sign);
                //cout<< subs.size()<<endl;
                if(subs.size()==0){count++;
                // cout <<"Nocomb:No Trade\n";
                cout <<"No Trade\n";
                continue;}
                // cout << "\n"<<quantity[4]<<"\n";
                vector<int> plines;

                while(quantity[count] > 0 && subs.size()>0){

                    int maxp = 0;
                    int q = quantity[count];
                    for (int i=0; i<subs.size(); i++){
                        int p = 0;
                        for (auto j : subs[i]){
                            p += prices[j];
                            if(quantity[j] < q)q=quantity[j];
                        }
                        p = p*q;
                        if(p > maxp) {maxp = p;plines = subs[i];subs.erase(subs.begin()+ i);}
                    }
                    // cout << "q is "<<q;

                    if(maxp > 0){
                        finalprofit += maxp;
                        for (auto it = plines.rbegin(); it != plines.rend(); ++it) {
                            int l = *it;
                            for(auto f: stocks){
                                if(matrix[l][f] != 0){cout << f<<" "<< matrix[l][f]<<" ";}
                            }                         // work on this output
                            if(Sign[l]){
                            cout << prices[l]*-1<<" "<<q<<" ";
                            cout << "b\n";
                            }
                            else {
                            cout << prices[l]<<" "<<q<<" ";
                            cout << "s\n";
                            }
                        }

                        for(auto k:plines){
                            if(quantity[k] == q){
                            orders.erase(std::remove(orders.begin(), orders.end(), k), orders.end());
                            quantity[k] = 0;
                            // cout << "removed order "<< k;
                            }
                            else {quantity[k] -= q;
                            // cout << "decreased "<<k;
                            }
                        }
                        // for(auto f:orders)
                        // cout << f<<". ";
                    }
                    else{
                        // cout <<"Loss:No Trade\n";
                        cout <<"No Trade\n";
                        count++;
                        break;
                    }

                }
                // cout << "prices are: \n";
                // for (auto c: prices){
                //     cout << c <<". ";
                // }
                // cout <<endl;
            //     cout<<"orders till now:";
            //     for(auto c: orders){cout <<c<<". ";}
            //     cout <<"\n";
            // for (int i = 0; i<count;i++){
            //     for(auto c:stocks){
            //         cout << c << ": "<<matrix[i][c]<<". ";
            //     }
            //     cout <<"\n";
            // }
                // cout << count;
                // matrix[4].printMap();
                // cout << prices[4];
                count++;
            }
                if(!characterExists) message = rcv.readIML();
                else break;
        }
                cout << finalprofit;

    }
    
    return 0;
}

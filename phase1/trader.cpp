#include "receiver.h"
#include <vector>
#include <string>
#include<unordered_map>

using namespace std;
vector<string> splitt(string s)
{
    string tmp="";
    vector<string> ans;
    for(char& c: s)
    {
        if(c!=' ')
        {
            tmp+=c;
        }
        else
        {
            ans.push_back(tmp);
            tmp="";
        }
    }
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
        else
        {
            ans.push_back(tmp);
            tmp="";
        }
    }
    return ans;
}
    
    std::unordered_map<string,int> order_book;

string processor(string stocking){
    string ans="No Trade\n";
    vector<string> order=splitt(stocking);
    cout << order[0] << " "<< order[1] << " "<<order[2];
    if(order_book[order[0]]==0)
    {
        order_book[order[0]]=stoi(order[1]);
    }
    if(order[2] == "b#"){
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

    Receiver rcv;
    sleep(4);
    std::string message = rcv.readIML();
    vector<string> ans;
    ans = splitn(message);
    for(auto c:ans){
        cout << processor(c);
    }
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

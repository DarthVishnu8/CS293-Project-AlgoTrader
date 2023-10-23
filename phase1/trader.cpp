#include "receiver.h"
#include<string>
#include<vector>
#include<unordered_map>
using namespace std;

int main() {

    Receiver rcv;
    sleep(5);
    std::string message;
    while (true) {
        message = rcv.readIML();

        // Check for the termination message "$"
        if (message == "$") {
            std::cout << "Received termination message. Exiting..." << std::endl;
            break;
        }

        // Print the received message
        std::cout << message;
    }

    // Close the receiver and exit
    rcv.terminate();
    return 0;
}

vector<string> splitt(string s)
{
    string tmp="";
    vector<string> ans;
    for(auto c: s)
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
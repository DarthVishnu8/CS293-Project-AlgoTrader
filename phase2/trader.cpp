// This is your trader. Place your orders from here


// #include <string>

// int reader(int time)
// {
//     return 1;
// }

// int trader(std::string *message)
// {
//     return 1;
// }

// above this is the original code

// This is your trader. Place your orders from here


#include <string>
#include <vector>
#include <fstream>
    
std::vector<std::string> orderList;    // declaring global variable orderList here

int reader(int time)                   // this part of the code reads the required output file (a test output file named myoutput.txt for now) and stores every line in the form a vector<string> named orderList
{
    std::ifstream inputFile;
    inputFile.open("myoutput.txt");


    // Read from the file
    std::string line;
    while (std::getline(inputFile, line)) {
        orderList.push_back(line);
    }

    // Close the file
    inputFile.close();

    // return 0; // Return success
    return 1;

}

int trader(std::string *message)
{
    
    return 1;
}


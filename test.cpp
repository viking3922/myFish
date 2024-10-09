#include <iostream>
#include <limits>
//using namespace std;

int getNumber(){
    //if the user enters a valid number, we break out from this endless loop;
    int num;
    while(true){
        std::cin >> num; // the stream will go in a fail state if the user enters an invalid value here (a character, for example)
        if (std::cin.fail()){ // cathes the fail state
            std::cout << "Enter a valid number!" << std::endl; //if cin.fail returns true
            std::cin.clear();//clear the fail state of the buffer
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');//clear the buffer from values entered
        }
        else
            break;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');//clear the buffer from values entered
    return num;
}

int main(){
    std::cout << getNumber() << std::endl;
    std::cout << getNumber();
    return 0;
}

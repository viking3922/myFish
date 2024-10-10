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
    for (int i = 1; i <= 4; i++){
        std::cout << "If you want to pass enter P" << std::endl;
        char answer;
        std::cin >> answer;
        if (answer == 'p'){
            std::cout << "Player " << i << " passes his/her turn" << std::endl;
            continue;
        }
        else{
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); //если пользователь вводит строку, то считывается только первый чар, а остально находится в буфере => надо очистить
            std::cout << "Select a figure to replace (a hex from which you want to replace your figure)" << std::endl;
            int currentPosition = getNumber();
            std::cout << "Where do you want to place your penguin? (Enter the Hex number)" << std::endl;
            int destination = getNumber();
            std::cout << "Player " << i << " moves his/her figure from " << currentPosition << " to "
                      << destination << std::endl;
        }
    }
    return 0;
}

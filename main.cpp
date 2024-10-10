#include <iostream>
#include <cstdlib> //rand() and srand() functions live here
#include <ctime> //time() function live here
#include <vector>
#include <map>
#include <limits>
#include "Hex.h"
#include "Figure.h"

int numberOfOneScoredHexes = 10;
int numberOfTwoScoredHexes = 5;
int numberOfThreeScoredHexes = 3;

std::vector<Hex> hexes;//later rewrite as array

//This function handles user input errors
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

//RANDOM FIELD GENERATION FUNCTIONS
std::map<int,int> grid;
//Is used to assign score value of a Hex
int randNumbGenerator(){
    const int maxValue = 3;
    const int minValue = 1;
    int score = (rand() % ( maxValue - minValue + 1)) + minValue;
    //std::cout << "RN generated: " << score << std::endl;
    return score;
}

// Is used to assign score value of a Hex - finds the Entry with Largest Value in a Map
int findKeyWithLargestValue(std::map<int, int> sampleMap){
    int keyWithLargestValue = 0; // for storage
    int largestValue = 0; // a reference variable
    // Iterate the map to find the required entry
    std::map<int, int>::iterator currentEntry;
    for (currentEntry = sampleMap.begin(); currentEntry != sampleMap.end(); ++currentEntry) {
        // If this entry's value is more than the largest value, set this entry as max
        if (currentEntry->second > largestValue) {
            keyWithLargestValue = currentEntry->first;
        }
    }
    return keyWithLargestValue;
}

// Function to print the Map
void printMap(std::map<int, int> sampleMap) {
    std::map<int, int>::iterator itr;
    for (itr = sampleMap.begin();
        itr != sampleMap.end();
        ++itr) {
        std::cout << itr->first
            << " = " << itr->second << ", ";
        }
    std::cout << std::endl;
}

int scoreAssignment(){
    //printMap(grid);
    int point = 0;
    int number = randNumbGenerator();
    //std::cout << number << std::endl;
    auto it = grid.find(number);
    if (it -> second != 0){
        //std::cout << "Generated number is OK" << std::endl;
        it -> second -= 1;
        point = it -> first;
    }
    else{
        int key = findKeyWithLargestValue(grid); //нашли наиболее редко встречающееся кол-во очков на настоящий момент
        auto itr = grid.find(key);
        //std::cout << "Generated number is NOT OK" << std::endl;
        itr -> second -= 1; // уменьшаем value
        point = itr -> first;//присваиваем хексу кол-во очков, равное key этой пары
    }
    return point;
}

//SHOW GRID FUCTION
void showGrid(){
    std::cout << "Hex num" << " Coords" << " Points" << " Exists?" << " Is free?" << " Owner" <<std::endl;
    for (int i = 0; i < hexes.size(); i++){
        std::cout << i + 1 << "\t" <<hexes[i];
    }
}


int main(){
    srand(time(nullptr));
    //Grid generation
    grid.emplace(1,numberOfOneScoredHexes);
    grid.emplace(2,numberOfTwoScoredHexes);
    grid.emplace(3,numberOfThreeScoredHexes);

    //std::vector<Hex> hexes;//later rewrite as array
    for (int i = 0; i <= 6; i++){
        Hex h;
        h.setX(i);
        for (int j = 0; j <= 4; j++){
            if(i % 2 == 0 && j % 2 == 0){
                h.setY(j);
                h.setScore(scoreAssignment());
                hexes.push_back(h);
                //std::cout << h.getX() << "," << h.getY() <<"\t";
            }
            else{
                if(i % 2 != 0 && j % 2 != 0){
                    h.setY(j);
                    h.setScore(scoreAssignment());
                    hexes.push_back(h);
                    //std::cout << h.getX() << "," << h.getY() <<"\t";
                }
            }
        }
        //std::cout << std::endl;
    }
    std::cout<<hexes.size()<<std::endl;

    showGrid();
    /*std::cout << "Hex num" << " Coords" << " Points" << " Exists?" << " Is free?" << " Owner" <<std::endl;
    for (int i = 0; i < hexes.size(); i++){
        std::cout << i + 1 << "\t" <<hexes[i];
    }*/

    /*for (auto hex : hexes){
        std::cout << hex;
    }*/

    //Figures placement
    int numOfPlayers = 2;
    int numOfFigures = 2;
    /*std::cout << "Enter the number of players: " << std::endl;
    std::cin >> numOfPlayers;
    if(numOfPlayers == 2)
        numOfFigures = 4;
    else if (numOfPlayers == 3)
        numOfFigures = 3;
    else if (numOfPlayers == 4)
        numOfFigures = 2;
    else
        std::cout << "Wrong number of players" << std::endl;
    */

    for (int i = 0; i < numOfFigures; i++)
        for (int j = 0; j < numOfPlayers; j++){
            //Figure f;
            int destination = 300; //doesn't exist
            std::cout << "Player" << j + 1 << ", where do you want to place your " << i + 1 << " penguin? (Enter the Hex number)" << std::endl;
            destination = getNumber();
            //std::cin >> destination;
            bool flag = true;
            while (flag == true){
                while (destination <= 0 || destination > 18){
                    std::cout << "Wrong input" << std::endl;
                    destination = getNumber();
                    //std::cin >> destination;
                }

                if(hexes[destination - 1].getIfIsFree() == true)
                {
                    if (hexes[destination - 1].getScore() == 1){
                        std::cout << "Ok, player" << j + 1 << " penguin is placed on " << destination << " hex" << std::endl;
                        hexes[destination - 1].setIfIsFree(false);
                        hexes[destination - 1].setOwner(j+1);
                        //f.setX(hexes[destination].getX());
                        //f.setY(hexes[destination].getY());
                        flag = false;
                    }
                    else{
                        std::cout << "You've chosen a hex with more than ONE point, try another one " << std::endl;
                        destination = getNumber();
                    }
                }
                else{
                    std::cout << "You've chosen a hex which is already occupied, try another one" << std::endl;
                    destination = getNumber();
                }
            }
        }
    showGrid();

    int scores[numOfPlayers];

    //One game round
    for (int i = 0; i < numOfPlayers; i++){
        std::cout << "Player " << i + 1 << "; If you want to pass your turn enter P, otherwise enter anything else" << std::endl;
        char answer;
        std::cin >> answer;
        if (answer == 'P'){
            std::cout << "Player " << i + 1 << " passes his/her turn" << std::endl;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); //если пользователь вводит строку, то считывается только первый чар, а остально находится в буфере => надо очистить
            continue;
        }
        else
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); //если пользователь вводит строку, то считывается только первый чар, а остально находится в буфере => надо очистить
            std::cout << "Select a figure to replace (a hex from which you want to replace your figure)" << std::endl;
            int currentPosition = getNumber();
            bool flag1 = true;
            while (flag1 == true){
                while (currentPosition <= 0 || currentPosition > 18){
                    std::cout << "Wrong input" << std::endl;
                    currentPosition = getNumber();
                }
                if(hexes[currentPosition - 1].getOwner() == i + 1){
                    std::cout << "Yep, this hex is occupied by your penguin" << std::endl;
                    flag1 = false;

                    std::cout << "Where do you want to place your penguin? (Enter the Hex number)" << std::endl;
                    int dest = getNumber();
                    bool flag2 = true;
                    while (flag2 == true){
                        while (dest <= 0 || dest > 18){
                            std::cout << "Wrong input" << std::endl;
                            dest = getNumber();
                        }

                        if(hexes[dest - 1].getIfExists() == true){
                            if(hexes[dest - 1].getIfIsFree() == true){
                                std::cout << "Yep, this hex is free, so the movement is possible" << std::endl;
                                hexes[currentPosition - 1].setOwner(0);
                                hexes[currentPosition - 1].setIfIsFree(true);
                                hexes[currentPosition - 1].setIfExists(false);
                                scores[i] = hexes[currentPosition - 1].getScore();
                                hexes[dest - 1].setIfIsFree(false);
                                hexes[dest - 1].setOwner(i+1);
                                flag2 = false;
                                std::cout << "Player " << i + 1 << " moves his/her figure from " << currentPosition << " to "
                                          << dest << std::endl;
                            }
                            else{
                                std::cout << "You've chosen a hex, which is already occupied, try another one " << std::endl;
                                dest = getNumber();
                            }
                        }
                        else{
                            std::cout << "You've chosen a hex, which doesn't exists anymore, try another one " << std::endl;
                            dest = getNumber();
                        }
                    }
                }
                else{
                    std::cout << "This hex is NOT occupied by your penguin, try another one" << std::endl;
                    currentPosition = getNumber();
                }
            }
        }
    }

    std::cout << "Scores: ";
    for (int score : scores){
        std::cout << score << " ";
    }
    std::cout << std::endl;

    showGrid();
    return 0;
}

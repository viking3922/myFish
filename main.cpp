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

    std::cout << "Hex num" << " Coords" << " Points" << " Exists?" << " Is free?" << " Owner" <<std::endl;
    for (int i = 0; i < hexes.size(); i++){
        std::cout << i << "\t" <<hexes[i];
    }

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
            std::cout << "Where do you want to place your penguin? (Enter the Hex number)" << std::endl;
            destination = getNumber();
            //std::cin >> destination;
            bool flag = true;
            while (flag == true){
                while (destination < 0 || destination >= 18){
                    std::cout << "Wrong input" << std::endl;
                    destination = getNumber();
                    //std::cin >> destination;
                }
                if(hexes[destination].getIfIsFree() == true)
                {
                    if (hexes[destination].getScore() == 1){
                        std::cout << "Ok, your figure is placed on " << destination << " hex" << std::endl;
                        hexes[destination].setIfIsFree(false);
                        hexes[destination].setOwner(j+1);
                        //f.setX(hexes[destination].getX());
                        //f.setY(hexes[destination].getY());
                        flag = false;
                    }
                    else{
                        std::cout << "You've chosen a hex with more than ONE point, try another one " << std::endl;
                        destination = getNumber();
                        //std::cin >> destination;
                    }
                }
                else{
                    std::cout << "You've chosen a hex which is already occupied, try another one " << std::endl;
                    destination = getNumber();
                    //std::cin >> destination;
                }
            }
        }

    std::cout << "Hex num" << " Coords" << " Points" << " Exists?" << " Is free?" << " Owner" <<std::endl;
    for (int i = 0; i < hexes.size(); i++){
        std::cout << i << "\t" <<hexes[i];
    }

    return 0;
}

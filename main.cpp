#include <iostream>
#include <cstdlib> //rand() and srand() functions live here
#include <ctime> //time() function live here
#include <vector>
#include <map>
#include <limits>
#include "Hex.h"
#include "Figure.h"

const int numberOfOneScoredHexes = 30;
const int numberOfTwoScoredHexes = 20;
const int numberOfThreeScoredHexes = 10;
int rows = 14;
int cols = 7;

Hex hexes[(numberOfOneScoredHexes+numberOfTwoScoredHexes+numberOfThreeScoredHexes)];

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

//SHOW GRID FUNCTION
void showGrid(){
    std::cout << "Hex num" << " Coords" << " Points" << " Owner" <<std::endl;
    for (int i = 0; i < std::size(hexes); i++){
        std::cout << i + 1 << "\t" <<hexes[i];
    }
}

//функция поиска индекса хекса по его координатам
int findIndexViaCoords(int x, int y){
    int ind = 0;
    if (y==0 || y==1)
        ind = x * 4;
    else if (y==2 || y==3)
        ind = x*4 + 1;
    else if (y==4 || y==5)
        ind = x*4 + 2;
    else
        ind = x*4 + 3;
    return ind;
}

int whichDirection(int currentHexInd, int destHexInd){
    int xDifference = 0;
    int direction = 0;
    if ((hexes[currentHexInd].getX()-hexes[destHexInd].getX())%2==0 && hexes[currentHexInd].getY() == hexes[destHexInd].getY()){
        xDifference=hexes[currentHexInd].getX()-hexes[destHexInd].getX();
        if (xDifference > 0) {
            std::cout << "figure moves to North" << std::endl;
            direction = 1;
        }
        else{
            std::cout << "figure moves to South" << std::endl;
            direction = 4;
        }
    }
    else if(hexes[currentHexInd].getX()-hexes[destHexInd].getX()==(hexes[currentHexInd].getY()-hexes[destHexInd].getY())*-1){
        xDifference=hexes[currentHexInd].getX()-hexes[destHexInd].getX();
        if (xDifference > 0) {
            std::cout << "figure moves to North-east" << std::endl;
            direction = 2;
        }
        else{
            std::cout << "figure moves to South-west" << std::endl;
            direction = 5;
        }
    }

    else if(hexes[currentHexInd].getX()-hexes[destHexInd].getX()==hexes[currentHexInd].getY()-hexes[destHexInd].getY()){
        xDifference=hexes[currentHexInd].getX()-hexes[destHexInd].getX();
        if (xDifference > 0) {
            std::cout << "figure moves to North-west" << std::endl;
            direction = 6;
        }
        else{
            std::cout << "figure moves to South-east" << std::endl;
            direction = 3;
        }
    }
    else{
        std::cout << "INAPPROPRIATE DIRECTION" << std::endl;
        direction = 0;
    }
    return direction;
}

bool noObstacles(int direction, int currentHexInd,int destHexInd){
    bool answer = false;//assume that there are some obstacles
    bool flag = true;//while we haven't reach the destination

    if (direction == 1){
        while(flag == true){
            int tempInd = findIndexViaCoords(hexes[currentHexInd].getX() - 2,hexes[currentHexInd].getY());
            if (tempInd == destHexInd){
                std::cout<<"No obstacles detected"<<std::endl;
                flag = false;
                answer = true;
            }
            else{
                if (hexes[tempInd].getScore() != 0 && hexes[tempInd].getOwner() == 0){
                    std::cout << "Jump to hex " << tempInd+1 << " was commited" <<std::endl;
                    currentHexInd = tempInd;
                }
                else{
                    flag = false;
                    break;
                }
            }
        }
    }

    else if (direction == 4){
        while(flag == true){
            int tempInd = findIndexViaCoords(hexes[currentHexInd].getX() + 2,hexes[currentHexInd].getY());
            if (tempInd == destHexInd){
                std::cout<<"No obstacles detected"<<std::endl;
                flag = false;
                answer = true;
            }
            else{
                if (hexes[tempInd].getScore() != 0 && hexes[tempInd].getOwner() == 0){
                    std::cout << "Jump to hex " << tempInd+1 << " was commited" <<std::endl;
                    currentHexInd = tempInd;
                }
                else{
                    flag = false;
                    break;
                }
            }
        }
    }

    else if (direction == 2){
        while(flag == true){
            int tempInd = findIndexViaCoords(hexes[currentHexInd].getX() - 1,hexes[currentHexInd].getY()+1);
            if (tempInd == destHexInd){
                std::cout<<"No obstacles detected"<<std::endl;
                flag = false;
                answer = true;
            }
            else{
                if (hexes[tempInd].getScore() != 0 && hexes[tempInd].getOwner() == 0){
                    std::cout << "Jump to hex " << tempInd+1 << " was commited" <<std::endl;
                    currentHexInd = tempInd;
                }
                else{
                    flag = false;
                    break;
                }
            }
        }
    }

    else if (direction == 5){
        while(flag == true){
            int tempInd = findIndexViaCoords(hexes[currentHexInd].getX() + 1,hexes[currentHexInd].getY()-1);
            if (tempInd == destHexInd){
                std::cout<<"No obstacles detected"<<std::endl;
                flag = false;
                answer = true;
            }
            else{
                if (hexes[tempInd].getScore() != 0 && hexes[tempInd].getOwner() == 0){
                    std::cout << "Jump to hex " << tempInd+1 << " was commited" <<std::endl;
                    currentHexInd = tempInd;
                }
                else{
                    flag = false;
                    break;
                }
            }
        }
    }

    else if (direction == 6){
        while(flag == true){
            int tempInd = findIndexViaCoords(hexes[currentHexInd].getX() - 1,hexes[currentHexInd].getY()-1);
            if (tempInd == destHexInd){
                std::cout<<"No obstacles detected"<<std::endl;
                flag = false;
                answer = true;
            }
            else{
                if (hexes[tempInd].getScore() != 0 && hexes[tempInd].getOwner() == 0){
                    std::cout << "Jump to hex " << tempInd+1 << " was commited" <<std::endl;
                    currentHexInd = tempInd;
                }
                else{
                    flag = false;
                    break;
                }
            }
        }
    }

    else {
        while(flag == true){
            int tempInd = findIndexViaCoords(hexes[currentHexInd].getX() + 1,hexes[currentHexInd].getY()+1);
            if (tempInd == destHexInd){
                std::cout<<"No obstacles detected"<<std::endl;
                flag = false;
                answer = true;
            }
            else{
                if (hexes[tempInd].getScore() != 0 && hexes[tempInd].getOwner() == 0){
                    std::cout << "Jump to hex " << tempInd+1 << " was commited" <<std::endl;
                    currentHexInd = tempInd;
                }
                else{
                    flag = false;
                    break;
                }
            }
        }
    }
    return answer;
}

int main(){
    srand(time(nullptr));
    //Grid generation
    grid.emplace(1,numberOfOneScoredHexes);
    grid.emplace(2,numberOfTwoScoredHexes);
    grid.emplace(3,numberOfThreeScoredHexes);

    //std::vector<Hex> hexes;//later rewrite as array
    Hex* ptr = hexes;//указывает на первый элемент массива

    //int rows = 14;
    //int cols = 7;
    for (int i = 0; i <= rows; i++){
        Hex h;
        h.setX(i);
        for (int j = 0; j <= cols; j++){
            if(i % 2 == 0 && j % 2 == 0){
                h.setY(j);
                h.setScore(scoreAssignment());
                //hexes.push_back(h);
                *ptr = h;
                ptr++;
                //std::cout << h.getX() << "," << h.getY() <<"\t";
            }
            else{
                if(i % 2 != 0 && j % 2 != 0){
                    h.setY(j);
                    h.setScore(scoreAssignment());
                    //hexes.push_back(h);
                    *ptr = h;
                    ptr++;
                    //std::cout << h.getX() << "," << h.getY() <<"\t";
                }
            }
        }
        //std::cout << std::endl;
    }

    showGrid();

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

    //Figures placement
    for (int i = 0; i < numOfFigures; i++)
        for (int j = 0; j < numOfPlayers; j++){
            //Figure f;
            int destination = 300; //doesn't exist
            std::cout << "Player" << j + 1 << ", where do you want to place your " << i + 1 << " penguin? (Enter the Hex number)" << std::endl;
            destination = getNumber();
            //std::cin >> destination;
            bool flag = true;
            while (flag == true){
                while (destination <= 0 || destination > std::size(hexes)){
                    std::cout << "Wrong input" << std::endl;
                    destination = getNumber();
                    //std::cin >> destination;
                }

                if(hexes[destination - 1].getOwner() == 0)
                {
                    if (hexes[destination - 1].getScore() == 1){
                        std::cout << "Ok, player" << j + 1 << " penguin is placed on " << destination << " hex" << std::endl;
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

    std::cout<<findIndexViaCoords(0,4) << " " << findIndexViaCoords(1,5);

    int scores[numOfPlayers] = {0};

    for (int j = 0; j < 2; j++){
        std::cout << "Round" << j << std::endl;
        for (int i = 0; i < numOfPlayers; i++){
            std::cout << "Player " << i + 1 << "; If you want to pass your turn enter P, otherwise enter anything else" << std::endl;
            char answer;
            std::cin >> answer;
            if (answer == 'P'){
                std::cout << "Player " << i + 1 << " passes his/her turn" << std::endl;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); //если пользователь вводит строку, то считывается только первый чар, а остально находится в буфере => надо очистить
                continue;
            }
            else{
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); //если пользователь вводит строку, то считывается только первый чар, а остально находится в буфере => надо очистить
                std::cout << "Select a figure to replace (a hex from which you want to replace your figure)" << std::endl;
                int currentPosition = getNumber();
                bool flag1 = true;
                while (flag1 == true){
                    while (currentPosition <= 0 || currentPosition > std::size(hexes)){
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
                            while (dest <= 0 || dest > std::size(hexes)){
                                std::cout << "Wrong input" << std::endl;
                                dest = getNumber();
                            }

                            if((hexes[dest - 1].getScore() != 0) && hexes[dest - 1].getOwner() == 0){
                                std::cout << "Yep, this hex exists and is free. But what about direction?"<< std::endl; // not really - before (?) you need to check 1) DIRECTION, 2) the existance of NON-EXISTENT hexes a;ong the way, 3) the existance of OCCUPIED hexes along the way
                                if(whichDirection(currentPosition - 1,dest - 1) != 0){
                                    std::cout << "Yep, the direction is OK."<< std::endl;
                                    if(noObstacles(whichDirection(currentPosition - 1,dest - 1), currentPosition - 1, dest - 1) == true){
                                        scores[i] += hexes[currentPosition - 1].getScore();
                                        hexes[currentPosition - 1].setOwner(0);
                                        hexes[currentPosition - 1].setScore(0);
                                        hexes[dest - 1].setOwner(i+1);
                                        flag2 = false;
                                        std::cout << "Player " << i + 1 << " moves his/her figure from " << currentPosition << " to "
                                                  << dest << std::endl;
                                    }
                                    else{
                                        std::cout << "There are occupied or non-existing hexes on the way" << std::endl;
                                        dest = getNumber();
                                    }
                                }

                                else{
                                    std::cout << "You've chosen an inappropriate hex (no direction)." << std::endl;
                                    dest = getNumber();
                                }
                            }
                            else{
                            std::cout << "You've chosen a hex, which doesn't exists anymore, or is occupied" << std::endl;
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
    }

    return 0;
}

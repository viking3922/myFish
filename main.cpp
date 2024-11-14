#include <iostream>
#include <cstdlib> //rand() and srand() functions live here
#include <ctime> //time() function live here
#include <vector>
#include <map>
#include <limits>
#include "Hex.h"


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

bool anyNeighbours(int hexIndex){
    bool neighbourFound = false; //пока ни один сосед не найден
    int ind = 300; //здесь будем хранить индекс существующего соседа

    //если северного соседа нет в сетке
    if (hexes[hexIndex].getX() - 2 < 0){
        std::cout<<"No N neighbour in grid" << std::endl;
    }
    else{
        std::cout <<"N neighbour in grid" << std::endl;
        ind = findIndexViaCoords(hexes[hexIndex].getX() - 2, hexes[hexIndex].getY()); // находим индекс северного соседа
        //если cосед подходит
        if(hexes[ind].getOwner()==0 && hexes[ind].getScore()!=0){
            std::cout << "Hex " << ind + 1 << " suits!" << std::endl;
            neighbourFound = true;
        }
        else{
            std::cout << "But it doesn't suit!" << std::endl;
        }
    }

    if(neighbourFound == false){
        //если СВ соседа нет в сетке
        if(hexes[hexIndex].getX() - 1 < 0 || hexes[hexIndex].getY() + 1 > cols){
            std::cout<<"No NE neighbour in grid" << std::endl;
        }
        else{
            std::cout <<"NE neighbour in grid" << std::endl;
            ind = findIndexViaCoords(hexes[hexIndex].getX() - 1, hexes[hexIndex].getY() + 1); // находим индекс СВ соседа
            //если сосед подходит
            if(hexes[ind].getOwner()==0 && hexes[ind].getScore()!=0){
                std::cout << "Hex " << ind + 1 << " suits!" << std::endl;
                neighbourFound = true;
            }
            else{
                std::cout << "But it doesn't suit!" << std::endl;
            }
        }
    }

    if(neighbourFound == false){
        //если ЮВ соседа нет сетке
        if(hexes[hexIndex].getX() + 1 > rows || hexes[hexIndex].getY() + 1 > cols){
            std::cout<<"No SE neighbour in grid" << std::endl;
        }
        else{
            std::cout <<"SE neighbour in grid" << std::endl;
            ind = findIndexViaCoords(hexes[hexIndex].getX() + 1, hexes[hexIndex].getY() + 1); // находим индекс ЮВ соседа
            //если сосед подходит
            if(hexes[ind].getOwner()==0 && hexes[ind].getScore()!=0){
                std::cout << "Hex " << ind + 1 << " suits!" << std::endl;
                neighbourFound = true;
            }
            else{
                std::cout << "But it doesn't suit!" << std::endl;
            }
        }
    }

    if(neighbourFound == false){
        //если Ю соседа нет сетке
        if(hexes[hexIndex].getX() + 2 > rows){
            std::cout<<"No S neighbour in grid" << std::endl;
        }
        else{
            std::cout <<"S neighbour in grid" << std::endl;
            ind = findIndexViaCoords(hexes[hexIndex].getX() + 2,hexes[hexIndex].getY()); // находим индекс южного соседа
            //если сосед подходит
            if(hexes[ind].getOwner()==0 && hexes[ind].getScore()!=0){
                std::cout << "Hex " << ind + 1 << " suits!" << std::endl;
                neighbourFound = true;
            }
            else{
                std::cout << "But it doesn't suit!" << std::endl;
            }
        }
    }

    if(neighbourFound == false){
        //если ЮЗ соседа нет сетке
        if(hexes[hexIndex].getX() + 1 > rows || hexes[hexIndex].getY() - 1 < 0){
            std::cout<<"No SW neighbour in grid" << std::endl;
        }
        else{
            std::cout <<"SW neighbour in grid" << std::endl;
            ind = findIndexViaCoords(hexes[hexIndex].getX() + 1, hexes[hexIndex].getY() - 1); // находим индекс ЮЗ соседа
            //если сосед подходит
            if(hexes[ind].getOwner()==0 && hexes[ind].getScore()!=0){
                std::cout << "Hex " << ind + 1 << " suits!" << std::endl;
                neighbourFound = true;
            }
            else{
                std::cout << "But it doesn't suit!" << std::endl;
            }
        }
    }

    if(neighbourFound == false){
        //если CЗ соседа нет сетке
        if(hexes[hexIndex].getX() - 1 < 0 || hexes[hexIndex].getY() - 1 < 0){
            std::cout<<"No NW neighbour in grid" << std::endl;
        }
        else{
            std::cout <<"NW neighbour in grid" << std::endl;
            ind = findIndexViaCoords(hexes[hexIndex].getX() - 1, hexes[hexIndex].getY() - 1); // находим индекс СЗ соседа
            //если сосед подходит
            if(hexes[ind].getOwner()==0 && hexes[ind].getScore()!=0){
                std::cout << "Hex " << ind + 1 << " suits!" << std::endl;
                neighbourFound = true;
            }
            else{
                std::cout << "But it doesn't suit!" << std::endl;
            }
        }
    }

    if(neighbourFound == false){
        std::cout << "No good neigbours available" <<std::endl;
    }
    return neighbourFound;
}

bool gameOver(int totalNumOfFigures){
    bool gOver = true;
    for (int i = 0; i < std::size(hexes); i++){
        if(totalNumOfFigures>0){
            if(hexes[i].getOwner()!=0){
                std::cout << "Checking neighbours of Hex" << i + 1 << std::endl;
                totalNumOfFigures-=1;
                if(anyNeighbours(i)==true){
                    gOver = false;
                    break;
                }
            }
        }
    }
    return gOver;
}

bool playerCanMove(int numOfFigures, int player){
    bool anyMoves = false;
    for (int i = 0; i < std::size(hexes); i++){
        if (numOfFigures>0){
            if(hexes[i].getOwner() == player){
                std::cout << "Does player" << player << " have possible moves? Let's find out!" << std::endl;
                numOfFigures-=1;
                std::cout << "Checking neighbours of hex "<< i + 1 << std::endl;
                if(anyNeighbours(i)==true){
                    anyMoves = true;
                    break;
                }
            }
        }
    }
    return anyMoves;
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

    int scores[numOfPlayers] = {0};
    int roundCounter = 1;
    while(gameOver(numOfPlayers*numOfFigures)==false){
        std::cout << "Round " << roundCounter << ":" << std::endl;
        for (int i = 1; i <= numOfPlayers; i++){
            if(playerCanMove(numOfFigures,i)==true){
                std::cout << "Player" << i << " makes his move" << std::endl;
                std::cout << "Select a figure to replace (a hex from which you want to replace your figure)" << std::endl;
                int currentPosition = getNumber();
                bool flag1 = true;
                while (flag1 == true){
                    while (currentPosition <= 0 || currentPosition > std::size(hexes)){
                        std::cout << "Wrong input" << std::endl;
                        currentPosition = getNumber();
                    }
                    if(hexes[currentPosition - 1].getOwner() == i){
                        std::cout << "Yep, this hex is occupied by your penguin" << std::endl;

                        if(anyNeighbours(currentPosition - 1) == true){
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
                                            scores[i-1] += hexes[currentPosition - 1].getScore();
                                            hexes[currentPosition - 1].setOwner(0);
                                            hexes[currentPosition - 1].setScore(0);
                                            hexes[dest - 1].setOwner(i);
                                            flag2 = false;
                                            std::cout << "Player " << i << " moves his/her figure from " << currentPosition << " to "
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
                            std::cout << "But there are no options for movement, so choose another hex" << std::endl;
                            currentPosition = getNumber();
                        }
                    }

                    else{
                        std::cout << "This hex is NOT occupied by your penguin, try another one" << std::endl;
                        currentPosition = getNumber();
                    }
                }
            }
        }
        roundCounter+=1;
        std::cout << "Scores: ";
        for (int score : scores){
            std::cout << score << " ";
        }
        std::cout << std::endl;
        showGrid();
    }
    std::cout<<"GAME OVER!!!"<<std::endl;

    std::cout << "Scores: ";
    int totalNumOfPlayers = numOfPlayers*numOfFigures;

    // Для учета очков на тех хексах, с которых сдвинуться нельзя.
    for (int i = 0; i < std::size(hexes); i++){
        if(totalNumOfPlayers>0){
            if(hexes[i].getOwner() != 0){
                scores[hexes[i].getOwner() - 1] += hexes[i].getScore();
                hexes[i].setOwner(0);
                hexes[i].setScore(0);
                totalNumOfPlayers-=1;
            }
        }
    }

    for (int score : scores){
        std::cout << score << " ";
    }

    return 0;
}

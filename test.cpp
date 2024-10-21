#include <iostream>
#include <limits>
//using namespace std
#include "Hex.h"

const int numberOfOneScoredHexes = 10;
const int numberOfTwoScoredHexes = 4;
const int numberOfThreeScoredHexes = 7;
int rows = 6;
int cols = 5;

Hex hexes[(numberOfOneScoredHexes+numberOfTwoScoredHexes+numberOfThreeScoredHexes)];

//функция поиска индекса хекса по его координатам
int findIndexViaCoords(int x, int y){
    int ind = 0;
    if (y==0 || y==1)
        ind = x * 3;
    else if (y==2 || y==3)
        ind = x*3 + 1;
    else
        ind = x*3 + 2;
    return ind;
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


bool moveIsPossible(int numOfFigures, int player){
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

//SHOW GRID FUNCTION
void showGrid(){
    std::cout << "Hex num" << " Coords" << " Points" << " Owner" <<std::endl;
    for (int i = 0; i < std::size(hexes); i++){
        std::cout << i + 1 << "\t" <<hexes[i];
    }
}
/*bool massive search
bool endGame(bool myBools, int myBoolsSize){
    bool end = true;
    for (int i = 0; i < myBoolsSize; i++){
        if(myBools[i]==true){
            end = false;
            break;
        }
    }
    return end;
}*/

int main(){
    Hex* ptr = hexes;//указывает на первый элемент массива
    for (int i = 0; i <= rows; i++){
        Hex h;
        h.setX(i);
        for (int j = 0; j <= cols; j++){
            if(i % 2 == 0 && j % 2 == 0){
                h.setY(j);
                h.setScore(1);
                *ptr = h;
                ptr++;
            }
            else{
                if(i % 2 != 0 && j % 2 != 0){
                    h.setY(j);
                    h.setScore(1);
                    *ptr = h;
                    ptr++;
                }
            }
        }

    }
    showGrid();
    hexes[2].setOwner(1);
    hexes[5].setOwner(2);
    hexes[8].setOwner(1);
    hexes[4].setOwner(2);
    showGrid();

    std::cout << whichDirection(7,1) << std::endl;
    std::cout << whichDirection(7,2) << std::endl;
    std::cout << whichDirection(7,17) << std::endl;
    std::cout << whichDirection(7,19) << std::endl;
    std::cout << whichDirection(7,12) << std::endl;
    std::cout << whichDirection(7,0) << std::endl;
    std::cout << whichDirection(7,15) << std::endl;


    int numOfPlayers = 2;
    int numOfFigures = 2;







    /*int xDifference;
    if ((x1-x2)%2==0 && y1 == y2){
        xDifference=(x1-x2);
        if (xDifference > 0) {
            std::cout << "figure moves to North" << std::endl;
        }
        else{
            std::cout << "figure moves to South" << std::endl;
        }
    }
    else if((x1-x2)==(y1-y2)*-1){
        xDifference=x1-x2;
        if (xDifference > 0) {
            std::cout << "figure moves to North-west" << std::endl;
        }
        else{
            std::cout << "figure moves to South-east" << std::endl;
        }
    }

    else if((x1-x2)==(y1-y2)){
        xDifference=x1-x2;
        if (xDifference > 0) {
            std::cout << "figure moves to South-east" << std::endl;
        }
        else{
            std::cout << "figure moves to North-west" << std::endl;
        }
    }
    else
        std::cout << "INAPPROPRIATE DIRECTION" << std::endl;

    */
    return 0;
}

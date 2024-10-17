#include <iostream>
#include <limits>
//using namespace std
#include "Hex.h"

const int numberOfOneScoredHexes = 30;
const int numberOfTwoScoredHexes = 20;
const int numberOfThreeScoredHexes = 10;

Hex hexes[(numberOfOneScoredHexes+numberOfTwoScoredHexes+numberOfThreeScoredHexes)];
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

int main(){
    std::cout << findIndexViaCoords(0,0) << " " << findIndexViaCoords(0,4) << " " << findIndexViaCoords(1,7)
              << " " << findIndexViaCoords(5,3) << " " << findIndexViaCoords(6,2) << " " << findIndexViaCoords(7,5)
              << " " << findIndexViaCoords(12,6) << " " << findIndexViaCoords(13,1);



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

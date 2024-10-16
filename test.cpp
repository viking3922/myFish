#include <iostream>
#include <limits>
//using namespace std
#include "Hex.h"

const int numberOfOneScoredHexes = 30;
const int numberOfTwoScoredHexes = 20;
const int numberOfThreeScoredHexes = 10;

Hex hexes[(numberOfOneScoredHexes+numberOfTwoScoredHexes+numberOfThreeScoredHexes)];

int main(){
    int x1 = 6;
    int y1 = 4;
    int x2 = 9;
    int y2 = 7;

    /*Hex h26={6,4,1,1,0,1};//существует, занята первым игроком
    Hex h18={4,4,2,0,1,0};//не существует, свободна
    Hex h22={5,5,1,1,0,2};//существует, занята вторым*/



    int xDifference;

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

    return 0;



    return 0;
}

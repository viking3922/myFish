#include <iostream>
#include "Hex.h"

/*int Hex::getInd() const{
    return ind;
}*/

int Hex::getX() const{
    return x;
}

int Hex::getY() const{
    return y;
}

/*bool Hex::getIfExists() const{
    return existance;
}*/

/*bool Hex::getIfIsFree() const{
    return isFree;
}*/

int Hex::getOwner() const{
    return owner;
}

int Hex::getScore() const{
    return score;
}

void Hex::setX(int x){
    this->x = x;
}

void Hex::setY(int y){
    this->y = y;
}

void Hex::setScore(int score){
    this->score = score;
}

/*void Hex::setIfExists(bool existance){
    this->existance = existance;
}*/

/*void Hex::setIfIsFree(bool isFree){
    this->isFree = isFree;
}*/

void Hex::setOwner(int owner){
    this->owner = owner;
}

/*std::ostream& operator<<(std::ostream& stream, const Hex& hex){
    stream << "[" << hex.getX() << "," << hex.getY() << "]" << "\t" << hex.getScore() << "\t"
           << hex.getIfExists() <<  "\t" << hex.getIfIsFree() <<  "\t" << hex.getOwner() << std::endl;
    return stream;
}*/

std::ostream& operator<<(std::ostream& stream, const Hex& hex){
    stream << "[" << hex.getX() << "," << hex.getY() << "]" << "\t" << hex.getScore() << "\t"
           <<  hex.getOwner() << std::endl;
    return stream;
}

/*Hex::Hex(int x, int y, int score){
    setX(x);
    setY(y);
    setScore(score);
    std::cout << "Hex is constructed" << std::endl;
}*/

Hex::Hex(int x, int y, int score, int owner)
{
    setX(x);
    setY(y);
    setScore(score);
    setOwner(owner);
}


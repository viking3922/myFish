//
// Created by user on 01.10.2024.
//

#ifndef HEX_H
#define HEX_H
#include <ostream>

class Hex {
public:
    Hex()=default;
    //Hex(int x, int y, int score);
    //Getters
    int getX() const;
    int getY() const;
    int getScore() const;
    bool getIfExists() const;
    bool getIfIsFree() const;
    int getOwner() const;
    //Setters
    void setX(int x);
    void setY(int y);
    void setScore(int x);
    void setIfExists(bool existance);
    void setIfIsFree(bool isFree);
    void setOwner(int owner);
private:
    int x = 0;
    int y = 0;
    bool existance = true;
    bool isFree = true;
    int score = 0;
    int owner = 0;
};

std::ostream& operator <<(std::ostream& stream, const Hex& hex);



#endif //HEX_H

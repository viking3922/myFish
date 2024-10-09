//
// Created by user on 04.10.2024.
//

#ifndef FIGURE_H
#define FIGURE_H
#include <ostream>
#include "Hex.h"

class Figure {
public:
    int getX() const;
    int getY() const;
    void setX(int x);
    void setY(int y);
private:
    //no such Hex on a grid
    int x = 0;
    int y = 1;
    std::string colour;
};



#endif //FIGURE_H

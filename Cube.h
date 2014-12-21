#ifndef CUBE_H
#define CUBE_H

#include <vector>

class Cube
{
public:
    Cube();
    void initVertices();
    void initColors( int numOfVertices );

    std::vector<float> vertices;
    std::vector<float> colors;
};

#endif // CUBE_H

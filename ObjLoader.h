#ifndef OBJLOADER_H
#define OBJLOADER_H

#include <vector>

class ObjLoader
{
public:
    static std::vector<float> load( const char *fileName );
};

#endif // OBJLOADER_H

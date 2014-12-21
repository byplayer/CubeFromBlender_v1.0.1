#include <fstream>
#include <iostream>
#include <string>
#include <cstdio>
#include "ObjLoader.h"

std::vector<float> ObjLoader::load( const char *fileName )
{
    std::vector<float> vertices;

    std::ifstream in( fileName );
    if ( !in.is_open() )
    {
        std::cerr << "Error: unable to open the file " << fileName << std::endl;
        return vertices;
    }

    char buf[256];
    std::vector<std::string> strArray;
    while( !in.eof() )
    {
        in.getline( buf, 256 );
        std::string str( buf );
        strArray.push_back( str );
    }

    for ( unsigned int i = 0; i < strArray.size(); ++i )
    {
        if ( strArray[i].c_str()[0] == '#' )
            continue;
        else if ( strArray[i].c_str()[0] == 'v' && strArray[i].c_str()[1] == ' ' )
        {
            float tmpX, tmpY, tmpZ;
            sscanf( strArray[i].c_str(), "v %f %f %f", &tmpX, &tmpY, &tmpZ );
            vertices.push_back( tmpX );
            vertices.push_back( tmpY );
            vertices.push_back( tmpZ );
        }
    }

    return vertices;
}

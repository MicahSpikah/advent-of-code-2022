#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

std::vector< std::string > parse_input( int const argc, char* const argv[] )
{
    if( argc != 2 )
    {
        std::cerr << "Error: Run as " << argv[ 0 ] << " <input.txt>\n";
        std::exit( 1 );
    }
    std::vector< std::string > out;
    std::ifstream file( argv[ 1 ] );
    if( !file.is_open() )
    {
        std::cerr << "Error: Could not open " << argv[ 1 ] << '\n';
        std::exit( 1 );
    }

    for( std::string line; std::getline( file, line ); )
    {
        out.push_back( line );
    }

    return out;
}

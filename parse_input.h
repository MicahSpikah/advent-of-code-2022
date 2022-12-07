#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <variant>
#include <vector>

using advent_t = std::variant< std::string, int >;
advent_t advent( std::vector< std::string > const& raw_input );

int main( int const argc, char* const argv[] )
try
{
    if( argc != 2 )
    {
        std::cerr << "Error: Run as " << argv[ 0 ] << " <input.txt>\n";
        std::exit( 1 );
    }
    std::ifstream file( argv[ 1 ] );
    if( !file.is_open() )
    {
        std::cerr << "Error: Could not open " << argv[ 1 ] << '\n';
        std::exit( 1 );
    }

    std::vector< std::string > raw_input;
    for( std::string line; std::getline( file, line ); )
    {
        raw_input.push_back( line );
    }

    std::visit( []( auto const result ) { std::cout << result << '\n'; }, advent( raw_input ) );
}
catch( std::exception const& e )
{
    std::cout << "Exception: " << e.what() << '\n';
    return 1;
}
catch( ... )
{
    std::cout << "Unknown exception\n";
    return 1;
}

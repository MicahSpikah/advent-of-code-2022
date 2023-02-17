#include "parse_input.h"
#include <set>
#include <tuple>

advent_t advent( std::vector< std::string > const& input )
{
    std::set< std::tuple< int, int, int > > points;
    for( auto const& line : input )
    {
        int x, y, z;
        sscanf( line.c_str(), "%d,%d,%d", &x, &y, &z );
        points.insert( { x, y, z } );
    }
    int area{};

    for( auto const& p : points )
    {
        if( !points.contains( { std::get< 0 >( p ) + 1, std::get< 1 >( p ), std::get< 2 >( p ) } ) )
            ++area;
        if( !points.contains( { std::get< 0 >( p ) - 1, std::get< 1 >( p ), std::get< 2 >( p ) } ) )
            ++area;
        if( !points.contains( { std::get< 0 >( p ), std::get< 1 >( p ) + 1, std::get< 2 >( p ) } ) )
            ++area;
        if( !points.contains( { std::get< 0 >( p ), std::get< 1 >( p ) - 1, std::get< 2 >( p ) } ) )
            ++area;
        if( !points.contains( { std::get< 0 >( p ), std::get< 1 >( p ), std::get< 2 >( p ) + 1 } ) )
            ++area;
        if( !points.contains( { std::get< 0 >( p ), std::get< 1 >( p ), std::get< 2 >( p ) - 1 } ) )
            ++area;
    }

    return area;
}

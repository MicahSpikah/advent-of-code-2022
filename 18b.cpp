#include "parse_input.h"
#include <set>
#include <tuple>

std::set< std::tuple< int, int, int > > points;
std::set< std::tuple< int, int, int > > exterior;

int minx, maxx, miny, maxy, minz, maxz;

void grow_exterior( std::tuple< int, int, int > p )
{
    auto x = std::get< 0 >( p );
    auto y = std::get< 1 >( p );
    auto z = std::get< 2 >( p );

    if( x < minx - 1 || x > maxx + 1 || y < miny - 1 || y > maxy + 1 || z < minz - 1 || z > maxz + 1 || points.contains( p ) || exterior.contains( p ) )
    {
        return;
    }

    exterior.insert( p );
    grow_exterior( { x - 1, y, z } );
    grow_exterior( { x + 1, y, z } );
    grow_exterior( { x, y - 1, z } );
    grow_exterior( { x, y + 1, z } );
    grow_exterior( { x, y, z - 1 } );
    grow_exterior( { x, y, z + 1 } );
}

advent_t advent( std::vector< std::string > const& input )
{
    for( auto const& line : input )
    {
        int x, y, z;
        sscanf( line.c_str(), "%d,%d,%d", &x, &y, &z );
        points.insert( { x, y, z } );
    }
    int area{};

    minx = std::get< 0 >( *points.cbegin() );
    maxx = std::get< 0 >( *points.cbegin() );
    miny = std::get< 1 >( *points.cbegin() );
    maxy = std::get< 1 >( *points.cbegin() );
    minz = std::get< 2 >( *points.cbegin() );
    maxz = std::get< 2 >( *points.cbegin() );

    for( auto const& p : points )
    {
        minx = std::min( minx, std::get< 0 >( p ) );
        maxx = std::max( maxx, std::get< 0 >( p ) );
        miny = std::min( miny, std::get< 1 >( p ) );
        maxy = std::max( maxy, std::get< 1 >( p ) );
        minz = std::min( minz, std::get< 2 >( p ) );
        maxz = std::max( maxz, std::get< 2 >( p ) );
    }

    grow_exterior( { minx - 1, miny - 1, minz - 1 } );

    for( auto const& p : points )
    {
        if( exterior.contains( { std::get< 0 >( p ) + 1, std::get< 1 >( p ), std::get< 2 >( p ) } ) )
            ++area;
        if( exterior.contains( { std::get< 0 >( p ) - 1, std::get< 1 >( p ), std::get< 2 >( p ) } ) )
            ++area;
        if( exterior.contains( { std::get< 0 >( p ), std::get< 1 >( p ) + 1, std::get< 2 >( p ) } ) )
            ++area;
        if( exterior.contains( { std::get< 0 >( p ), std::get< 1 >( p ) - 1, std::get< 2 >( p ) } ) )
            ++area;
        if( exterior.contains( { std::get< 0 >( p ), std::get< 1 >( p ), std::get< 2 >( p ) + 1 } ) )
            ++area;
        if( exterior.contains( { std::get< 0 >( p ), std::get< 1 >( p ), std::get< 2 >( p ) - 1 } ) )
            ++area;
    }
    return area;
}

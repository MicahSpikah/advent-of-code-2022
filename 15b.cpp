#include "parse_input.h"
#include <cmath>

struct range
{
    std::int64_t min;
    std::int64_t max;
};

//std::int64_t limit{ 20 };
std::int64_t limit{ 4000000 };

advent_t advent( std::vector< std::string > const& input )
{
    for( std::int64_t target = 0; target <= limit; ++target )
    {
        if( target % 100000 == 0 )
            std::cout << target << '\n';
        std::vector< range > ranges;

        for( auto const& l : input )
        {
            std::int64_t sx, sy, bx, by;
            std::sscanf( l.c_str(), "Sensor at x=%lld, y=%lld: closest beacon is at x=%lld, y=%lld", &sx, &sy, &bx, &by );

            auto const dist = std::abs( sx - bx ) + std::abs( sy - by );

            if( auto const rows_to_target = std::abs( target - sy ); rows_to_target <= dist )
            {
                range r{ sx - ( dist - rows_to_target ), sx + ( dist - rows_to_target ) };

                r.min = std::max( 0ll, r.min );
                r.max = std::min( r.max, limit );
                // std::cout << "Sensor " << sx << ", " << sy << " implies no beacons from " << r.min << " to " << r.max << '\n';
                if( r.min <= r.max )
                {
                    ranges.push_back( r );
                }
            }
        }

        if( ranges.empty() )
            throw std::runtime_error( "Empty row" );

        std::sort( ranges.begin(), ranges.end(), [ & ]( auto const& r0, auto const& r1 ) { return r0.min < r1.min; } );

        if( ranges.front().min == 1 )
            return target;
        else if( ranges.front().min > 1 )
            throw std::runtime_error( "Initial gap" );

        std::int64_t max = ranges.front().max;

        for( auto const& r : ranges )
        {
            if( r.min <= max + 1 )
                max = std::max( max, r.max );
            else if( max + 2 == r.min )
                return 4000000 * ( max + 1 ) + target;
            else
                throw std::runtime_error( "Big gap" );
        }
        if( max + 1 == limit )
            return 4000000 * limit + target;
        else if( max < limit )
            throw std::runtime_error( "End gap" );
    }

    throw std::runtime_error( "Never found any potential" );
}

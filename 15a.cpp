#include "parse_input.h"
#include <cmath>

struct range
{
    std::int64_t min;
    std::int64_t max;
};

std::int64_t target{ 2000000 };
//std::int64_t target{10};

advent_t advent( std::vector< std::string > const& input )
{
    std::vector< range > ranges;

    for( auto const& l : input )
    {
        std::int64_t sx, sy, bx, by;
        std::sscanf( l.c_str(), "Sensor at x=%lld, y=%lld: closest beacon is at x=%lld, y=%lld", &sx, &sy, &bx, &by );

        auto const dist = std::abs( sx - bx ) + std::abs( sy - by );

        if( auto const rows_to_target = std::abs( target - sy ); rows_to_target <= dist )
        {
            range r{ sx - ( dist - rows_to_target ), sx + ( dist - rows_to_target ) };
            if( by == target )
            {
                if( bx == r.min )
                    ++r.min;
                else
                    --r.max;
            }

            if( r.min <= r.max )
            {
                // std::cout << "Sensor " << sx << ", " << sy << " implies no beacons from " << r.min << " to " << r.max << '\n';
                ranges.push_back( r );
            }
        }
    }

    std::sort( ranges.begin(), ranges.end(), [ & ]( auto const& r0, auto const& r1 ) { return r0.min < r1.min; } );

    std::vector< range > consolidated;

    for( auto const& r : ranges )
    {
        if( consolidated.empty() || consolidated.back().max + 1 < r.min )
            consolidated.push_back( r );
        else
            consolidated.back().max = std::max( r.max, consolidated.back().max );
    }

    for( auto const& r : ranges )
    {
        // std::cout << r.min << ", " << r.max << "\n";
    }

    std::int64_t sum{};
    for( auto const& r : consolidated )
    {
        // std::cout << r.min << ", " << r.max << "\n";
        sum += r.max + 1 - r.min;
    }

    return sum;
}

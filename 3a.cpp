#include "parse_input.h"

advent_t advent( std::vector< std::string > const& input )
{
    int sum{};
    for( auto line : input )
    {
        auto const midpoint{ line.size() / 2 };
        std::sort( line.begin(), line.begin() + midpoint );
        std::sort( line.begin() + midpoint, line.end() );
        std::string i;
        std::set_intersection( line.cbegin(), line.cbegin() + midpoint, line.cbegin() + midpoint, line.cend(), std::back_inserter( i ) );
        auto const common{ i.front() };
        if( 'a' <= common && common <= 'z' )
        {
            auto const score = 1 + ( common - 'a' );
            sum += score;
        }
        else
        {
            auto const score = 27 + ( common - 'A' );
            sum += score;
        }
    }

    return sum;
}

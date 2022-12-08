#include "parse_input.h"

advent_t advent( std::vector< std::string > const& input )
{
    std::vector< std::vector< int > > heights;

    for( auto const& l : input )
    {
        heights.push_back( {} );
        for( auto const& c : l )
        {
            heights.back().push_back( c - '0' );
        }
    }

    auto const is_visible{ [ & ]( auto const x, auto const y ) {
        std::vector< int > vertical;
        for( int y{}; y < heights.size(); ++y )
        {
            vertical.push_back( heights[ y ][ x ] );
        }

        auto const is_visible_1d{ []( auto const& values, auto const place ) {
            return place == 0 ||
                   place == values.size() - 1 ||
                   values[ place ] > *std::max_element( values.cbegin(), values.cbegin() + place ) ||
                   values[ place ] > *std::max_element( values.cbegin() + place + 1, values.cend() );
        } };

        return is_visible_1d( heights[ y ], x ) || is_visible_1d( vertical, y );
    } };

    int sum{};
    for( int y{}; y < heights.size(); ++y )
    {
        for( int x{}; x < heights[ y ].size(); ++x )
        {
            if( is_visible( x, y ) )
            {
                ++sum;
            }
        }
    }

    return sum;
}

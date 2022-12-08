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

    auto const get_score{ [ & ]( auto const x, auto const y ) {
        std::vector< int > vertical;
        for( int y{}; y < heights.size(); ++y )
        {
            vertical.push_back( heights[ y ][ x ] );
        }

        auto const score_1d{ []( auto const& values, auto const place ) {
            int l{ place - 1 };
            int r{ place + 1 };
            while( l > 0 && values[ l ] < values[ place ] )
            {
                --l;
            }
            while( r < values.size() - 1 && values[ r ] < values[ place ] )
            {
                ++r;
            }
            return ( place - l ) * ( r - place );
        } };

        return score_1d( heights[ y ], x ) * score_1d( vertical, y );
    } };

    int best{};
    for( int y{ 1 }; y < heights.size() - 1; ++y )
    {
        for( int x{ 1 }; x < heights[ y ].size() - 1; ++x )
        {
            if( auto const score = get_score( x, y ) )
            {
                best = std::max( score, best );
            }
        }
    }

    return best;
}

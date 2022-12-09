#include "parse_input.h"
#include <unordered_set>
#include <utility>

struct loc_t
{
    int first{};
    int second{};
};

advent_t advent( std::vector< std::string > const& input )
{
    loc_t head{ 0, 0 };
    loc_t tail{ 0, 0 };
    std::unordered_set< std::string > locs{ "0,0" };

    auto const r{ [ & ] {
        ++head.first;
        if( tail.first + 1 < head.first )
        {
            ++tail.first;
            tail.second = head.second;
        }
        locs.insert( std::to_string( tail.first ) + "," + std::to_string( tail.second ) );
    } };
    auto const l{ [ & ] {
        --head.first;
        if( head.first + 1 < tail.first )
        {
            --tail.first;
            tail.second = head.second;
        }
        locs.insert( std::to_string( tail.first ) + "," + std::to_string( tail.second ) );
    } };
    auto const u{ [ & ] {
        ++head.second;
        if( tail.second + 1 < head.second )
        {
            ++tail.second;
            tail.first = head.first;
        }
        locs.insert( std::to_string( tail.first ) + "," + std::to_string( tail.second ) );
    } };
    auto const d{ [ & ] {
        --head.second;
        if( head.second + 1 < tail.second )
        {
            --tail.second;
            tail.first = head.first;
        }
        locs.insert( std::to_string( tail.first ) + "," + std::to_string( tail.second ) );
    } };

    for( auto const& instruction : input )
    {
        switch( instruction.front() )
        {
        case 'U':
            for( int i = 0; i < std::stoi( instruction.substr( 2 ) ); ++i )
                u();
            break;
        case 'D':
            for( int i = 0; i < std::stoi( instruction.substr( 2 ) ); ++i )
                d();
            break;
        case 'L':
            for( int i = 0; i < std::stoi( instruction.substr( 2 ) ); ++i )
                l();
            break;
        case 'R':
            for( int i = 0; i < std::stoi( instruction.substr( 2 ) ); ++i )
                r();
            break;
        default:
            throw std::runtime_error( "Input parsing problem" );
        }
    }

    return static_cast< int >( locs.size() );
}

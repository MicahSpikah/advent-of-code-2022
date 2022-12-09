#include "parse_input.h"
#include <unordered_set>
#include <utility>

struct loc_t
{
    int x{};
    int y{};
};

advent_t advent( std::vector< std::string > const& input )
{
    std::vector< loc_t > knots( 10 );
    std::unordered_set< std::string > locs{ "0,0" };

    auto const dbg_out{ [ & ] {
        for( auto const& k : knots )
            std::cout << "(" << k.x << ", " << k.y << ") ";
        std::cout << '\n';
    } };

    auto const bump_knots{ [ & ] {
        for( auto k{ 1 }; k < knots.size(); ++k )
        {
            auto& head{ knots[ k - 1 ] };
            auto& tail{ knots[ k ] };

            if( tail.x + 1 < head.x )
            {
                ++tail.x;
                if( tail.y < head.y )
                    ++tail.y;
                else if( tail.y > head.y )
                    --tail.y;
            }
            else if( head.x + 1 < tail.x )
            {
                --tail.x;
                if( tail.y < head.y )
                    ++tail.y;
                else if( tail.y > head.y )
                    --tail.y;
            }
            else if( tail.y + 1 < head.y )
            {
                ++tail.y;
                if( tail.x < head.x )
                    ++tail.x;
                else if( tail.x > head.x )
                    --tail.x;
            }
            else if( head.y + 1 < tail.y )
            {
                --tail.y;
                if( tail.x < head.x )
                    ++tail.x;
                else if( tail.x > head.x )
                    --tail.x;
            }
        }

        locs.insert( std::to_string( knots.back().x ) + "," + std::to_string( knots.back().y ) );
    } };

    auto const r{ [ & ] {
        ++knots[ 0 ].x;
        bump_knots();
    } };
    auto const l{ [ & ] {
        --knots[ 0 ].x;
        bump_knots();
    } };
    auto const u{ [ & ] {
        ++knots[ 0 ].y;
        bump_knots();
    } };
    auto const d{ [ & ] {
        --knots[ 0 ].y;
        bump_knots();
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

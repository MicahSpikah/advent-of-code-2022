#include "parse_input.h"

advent_t advent( std::vector< std::string > const& input )
{
    std::vector< std::string > crt( 1 );
    int c{ 1 };
    int reg{ 1 };

    auto const fire_pixel{ [ & ] {
        if( c == reg || c == reg + 1 || c == reg + 2 )
            crt.back().push_back( '#' );
        else
            crt.back().push_back( '.' );
        if( c++ == 40 )
        {
            c -= 40;
            crt.push_back( {} );
        }
    } };
    for( auto const& instruction : input )
    {
        if( instruction == "noop" )
        {
            fire_pixel();
        }
        else
        {
            fire_pixel();
            fire_pixel();
            reg += std::stoi( instruction.substr( 5 ) );
        }
    }

    return crt;
}

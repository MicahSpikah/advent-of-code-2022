#include "parse_input.h"

advent_t advent( std::vector< std::string > const& input )
{
    int c{ 1 };
    int reg{ 1 };
    int sum{};

    auto const interesting_cycle{ []( auto const counter ) {
        return counter == 20 || counter == 60 || counter == 100 || counter == 140 || counter == 180 || counter == 220;
    } };

    for( auto const& instruction : input )
    {
        if( interesting_cycle( c ) )
        {
            sum += c * reg;
        }

        if( instruction == "noop" )
        {
            ++c;
        }
        else
        {
            if( interesting_cycle( c + 1 ) )
            {
                sum += ( c + 1 ) * reg;
            }
            c += 2;
            reg += std::stoi( instruction.substr( 5 ) );
        }
    }

    if( interesting_cycle( c ) )
    {
        sum += c * reg;
    }

    return sum;
}

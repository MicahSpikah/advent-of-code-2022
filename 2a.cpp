#include "parse_input.h"
#include <map>

advent_t advent( std::vector< std::string > const& input )
{
    std::map< std::string, int > const score{
        { "A X", 1 + 3 },
        { "A Y", 2 + 6 },
        { "A Z", 3 + 0 },
        { "B X", 1 + 0 },
        { "B Y", 2 + 3 },
        { "B Z", 3 + 6 },
        { "C X", 1 + 6 },
        { "C Y", 2 + 0 },
        { "C Z", 3 + 3 }
    };

    int sum{};
    for( auto const& line : input )
    {
        sum += score.at( line );
    }

    return sum;
}

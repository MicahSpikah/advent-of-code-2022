#include "parse_input.h"
#include <map>

int main( int const argc, char* const argv[] )
{
    auto const input{ parse_input( argc, argv ) };

    std::map< std::string, int > const score{
        { "A X", 3 + 0 },
        { "A Y", 1 + 3 },
        { "A Z", 2 + 6 },
        { "B X", 1 + 0 },
        { "B Y", 2 + 3 },
        { "B Z", 3 + 6 },
        { "C X", 2 + 0 },
        { "C Y", 3 + 3 },
        { "C Z", 1 + 6 }
    };

    int sum{};
    for( auto const& line : input )
    {
        sum += score.at( line );
    }

    std::cout << sum << '\n';
}

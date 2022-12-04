#include "parse_input.h"

int main( int const argc, char* const argv[] )
{
    auto const input{ parse_input( argc, argv ) };

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

    std::cout << sum << '\n';
}

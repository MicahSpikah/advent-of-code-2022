#include "parse_input.h"

int score( char const common )
{
    if( 'a' <= common && common <= 'z' )
    {
        return 1 + ( common - 'a' );
    }
    else
    {
        return 27 + ( common - 'A' );
    }
}

int main( int const argc, char* const argv[] )
{
    auto input{ parse_input( argc, argv ) };

    int sum{};

    for( std::size_t i{}; i < input.size(); i += 3 )
    {
        std::string first;
        std::string intersection;

        std::sort( input[ i ].begin(), input[ i ].end() );
        std::sort( input[ i + 1 ].begin(), input[ i + 1 ].end() );
        std::sort( input[ i + 2 ].begin(), input[ i + 2 ].end() );
        std::set_intersection( input[ i ].cbegin(), input[ i ].cend(), input[ i + 1 ].cbegin(), input[ i + 1 ].cend(), std::back_inserter( first ) );
        std::set_intersection( first.cbegin(), first.cend(), input[ i + 2 ].cbegin(), input[ i + 2 ].cend(), std::back_inserter( intersection ) );
        sum += score( intersection.front() );
    }

    std::cout << sum << '\n';
}

#include "parse_input.h"
#include <unordered_set>

static int constexpr header_size{ 4 };

int main( int const argc, char* const argv[] )
{
    auto const input{ parse_input( argc, argv ) };

    std::string const& buffer{ input.front() };

    for( int i{}; i + header_size - 1 < buffer.size(); ++i )
    {
        if( std::unordered_set< char >( buffer.cbegin() + i, buffer.cbegin() + i + header_size ).size() == header_size )
        {
            std::cout << ( i + header_size ) << '\n';
            std::exit( 0 );
        }
    }
    return 1;
}

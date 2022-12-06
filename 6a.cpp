#include "parse_input.h"
#include <unordered_set>

static int constexpr header_size{ 4 };

advent_t advent( std::vector< std::string > const& input )
{
    std::string const& buffer{ input.front() };

    for( int i{}; i + header_size - 1 < buffer.size(); ++i )
    {
        if( std::unordered_set< char >( buffer.cbegin() + i, buffer.cbegin() + i + header_size ).size() == header_size )
        {
            return i + header_size;
        }
    }
    throw std::runtime_error( "Header not found" );
}

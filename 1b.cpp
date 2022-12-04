#include "parse_input.h"
#include <numeric>

int main( int const argc, char* const argv[] )
{
    auto const input{ parse_input( argc, argv ) };
    int running_sum{};
    std::vector< int > total_calories_per_elf( 1 );

    for( auto const& l : input )
    {
        if( l.empty() )
        {
            total_calories_per_elf.push_back( 0 );
        }
        else
        {
            total_calories_per_elf.back() += std::stoi( l );
        }
    }
    std::nth_element( total_calories_per_elf.begin(), total_calories_per_elf.end() - 3, total_calories_per_elf.end() );

    for( auto const& tc : total_calories_per_elf )
    {
        std::cout << tc << '\n';
    }
    for( auto const& tc : total_calories_per_elf )
    {
        std::cout << tc << '\n';
    }

    std::cout << std::reduce( total_calories_per_elf.end() - 3, total_calories_per_elf.end() ) << '\n';
}

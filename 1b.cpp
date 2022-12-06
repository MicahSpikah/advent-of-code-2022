#include "parse_input.h"
#include <numeric>

advent_t advent( std::vector< std::string > const& input )
{
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

    return std::reduce( total_calories_per_elf.end() - 3, total_calories_per_elf.end() );
}

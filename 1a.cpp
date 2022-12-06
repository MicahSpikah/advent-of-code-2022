#include "parse_input.h"

advent_t advent( std::vector< std::string > const& input )
{
    int max{};
    int running_sum{};

    for( auto const& l : input )
    {
        if( l.empty() )
        {
            running_sum = 0;
        }
        else
        {
            running_sum += std::stoi( l );
            max = std::max( max, running_sum );
        }
    }

    return max;
}

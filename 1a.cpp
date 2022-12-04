#include "parse_input.h"

int main( int const argc, char* const argv[] )
{
    auto const input{ parse_input( argc, argv ) };
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

    std::cout << max << '\n';
}

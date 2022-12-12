#include "parse_input.h"

advent_t advent( std::vector< std::string > const& input )
{
    std::vector< std::vector< int > > shortest_path( input.size(), std::vector< int >( input.front().size(), -1 ) );
    bool closer_step_found{ true };

    for( int path_length{}; closer_step_found; ++path_length )
    {
        closer_step_found = false;
        for( int y{}; y < input.size(); ++y )
        {
            for( int x{}; x < input.front().size(); ++x )
            {
                auto const reachable_from{ [ & ]( auto const prev_x, auto const prev_y ) {
                    auto const prev_height{ input[ prev_y ][ prev_x ] == 'S' ? 'a' : input[ prev_y ][ prev_x ] };
                    auto const dest_height{ input[ y ][ x ] == 'E' ? 'z' : input[ y ][ x ] };

                    return prev_height + 1 >= dest_height;
                } };

                bool match{};

                if( path_length == 0 )
                {
                    if( input[ y ][ x ] == 'S' )
                    {
                        shortest_path[ y ][ x ] = 0;
                        closer_step_found       = true;
                    }
                }
                else if( x > 0 && shortest_path[ y ][ x - 1 ] == path_length - 1 && reachable_from( x - 1, y ) )
                {
                    match = true;
                }
                else if( x + 1 < input.front().size() && shortest_path[ y ][ x + 1 ] == path_length - 1 && reachable_from( x + 1, y ) )
                {
                    match = true;
                }
                else if( y > 0 && shortest_path[ y - 1 ][ x ] == path_length - 1 && reachable_from( x, y - 1 ) )
                {
                    match = true;
                }
                else if( y + 1 < input.size() && shortest_path[ y + 1 ][ x ] == path_length - 1 && reachable_from( x, y + 1 ) )
                {
                    match = true;
                }

                if( match )
                {
                    if( input[ y ][ x ] == 'E' )
                        return path_length;
                    shortest_path[ y ][ x ] = path_length;
                    closer_step_found       = true;
                }
            }
        }
    }

    throw std::runtime_error( "Couldn't complete path" );
}

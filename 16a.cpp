#include "parse_input.h"
#include <map>
#include <numeric>
#include <set>
#include <unordered_set>

struct valve
{
    std::vector< std::string > tunnels;
    int flow_rate;
    bool open{};
};

using valve_map     = std::map< std::string, valve >;
using rooms_visited = std::unordered_set< std::string >;

struct state
{
    valve_map valves;
    rooms_visited visited;
    int flow{};
    std::string location{ "AA" };
    int minutes_remaining{ 30 };
    std::vector< std::string > path;
    std::vector< int > untaken_paths;
};

int get_best_outcome( state the_state )
{
    if( the_state.minutes_remaining <= 1 || std::all_of( the_state.valves.cbegin(), the_state.valves.cend(), []( auto const& t ) { return t.second.open; } ) )
        return the_state.flow;

    int best_result = the_state.flow;

    if( the_state.untaken_paths.size() < 5 )
    {
        the_state.untaken_paths.push_back( 0 );
        if( !the_state.valves[ the_state.location ].open )
            ++the_state.untaken_paths.back();
        for( auto const& next_room : the_state.valves[ the_state.location ].tunnels )
            ++the_state.untaken_paths.back();
        for( auto const i : the_state.untaken_paths )
            std::cerr << i << ' ';
        std::cerr << '\n';
    }

    if( !the_state.valves[ the_state.location ].open )
    {
        state x = the_state;
        --x.minutes_remaining;
        x.valves[ x.location ].open = true;
        x.flow += x.minutes_remaining * x.valves[ x.location ].flow_rate;
        x.visited = std::unordered_set< std::string >{ x.location };

        best_result = get_best_outcome( std::move( x ) );
        if( the_state.untaken_paths.size() < 5 )
        {
            --the_state.untaken_paths.back();
            for( auto const i : the_state.untaken_paths )
                std::cerr << i << ' ';
            std::cerr << '\n';
        }
    }

    for( auto const& next_room : the_state.valves[ the_state.location ].tunnels )
    {
        if( !the_state.visited.contains( next_room ) )
        {
            state x = the_state;
            --x.minutes_remaining;
            x.location = next_room;
            for( auto const& not_here : the_state.valves[ the_state.location ].tunnels )
            {
                x.visited.emplace( not_here );
            }
            best_result = std::max( best_result, get_best_outcome( std::move( x ) ) );
            if( the_state.untaken_paths.size() < 5 )
            {
                --the_state.untaken_paths.back();
                for( auto const i : the_state.untaken_paths )
                    std::cerr << i << ' ';
                std::cerr << '\n';
            }
        }
    }

    return best_result;
}

advent_t advent( std::vector< std::string > const& input )
{
    state initial;

    for( auto line : input )
    {
        std::string name = line.substr( 6, 2 );
        valve v;
        v.flow_rate = std::atoi( line.substr( 23 ).c_str() );
        if( v.flow_rate == 0 )
            v.open = true;

        for( auto index = line.rfind( " " ); line[ index + 1 ] != 'v'; index = line.rfind( " " ) )
        {
            v.tunnels.push_back( line.substr( index + 1, 2 ) );
            line.resize( index );
        }

        initial.valves[ name ] = v;
    }

    return get_best_outcome( initial );
}

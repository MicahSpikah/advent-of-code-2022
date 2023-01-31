#include "parse_input.h"
#include <map>
#include <numeric>
#include <set>
#include <unordered_set>

std::map< std::string, int > flow_rate;

struct state
{
    std::map< std::string, std::map< std::string, int > > distance;
    int flow{};
    int minutes_remaining{ 30 };
    std::string loc{ "AA" };
};

int best_from( state s )
{
    int best = s.flow;

    for( auto const& next : s.distance.at( s.loc ) )
        if( next.second <= s.minutes_remaining )
        {
            state mod = s;
            mod.minutes_remaining -= next.second;
            mod.flow += mod.minutes_remaining * flow_rate.at( next.first );
            mod.distance.erase( mod.loc );
            for( auto& room : mod.distance )
                room.second.erase( mod.loc );
            mod.loc = next.first;
            best    = std::max( best_from( mod ), best );
        }

    return best;
}

advent_t advent( std::vector< std::string > const& input )
{
    std::map< std::string, std::unordered_set< std::string > > valves;

    for( auto line : input )
    {
        std::string name  = line.substr( 6, 2 );
        flow_rate[ name ] = std::atoi( line.substr( 23 ).c_str() );

        for( auto index = line.rfind( " " ); line[ index + 1 ] != 'v'; index = line.rfind( " " ) )
        {
            std::string dest_name = line.substr( index + 1, 2 );
            valves[ name ].insert( dest_name );
            line.resize( index );
        }
    }

    state initial;
    // For AA and each valve with positive flow, what's the distance to each other valve with positive flow?
    for( auto const& src : valves )
    {
        if( src.first == "AA" || flow_rate.at( src.first ) > 0 )
        {
            for( auto const& dst : valves )
            {
                if( dst.first != src.first && flow_rate.at( dst.first ) > 0 )
                {
                    std::unordered_set< std::string > reachable = { src.first };
                    int in                                      = 1;
                    while( !reachable.contains( dst.first ) )
                    {
                        ++in;
                        auto prev_reachable = reachable;
                        for( auto const& adj : prev_reachable )
                        {
                            reachable.insert( valves.at( adj ).cbegin(), valves.at( adj ).cend() );
                        }
                    }
                    initial.distance[ src.first ][ dst.first ] = in;
                }
            }
        }
    }

    return best_from( initial );
}

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
    int t1{ 26 };
    int t2{ 26 };
    std::string l1{ "AA" };
    std::string l2{ "AA" };
};

int best_from( state s )
{
    int best = s.flow;

    for( auto const& next : s.distance.at( s.l2 ) )
    {
        if( next.second <= s.t2 )
        {
            state mod = s;
            mod.t2 -= next.second;
            mod.flow += mod.t2 * flow_rate.at( next.first );
            mod.l2 = next.first;
            for( auto& room : mod.distance )
                room.second.erase( mod.l2 );
            best = std::max( best, best_from( mod ) );
        }
    }
    if( best != s.flow )
    {
        auto mod = s;
        mod.t2   = 0;
        best     = std::max( best, best_from( mod ) );
    }
    else
    {
        for( auto const& next : s.distance.at( s.l1 ) )
        {
            if( next.second <= s.t1 )
            {
                state mod = s;
                mod.t1 -= next.second;
                mod.flow += mod.t1 * flow_rate.at( next.first );
                mod.l1 = next.first;
                for( auto& room : mod.distance )
                    room.second.erase( mod.l1 );
                best = std::max( best, best_from( mod ) );
            }
        }
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

    int best{};
    int loops{};

    //Without loss of generality, pick the first two destinations. l1 always goes to the first room lexigraphically
    for( auto const& d1 : initial.distance.at( "AA" ) )
        for( auto const& d2 : initial.distance.at( "AA" ) )
            if( d1.first < d2.first )
            {
                std::cerr << (++loops) << "/210\n";
                state mod = initial;
                mod.t1 -= d1.second;
                mod.flow += mod.t1 * flow_rate.at( d1.first );
                mod.l1 = d1.first;
                mod.t2 -= d2.second;
                mod.flow += mod.t2 * flow_rate.at( d2.first );
                mod.l2 = d2.first;
                for( auto& room : mod.distance )
                {
                    room.second.erase( mod.l1 );
                    room.second.erase( mod.l2 );
                }
                best = std::max( best, best_from( mod ) );
            }

    return best;
}

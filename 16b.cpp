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
    int best         = s.flow;
    state best_state = s;

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

    return best_from( initial );
    /*
        while( true )
    {
        auto out = best_from( initial );
        if( out.second.t1 == initial.t1 && out.second.t2 == initial.t2 )
        {
            return out.first;
        }
        else if(out.second.t1 == initial.t1)
        {
            std::cerr << "Minute " << ( 27 - out.second.t2) << ": ELEPHANT Move to " << out.second.l2<< " and open, flow at " << out.second.flow << "\n";
            initial = out.second;
        }
        else
        {
            std::cerr << "Minute " << ( 27 - out.second.t1) << ": Move to " << out.second.l1<< " and open, flow at " << out.second.flow << "\n";
            initial = out.second;
        }
        std::cerr << "Places you can get from AA:";
        for(auto const dst : out.second.distance.at("AA"))
            std::cerr << ' ' << dst.first;
        std::cerr << '\n';
    }
    */
}

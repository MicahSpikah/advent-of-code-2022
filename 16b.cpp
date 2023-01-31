#include "parse_input.h"
#include <map>
#include <numeric>
#include <set>
#include <unordered_set>

struct valve
{
    std::vector< int > tunnels;
    int flow_rate;
    bool open{};
};

struct state
{
    std::vector< state* > old_states;
    std::vector< valve > valves;
    int flow{};
    int l1{};
    int l2{};
    int minutes_remaining{ 26 };
    std::vector< int > possibilities;
};

using option = std::variant< bool, int >;

int get_best_outcome( state the_state )
{
    if( the_state.minutes_remaining <= 1 || std::all_of( the_state.valves.cbegin(), the_state.valves.cend(), []( auto const& t ) { return t.open; } ) || std::any_of( the_state.old_states.cbegin(), the_state.old_states.cend(), [ & ]( auto const prev_state ) { return ( prev_state->l1 == the_state.l1 && prev_state->l2 == the_state.l2 ) || ( prev_state->l1 == the_state.l2 && prev_state->l2 == the_state.l1 ); } ) )
    {
        return the_state.flow;
    }

    for( auto const p : the_state.possibilities )
        std::cerr << p << ' ';
    std::cerr << '\n';

    the_state.old_states.push_back( &the_state );

    int best_result = the_state.flow;

    std::vector< std::pair< option, option > > options;

    std::vector< option > o1, o2;

    if( !the_state.valves.at( the_state.l1 ).open )
    {
        o1.push_back( true );
    }
    for( auto const& loc : the_state.valves.at( the_state.l1 ).tunnels )
    {
        o1.push_back( loc );
    }
    if( the_state.l1 != the_state.l2 )
    {
        if( !the_state.valves.at( the_state.l2 ).open )
        {
            o2.push_back( true );
        }
        for( auto const& loc : the_state.valves.at( the_state.l2 ).tunnels )
        {
            o2.push_back( loc );
        }
        for( auto const& opt1 : o1 )
            for( auto const& opt2 : o2 )
                options.emplace_back( opt1, opt2 );
    }
    else
    {
        for( int opt1_i = 0; opt1_i < o1.size(); ++opt1_i )
            for( int opt2_i = ( std::holds_alternative< bool >( o1.at( opt1_i ) ) ? opt1_i + 1 : opt1_i ); opt2_i < o1.size(); ++opt2_i )
                options.emplace_back( o1.at( opt1_i ), o1.at( opt2_i ) );
    }

    the_state.possibilities.push_back( options.size() );

    --the_state.minutes_remaining;
    for( auto const o : options )
    {
        auto x = the_state;
        if( std::holds_alternative< bool >( o.first ) )
        {
            x.old_states.clear();
            x.valves.at( x.l1 ).open = true;
            x.flow += x.minutes_remaining * x.valves.at( x.l1 ).flow_rate;
        }
        else
        {
            x.l1 = std::get< int >( o.first );
        }
        if( std::holds_alternative< bool >( o.second ) )
        {
            x.old_states.clear();
            x.valves.at( x.l2 ).open = true;
            x.flow += x.minutes_remaining * x.valves.at( x.l2 ).flow_rate;
        }
        else
        {
            x.l2 = std::get< int >( o.second );
        }
        best_result = get_best_outcome( std::move( x ) );
        --the_state.possibilities.back();
    }

    return best_result;
}

advent_t advent( std::vector< std::string > const& input )
{
    std::map< std::string, int > valve_lookup;
    valve_lookup[ "AA" ] = 0;

    state initial;
    initial.valves.resize( 1 );

    for( auto line : input )
    {
        int i;
        {
            std::string name = line.substr( 6, 2 );
            if( !valve_lookup.contains( name ) )
            {
                i                    = initial.valves.size();
                valve_lookup[ name ] = i;
                initial.valves.resize( i + 1 );
            }
            else
            {
                i = valve_lookup.at( name );
            }
        }
        valve v;
        v.flow_rate = std::atoi( line.substr( 23 ).c_str() );
        if( v.flow_rate == 0 )
            v.open = true;

        for( auto index = line.rfind( " " ); line[ index + 1 ] != 'v'; index = line.rfind( " " ) )
        {
            std::string name = line.substr( index + 1, 2 );
            int d;

            if( !valve_lookup.contains( name ) )
            {
                valve_lookup[ name ] = initial.valves.size();
                initial.valves.resize( initial.valves.size() + 1 );
            }

            v.tunnels.push_back( valve_lookup.at( name ) );
            line.resize( index );
        }

        initial.valves.at( i ) = v;
    }

    return get_best_outcome( initial );
}

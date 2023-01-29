#include "parse_input.h"
#include <unordered_set>
#include <map>
#include <numeric>
#include <set>

struct valve
{
    std::vector< std::string > tunnels;
    int flow_rate;
    bool open{};
};

using valve_map=   std::map< std::string, valve > ;
using rooms_visited=   std::unordered_set< std::string > ;

struct state
{
    valve_map valves;
    rooms_visited visited;
    int flow{};
    std::string location{"AA"};
    int minutes_remaining{30};
};

int get_best_outcome(state the_state)
{
    std::cerr << "TR: " << the_state.minutes_remaining << " in room " << the_state.location << " with flow " << the_state.flow << '\n';
    if(the_state.minutes_remaining <= 1) return the_state.flow;

    the_state.visited.emplace(the_state.location);

    int best_result = the_state.flow;

    if( !the_state.valves[the_state.location].open )
    {
        state x = the_state;
        --x.minutes_remaining;
        x.valves[x.location].open = true;
        x.flow += x.minutes_remaining * x.valves[x.location].flow_rate;
        x.visited.clear(); 

        best_result = get_best_outcome(std::move(x));
    }

    for(auto const& next_room : the_state.valves[the_state.location].tunnels)
    {
        if(!the_state.visited.contains(next_room))
        {
            state x = the_state;
            --x.minutes_remaining;
            x.location = next_room;
            best_result = std::max(best_result, get_best_outcome(std::move(x)));
        }
    }

    return best_result;
}

advent_t advent( std::vector< std::string > const& input )
{
    state initial;

    for(auto line : input )
    {
        std::cerr << "parsing " << line << '\n';
        std::string name = line.substr(6,2);
        valve v;
        v.flow_rate = std::atoi(line.substr(23).c_str()); 
        if(v.flow_rate==0) v.open = true;
        
        for(auto index = line.rfind(" ");line[index+1] != 'v'; index = line.rfind(" "))
        {
            v.tunnels.push_back(line.substr(index+1, 2));
            line.resize(index);
        }

        std::cerr << "  Valve " << name << " flow " << v.flow_rate << " with connections to "; 
        for(auto const c : v.tunnels) std::cerr << c << ' ';
        std::cerr << '\n';

        initial.valves[name] = v;
    }

    return get_best_outcome(initial);
}

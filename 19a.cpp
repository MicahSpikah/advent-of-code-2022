#include "parse_input.h"

int constexpr max_time{ 15 };

struct state
{
    int blueprint;
    int ore_cost;
    int clay_cost;
    int obsidian_ore_cost;
    int obsidian_clay_cost;
    int geode_ore_cost;
    int geode_obsidian_cost;

    int ore_robots{ 1 };
    int clay_robots{};
    int obsidian_robots{};
    int ore{};
    int clay{};
    int obsidian{};
    int geode{};

    int constructing_ore_robots{};
    int constructing_clay_robots{};
    int constructing_obsidian_robots{};

    int time{};
    std::string history{};

    bool afford_ore_robot() const
    {
        return ore >= ore_cost;
    }

    bool afford_clay_robot() const
    {
        return ore >= clay_cost;
    }

    bool afford_obsidian_robot() const
    {
        return ore >= obsidian_ore_cost && clay >= obsidian_clay_cost;
    }

    bool afford_geode_robot() const
    {
        return ore >= geode_ore_cost && obsidian >= geode_obsidian_cost;
    }

    void construct_ore_robot()
    {
        history += "o";
        ++constructing_ore_robots;
        ore -= ore_cost;
    }

    void construct_clay_robot()
    {
        history += "c";
        ++constructing_clay_robots;
        ore -= clay_cost;
    }

    void construct_obsidian_robot()
    {
        history += "O";
        ++constructing_obsidian_robots;
        ore -= obsidian_ore_cost;
        clay -= obsidian_clay_cost;
    }

    void construct_geode_robot()
    {
        history += "G";
        ore -= geode_ore_cost;
        obsidian -= geode_obsidian_cost;
        geode += (max_time - 1);
    }

    void tick()
    {
        ++time;
        ore += ore_robots;
        clay += clay_robots;
        obsidian += obsidian_robots;
        ore_robots += constructing_ore_robots;
        clay_robots += constructing_clay_robots;
        obsidian_robots += constructing_obsidian_robots;
        constructing_ore_robots      = 0;
        constructing_clay_robots     = 0;
        constructing_obsidian_robots = 0;
    }
};

int get_best_state( state const s )
{
    int geodes = s.geode;
    if( s.time == max_time )
    {
        std::cout << s.history << " = " << geodes << '\n';
        return geodes;
    }

    {
        auto t = s;
        while( !t.afford_ore_robot() && t.time < max_time )
        {
            t.tick();
        }
        t.construct_ore_robot();
        geodes = std::max( geodes, get_best_state( t ) );
    }
    {
        auto t = s;
        while( !t.afford_clay_robot() && t.time < max_time )
        {
            t.tick();
        }
        t.construct_clay_robot();
        geodes = std::max( geodes, get_best_state( t ) );
    }
    if( s.clay_robots > 0 )
    {
        auto t = s;
        while( !t.afford_obsidian_robot() && t.time < max_time )
        {
            t.tick();
        }
        t.construct_obsidian_robot();
        geodes = std::max( geodes, get_best_state( t ) );
    }
    if( s.obsidian_robots > 0 )
    {
        auto t = s;
        while( !t.afford_geode_robot() && t.time < max_time )
        {
            t.tick();
        }
        t.construct_geode_robot();
        geodes = std::max( geodes, get_best_state( t ) );
    }

    return geodes;
}

advent_t advent( std::vector< std::string > const& input )
{
    int quality_sum{};

    for( auto const& line : input )
    {
        state s;
        std::sscanf( line.c_str(), "Blueprint %d: Each ore robot costs %d ore. Each clay robot costs %d ore. Each obsidian robot costs %d ore and %d clay. Each geode robot costs %d ore and %d obsidian.", &s.blueprint, &s.ore_cost, &s.clay_cost, &s.obsidian_ore_cost, &s.obsidian_clay_cost, &s.geode_ore_cost, &s.geode_obsidian_cost );

        quality_sum += get_best_state( s ) * s.blueprint;
    }

    return quality_sum;
}

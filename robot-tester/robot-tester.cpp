#include "robot-tester.h"

#include <QObject>

RobotTester::RobotTester( QWidget* parent ) :
    QMainWindow( parent )
{
    ui_.setupUi( this );

    connect( ui_.buy_ore_, &QAbstractButton::clicked, this, &RobotTester::buy_ore_robot );
    connect( ui_.buy_clay_, &QAbstractButton::clicked, this, &RobotTester::buy_clay_robot );
    connect( ui_.buy_obsidian_, &QAbstractButton::clicked, this, &RobotTester::buy_obsidian_robot );
    connect( ui_.buy_geode_, &QAbstractButton::clicked, this, &RobotTester::buy_geode_robot );
    connect( ui_.advance_, &QAbstractButton::clicked, this, &RobotTester::advance );
    connect( ui_.reset_, &QAbstractButton::clicked, this, &RobotTester::reset );

    reset();
}

void RobotTester::advance()
{
    ore_ += ore_robots_;
    clay_ += clay_robots_;
    obsidian_ += obsidian_robots_;
    geode_ += geode_robots_;

    ore_robots_ += ore_robots_under_construction_;
    clay_robots_ += clay_robots_under_construction_;
    obsidian_robots_ += obsidian_robots_under_construction_;
    geode_robots_ += geode_robots_under_construction_;

    ore_robots_under_construction_      = 0;
    clay_robots_under_construction_     = 0;
    obsidian_robots_under_construction_ = 0;
    geode_robots_under_construction_    = 0;

    ++time_;
    high_score_ = std::max( geode_, high_score_ );
    update_ui();
}

void RobotTester::buy_ore_robot()
{
    ore_ -= ore_robot_cost_ore_;
    ++ore_robots_under_construction_;
    update_ui();
}

void RobotTester::buy_clay_robot()
{
    ore_ -= clay_robot_cost_ore_;
    ++clay_robots_under_construction_;
    update_ui();
}

void RobotTester::buy_obsidian_robot()
{
    ore_ -= obsidian_robot_cost_ore_;
    clay_ -= obsidian_robot_cost_clay_;
    ++obsidian_robots_under_construction_;
    update_ui();
}

void RobotTester::buy_geode_robot()
{
    ore_ -= geode_robot_cost_ore_;
    obsidian_ -= geode_robot_cost_obsidian_;
    ++geode_robots_under_construction_;
    update_ui();
}

void RobotTester::reset()
{
    ore_robots_                         = 1;
    clay_robots_                        = 0;
    obsidian_robots_                    = 0;
    geode_robots_                       = 0;
    ore_robots_under_construction_      = 0;
    clay_robots_under_construction_     = 0;
    obsidian_robots_under_construction_ = 0;
    geode_robots_under_construction_    = 0;
    ore_                                = 0;
    clay_                               = 0;
    obsidian_                           = 0;
    geode_                              = 0;
    time_                               = 0;

    update_ui();
}

void RobotTester::update_ui()
{
    ui_.buy_ore_->setEnabled( ore_ >= ore_robot_cost_ore_ );
    ui_.buy_clay_->setEnabled( ore_ >= clay_robot_cost_ore_ );
    ui_.buy_obsidian_->setEnabled( ore_ >= obsidian_robot_cost_ore_ && clay_ >= obsidian_robot_cost_clay_ );
    ui_.buy_geode_->setEnabled( ore_ >= geode_robot_cost_ore_ && obsidian_ >= geode_robot_cost_obsidian_ );

    ui_.advance_->setEnabled( time_ < 24 );

    ui_.buy_ore_->setText( "Buy Ore Collector (" + QString::number( ore_robot_cost_ore_ ) + " ore)" );
    ui_.buy_clay_->setText( "Buy Clay Collector (" + QString::number( clay_robot_cost_ore_ ) + " ore)" );
    ui_.buy_obsidian_->setText( "Buy Obsidian Collector (" + QString::number( obsidian_robot_cost_ore_ ) + " ore " + QString::number( obsidian_robot_cost_clay_ ) + " clay)" );
    ui_.buy_geode_->setText( "Buy Geode Collector (" + QString::number( geode_robot_cost_ore_ ) + " ore " + QString::number( geode_robot_cost_obsidian_ ) + " obsidian)" );

    ui_.ore_robots_->setText( "Ore robots: " + QString::number( ore_robots_ ) );
    ui_.clay_robots_->setText( "Clay robots: " + QString::number( clay_robots_ ) );
    ui_.obsidian_robots_->setText( "Obsidian robots: " + QString::number( obsidian_robots_ ) );
    ui_.geode_robots_->setText( "Geode robots: " + QString::number( geode_robots_ ) );

    ui_.ore_->setText( "Ore: " + QString::number( ore_ ) );
    ui_.clay_->setText( "Clay: " + QString::number( clay_ ) );
    ui_.obsidian_->setText( "Obsidian: " + QString::number( obsidian_ ) );
    ui_.geodes_->setText( "Geode: " + QString::number( geode_ ) );

    ui_.day_->setText( "Time: " + QString::number( time_ ) );
}

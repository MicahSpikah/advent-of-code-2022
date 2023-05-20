#pragma once

#include "ui_robot-tester.h"

class RobotTester : public QMainWindow
{
    Q_OBJECT

public:
    explicit RobotTester( QWidget* parent = nullptr );

    void advance();
    void buy_ore_robot();
    void buy_clay_robot();
    void buy_obsidian_robot();
    void buy_geode_robot();

private:
    Ui::MainWindow ui_;

    int ore_robots_{ 1 };
    int clay_robots_{};
    int obsidian_robots_{};
    int geode_robots_{};
    int ore_robots_under_construction_{};
    int clay_robots_under_construction_{};
    int obsidian_robots_under_construction_{};
    int geode_robots_under_construction_{};
    int ore_{};
    int clay_{};
    int obsidian_{};
    int geode_{};
    int ore_robot_cost_ore_{ 4 };
    int clay_robot_cost_ore_{ 2 };
    int obsidian_robot_cost_ore_{ 3 };
    int obsidian_robot_cost_clay_{ 14 };
    int geode_robot_cost_ore_{ 2 };
    int geode_robot_cost_obsidian_{ 7 };
    int time_{};
    int high_score_{};

    void reset();
    void update_ui();
};

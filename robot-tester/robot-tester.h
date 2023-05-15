#pragma once

#include "ui_robot-tester.h"

class RobotTester : public QMainWindow
{
    Q_OBJECT

    public:
        explicit RobotTester(QWidget *parent = nullptr);
    private:
        Ui::MainWindow ui;
};

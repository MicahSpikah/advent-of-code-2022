#include "robot-tester.h"

#include <QLabel>
#include <QApplication>

int main(int  argc, char*  argv[])
{
    QApplication app(argc, argv);

    RobotTester rt;
    rt.show();
    app.exec();
}

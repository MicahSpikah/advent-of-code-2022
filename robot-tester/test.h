/********************************************************************************
** Form generated from reading UI file 'robot-tester.ui'
**
** Created by: Qt User Interface Compiler version 6.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef TEST_H
#define TEST_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QLabel *day_;
    QPushButton *reset_;
    QPushButton *buy_ore_;
    QLabel *ore_robots_;
    QPushButton *undo_;
    QPushButton *buy_geode_;
    QLabel *obsidian_robots_;
    QPushButton *buy_clay_;
    QLabel *geode_robots_;
    QPushButton *buy_obsidian;
    QPushButton *advance_;
    QLabel *clay_robots_;
    QLabel *ore_;
    QLabel *clay_;
    QLabel *obsidian_;
    QLabel *geodes_;
    QPushButton *view_history_;
    QLabel *high_score_;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(643, 437);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout_2 = new QGridLayout(centralwidget);
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        day_ = new QLabel(centralwidget);
        day_->setObjectName("day_");

        gridLayout->addWidget(day_, 4, 1, 1, 1);

        reset_ = new QPushButton(centralwidget);
        reset_->setObjectName("reset_");

        gridLayout->addWidget(reset_, 6, 0, 1, 1);

        buy_ore_ = new QPushButton(centralwidget);
        buy_ore_->setObjectName("buy_ore_");

        gridLayout->addWidget(buy_ore_, 0, 0, 1, 1);

        ore_robots_ = new QLabel(centralwidget);
        ore_robots_->setObjectName("ore_robots_");

        gridLayout->addWidget(ore_robots_, 0, 1, 1, 1);

        undo_ = new QPushButton(centralwidget);
        undo_->setObjectName("undo_");

        gridLayout->addWidget(undo_, 5, 0, 1, 1);

        buy_geode_ = new QPushButton(centralwidget);
        buy_geode_->setObjectName("buy_geode_");

        gridLayout->addWidget(buy_geode_, 3, 0, 1, 1);

        obsidian_robots_ = new QLabel(centralwidget);
        obsidian_robots_->setObjectName("obsidian_robots_");

        gridLayout->addWidget(obsidian_robots_, 2, 1, 1, 1);

        buy_clay_ = new QPushButton(centralwidget);
        buy_clay_->setObjectName("buy_clay_");

        gridLayout->addWidget(buy_clay_, 1, 0, 1, 1);

        geode_robots_ = new QLabel(centralwidget);
        geode_robots_->setObjectName("geode_robots_");

        gridLayout->addWidget(geode_robots_, 3, 1, 1, 1);

        buy_obsidian = new QPushButton(centralwidget);
        buy_obsidian->setObjectName("buy_obsidian");

        gridLayout->addWidget(buy_obsidian, 2, 0, 1, 1);

        advance_ = new QPushButton(centralwidget);
        advance_->setObjectName("advance_");

        gridLayout->addWidget(advance_, 4, 0, 1, 1);

        clay_robots_ = new QLabel(centralwidget);
        clay_robots_->setObjectName("clay_robots_");

        gridLayout->addWidget(clay_robots_, 1, 1, 1, 1);

        ore_ = new QLabel(centralwidget);
        ore_->setObjectName("ore_");

        gridLayout->addWidget(ore_, 0, 2, 1, 1);

        clay_ = new QLabel(centralwidget);
        clay_->setObjectName("clay_");

        gridLayout->addWidget(clay_, 1, 2, 1, 1);

        obsidian_ = new QLabel(centralwidget);
        obsidian_->setObjectName("obsidian_");

        gridLayout->addWidget(obsidian_, 2, 2, 1, 1);

        geodes_ = new QLabel(centralwidget);
        geodes_->setObjectName("geodes_");

        gridLayout->addWidget(geodes_, 3, 2, 1, 1);

        view_history_ = new QPushButton(centralwidget);
        view_history_->setObjectName("view_history_");

        gridLayout->addWidget(view_history_, 4, 2, 1, 1);

        high_score_ = new QLabel(centralwidget);
        high_score_->setObjectName("high_score_");

        gridLayout->addWidget(high_score_, 6, 2, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 1, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 643, 37));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Robot Tester", nullptr));
        day_->setText(QCoreApplication::translate("MainWindow", "Day:", nullptr));
        reset_->setText(QCoreApplication::translate("MainWindow", "Reset", nullptr));
        buy_ore_->setText(QCoreApplication::translate("MainWindow", "Buy Ore Collector", nullptr));
        ore_robots_->setText(QCoreApplication::translate("MainWindow", "Ore Collectors:", nullptr));
        undo_->setText(QCoreApplication::translate("MainWindow", "Undo", nullptr));
        buy_geode_->setText(QCoreApplication::translate("MainWindow", "Buy Geode collector", nullptr));
        obsidian_robots_->setText(QCoreApplication::translate("MainWindow", "Obsidian Collectors:", nullptr));
        buy_clay_->setText(QCoreApplication::translate("MainWindow", "Buy Clay Collector", nullptr));
        geode_robots_->setText(QCoreApplication::translate("MainWindow", "Geode Collectors:", nullptr));
        buy_obsidian->setText(QCoreApplication::translate("MainWindow", "Buy Obsidian collector", nullptr));
        advance_->setText(QCoreApplication::translate("MainWindow", "Advance", nullptr));
        clay_robots_->setText(QCoreApplication::translate("MainWindow", "Clay Collectors:", nullptr));
        ore_->setText(QCoreApplication::translate("MainWindow", "Ore:", nullptr));
        clay_->setText(QCoreApplication::translate("MainWindow", "Clay:", nullptr));
        obsidian_->setText(QCoreApplication::translate("MainWindow", "Obsidian:", nullptr));
        geodes_->setText(QCoreApplication::translate("MainWindow", "Geodes:", nullptr));
        view_history_->setText(QCoreApplication::translate("MainWindow", "View History", nullptr));
        high_score_->setText(QCoreApplication::translate("MainWindow", "High Score:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // TEST_H

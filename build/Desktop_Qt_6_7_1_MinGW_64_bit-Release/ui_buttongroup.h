/********************************************************************************
** Form generated from reading UI file 'buttongroup.ui'
**
** Created by: Qt User Interface Compiler version 6.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BUTTONGROUP_H
#define UI_BUTTONGROUP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QWidget>
#include "mybutton.h"

QT_BEGIN_NAMESPACE

class Ui_ButtonGroup
{
public:
    QHBoxLayout *horizontalLayout;
    QStackedWidget *stackedWidget;
    QWidget *startPage;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    MyButton *start;
    QSpacerItem *horizontalSpacer_2;
    QWidget *playCardPage;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_3;
    MyButton *playCard_1;
    QSpacerItem *horizontalSpacer_4;
    QWidget *passOrPlayPage;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_5;
    MyButton *pass;
    QSpacerItem *horizontalSpacer_6;
    MyButton *playCard_2;
    QSpacerItem *horizontalSpacer_7;
    QWidget *callLordPage;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_8;
    MyButton *giveUp;
    QSpacerItem *horizontalSpacer_10;
    MyButton *oneScore;
    QSpacerItem *horizontalSpacer_11;
    MyButton *twoScore;
    QSpacerItem *horizontalSpacer_12;
    MyButton *threeScore;
    QSpacerItem *horizontalSpacer_9;
    QWidget *nullPage;

    void setupUi(QWidget *ButtonGroup)
    {
        if (ButtonGroup->objectName().isEmpty())
            ButtonGroup->setObjectName("ButtonGroup");
        ButtonGroup->resize(470, 121);
        horizontalLayout = new QHBoxLayout(ButtonGroup);
        horizontalLayout->setObjectName("horizontalLayout");
        stackedWidget = new QStackedWidget(ButtonGroup);
        stackedWidget->setObjectName("stackedWidget");
        startPage = new QWidget();
        startPage->setObjectName("startPage");
        horizontalLayout_2 = new QHBoxLayout(startPage);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalSpacer = new QSpacerItem(173, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        start = new MyButton(startPage);
        start->setObjectName("start");

        horizontalLayout_2->addWidget(start);

        horizontalSpacer_2 = new QSpacerItem(173, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        stackedWidget->addWidget(startPage);
        playCardPage = new QWidget();
        playCardPage->setObjectName("playCardPage");
        horizontalLayout_3 = new QHBoxLayout(playCardPage);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalSpacer_3 = new QSpacerItem(173, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        playCard_1 = new MyButton(playCardPage);
        playCard_1->setObjectName("playCard_1");

        horizontalLayout_3->addWidget(playCard_1);

        horizontalSpacer_4 = new QSpacerItem(173, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_4);

        stackedWidget->addWidget(playCardPage);
        passOrPlayPage = new QWidget();
        passOrPlayPage->setObjectName("passOrPlayPage");
        horizontalLayout_4 = new QHBoxLayout(passOrPlayPage);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalSpacer_5 = new QSpacerItem(119, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_5);

        pass = new MyButton(passOrPlayPage);
        pass->setObjectName("pass");

        horizontalLayout_4->addWidget(pass);

        horizontalSpacer_6 = new QSpacerItem(15, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_6);

        playCard_2 = new MyButton(passOrPlayPage);
        playCard_2->setObjectName("playCard_2");

        horizontalLayout_4->addWidget(playCard_2);

        horizontalSpacer_7 = new QSpacerItem(119, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_7);

        stackedWidget->addWidget(passOrPlayPage);
        callLordPage = new QWidget();
        callLordPage->setObjectName("callLordPage");
        horizontalLayout_5 = new QHBoxLayout(callLordPage);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_8);

        giveUp = new MyButton(callLordPage);
        giveUp->setObjectName("giveUp");

        horizontalLayout_5->addWidget(giveUp);

        horizontalSpacer_10 = new QSpacerItem(10, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_10);

        oneScore = new MyButton(callLordPage);
        oneScore->setObjectName("oneScore");

        horizontalLayout_5->addWidget(oneScore);

        horizontalSpacer_11 = new QSpacerItem(10, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_11);

        twoScore = new MyButton(callLordPage);
        twoScore->setObjectName("twoScore");

        horizontalLayout_5->addWidget(twoScore);

        horizontalSpacer_12 = new QSpacerItem(10, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_12);

        threeScore = new MyButton(callLordPage);
        threeScore->setObjectName("threeScore");

        horizontalLayout_5->addWidget(threeScore);

        horizontalSpacer_9 = new QSpacerItem(25, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_9);

        stackedWidget->addWidget(callLordPage);
        nullPage = new QWidget();
        nullPage->setObjectName("nullPage");
        stackedWidget->addWidget(nullPage);

        horizontalLayout->addWidget(stackedWidget);


        retranslateUi(ButtonGroup);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(ButtonGroup);
    } // setupUi

    void retranslateUi(QWidget *ButtonGroup)
    {
        ButtonGroup->setWindowTitle(QCoreApplication::translate("ButtonGroup", "Form", nullptr));
        start->setText(QCoreApplication::translate("ButtonGroup", "PushButton", nullptr));
        playCard_1->setText(QCoreApplication::translate("ButtonGroup", "PushButton", nullptr));
        pass->setText(QCoreApplication::translate("ButtonGroup", "PushButton", nullptr));
        playCard_2->setText(QCoreApplication::translate("ButtonGroup", "PushButton", nullptr));
        giveUp->setText(QCoreApplication::translate("ButtonGroup", "PushButton", nullptr));
        oneScore->setText(QCoreApplication::translate("ButtonGroup", "PushButton", nullptr));
        twoScore->setText(QCoreApplication::translate("ButtonGroup", "PushButton", nullptr));
        threeScore->setText(QCoreApplication::translate("ButtonGroup", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ButtonGroup: public Ui_ButtonGroup {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BUTTONGROUP_H

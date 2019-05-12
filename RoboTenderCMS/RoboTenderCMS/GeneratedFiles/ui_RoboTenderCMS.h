/********************************************************************************
** Form generated from reading UI file 'RoboTenderCMS.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ROBOTENDERCMS_H
#define UI_ROBOTENDERCMS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RoboTenderCMSClass
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QTableWidget *tableWidget;
    QHBoxLayout *horizontalLayout_1;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnSimulation;
    QPushButton *btnTopView;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *btnAddPoint;
    QPushButton *btnRemovePoint;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *btnLoadPoint;
    QPushButton *btnSavePoint;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;

    void setupUi(QMainWindow *RoboTenderCMSClass)
    {
        if (RoboTenderCMSClass->objectName().isEmpty())
            RoboTenderCMSClass->setObjectName(QStringLiteral("RoboTenderCMSClass"));
        RoboTenderCMSClass->resize(1162, 881);
        centralWidget = new QWidget(RoboTenderCMSClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        centralWidget->setMaximumSize(QSize(16777215, 16777215));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetMaximumSize);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetMaximumSize);
        tableWidget = new QTableWidget(centralWidget);
        if (tableWidget->columnCount() < 5)
            tableWidget->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        sizePolicy.setHeightForWidth(tableWidget->sizePolicy().hasHeightForWidth());
        tableWidget->setSizePolicy(sizePolicy);
        tableWidget->setMaximumSize(QSize(400, 16777215));

        horizontalLayout->addWidget(tableWidget);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_1 = new QHBoxLayout();
        horizontalLayout_1->setSpacing(6);
        horizontalLayout_1->setObjectName(QStringLiteral("horizontalLayout_1"));
        horizontalLayout_1->setSizeConstraint(QLayout::SetMaximumSize);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_1->addItem(horizontalSpacer);

        btnSimulation = new QPushButton(centralWidget);
        btnSimulation->setObjectName(QStringLiteral("btnSimulation"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(btnSimulation->sizePolicy().hasHeightForWidth());
        btnSimulation->setSizePolicy(sizePolicy1);

        horizontalLayout_1->addWidget(btnSimulation);

        btnTopView = new QPushButton(centralWidget);
        btnTopView->setObjectName(QStringLiteral("btnTopView"));

        horizontalLayout_1->addWidget(btnTopView);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_1->addItem(horizontalSpacer_2);

        btnAddPoint = new QPushButton(centralWidget);
        btnAddPoint->setObjectName(QStringLiteral("btnAddPoint"));
        sizePolicy1.setHeightForWidth(btnAddPoint->sizePolicy().hasHeightForWidth());
        btnAddPoint->setSizePolicy(sizePolicy1);

        horizontalLayout_1->addWidget(btnAddPoint);

        btnRemovePoint = new QPushButton(centralWidget);
        btnRemovePoint->setObjectName(QStringLiteral("btnRemovePoint"));
        sizePolicy1.setHeightForWidth(btnRemovePoint->sizePolicy().hasHeightForWidth());
        btnRemovePoint->setSizePolicy(sizePolicy1);

        horizontalLayout_1->addWidget(btnRemovePoint);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_1->addItem(horizontalSpacer_3);

        btnLoadPoint = new QPushButton(centralWidget);
        btnLoadPoint->setObjectName(QStringLiteral("btnLoadPoint"));
        sizePolicy1.setHeightForWidth(btnLoadPoint->sizePolicy().hasHeightForWidth());
        btnLoadPoint->setSizePolicy(sizePolicy1);

        horizontalLayout_1->addWidget(btnLoadPoint);

        btnSavePoint = new QPushButton(centralWidget);
        btnSavePoint->setObjectName(QStringLiteral("btnSavePoint"));
        sizePolicy1.setHeightForWidth(btnSavePoint->sizePolicy().hasHeightForWidth());
        btnSavePoint->setSizePolicy(sizePolicy1);

        horizontalLayout_1->addWidget(btnSavePoint);


        verticalLayout->addLayout(horizontalLayout_1);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);

        RoboTenderCMSClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(RoboTenderCMSClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1162, 25));
        RoboTenderCMSClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(RoboTenderCMSClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        RoboTenderCMSClass->addToolBar(Qt::TopToolBarArea, mainToolBar);

        retranslateUi(RoboTenderCMSClass);

        QMetaObject::connectSlotsByName(RoboTenderCMSClass);
    } // setupUi

    void retranslateUi(QMainWindow *RoboTenderCMSClass)
    {
        RoboTenderCMSClass->setWindowTitle(QApplication::translate("RoboTenderCMSClass", "RoboTenderCMS", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("RoboTenderCMSClass", "PX,PY,PZ", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("RoboTenderCMSClass", "RX,RY,RZ", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("RoboTenderCMSClass", "DT(ms)", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("RoboTenderCMSClass", "AT(ms)", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("RoboTenderCMSClass", "Attr", Q_NULLPTR));
        btnSimulation->setText(QApplication::translate("RoboTenderCMSClass", "Simulation", Q_NULLPTR));
        btnTopView->setText(QApplication::translate("RoboTenderCMSClass", "TopView", Q_NULLPTR));
        btnAddPoint->setText(QApplication::translate("RoboTenderCMSClass", "Add", Q_NULLPTR));
        btnRemovePoint->setText(QApplication::translate("RoboTenderCMSClass", "Remove", Q_NULLPTR));
        btnLoadPoint->setText(QApplication::translate("RoboTenderCMSClass", "Load", Q_NULLPTR));
        btnSavePoint->setText(QApplication::translate("RoboTenderCMSClass", "Save", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class RoboTenderCMSClass: public Ui_RoboTenderCMSClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ROBOTENDERCMS_H

/********************************************************************************
** Form generated from reading UI file 'SystemInfoView.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SYSTEMINFOVIEW_H
#define UI_SYSTEMINFOVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SystemInfoView
{
public:
    QFrame *frame;
    QLabel *label;
    QPushButton *btnStart;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QLabel *label_2;
    QLabel *labComputeName;
    QLabel *label_3;
    QLabel *labProcessorName;
    QLabel *label_4;
    QLabel *labCard;
    QLabel *label_5;
    QLabel *labMemory;
    QLabel *label_6;
    QLabel *labSystem;
    QLabel *label_7;
    QLabel *labDisplay;
    QLabel *label_8;
    QLabel *labSpace;
    QPushButton *btnMini;
    QPushButton *btnClose;

    void setupUi(QWidget *SystemInfoView)
    {
        if (SystemInfoView->objectName().isEmpty())
            SystemInfoView->setObjectName(QStringLiteral("SystemInfoView"));
        SystemInfoView->resize(708, 499);
        SystemInfoView->setStyleSheet(QLatin1String("QWidget#SystemInfoView{\n"
"	\n"
"	background-color: rgb(40,52,74);\n"
"}"));
        frame = new QFrame(SystemInfoView);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setGeometry(QRect(8, 38, 691, 40));
        frame->setStyleSheet(QLatin1String("QFrame#frame{\n"
"background-color: rgba(195,195,195,150);\n"
"border-radius:6px;\n"
"}"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        label = new QLabel(frame);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(22, 4, 111, 28));
        label->setStyleSheet(QString::fromUtf8("QLabel{\n"
"	color: rgb(255, 255, 255);\n"
"	font: 24px \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"}"));
        btnStart = new QPushButton(SystemInfoView);
        btnStart->setObjectName(QStringLiteral("btnStart"));
        btnStart->setGeometry(QRect(601, 458, 91, 31));
        layoutWidget = new QWidget(SystemInfoView);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(28, 90, 661, 351));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setMinimumSize(QSize(100, 30));
        label_2->setStyleSheet(QString::fromUtf8("QLabel{\n"
"	color: rgb(255, 255, 255);\n"
"	font: 20px \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"}"));

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        labComputeName = new QLabel(layoutWidget);
        labComputeName->setObjectName(QStringLiteral("labComputeName"));
        labComputeName->setMinimumSize(QSize(530, 30));
        labComputeName->setStyleSheet(QString::fromUtf8("QLabel{\n"
"	\n"
"	font: 20px \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"	color: rgb(255, 255, 255);\n"
"}"));

        gridLayout->addWidget(labComputeName, 0, 1, 1, 1);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setMinimumSize(QSize(100, 30));
        label_3->setStyleSheet(QString::fromUtf8("QLabel{\n"
"	color: rgb(255, 255, 255);\n"
"	font: 20px \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"}"));

        gridLayout->addWidget(label_3, 1, 0, 1, 1);

        labProcessorName = new QLabel(layoutWidget);
        labProcessorName->setObjectName(QStringLiteral("labProcessorName"));
        labProcessorName->setMinimumSize(QSize(530, 30));
        labProcessorName->setStyleSheet(QString::fromUtf8("QLabel{\n"
"	\n"
"	font: 20px \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"	color: rgb(255, 255, 255);\n"
"}"));

        gridLayout->addWidget(labProcessorName, 1, 1, 1, 1);

        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setMinimumSize(QSize(100, 30));
        label_4->setStyleSheet(QString::fromUtf8("QLabel{\n"
"	color: rgb(255, 255, 255);\n"
"	font: 20px \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"}"));

        gridLayout->addWidget(label_4, 2, 0, 1, 1);

        labCard = new QLabel(layoutWidget);
        labCard->setObjectName(QStringLiteral("labCard"));
        labCard->setMinimumSize(QSize(530, 30));
        labCard->setStyleSheet(QString::fromUtf8("QLabel{\n"
"	\n"
"	font: 20px \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"	color: rgb(255, 255, 255);\n"
"}"));

        gridLayout->addWidget(labCard, 2, 1, 1, 1);

        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setMinimumSize(QSize(100, 30));
        label_5->setStyleSheet(QString::fromUtf8("QLabel{\n"
"	color: rgb(255, 255, 255);\n"
"	font: 20px \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"}"));

        gridLayout->addWidget(label_5, 3, 0, 1, 1);

        labMemory = new QLabel(layoutWidget);
        labMemory->setObjectName(QStringLiteral("labMemory"));
        labMemory->setMinimumSize(QSize(530, 30));
        labMemory->setStyleSheet(QString::fromUtf8("QLabel{\n"
"	\n"
"	font: 20px \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"	color: rgb(255, 255, 255);\n"
"}"));

        gridLayout->addWidget(labMemory, 3, 1, 1, 1);

        label_6 = new QLabel(layoutWidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setMinimumSize(QSize(100, 30));
        label_6->setStyleSheet(QString::fromUtf8("QLabel{\n"
"	color: rgb(255, 255, 255);\n"
"	font: 20px \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"}"));

        gridLayout->addWidget(label_6, 4, 0, 1, 1);

        labSystem = new QLabel(layoutWidget);
        labSystem->setObjectName(QStringLiteral("labSystem"));
        labSystem->setMinimumSize(QSize(530, 30));
        labSystem->setStyleSheet(QString::fromUtf8("QLabel{\n"
"	\n"
"	font: 20px \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"	color: rgb(255, 255, 255);\n"
"}"));

        gridLayout->addWidget(labSystem, 4, 1, 1, 1);

        label_7 = new QLabel(layoutWidget);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setMinimumSize(QSize(100, 30));
        label_7->setStyleSheet(QString::fromUtf8("QLabel{\n"
"	color: rgb(255, 255, 255);\n"
"	font: 20px \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"}"));

        gridLayout->addWidget(label_7, 5, 0, 1, 1);

        labDisplay = new QLabel(layoutWidget);
        labDisplay->setObjectName(QStringLiteral("labDisplay"));
        labDisplay->setMinimumSize(QSize(530, 30));
        labDisplay->setStyleSheet(QString::fromUtf8("QLabel{\n"
"	\n"
"	font: 20px \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"	color: rgb(255, 255, 255);\n"
"}"));

        gridLayout->addWidget(labDisplay, 5, 1, 1, 1);

        label_8 = new QLabel(layoutWidget);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setMinimumSize(QSize(100, 30));
        label_8->setStyleSheet(QString::fromUtf8("QLabel{\n"
"	color: rgb(255, 255, 255);\n"
"	font: 20px \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"}"));

        gridLayout->addWidget(label_8, 6, 0, 1, 1);

        labSpace = new QLabel(layoutWidget);
        labSpace->setObjectName(QStringLiteral("labSpace"));
        labSpace->setMinimumSize(QSize(530, 30));
        labSpace->setStyleSheet(QString::fromUtf8("QLabel{\n"
"	\n"
"	font: 20px \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"	color: rgb(255, 255, 255);\n"
"}"));
        labSpace->setWordWrap(true);

        gridLayout->addWidget(labSpace, 6, 1, 1, 1);

        btnMini = new QPushButton(SystemInfoView);
        btnMini->setObjectName(QStringLiteral("btnMini"));
        btnMini->setGeometry(QRect(648, 9, 18, 18));
        btnMini->setStyleSheet(QLatin1String("QPushButton{\n"
"border-image: url(:/Images/mini.png);\n"
"}\n"
"QPushButton:hover{\n"
"border-image: url(:/Images/mini_hover.png);\n"
"}"));
        btnClose = new QPushButton(SystemInfoView);
        btnClose->setObjectName(QStringLiteral("btnClose"));
        btnClose->setGeometry(QRect(678, 10, 18, 18));
        btnClose->setStyleSheet(QLatin1String("QPushButton{\n"
"border-image: url(:/Images/close.png);\n"
"}\n"
"QPushButton:hover{\n"
"border-image: url(:/Images/close_hover.png);\n"
"}"));

        retranslateUi(SystemInfoView);

        QMetaObject::connectSlotsByName(SystemInfoView);
    } // setupUi

    void retranslateUi(QWidget *SystemInfoView)
    {
        SystemInfoView->setWindowTitle(QApplication::translate("SystemInfoView", "SystemInfoView", Q_NULLPTR));
        label->setText(QApplication::translate("SystemInfoView", "\347\263\273\347\273\237\344\277\241\346\201\257", Q_NULLPTR));
        btnStart->setText(QApplication::translate("SystemInfoView", "\345\210\267\346\226\260", Q_NULLPTR));
        label_2->setText(QApplication::translate("SystemInfoView", "\347\224\265\350\204\221\345\220\215\347\247\260\357\274\232", Q_NULLPTR));
        labComputeName->setText(QString());
        label_3->setText(QApplication::translate("SystemInfoView", "\345\244\204  \347\220\206  \345\231\250\357\274\232", Q_NULLPTR));
        labProcessorName->setText(QString());
        label_4->setText(QApplication::translate("SystemInfoView", "\346\230\276       \345\215\241\357\274\232", Q_NULLPTR));
        labCard->setText(QString());
        label_5->setText(QApplication::translate("SystemInfoView", "\345\206\205       \345\255\230\357\274\232", Q_NULLPTR));
        labMemory->setText(QString());
        label_6->setText(QApplication::translate("SystemInfoView", "\346\223\215\344\275\234\347\263\273\347\273\237\357\274\232", Q_NULLPTR));
        labSystem->setText(QString());
        label_7->setText(QApplication::translate("SystemInfoView", "\346\230\276  \347\244\272  \345\231\250\357\274\232", Q_NULLPTR));
        labDisplay->setText(QString());
        label_8->setText(QApplication::translate("SystemInfoView", "\347\243\201\347\233\230\347\251\272\351\227\264\357\274\232", Q_NULLPTR));
        labSpace->setText(QString());
        btnMini->setText(QString());
        btnClose->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class SystemInfoView: public Ui_SystemInfoView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SYSTEMINFOVIEW_H

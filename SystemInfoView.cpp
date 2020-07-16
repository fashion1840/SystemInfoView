#include "SystemInfoView.h"
#include "WindowsSysInfo.h"
#include "ui_SystemInfoView.h"

#pragma execution_character_set("utf-8")

SystemInfoView::SystemInfoView(QWidget *parent) : IMoveWidget(parent), ui(new Ui::SystemInfoView), sysInfo(nullptr)
{
    ui->setupUi(this);

    setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint | Qt::FramelessWindowHint);

#ifdef Q_OS_LINUX
    sysInfo = new LinuxSysInfo();
#elif defined Q_OS_MACOS
    sysInfo = new MacxSysInfo();
#else
    sysInfo = new WindowsSysInfo();
#endif
}

SystemInfoView::~SystemInfoView()
{
    delete ui;
}

void SystemInfoView::on_btnStart_clicked()
{
    if (sysInfo == nullptr)
    {
        return;
    }

    clearAll();

    ui->labComputeName->setText(sysInfo->localmachineName());

    ui->labProcessorName->setText(sysInfo->cpuType());

    ui->labCard->setText(sysInfo->displayCard());

    ui->labMemory->setText(sysInfo->memory());

    ui->labSystem->setText(sysInfo->osVersion());

    ui->labDisplay->setText(sysInfo->screen());

    ui->labSpace->setText(sysInfo->disk());
}

void SystemInfoView::clearAll()
{
    ui->labComputeName->setText("");
    ui->labProcessorName->setText("");
    ui->labCard->setText("");
    ui->labMemory->setText("");
    ui->labSystem->setText("");
    ui->labDisplay->setText("");
    ui->labSpace->setText("");
}

void SystemInfoView::on_btnMini_clicked()
{
    this->showMinimized();
}

void SystemInfoView::on_btnClose_clicked()
{
    this->close();
}

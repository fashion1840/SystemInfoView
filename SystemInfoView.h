#ifndef SYSTEMINFOVIEW_H
#define SYSTEMINFOVIEW_H

#include "ISystemInfoFactory.h"

#include "IMoveWidget.h"

namespace Ui
{
    class SystemInfoView;
}

class SystemInfoView : public IMoveWidget
{
    Q_OBJECT

public:
    explicit SystemInfoView(QWidget *parent = nullptr);
    ~SystemInfoView();

private slots:
    void on_btnStart_clicked();

    void on_btnMini_clicked();

    void on_btnClose_clicked();

private:
    Ui::SystemInfoView *ui;

    ISystemInfoFactory *sysInfo;

    void clearAll();
};

#endif // SYSTEMINFOVIEW_H

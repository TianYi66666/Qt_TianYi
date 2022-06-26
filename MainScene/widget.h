#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE
struct Timer{
public:
    int year, month, date;
    Timer(int year_=0, int month_=0, int date_=0):year(year_),month(month_),date(date_){ }
};
class Country{
public:
    QString name;
    unsigned long long tot, infected, killed, healthy;
    QPushButton * btn;
    Country(QString name_, unsigned long long tot_, unsigned long long infected_, unsigned long long killed_, unsigned long long healthy_):
    name(name_),tot(tot_),infected(infected_),killed(killed_),healthy(healthy_){ }
};
//国家（父类）
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void Country_Button(QPushButton * pushbutton, int x, int y, const QString loc, int alpha);
    //ui按钮 位置x y mask地址 透明度（透明度取值范围0-255 越大越不透明）
    Timer getCurTime();
    void timedisplay(Timer t);
    Timer Date2Timer(QDate Date);

private:
    Ui::Widget *ui;
    Timer CurTime;
};
#endif // WIDGET_H

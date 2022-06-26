#include "widget.h"
#include "ui_widget.h"
#include <QImage>
#include <QPalette>
#include <QPixmap>
#include <QBitmap>
#include <QPushButton>
#include <QDate>
#include <QDebug>
#include <QTimer>
#include <QIcon>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->resize(1280,720);

    QImage * img = new QImage(":/main_background.png");
    ui->lbl->setGeometry(0,-40,1300,800);
    QImage * scaledimg = new QImage;
    *scaledimg = img->scaled(1300,800,Qt::KeepAspectRatio);
    ui->lbl->setPixmap(QPixmap::fromImage(*scaledimg));

    QImage * img2 = new QImage(":/datepad.png");
    ui->datepad->setGeometry(1080, 0,200,40);
    ui->datepad->setPixmap(QPixmap::fromImage(*img2));
    ui->datedisplay->setGeometry(1120, 3, 180, 35);

    Country_Button(ui->australia, 427, 140, "/Users/xutianyi/Desktop/素材-project/au.png", 200);
    Country_Button(ui->mid_africa, 88, 57, "/Users/xutianyi/Desktop/素材-project/中非.png", 100);
    Country_Button(ui->north_africa, 27, -20, "/Users/xutianyi/Desktop/素材-project/北非.png", 200);
    Country_Button(ui->south_africa, 77, 137, "/Users/xutianyi/Desktop/素材-project/南非.png", 200);
    Country_Button(ui->mozangbic, 146, 123, "/Users/xutianyi/Desktop/素材-project/莫桑比克.png", 50);
    Country_Button(ui->alaska, -585, -275, "/Users/xutianyi/Desktop/素材-project/阿拉斯加.png", 200);
    Country_Button(ui->america, -374, -95, "/Users/xutianyi/Desktop/素材-project/美国.png", 200);
    Country_Button(ui->canada, -397, -262, "/Users/xutianyi/Desktop/素材-project/加拿大.png", 75);
    Country_Button(ui->south_america, -256, 107, "/Users/xutianyi/Desktop/素材-project/南美.png", 100);
    QPushButton * arabia = new QPushButton;
    QPushButton * north_europe = new QPushButton;
    QPushButton * greenland = new QPushButton;
    QPushButton * north_asia = new QPushButton;
    QPushButton * east_asia = new QPushButton;
    QPushButton * south_asia = new QPushButton;
    QPushButton * islands = new QPushButton;
    QPushButton * norway = new QPushButton;
    QPushButton * southwest_asia = new QPushButton;
    QPushButton * west_asia = new QPushButton;
    QPushButton * mid_asia = new QPushButton;
    QPushButton * newzealand = new QPushButton;
    greenland->setParent(this);
    Country_Button(greenland, -157, -283, "/Users/xutianyi/Desktop/素材-project/格陵兰岛.png", 100);
    arabia->setParent(this);
    Country_Button(arabia, 153, -58, "/Users/xutianyi/Desktop/素材-project/阿拉伯半岛.png", 100);
    north_europe->setParent(this);
    Country_Button(north_europe, 38, -133, "/Users/xutianyi/Desktop/素材-project/北欧.png", 100);
    norway->setParent(this);
    Country_Button(norway, 65, -233, "/Users/xutianyi/Desktop/素材-project/挪威.png", 100);
    south_asia->setParent(this);
    Country_Button(south_asia, 286, -18, "/Users/xutianyi/Desktop/素材-project/南亚.png", 200);
    west_asia->setParent(this);
    Country_Button(west_asia, 133, -186, "/Users/xutianyi/Desktop/素材-project/西亚.png", 255);
    east_asia->setParent(this);
    Country_Button(east_asia, 395, -94, "/Users/xutianyi/Desktop/素材-project/东亚.png", 200);
    southwest_asia->setParent(this);
    Country_Button(southwest_asia, 238, -106, "/Users/xutianyi/Desktop/素材-project/西南亚.png", 100);
    mid_asia->setParent(this);
    Country_Button(mid_asia, 413, -208, "/Users/xutianyi/Desktop/素材-project/中亚.png", 150);
    north_asia->setParent(this);
    Country_Button(north_asia, 364, -300, "/Users/xutianyi/Desktop/素材-project/北亚.png", 150);
    islands->setParent(this);
    Country_Button(islands, 391, 39, "/Users/xutianyi/Desktop/素材-project/岛屿.png", 150);
    newzealand->setParent(this);
    Country_Button(newzealand, 542, 183, "/Users/xutianyi/Desktop/素材-project/新西兰.png", 150);

    timedisplay(getCurTime());
    //下面是时间控制按钮的设置
    QPushButton * st_or_pause = new QPushButton;
    st_or_pause->setParent(this);
    st_or_pause->setGeometry(0, 0, 2000, 2000);
    st_or_pause->setMask(QRegion(1083, 3, 28, 28,QRegion::Ellipse));
    st_or_pause->setStyleSheet("background-image: url(/Users/xutianyi/Desktop/素材-project/暂停.png)");

    QPushButton * speedup = new QPushButton;
    speedup->setParent(this);
    speedup->setGeometry(0, 0, 2000, 2000);
    speedup->setMask(QRegion(1112, 3, 27, 27,QRegion::Ellipse));
    speedup->setStyleSheet("background-image: url(/Users/xutianyi/Desktop/素材-project/快进.png)");
    //时间遍历
    static int num=0;
    QTimer * timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [=](){
        QDate now =  QDate::currentDate();
        QDate next = now.addDays(num++);
        CurTime=Date2Timer(next);
        timedisplay(Date2Timer(next));
    });
    connect(st_or_pause, &QPushButton::clicked, [=](){
        st_or_pause->setStyleSheet("background-image: url(/Users/xutianyi/Desktop/素材-project/暂停.png)");
        if (!timer->isActive()){
            timer->start(500);
        }
        else{
            timer->stop();
            st_or_pause->setStyleSheet("background-image: url(/Users/xutianyi/Desktop/素材-project/启动.png)");
            if (timer->interval()==30){
                speedup->setMask(QRegion(1112, 3, 27, 27,QRegion::Ellipse));
                speedup->setStyleSheet("background-image: url(/Users/xutianyi/Desktop/素材-project/快进.png)");
            }
        }
    });
    connect(speedup, &QPushButton::clicked, [=](){
        speedup->setMask(QRegion(1112, 3, 26, 26,QRegion::Ellipse));
        speedup->setStyleSheet("background-image: url(/Users/xutianyi/Desktop/素材-project/停止快进.png)");
        if (!timer->isActive() || timer->interval()==500){
            timer->start(30);
        }
        else{
            timer->start(500);
            speedup->setMask(QRegion(1112, 3, 27, 27,QRegion::Ellipse));
            speedup->setStyleSheet("background-image: url(/Users/xutianyi/Desktop/素材-project/快进.png)");
            st_or_pause->setStyleSheet("background-image: url(/Users/xutianyi/Desktop/素材-project/暂停.png)");
        }
    });


}
void Widget::Country_Button(QPushButton * pushbutton, int x, int y, QString loc, int alpha){
    QPixmap * image = new QPixmap(loc);
    pushbutton->setGeometry(x,y,1300,800);
    *image = image->scaled(1300,800,Qt::KeepAspectRatio);
    pushbutton->setMask(image->mask());
    pushbutton->setFlat(true);
    pushbutton->setAutoFillBackground(true);
    QPalette palette = pushbutton->palette();
    palette.setColor(QPalette::Button,QColor(255,0,0,alpha));
    pushbutton->setPalette(palette);
}
Timer Widget::getCurTime(){
    return CurTime;
}
void Widget::timedisplay(Timer t){
    QPalette pe;
    QFont ft;
    ft.setPointSize(20);
    pe.setColor(QPalette::WindowText, Qt::white);
    ui->datedisplay->setPalette(pe);
    ui->datedisplay->setFont(ft);
    QString str=QString::number(t.year)+"-"+QString::number(t.month)+"-"+QString::number(t.date);
    ui->datedisplay->setText(str);

}
Timer Widget::Date2Timer(QDate Date){
    QString str1 = Date.toString("yyyy-MM-dd");
    QStringList list = str1.split("-");
    int year=list.at(0).toInt();
    int month=list.at(1).toInt();
    int date=list.at(2).toInt();
    return Timer(year, month, date);
}
Widget::~Widget()
{
    delete ui;
}


#include "virusinfo.h"
#include "ui_virusinfo.h"
#include "evolutionbutton.h"
#include <QMovie>
#include <QDebug>
#include <QMediaPlayer>
#include <QMediaPlaylist>

VirusInfo::VirusInfo(QWidget *parent) :
    QTabWidget(parent),
    ui(new Ui::VirusInfo)
{
    /*
    QMediaPlaylist *playlist = new QMediaPlaylist();
    playlist->addMedia(QUrl(":/res/bg-Music.mp3"));
    playlist->addMedia(QUrl(":/res/bg-Music.mp3"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);
    playlist->setCurrentIndex(0);
    QMediaPlayer *music = new QMediaPlayer();
    music->setPlaylist(playlist);
    music->setVolume(60);
    music->play();
    */


    currButton = nullptr;
    DNAtotal = 999;Acttotal = 0; testa = 24;
    ui->setupUi(this);

    QMovie *movie = new QMovie(":/res/virus.gif");
    ui->virus1->setMovie(movie);
    movie->start();

    //page1

    //page2
    //backbutton
    connect(ui->pushButton_4, &QPushButton::clicked, this, [=](){
        emit back_to_last();
        qDebug() << "signal called";
    });

    //SpreadTree building...
    QWidget * tmp = ui->SpreadTree;
    spreadTree[1] = new EvolutionButton(tmp, 1, DNAtotal, Acttotal, {120, 50});
    spreadTree[2] = new EvolutionButton(tmp, 2, DNAtotal, Acttotal, spreadTree[1]->bottomRight());
    spreadTree[3] = new EvolutionButton(tmp, 3, DNAtotal, Acttotal, spreadTree[2]->bottomRight());
    spreadTree[4] = new EvolutionButton(tmp, 4, DNAtotal, Acttotal, spreadTree[3]->bottomRight());
    spreadTree[5] = new EvolutionButton(tmp, 5, DNAtotal, Acttotal, spreadTree[4]->topRight());
    spreadTree[6] = new EvolutionButton(tmp, 6, DNAtotal, Acttotal, spreadTree[3]->bottomLeft());
    spreadTree[7] = new EvolutionButton(tmp, 7, DNAtotal, Acttotal, spreadTree[6]->bottomLeft());
    spreadTree[8] = new EvolutionButton(tmp, 8, DNAtotal, Acttotal, {550, 90});
    spreadTree[9] = new EvolutionButton(tmp, 9, DNAtotal, Acttotal, spreadTree[8]->bottomRight());
    spreadTree[10] = new EvolutionButton(tmp, 10, DNAtotal, Acttotal, spreadTree[9]->bottom());
    spreadTree[11] = new EvolutionButton(tmp, 11, DNAtotal, Acttotal, spreadTree[10]->bottom());
    spreadTree[12] = new EvolutionButton(tmp, 12, DNAtotal, Acttotal, spreadTree[11]->bottomLeft());
    spreadTree[13] = new EvolutionButton(tmp, 13, DNAtotal, Acttotal, {120, 320});
    spreadTree[14] = new EvolutionButton(tmp, 14, DNAtotal, Acttotal, spreadTree[13]->topRight());
    spreadTree[15] = new EvolutionButton(tmp, 15, DNAtotal, Acttotal, spreadTree[14]->topRight());
    spreadTree[16] = new EvolutionButton(tmp, 16, DNAtotal, Acttotal, spreadTree[15]->bottomRight());
    spreadTree[17] = new EvolutionButton(tmp, 17, DNAtotal, Acttotal, spreadTree[16]->bottomRight());

    spreadTree[2]->addParents(spreadTree[1]);
    spreadTree[3]->addParents(spreadTree[2]);
    spreadTree[3]->addParents(spreadTree[6]);
    spreadTree[3]->addParents(spreadTree[4]);
    spreadTree[4]->addParents(spreadTree[5]);
    spreadTree[6]->addParents(spreadTree[7]);
    spreadTree[9]->addParents(spreadTree[8]);
    spreadTree[10]->addParents(spreadTree[9]);
    spreadTree[10]->addParents(spreadTree[11]);
    spreadTree[11]->addParents(spreadTree[12]);
    spreadTree[14]->addParents(spreadTree[13]);
    spreadTree[15]->addParents(spreadTree[14]);
    spreadTree[15]->addParents(spreadTree[16]);
    spreadTree[16]->addParents(spreadTree[17]);

    for (int i=1; i<18; ++i)
    {
        connect(spreadTree[i], &EvolutionButton::beselected, this, [=](){
            qDebug() << "button" << i << " be selected";
            currButton = spreadTree[i];
            widgetUpgrade();
        });
    }

    connect(ui->pushButton, &QPushButton::clicked, this, [=](){
        if (currButton != nullptr && currButton->Isemerged() && currButton->Isaffordable())
        {
            if (currButton->Isactivated())
            {
                DNAtotal -= 3;
                currButton->degenerate();
                testa -= 5;
            }
            else
            {
                DNAtotal -= currButton->getcost();
                currButton->activate();
                testa += 5;
            }
            widgetUpgrade();
        }
    });


    //progressBar
    ui->progressBar->setTextVisible(false);
    ui->progressBar->setRange(0, 100);
    ui->progressBar_2->setTextVisible(false);
    ui->progressBar_2->setRange(0, 100);
    ui->progressBar_3->setTextVisible(false);
    ui->progressBar_3->setRange(0, 100);
    ui->progressBar_hiden1->setTextVisible(false);
    ui->progressBar_hiden1->setRange(0, 100);
    ui->progressBar_hiden2->setTextVisible(false);
    ui->progressBar_hiden2->setRange(0, 100);
    ui->progressBar_hiden3->setTextVisible(false);
    ui->progressBar_hiden3->setRange(0, 100);

    //info_widget
    infobutton1 = new QPushButton(ui->info_widget1);
    infobutton1->move(65, 40);
    infobutton1->setStyleSheet("QPushButton{background-image:url(:/res/buttonbg.png); border:none;}");
    infobutton1->setFixedSize(64, 56);

    widgetUpgrade();
}

VirusInfo::~VirusInfo()
{
    delete ui;
}

void VirusInfo::mousePressEvent(QMouseEvent *event)
{
    qDebug() << event->x() << " " << event->y();
    if (ui->SpreadTree->geometry().contains(event->pos()))
    {
        qDebug() << "TreeWidget clicked";
        currButton = nullptr;
    }
    widgetUpgrade();
}

void VirusInfo::widgetUpgrade()
{
    //page1

    //page2
    //SpreadTree
    for (int i=1; i<18; ++i)
        spreadTree[i]->statecheck();
    for (int i=1; i<18; ++i)
        spreadTree[i]->statecheck();

    //progressBar(waiting to be bulit...)
    ui->progressBar->setValue(testa);
    ui->progressBar_2->setValue(testa);
    ui->progressBar_3->setValue(testa);
    if (currButton!=nullptr && !currButton->Isactivated())
    {
        ui->progressBar_hiden1->setValue(testa+5);
        ui->progressBar_hiden2->setValue(testa+5);
        ui->progressBar_hiden3->setValue(testa+5);
    }
    else
    {
        ui->progressBar_hiden1->setValue(testa);
        ui->progressBar_hiden2->setValue(testa);
        ui->progressBar_hiden3->setValue(testa);
    }

    //infowidget
    if (currButton==nullptr)
    {
        ui->SpreadTree_info1->setText("传播特性");
        infobutton1->setIcon(pix_none);
        ui->pushButton->hide();
    }
    else
    {
        ui->SpreadTree_info1->setText(infos[currButton->getType()][0]);
        pix.load(QString(":/icon/%1.png").arg(currButton->getType()));
        infobutton1->setIcon(pix);
        infobutton1->setIconSize(QSize(pix.width()/2,pix.height()/2));
        infobutton1->setFlat(true);
        ui->pushButton->show();
        if (!currButton->Isaffordable())
        {
            ui->pushButton->setText("你没DNA了<-_->");
        }
        else if (currButton->Isactivated())
        {
            ui->pushButton->setText("确认降级");
        }
        else
        {
            ui->pushButton->setText("确认升级");
        }
    }
    ui->lcdNumber->display(DNAtotal);

}



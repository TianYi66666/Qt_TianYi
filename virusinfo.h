#ifndef VIRUSINFO_H
#define VIRUSINFO_H

#include <QTabWidget>
#include "evolutionbutton.h"

namespace Ui {
class VirusInfo;
}

class VirusInfo : public QTabWidget
{
    Q_OBJECT
    int DNAtotal, Acttotal;
    EvolutionButton *currButton;
    EvolutionButton *spreadTree[20];
    QPushButton *infobutton1;
    QPixmap pix, pix_none;


    int testa;


public:
    explicit VirusInfo(QWidget *parent = nullptr);
    ~VirusInfo();

private:
    Ui::VirusInfo *ui;
    void mousePressEvent(QMouseEvent * event);
    void widgetUpgrade();

signals:
    void back_to_last();
};

#endif // VIRUSINFO_H

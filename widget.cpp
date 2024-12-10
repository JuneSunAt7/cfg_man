#include "widget.h"
#include "ui_widget.h"
#include "get_data_of_pc.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->nameOfPc->setText(getSystemModel());
    cpuUsageGraph = new CPUUsageGraph(ui->user_view_widget);
    cpuUsageGraph->setGeometry(0, 0, ui->user_view_widget->width(), ui->user_view_widget->height());
    cpuUsageGraph->show(); // Показываем график
}

Widget::~Widget()
{
    delete ui;
    delete cpuUsageGraph;
}


void Widget::on_openConfig_pbn_clicked()
{
    *currentConfName = QFileDialog::getOpenFileName(this,
                                  tr("Open config file"), "", tr("Config files(*.conf, *cfg)"));
}


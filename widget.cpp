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
    cpuUsageGraph->show();

    ui->saveConf_btn->setVisible(false);
    ui->saveConfAs_btn->setVisible(false);
    ui->closeConf_btn->setVisible(false);

    ui->editor->setVisible(false);

}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_openConfig_pbn_clicked()
{
    currentConfName = QFileDialog::getOpenFileName(this,
                                  tr("Open config file"), "", tr("All config files()"));
    cpuUsageGraph->setVisible(false);

    show_text_editor();


}
void Widget::show_text_editor(){
    ui->label_2->setVisible(false);
    ui->editor->setVisible(true);

    read_to_editor();

    ui->saveConf_btn->setVisible(true);
    ui->saveConfAs_btn->setVisible(true);
    ui->closeConf_btn->setVisible(true);
}

void Widget::read_to_editor(){
    QFile opened_conf(currentConfName);
    if (!opened_conf.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(nullptr, "Error", "No opening file: " + opened_conf.errorString());
        return;
    }

    QTextStream in(&opened_conf);
    QString fileContent = in.readAll(); // Считываем весь текст из файла
    ui->editor->setPlainText(fileContent);    // Устанавливаем текст в QTextEdit

    opened_conf.close();
}

void Widget::on_saveConf_btn_clicked()
{
    QFile file(currentConfName);
    file.open(QIODevice::WriteOnly);
            QTextStream out(&file);
            out << ui->editor->toPlainText(); // Запись текста из QTextEdit в файл
            file.close();
    QMessageBox::information(nullptr,"Saved", "Config saved");
    ui->editor->clear();

}


void Widget::on_saveConfAs_btn_clicked()
{
    QString filePath = QFileDialog::getSaveFileName(this, "Save as..", "", "All Files (*)");
            if (filePath.isEmpty()) {
                return; // Если пользователь отменил выбор, ничего не делаем
            }
    QFile file(filePath);
    file.open(QIODevice::WriteOnly);
    QTextStream out(&file);
    out << ui->editor->toPlainText(); // Запись текста из QTextEdit в файл
    file.close();
    QMessageBox::information(nullptr,"Saved", "Config saved");
    ui->editor->clear();
}


void Widget::on_closeConf_btn_clicked()
{
    ui->editor->clear();
    ui->editor->setVisible(false);
    cpuUsageGraph->setVisible(true);

}


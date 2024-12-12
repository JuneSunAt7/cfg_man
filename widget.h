#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QFileDialog>
#include <QPlainTextEdit>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

#include "cpu_usage_graph.h"
#include "filesystem_view.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    QString currentConfName;
    ~Widget();

private slots:
    void on_openConfig_pbn_clicked();

    void on_saveConf_btn_clicked();

    void on_saveConfAs_btn_clicked();

    void on_closeConf_btn_clicked();

    void on_createConfig_pbn_clicked();

    void on_filesys_pbn_clicked();

private:
    Ui::Widget *ui;
    CPUUsageGraph *cpuUsageGraph;
    UserWidget *treeFs;

    void show_text_editor();
    void read_to_editor();
};
#endif // WIDGET_H

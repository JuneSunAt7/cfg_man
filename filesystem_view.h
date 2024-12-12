#ifndef USER_WIDGET_H
#define USER_WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFileSystemModel>
#include <QTreeView>
#include <QComboBox>

class UserWidget : public QWidget {
    Q_OBJECT

public:
    UserWidget(QWidget *parent = nullptr);
private slots:
    void changeDrive(int index);
private:
    QTreeView *treeView;
    QComboBox *comboBox;
    void showFileSystem();
};

#endif // USER_WIDGET_H

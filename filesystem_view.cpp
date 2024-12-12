#include "filesystem_view.h"
#include <QHBoxLayout>
#include <QFileIconProvider>
#include <QDir>
#include <QFileSystemModel>
#include <QDebug>
#include <QComboBox>
#include <QVBoxLayout>
#include <QTreeView>

UserWidget::UserWidget(QWidget *parent)
    : QWidget(parent), treeView(new QTreeView(this)), comboBox(new QComboBox(this)) {

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(comboBox);
    layout->addWidget(treeView);
    setLayout(layout);

    showFileSystem();

    // Подключаем сигнал изменения текущего индекса в comboBox
    connect(comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &UserWidget::changeDrive);

}
void UserWidget::showFileSystem() {
    QFileSystemModel *model = new QFileSystemModel(this);

    // Устанавливаем корень модели на корневую директорию (C:\, D:\ и т.д.)
    model->setRootPath(QDir::rootPath());

    // Установка модели
    treeView->setModel(model);

    // Получаем список всех доступных дисков
    foreach(const QFileInfo &driveInfo, QDir::drives()) {
        comboBox->addItem(driveInfo.absoluteFilePath()); // Добавляем диск в combobox
    }

    // Проверяем, есть ли доступные диски
    if (comboBox->count() > 0) { // Используем count() для проверки
        comboBox->setCurrentIndex(0);
        changeDrive(0); // Обновляем дерево для первого диска
    }

    treeView->setAnimated(true);
    treeView->setIndentation(20);
    treeView->setSortingEnabled(true);
    treeView->setColumnWidth(0, treeView->width() / 3);
    treeView->show();
}

void UserWidget::changeDrive(int index) {
    QFileSystemModel *model = dynamic_cast<QFileSystemModel*>(treeView->model());

    // Получаем выбранный диск
    QString drivePath = comboBox->itemText(index);
    QModelIndex driveIndex = model->index(drivePath);

    // Устанавливаем корень для выбранного диска
    if (driveIndex.isValid()) {
        treeView->setRootIndex(driveIndex);
    }
}

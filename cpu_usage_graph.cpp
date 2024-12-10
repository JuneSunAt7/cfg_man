#include "cpu_usage_graph.h"

CPUUsageGraph::CPUUsageGraph(QWidget *parent)
    : QGraphicsView(parent)
{
    scene = new QGraphicsScene(this);
    setScene(scene);
    setSceneRect(0, 0, 701, 571); // Установите размер сцены в соответствии с вашими предпочтениями
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &CPUUsageGraph::updateGraph);
    timer->start(200); // Обновление каждые 200 мс
}

CPUUsageGraph::~CPUUsageGraph()
{
    delete scene;
}

void CPUUsageGraph::updateGraph()
{
    // Получение загрузки процессора
    float cpuUsage = getCPUUsage();

    // Сглаживаем новые значения
    static QVector<float> cpuUsages;
    static const int maxPoints = 100;

    if (cpuUsages.size() >= maxPoints) {
        cpuUsages.remove(0); // Удаляем самое старое значение
    }

    // Добавляем сглаженное значение
    if (!cpuUsages.isEmpty()) {
        cpuUsage = (cpuUsages.last() * 0.8) + (cpuUsage * 0.2); // Сглаживание
    }

    cpuUsages.append(cpuUsage);

    scene->clear(); // Очищаем сцену

    // Рисуем оси координат
    QPen axisPen(Qt::blue);
    axisPen.setWidth(5);

    // Вертикальная ось Y
    scene->addLine(50, 0, 50, height(), axisPen);

    // Горизонтальная ось X
    scene->addLine(50, height(), width(), height(), axisPen);

    // Увеличенные множители для изменения масштаба
    float scaleFactor = 4.0; // Увеличивает высоту графика
    float xScaleFactor = static_cast<float>(width() - 50) / maxPoints; // Горизонтальное расстояние с использованием ширины виджета

    // Создаем путь для рисования графика
    QPainterPath path;
    path.moveTo(50, height() - (cpuUsages[0] * scaleFactor) - 20); // Инициализация первой точки с отступом

    for (int i = 1; i < cpuUsages.size(); ++i) {
        path.lineTo(50 + i * xScaleFactor, height() - (cpuUsages[i] * scaleFactor) - 20); // Добавляем линии между точками
    }

    // Рисуем график в сцене с заданной толщиной линии
    QPen pen(Qt::green);
    pen.setWidth(3);
    scene->addPath(path, pen);

    // Добавление сетки и меток на оси Y
    for (int i = 0; i <= 9; ++i) { // Для 0, 10, ..., 90
        float yValue = height() - (i * (height() - 20) / 9) - 20; // Равномерное распределение высоты с отступом
        scene->addLine(50, yValue, width(), yValue, QPen(Qt::lightGray, 1, Qt::DashLine)); // Горизонтальные линии

        // Добавляем метки по оси Y
        scene->addText(QString::number(i * 10))->setPos(10, yValue - 10); // Установка текста
    }

    for (int i = 0; i <= maxPoints; ++i) {
        scene->addLine(50 + i * xScaleFactor, 0, 50 + i * xScaleFactor, height(), QPen(Qt::lightGray, 1, Qt::DashLine)); // Вертикальные линии
    }
}
float CPUUsageGraph::getCPUUsage() {
#ifdef Q_OS_WIN
    QProcess process;
    process.start("wmic cpu get loadpercentage");
    process.waitForFinished();
    QByteArray output = process.readAllStandardOutput();
    QStringList lines = QString(output).split("\n", QString::SkipEmptyParts);
    if (lines.size() > 1) {
        return lines[1].toFloat();
    }
#elif defined(Q_OS_LINUX)
    QFile file("/proc/stat");
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        QString line = file.readLine();
        QStringList values = line.split(QRegExp("\\s+"), QString::SkipEmptyParts);
        if (values.size() > 1) {
            float idle = values[4].toFloat();
            float total = 0;
            for (const QString &value : values) {
                total += value.toFloat();
            }
            return (1.0 - (idle / total)) * 100; // Процентное соотношение
        }
    }
#endif
    return 0; // Возвращаем 0%, если не удалось получить данные
}

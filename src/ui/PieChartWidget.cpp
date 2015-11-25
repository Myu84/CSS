#include <QPainter>
#include <QColor>
#include <QBrush>
#include <QRect>
#include <QPalette>
#include <QPaintEvent>

#include "PieChartWidget.h"

#ifndef M_PI
#define M_PI 3.1415927
#endif

PieChartWidget::PieChartWidget(QWidget *parent)
    : QWidget(parent)
{
    mPieSize = 300;
    mTotalValue = 0.0;
}

void PieChartWidget::setData(QVector<QString> keys, QVector<double> values)
{
    mKeys = keys;
    mValues = values;
    mTotalValue = 0.0;

    for (double val : mValues) {
        mTotalValue += val;
    }
}

void PieChartWidget::paintEvent(QPaintEvent *event)
{
    // need to deal with default state (no data) up here
    if (mTotalValue == 0.0)
        return;

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QBrush b(Qt::white);
    painter.fillRect(event->rect(), b);

    painter.setBrush(Qt::red); // just for now

    double startAngle = 0.0;

    double rectSize = qMin(this->width(), this->height());
    QRectF size = QRectF(10, 10, rectSize/2, rectSize/2);

    for (int i = 0; i < mKeys.size(); i++) {
        QString key = mKeys.at(i);
        double value = mValues.at(i);

        if (value > 0.0) {
            double angle = 360*value/mTotalValue;
            painter.drawPie(size, int(startAngle*16), int(angle*16));
            startAngle += angle;
        }
    }
}

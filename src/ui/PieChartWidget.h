#ifndef PIECHARTWIDGET
#define PIECHARTWIDGET

#include <QWidget>
#include <QVector>
#include <QString>

class PieChartWidget : public QWidget {
    Q_OBJECT

public:
    PieChartWidget(QWidget *parent = 0);
    void setData(QVector<QString> keys, QVector<double> values);

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    QVector<QString> mKeys;
    QVector<double> mValues;
    int mPieSize;
    double mTotalValue;

};

#endif // PIECHARTWIDGET


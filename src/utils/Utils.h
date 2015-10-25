#ifndef UTILS_H
#define UTILS_H

#include <QPair>
#include <QDate>
#include <QList>

template <typename T>
QPair<QDate, QDate> findDateRange(const QList<T> &records) {
	QDate min;
	QDate max;
	
	for (const T &record : records) {
		if (record.date < min) {
			min = record.date;
		}
		if (record.date > max) {
			max = record.date;
		}
	}
	
	return qMakePair(min, max);
}

template <typename T, typename U>
QList<T> filterRecords(const QList<T> &records, U pred) {
	QList<T> output;
	
	for (const T &record : records) {
		if (pred(record)) {
			output.append(record);
		}
	}
	
	return output;
}

#endif

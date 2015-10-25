#ifndef UTILS_H
#define UTILS_H

#include <QPair>
#include <QDate>
#include <QList>

template <typename T>
QPair<QDate, QDate> findDateRange(const T &records) {
	QDate min, max;
	
	for (const auto &record : records) {
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
QList<typename T::value_type> filterRecords(const T &records, U pred) {
	QList<typename T::value_type> output;
	
	for (const auto &record : records) {
		if (pred(record)) {
			output.append(record);
		}
	}
	
	return output;
}

template <typename T>
int total(const T &vect) {
	int output = 0;
	
	for (const auto &val : vect) {
		output += val;
	}
	
	return output;
}

#endif

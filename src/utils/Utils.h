#ifndef UTILS_H
#define UTILS_H

#include <QPair>
#include <QDate>
#include <QList>

template <typename T>
QPair<QDate, QDate> findDateRange(const T &records) {
	QDate min, max;
    // this will crash if records is empty
    min = records[0].date;
    max = records[0].date;
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

template <typename T>
QList<typename T::value_type> filterByDateRange(const T &records, QDate startDate, QDate endDate) {
	QList<typename T::value_type> output;
	
	for (const auto &record : records) {
		if (record.date >= startDate && record.date <= endDate) {
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

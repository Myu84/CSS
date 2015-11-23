#ifndef UI_UTILS_H
#define UI_UTILS_H

#include <QPair>
#include <QDate>
#include <QList>

template <typename T>
QPair<QDate, QDate> findDateRange(const T &records) {
	QDate min = records[0].date;
	QDate max = records[0].date;
	
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
QPair<QDate, QDate> findDateRangeStartEnd(const T &records) {
	QDate min = records[0].startDate;
	QDate max = records[0].endDate;
	
	for (const auto &record : records) {
        if (record.startDate < min) {
            min = record.startDate;
		}
        if (record.endDate > max) {
            max = record.endDate;
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
QList<typename T::value_type> filterByDateRangeStartEnd(const T &records, QDate startDate, QDate endDate) {
	QList<typename T::value_type> output;
	
	for (const auto &record : records) {
		if (record.startDate >= startDate && record.endDate <= endDate) {
			output.append(record);
		}
	}
	
	return output;
}

#endif

#include <QString>
#include <QDate>
#include <QList>
#include <QDebug>

#include "../records/TeachingRecord.h"
#include "Parser.h"
#include "TeachingParser.h"

using namespace std;

// file_name should be path to file
QList<TeachingRecord> TeachingParser::parse(QString file_name) {
	CSVParser<10> parser(file_name.toStdString());

	parser.read_header(column_policy,
                       "Member Name",
                       "Primary Domain",
                       "Start Date",
                       "End Date",
                       "Program",
                       "Type of Course / Activity",
                       "Geographical Scope",
                       "Hours per Teaching Session or Week",
                       "Number Of Trainees",
                       "Total Hours"
		);
	
	QList<TeachingRecord> records;
	
	TeachingRecord curr_record;
    //for converting purposes
    QString curr_startDate;
    QString curr_endDate;
    QString curr_pro;
    QString curr_numTra;
    QString curr_totalH;
    
    int count = 2; // keep track of csv line being read. Start at 2 to account for the header
    while (parser.read_row(curr_record.memberName,
                           curr_record.primaryDomain,
                           curr_startDate,
                           curr_endDate,
                           curr_pro,curr_record.activityType,
                           curr_record.geographicalScope,
                           curr_record.hoursPerSession,
                           curr_numTra,
                           curr_totalH))
    {
		
        //validate name
        if (curr_record.memberName.isEmpty()) {
            //TODO: handle missing name
            qDebug() << "Missing [member name] on line " << count;
            continue;
        }
        
        //validate Primary Domain
        if (curr_record.primaryDomain.isEmpty()) {
            //TODO: handle missing name
            qDebug() << "Missing [Primary Domainon] on line " << count;
            continue;
        }
        
        QDate startDate;
        QDate endDate;

        //validate start date entry
        //category the academic year
        //rule: [2012-09-01, 2013-08-31] ==> academicYear="2012-2013"
        startDate = QDate::fromString(curr_startDate, "yyyy-MM-dd");

        if (!startDate.isValid()) {
            startDate = QDate::fromString(curr_startDate, "yyyy-MM");
            if (!startDate.isValid()) {
                startDate = QDate::fromString(curr_startDate, "yyyy");
                if (!startDate.isValid()) {
					//TODO: handle invalid date entry
                    qDebug() << "Invalid date entry: " << curr_startDate << " on line " << count;
					continue;
				}
                else{
                    //YYYY 2012-01-01 is 2011-2012
                    curr_record.academicYear= QString::number(startDate.year()-1)+"-"+ QString::number(startDate.year());
                }
			}
            else{
                //YYYY-MM
                if (startDate.month()<9)
                    //2012-01 is 2011-2012
                    curr_record.academicYear=QString::number(startDate.year()-1)+"-"+QString::number(startDate.year());
                else
                    //2012-10 is 2012-2013
                    curr_record.academicYear= QString::number(startDate.year())+"-"+ QString::number(startDate.year()+1);
            }
		}
        else{
            //YYYY-MM-dd
            if (startDate.month()<9)
                curr_record.academicYear = QString::number(startDate.year()-1)+"-"+ QString::number(startDate.year());
            else
                curr_record.academicYear= QString::number(startDate.year())+"-"+QString::number(startDate.year()+1);
        }
    curr_record.date=startDate;//for date filter


        //validate end date entry
        endDate = QDate::fromString(curr_endDate, "yyyy-MM-dd");
        if (!endDate.isValid()) {
            endDate = QDate::fromString(curr_endDate, "yyyy-MM");
            if (!endDate.isValid()) {
                endDate = QDate::fromString(curr_endDate, "yyyy");
                if (!endDate.isValid()) {
                    //TODO: handle invalid date entry
                    qDebug() << "Invalid date entry: " << curr_endDate << " on line " << count;
                    continue;
                }
            }
        }
        //verify the range
        if(startDate>endDate){
                 qDebug() << "Incorrect date range: "<<startDate<<" to "<<endDate<< "on line " << count;
                 continue;
        }
        

		
        //assign program type number
        if (curr_pro.isEmpty()) {
			//TODO: handle missing
                        qDebug() << "Missing [programe] on line " << count;
			continue;
        }
        else if(curr_pro.compare("Postgraduate Medical Education")==0)
            curr_record.programType="PME";
        else if(curr_pro.compare("Undergraduate Medical Education")==0)
            curr_record.programType="UME";
        else if(curr_pro.compare("Continuing Medical Education")==0)
            curr_record.programType="CME";
        else curr_record.programType="Other";//other
        
		
		//validate Type of Course / Activity
		if (curr_record.activityType.isEmpty()) {
			//TODO: handle missing
                        qDebug() << "Missing [Type of Course / Activity] on line " << count;
			continue;
		}
        
        
        //validate Geographical Scope
        if (curr_record.geographicalScope.isEmpty()) {
            //TODO: handle missing
            qDebug() << "Missing [Geographical Scope] on line " << count;
            continue;
        }
        
        //validate Hours per Teaching Session or Week
        if (curr_record.hoursPerSession.isEmpty()) {
            //TODO: handle missing
            qDebug() << "Missing [Hours per Teaching Session or Week] on line " << count;
            continue;
        }
        

        //get number of trainee
        if(curr_numTra.isEmpty()){
            //TODO: handle missing
            qDebug() << "Missing [number of trainees] on line " << count;
            continue;
        }
        else{
            bool ok1;
            curr_record.numStudent=curr_numTra.toInt(&ok1,10);
            if(!ok1){
                qDebug() << "[number of trainee] is not integer on line " << count;
                continue;
            }
            if(curr_record.numStudent<0){
                qDebug() << "[number of trainee] is negative on line " << count;
                continue;
            }
        }
        
        //get total hour
        if(curr_totalH.isEmpty()){
            //TODO: handle missing
            qDebug() << "Missing [total hours] on line " << count;
            continue;
        }
        else{
            bool ok2;
            curr_record.totalhours=curr_totalH.toDouble(&ok2);
            if(!ok2){
                qDebug() << "[total hours] is not double on line" << count;
                continue;
            }
            if(curr_record.totalhours<0){
                qDebug() << "[total hours] is negative on line " << count;
                continue;
            }

        }
		records.append(curr_record);
        ++count;
	}
	
	return records;
}

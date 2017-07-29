//Populate table on main tab

#include "mainwindow.h"
#include "table.h"


#include <QPushButton>
#include <QGridLayout>
#include <QFile>
#include <QDebug>
#include <QLabel>
#include <QCheckBox>
#include <QLineEdit>
#include <QTableWidget>
#include <QDate>

Table::Table()
{

}

void Table::create_PatTable(QWidget *patrol_Tab, int numSunk, QGridLayout *Pat_layout, QString career, QString patrolNum) {

    QTableWidget *table = new QTableWidget(patrol_Tab);
    Pat_layout->addWidget(table,2,0,15,15);
    table->setRowCount(numSunk);
    table->setColumnCount(11);
    QStringList HTableHeader;
    HTableHeader << "Date" << "Time" << "Name" << "Class" << "Type" << "Nationality" << "Side" << "Grid" << "Sunk Longitude\n(meters)" << "Sunk Latitude\n(meters)" << "Generic Name";

    table->setHorizontalHeaderLabels(HTableHeader);


    table->setStyleSheet("QHeaderView::section:horizontal { padding: 5px; padding-left: 20px; padding-right: 20px;}");
    table->setStyleSheet("QTableWidget:item { padding-left: 5px; padding-right: 5px;}");
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);

    add_Data(table, numSunk, career, patrolNum);

    set_ToolTips(table);

    table->resizeColumnsToContents();

}

QString Table::find_Data(QString career, QString patrolNum, QString find){
    QFile file("Careers/" + career + "/ShipSunk_Data.txt");
    if(!file.open(QIODevice::ReadOnly) && file.exists()) {
        qDebug() << file.errorString();
    }
    if(!file.exists()) {
        qDebug() << file.fileName() << "does not exist!";
    }

    QTextStream in(&file);
    QString line;
    while(!in.atEnd()) {
        line = in.readLine();
        if(!(line.indexOf("Career="+career, 0, Qt::CaseSensitive)==-1)) {
            while(!in.atEnd()) {
                line = in.readLine();
                if(!(line.indexOf("Patrol="+patrolNum, 0, Qt::CaseSensitive)==-1)) {
                    while(!in.atEnd()) {
                        line = in.readLine();
                        if((line.indexOf(find, 0, Qt::CaseSensitive)==0)) {
                            QRegExp rx("\\="); //RegEx for '='
                            QStringList query = line.split(rx);
                            file.close();
                            return query.value(1);
                        }
                    }
                }
            }
        }
    }
    file.close();
    return 0;
}

void Table::add_Data(QTableWidget *table, int numSunk, QString career, QString patrolNum) {
    for(int i=0;i<numSunk;++i) {

        QDate date(QDate::fromString((find_Data(career, patrolNum, "SunkDate=")), "yyyyMMdd"));
        table->setItem(i, 0, new QTableWidgetItem(date.toString("d MMMM yyyy")));
        table->item(i, 0)->setTextAlignment(Qt::AlignCenter);
        table->setItem(i, 1, new QTableWidgetItem(find_Data(career, patrolNum, "SunkTime=")));
        table->item(i, 1)->setTextAlignment(Qt::AlignCenter);
        table->setItem(i, 2, new QTableWidgetItem(find_Data(career, patrolNum, "Name=")));
        table->item(i, 2)->setTextAlignment(Qt::AlignCenter);
        table->setItem(i, 3, new QTableWidgetItem(find_Data(career, patrolNum, "Class=")));
        table->item(i, 3)->setTextAlignment(Qt::AlignCenter);

        table->setItem(i, 4, new QTableWidgetItem(grab_ShipType(find_Data(career, patrolNum, "Type="))));
        table->item(i, 4)->setTextAlignment(Qt::AlignCenter);
        table->setItem(i, 5, new QTableWidgetItem(find_Data(career, patrolNum, "Origin=")));
        table->item(i, 5)->setTextAlignment(Qt::AlignCenter);


        //change "Side" from number to Axis, Allies or Neutral
        if(find_Data(career, patrolNum, "Side=")=="0") {
            table->setItem(i, 6, new QTableWidgetItem("Neutral"));
        } else if(find_Data(career, patrolNum, "Side=")=="1") {
            table->setItem(i, 6, new QTableWidgetItem("Allies"));
        } else if(find_Data(career, patrolNum, "Side=")=="2") {
            table->setItem(i, 6, new QTableWidgetItem("Axis"));
        }
        table->item(i, 6)->setTextAlignment(Qt::AlignCenter);

        table->setItem(i, 7, new QTableWidgetItem(find_Data(career, patrolNum, "SunkGrid=")));
        table->item(i, 7)->setTextAlignment(Qt::AlignCenter);
        table->setItem(i,8, new QTableWidgetItem(QString::number((find_Data(career, patrolNum, "SunkLong=")).toDouble(), 'f', 2)));
        table->item(i, 8)->setTextAlignment(Qt::AlignCenter);
        table->setItem(i, 9, new QTableWidgetItem(QString::number((find_Data(career, patrolNum, "SunkLat=")).toDouble(), 'f', 2)));
        table->item(i, 9)->setTextAlignment(Qt::AlignCenter);
        table->setItem(i, 10, new QTableWidgetItem(find_Data(career, patrolNum, "GenericName=")));
        table->item(i, 10)->setTextAlignment(Qt::AlignCenter);

    }
}


QString Table::grab_ShipType(QString type) {
    GrabData *grabDataObj = new GrabData();
    QFile file(grabDataObj->return_sh3Directory()+"/data/Roster/English.cfg");

    if(!file.open(QIODevice::ReadOnly) && file.exists()) {
        qDebug() << file.errorString();
    }
    if(!file.exists()) {
        qDebug() << file.fileName() << "does not exist";
        file.close();
        return 0;
    }

    QTextStream in(&file);
    QString line;
    while(!in.atEnd()) {
        line = in.readLine();
        if(!(line.indexOf("Type" + type + "=", 0, Qt::CaseSensitive)==-1)) {
            QRegExp rx("\\="); //RegEx for '='
            QStringList query = line.split(rx);
            file.close();
            //qDebug() << query.value(1);
            return query.value(1);

        }
    }
    file.close();
    return 0;
}

void Table::set_ToolTips(QTableWidget *table){

    //horizontal headers
    table->horizontalHeaderItem(0)->setToolTip("Sunk date in \"d MMMM yyyy\" format.");
    table->horizontalHeaderItem(1)->setToolTip("Sunk time (24h).");
    table->horizontalHeaderItem(2)->setToolTip("Name of vessel.");
    table->horizontalHeaderItem(3)->setToolTip("Class of vessel.");
    table->horizontalHeaderItem(4)->setToolTip("Type of vessel.");
    table->horizontalHeaderItem(5)->setToolTip("Nationality of vessel.");
    table->horizontalHeaderItem(6)->setToolTip("Warring side of the vessel at time of sinking.");
    table->horizontalHeaderItem(7)->setToolTip("Sunk grid location.");
    table->horizontalHeaderItem(8)->setToolTip("Approximate sunk longitude, in meters (SH3 coordinate system).");
    table->horizontalHeaderItem(9)->setToolTip("Approximate sunk latitude, in meters (SH3 coordinate system).");
    table->horizontalHeaderItem(10)->setToolTip("Generic name. Name that it relates to in the \"Real_Ship_Name_List.txt\" file.\nThis is used to find other unique instances of the vessel in the campaign layers.\nThis is often a part of the actual vessel name.");


    //columns
    for(int i=0;i<table->rowCount();i++) {
        table->item(i,0)->setToolTip("Sunk date in \"d MMMM yyyy\" format.");
        table->item(i,1)->setToolTip("Sunk time (24h).");
        table->item(i,2)->setToolTip("Name of vessel.");
        table->item(i,3)->setToolTip("Class of vessel.");
        table->item(i,4)->setToolTip("Type of vessel.");
        table->item(i,5)->setToolTip("Nationality of vessel.");
        table->item(i,6)->setToolTip("Warring side of the vessel at time of sinking.");
        table->item(i,7)->setToolTip("Sunk grid location.");
        table->item(i,8)->setToolTip("Approximate sunk longitude, in meters (SH3 coordinate system).");
        table->item(i,9)->setToolTip("Approximate sunk latitude, in meters (SH3 coordinate system).");
        table->item(i,10)->setToolTip("Generic name. Name that it relates to in the \"Real_Ship_Name_List.txt\" file.\nThis is used to find other unique instances of the vessel in the campaign layers.\nThis is often a part of the actual vessel name.");


    }

}

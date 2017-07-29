#ifndef TABLE_H
#define TABLE_H


#include "grabdata.h"

#include <QWidget>
#include <QFile>
#include <QGridLayout>
#include <QPushButton>
#include <QCheckBox>
#include <QTableWidget>

class Table
{
public:
    Table();
    void create_PatTable(QWidget*, int, QGridLayout*, QString, QString);
    QString find_Data(QString, QString, QString);
    void add_Data(QTableWidget*, int, QString, QString);
    QString grab_ShipType(QString);
    void set_ToolTips(QTableWidget*);

private:

};

#endif // TABLE_H

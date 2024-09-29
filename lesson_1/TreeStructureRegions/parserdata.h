#ifndef PARSERDATA_H
#define PARSERDATA_H

#include <QString>
#include <QPair>
#include <QVector>
#include <QFile>
#include <QTextStream>
#include <QRegularExpression>

#include "country.h"

//using Params = QPair<QString, QString>;

class ParserData
{
public:
    ParserData() {}
    ParserData(const QString& filePath);
    ~ParserData() {}

    void setFilePath(const QString& filePath);

    QVector<ParamsFile> parsingCSV();

private:
    QString filePath_;
    QVector<ParamsFile> data_;
};

#endif // PARSERDATA_H

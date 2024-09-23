#ifndef PARSERDATA_H
#define PARSERDATA_H

#include <QString>
#include <QPair>
#include <QVector>
#include <QFile>
#include <QTextStream>
#include <QRegularExpression>

using Params = QPair<QString, QString>;

class ParserData
{
public:
    ParserData() {}
    ParserData(const QString& filePath);
    ~ParserData() {}

    void setFilePath(const QString& filePath);

    QVector<Params> parsingCSV();

private:
    QString filePath_;
    QVector<Params> data_;
};

#endif // PARSERDATA_H

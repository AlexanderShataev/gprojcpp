#include "parserdata.h"


ParserData::ParserData(const QString &filePath) : filePath_(filePath) {}

void ParserData::setFilePath(const QString &filePath) {
    filePath_ = filePath;
}

QVector<Params> ParserData::parsingCSV() {
    if (filePath_ == QString())
        return {};
    QFile file(filePath_);
    if (!file.open(QIODevice::ReadOnly))
        return {};

    QVector<Params> result;
    QTextStream stream(&file);
    while (!stream.atEnd()) {
        QString line = stream.readLine();
        auto temp = Params{line.section(",", 0, 0).remove(QRegularExpression("\"")),
                           line.section("\",\"", 4, 4).remove(QRegularExpression("\""))};
        if (temp.first == "city")
            continue;
        result.push_back(temp);
    }
    return result;
}

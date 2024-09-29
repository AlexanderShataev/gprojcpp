#include "parserdata.h"


ParserData::ParserData(const QString &filePath) : filePath_(filePath) {}

void ParserData::setFilePath(const QString &filePath) {
    filePath_ = filePath;
}

QVector<ParamsFile> ParserData::parsingCSV() {
    if (filePath_ == QString())
        // Имеет смысл добавить исключение
        return {};
    QFile file(filePath_);
    if (!file.open(QIODevice::ReadOnly))
        return {};

    QVector<ParamsFile> result;
    QTextStream stream(&file);
    while (!stream.atEnd()) {
        QString line = stream.readLine();
        if (line.section(",", 0, 0).remove(QRegularExpression("\"")) == "city")
            continue;
        auto temp = ParamsFile(line.section(",", 0, 0).remove(QRegularExpression("\"")),
                               line.section(",", 2, 2).remove(QRegularExpression("\"")).toDouble(),
                               line.section(",", 3, 3).remove(QRegularExpression("\"")).toDouble(),
                               line.section("\",\"", 4, 4).remove(QRegularExpression("\"")),
                               line.section(",", 5, 5).remove(QRegularExpression("\"")),
                               line.section(",", 6, 6).remove(QRegularExpression("\"")),
                               line.section(",", 9, 9).remove(QRegularExpression("\"")).toDouble());
        result.push_back(temp);
    }
    return result;
}

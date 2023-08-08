#include "notepadfile.h"

NotePadFile::NotePadFile(QUrl path)
{
    filePath = path.toLocalFile();
    fileName = path.fileName();
    group = GROUP_DEFAULT;
}

NotePadFile::~NotePadFile()
{

}

bool NotePadFile::GetContent(QString& output)
{
    QFile file(filePath);

    if(file.open(QIODevice::ReadOnly))
    {
        output = QString(file.readAll());
        file.close();
        return true;
    }
    return false;
}

bool NotePadFile::SaveContent(QString content, QUrl *saveTo)
{
    QString path = saveTo ? saveTo->toLocalFile() : filePath;

    QFile file(path);

    if(file.open(QIODevice::WriteOnly))
    {
        file.write(content.toStdString().c_str());
        return true;
    }
    return false;
}

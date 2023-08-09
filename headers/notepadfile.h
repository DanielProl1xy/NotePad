#ifndef NOTEPADFILE_H
#define NOTEPADFILE_H

#include <QFile>
#include <QUrl>

#define GROUP_DEFAULT "default"

class NotePadFile
{
public:
    NotePadFile(QUrl path);
    NotePadFile() { }
    ~NotePadFile();
public:
    bool GetContent(QString& content);
    bool SaveContent(QString content, QUrl *saveTo = nullptr);
    QString GetName() { return fileName; }
    QString GetPath() { return filePath; }

    bool operator==(const NotePadFile& other) const
    {
        return filePath == other.filePath;
    }

    void SetGroup(QString groupName) { group = groupName; }
    QString GetGroup() { return group; }
private:
    QString filePath;
    QString fileName;
    QString group;
};

#endif // NOTEPADFILE_H

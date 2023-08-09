#ifndef FILESTREEVIEW_H
#define FILESTREEVIEW_H

#include <QTreeView>
#include <QStandardItemModel>
#include "notepadfile.h"

#define DEFAULT_GROUP "default"

class FileTreeItem : public QStandardItem
{

public:
    FileTreeItem(NotePadFile *file);
    ~FileTreeItem();

public:
    NotePadFile *File;
};

class FilesTreeView : public QTreeView
{
    Q_OBJECT
public:
    FilesTreeView(QWidget *parent);
public:
    void AddFile(NotePadFile *fileNode);
    void RemoveFile(NotePadFile fileNode);
    bool ContainsFile(NotePadFile fileNode);
private:
    QStandardItemModel model;
    QVector<NotePadFile> storedFiles;
};

#endif // FILESTREEVIEW_H

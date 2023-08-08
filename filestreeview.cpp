#include "filestreeview.h"

FileTreeItem::FileTreeItem(NotePadFile *file)
    : QStandardItem(file->GetName())
{
    File = file;

}

FileTreeItem::~FileTreeItem()
{
    delete File;
}


FilesTreeView::FilesTreeView(QWidget *parent) : QTreeView(parent)
{
    this->setModel(&model);
}

void FilesTreeView::AddFile(NotePadFile* file)
{
    if(storedFiles.contains(*file))
    {
        return;
    }

    QStandardItem *rootItem = model.invisibleRootItem();
    FileTreeItem *fileItem = new FileTreeItem(file);
    rootItem->appendRow(fileItem);

    storedFiles.append(*file);
    return;

}

void FilesTreeView::RemoveFile(NotePadFile file)
{

}

bool FilesTreeView::ContainsFile(NotePadFile file)
{
    return storedFiles.contains(file);
}

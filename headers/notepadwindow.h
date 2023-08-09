#ifndef NOTEPADWINDOW_H
#define NOTEPADWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QTreeView>
#include <QGridLayout>
#include <QFileDialog>
#include <QUrl>
#include "notepadfile.h"
#include "closedialog.h"
#include "filestreeview.h"

QT_BEGIN_NAMESPACE
namespace Ui { class NotePadWindow; }
QT_END_NAMESPACE

#define NP_TITLE "NotePad"
#define NP_VERSION "0.1b"

class NotePadWindow : public QMainWindow
{
    Q_OBJECT

public:
    NotePadWindow(QWidget *parent = nullptr);
    ~NotePadWindow();

private:
    Ui::NotePadWindow *ui;
    QTextEdit *textEdit;
    FilesTreeView *filesView;
    QGridLayout *notePadLayout;
    QMenu *fileMenu;
    QAction *fileOpen;
    QAction *fileSave;
    QAction *fileClose;
    QAction *fileSaveAs;

private:
    NotePadFile *currentFile;
    bool fileOpened;

private:
    void initWidgets();
    void initMenuBar();
    void initActions();
    int showCloseDialog();
    void setCurrentFile(QUrl path);

private slots:
    void saveFile();
    void openFile();
    void closeFile();
    void saveFileAs();
};
#endif // NOTEPADWINDOW_H

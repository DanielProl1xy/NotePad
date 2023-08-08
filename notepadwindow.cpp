#include "notepadwindow.h"
#include "./ui_notepadwindow.h"

NotePadWindow::NotePadWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::NotePadWindow)
{
    ui->setupUi(this);
    initWidgets();
    initMenuBar();
    initActions();
    currentFile = new NotePadFile();
    fileOpened = false;

    QString title = tr("%1 : %2 ").arg(NP_TITLE, NP_VERSION);
    setWindowTitle(title);
}

NotePadWindow::~NotePadWindow()
{
    delete ui;
    delete textEdit;
    delete filesView;
    delete fileMenu;
    delete currentFile;
}

void NotePadWindow::initWidgets()
{
    QWidget *widget = new QWidget();
    setCentralWidget(widget);

    textEdit = new QTextEdit(widget);

    filesView = new FilesTreeView(widget);
    filesView->setMaximumWidth(180);

    notePadLayout = new QGridLayout(widget);
    notePadLayout->addWidget(textEdit, 0, 1);
    notePadLayout->addWidget(filesView, 0, 0);
}

void NotePadWindow::initMenuBar()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
}

void NotePadWindow::initActions()
{
    fileOpen = new QAction(tr("&Open"), this);
    fileSave = new QAction(tr("&Save"), this);
    fileSaveAs = new QAction(tr("&Save as..."), this);
    fileClose = new QAction(tr("&Close"), this);

    fileMenu->addAction(fileOpen);
    fileMenu->addAction(fileSave);
    fileMenu->addAction(fileClose);
    fileMenu->addAction(fileSaveAs);

    connect(fileOpen, &QAction::triggered, this, &NotePadWindow::openFile);
    connect(fileSave, &QAction::triggered, this, &NotePadWindow::saveFile);
    connect(fileClose, &QAction::triggered, this, &NotePadWindow::closeFile);
    connect(fileSaveAs, &QAction::triggered, this, &NotePadWindow::saveFileAs);
}

int NotePadWindow::showCloseDialog()
{
    CloseDialog *dlg = new CloseDialog(this);
    dlg->exec();
    int result = dlg->result();
    qDebug(std::to_string(result).c_str());
    switch (result)
    {
    case CloseDialogResult::Save:
        saveFile();
        return result;
    case CloseDialogResult::Skip:
        return result;
    case CloseDialogResult::Cancel:
        return result;
    default:
        return result;
    }
}

void NotePadWindow::setCurrentFile(QUrl path)
{
    currentFile = new NotePadFile(path);
    QString title = tr("%1 : %2 | file: %3").arg(NP_TITLE, NP_VERSION, currentFile->GetPath());
    setWindowTitle(title);
    QString content;
    fileOpened = currentFile->GetContent(content);
    if(fileOpened)
    {
        textEdit->setPlainText(content);
        filesView->AddFile(currentFile);
        return;
    }
    textEdit->setPlainText("");
}

void NotePadWindow::openFile()
{
    qDebug("Open action");

    if(fileOpened)
    {
        int result = showCloseDialog();
        if(result == CloseDialogResult::Cancel)
            return;
    }

    QUrl path = QFileDialog::getOpenFileUrl(this, tr("Open file"), QUrl(""), tr("all files ()"));

    qDebug(path.toLocalFile().toStdString().c_str());

    setCurrentFile(path);
}

void NotePadWindow::saveFile()
{
    qDebug("Save action");

    if(currentFile->SaveContent(textEdit->toPlainText()))
    {
        qDebug("Saved");
        return;
    }
    qDebug("Couldn't save");
}

void NotePadWindow::closeFile()
{
    qDebug("Close action");
    int result = showCloseDialog();
    if(result == CloseDialogResult::Cancel)
        return;
}

void NotePadWindow::saveFileAs()
{
    qDebug("file save as action");

    QUrl path = QFileDialog::getSaveFileUrl(this, tr("Save location"), QUrl(""), tr("all files (*)"));
    if(currentFile->SaveContent(textEdit->toPlainText(), &path))
    {
        qDebug("Saved");
        setCurrentFile(path);
        return;
    }
    qDebug("Couldn't save");
}


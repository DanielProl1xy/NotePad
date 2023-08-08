#ifndef CLOSEDIALOG_H
#define CLOSEDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QFormLayout>
#include <QGroupBox>


QT_BEGIN_NAMESPACE
namespace Ui { class CloseDialog; }
QT_END_NAMESPACE

enum CloseDialogResult
{
    Save = 0,
    Skip = 1,
    Cancel = 2
};

class CloseDialog : public QDialog
{
    Q_OBJECT
public:
    CloseDialog(QWidget *parent = nullptr);
    ~CloseDialog();

private:
    QFormLayout *formLayout;
    QPushButton *saveButton;
    QPushButton *skipButton;
    QPushButton *cancelButton;
    QLabel *infoLabel;

private:
    void initWidgets();
    void initActions();

private slots:
    void on_SaveButton();
    void on_SkipButton();
    void on_CancelButton();
};

#endif // CLOSEDIALOG_H

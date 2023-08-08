#include "closedialog.h"

CloseDialog::CloseDialog(QWidget *parent) : QDialog(parent)
{
    initWidgets();
    initActions();
}

CloseDialog::~CloseDialog()
{
    delete saveButton;
    delete skipButton;
    delete cancelButton;
    delete infoLabel;
}

void CloseDialog::initWidgets()
{
    saveButton = new QPushButton("Yes", this);
    skipButton = new QPushButton("No", this);
    cancelButton = new QPushButton("Cancel", this);
    infoLabel = new QLabel(this);
    infoLabel->setText("Would you like to save current file before closing it?");

    QGroupBox *buttonsBox = new QGroupBox(this);
    QHBoxLayout *buttonsLayout = new QHBoxLayout(buttonsBox);

    buttonsLayout->addWidget(saveButton);
    buttonsLayout->addWidget(skipButton);
    buttonsLayout->addWidget(cancelButton);

    formLayout = new QFormLayout(this);
    formLayout->addRow(infoLabel);
    formLayout->addRow(buttonsBox);
}

void CloseDialog::initActions()
{
    connect(saveButton, &QPushButton::clicked, this, &CloseDialog::on_SaveButton);
    connect(skipButton, &QPushButton::clicked, this, &CloseDialog::on_SkipButton);
    connect(cancelButton, &QPushButton::clicked, this, &CloseDialog::on_CancelButton);
}

void CloseDialog::on_SaveButton()
{
    done(CloseDialogResult::Save);
}

void CloseDialog::on_SkipButton()
{
    done(CloseDialogResult::Skip);
}

void CloseDialog::on_CancelButton()
{
    done(CloseDialogResult::Cancel);
}

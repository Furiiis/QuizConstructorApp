#include "form.h"
#include "ui_form.h"
#include <qpushbutton.h>
#include <qlistview.h>

Form::Form(QWidget *parent) :
    TestWindowForm(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    ui->verticalLayout->addWidget(new QPushButton(parent));
    ui->verticalLayout->addWidget(new QListView(parent));
}

Form::~Form()
{
    delete ui;
}

#include "sobre.h"
#include "ui_sobre.h"

Sobre::Sobre(QWidget *parent) : QWidget(parent), ui(new Ui::Sobre) {
    ui->setupUi(this);
    this->setWindowFlags(Qt::Dialog);
}

void Sobre::on_btn_ok_pressed() {
    this->close();
}

Sobre::~Sobre() {
    delete ui;
}

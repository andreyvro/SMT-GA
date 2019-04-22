/********************************************************************************
** Form generated from reading UI file 'sobre.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SOBRE_H
#define UI_SOBRE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Sobre
{
public:
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QFrame *line;
    QLabel *label_4;
    QLabel *label_5;
    QPushButton *btn_ok;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QFrame *line_2;
    QLabel *label_9;
    QLabel *label_10;

    void setupUi(QWidget *Sobre)
    {
        if (Sobre->objectName().isEmpty())
            Sobre->setObjectName(QStringLiteral("Sobre"));
        Sobre->setWindowModality(Qt::ApplicationModal);
        Sobre->resize(350, 230);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Sobre->sizePolicy().hasHeightForWidth());
        Sobre->setSizePolicy(sizePolicy);
        Sobre->setMinimumSize(QSize(0, 0));
        Sobre->setMaximumSize(QSize(400, 400));
        label = new QLabel(Sobre);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(0, 0, 351, 51));
        QFont font;
        font.setPointSize(18);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(Sobre);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(0, 30, 361, 51));
        QFont font1;
        font1.setPointSize(12);
        font1.setBold(true);
        font1.setWeight(75);
        label_2->setFont(font1);
        label_2->setAlignment(Qt::AlignCenter);
        label_3 = new QLabel(Sobre);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 90, 91, 16));
        QFont font2;
        font2.setPointSize(10);
        font2.setBold(true);
        font2.setWeight(75);
        label_3->setFont(font2);
        line = new QFrame(Sobre);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(10, 70, 331, 20));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        label_4 = new QLabel(Sobre);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(10, 110, 91, 16));
        label_4->setFont(font2);
        label_5 = new QLabel(Sobre);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(10, 130, 91, 16));
        label_5->setFont(font2);
        btn_ok = new QPushButton(Sobre);
        btn_ok->setObjectName(QStringLiteral("btn_ok"));
        btn_ok->setGeometry(QRect(130, 190, 91, 31));
        label_6 = new QLabel(Sobre);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(110, 90, 151, 16));
        QFont font3;
        font3.setPointSize(10);
        font3.setBold(false);
        font3.setWeight(50);
        label_6->setFont(font3);
        label_7 = new QLabel(Sobre);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(110, 110, 151, 16));
        label_7->setFont(font3);
        label_8 = new QLabel(Sobre);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(110, 130, 151, 16));
        label_8->setFont(font3);
        line_2 = new QFrame(Sobre);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setGeometry(QRect(10, 170, 331, 20));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);
        label_9 = new QLabel(Sobre);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(10, 150, 91, 16));
        label_9->setFont(font2);
        label_10 = new QLabel(Sobre);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(110, 150, 221, 16));
        label_10->setFont(font3);

        retranslateUi(Sobre);

        QMetaObject::connectSlotsByName(Sobre);
    } // setupUi

    void retranslateUi(QWidget *Sobre)
    {
        Sobre->setWindowTitle(QApplication::translate("Sobre", "Sobre", Q_NULLPTR));
        label->setText(QApplication::translate("Sobre", "Arvore M\303\255nima de Steiner", Q_NULLPTR));
        label_2->setText(QApplication::translate("Sobre", "Algoritmo Gen\303\251tico", Q_NULLPTR));
        label_3->setText(QApplication::translate("Sobre", "Aluno:", Q_NULLPTR));
        label_4->setText(QApplication::translate("Sobre", "Institui\303\247\303\243o:", Q_NULLPTR));
        label_5->setText(QApplication::translate("Sobre", "Ano:", Q_NULLPTR));
        btn_ok->setText(QApplication::translate("Sobre", "Ok", Q_NULLPTR));
        label_6->setText(QApplication::translate("Sobre", "Andrey de Oliveira", Q_NULLPTR));
        label_7->setText(QApplication::translate("Sobre", "UTFPR", Q_NULLPTR));
        label_8->setText(QApplication::translate("Sobre", "2017 / 2018", Q_NULLPTR));
        label_9->setText(QApplication::translate("Sobre", "E-mail:", Q_NULLPTR));
        label_10->setText(QApplication::translate("Sobre", "andreyvro@hotmail.com", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Sobre: public Ui_Sobre {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SOBRE_H

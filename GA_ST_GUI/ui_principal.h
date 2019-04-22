/********************************************************************************
** Form generated from reading UI file 'principal.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PRINCIPAL_H
#define UI_PRINCIPAL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_Principal
{
public:
    QAction *act_abrir_solucao;
    QAction *act_fechar;
    QAction *act_sobre;
    QWidget *centralWidget;
    QGroupBox *gb_grafo;
    QComboBox *cmb_grafo;
    QLabel *lbl_grafo;
    QCheckBox *chk_previsualizar;
    QLabel *label;
    QLabel *label_10;
    QLabel *lbl_qtd_vert;
    QLabel *lbl_mst;
    QLabel *lbl_smt;
    QLabel *lbl_qtd_ptst;
    QFrame *line_3;
    QLabel *lbl_reducao;
    QTabWidget *tb_solucao;
    QWidget *tab_grafo;
    QGraphicsView *grph_grafo;
    QWidget *tab_solucao;
    QLabel *label_11;
    QLabel *label_12;
    QLabel *label_13;
    QLabel *label_14;
    QLabel *label_15;
    QLabel *label_16;
    QLineEdit *txt_saida_grafo;
    QLineEdit *txt_saida_qtdInd;
    QLineEdit *txt_saida_muta;
    QLineEdit *txt_saida_cruza;
    QLineEdit *txt_saida_qtdGera;
    QLineEdit *txt_saida_fitness;
    QFrame *line;
    QLineEdit *txt_saida_semRnd;
    QLabel *saida_semRnd;
    QFrame *line_2;
    QLabel *label_17;
    QLabel *label_18;
    QLineEdit *txt_saida_qtdPtSt;
    QLabel *label_19;
    QCustomPlot *plt_grafico;
    QLineEdit *txt_saida_tempo;
    QLabel *label_20;
    QLineEdit *txt_saida_reducao;
    QLabel *label_21;
    QGroupBox *gb_ams;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QSpinBox *spn_ams_individuos;
    QDoubleSpinBox *spn_ams_cruzamento;
    QDoubleSpinBox *spn_ams_mutacao;
    QSpinBox *spn_ams_geracoes;
    QLabel *lbl_semente;
    QLineEdit *txt_random;
    QPushButton *btn_iniciar;
    QStatusBar *statusBar;
    QMenuBar *menuBar;
    QMenu *menuArquivo;
    QMenu *menuAjuda;

    void setupUi(QMainWindow *Principal)
    {
        if (Principal->objectName().isEmpty())
            Principal->setObjectName(QStringLiteral("Principal"));
        Principal->resize(1040, 720);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Principal->sizePolicy().hasHeightForWidth());
        Principal->setSizePolicy(sizePolicy);
        Principal->setMinimumSize(QSize(400, 285));
        Principal->setMaximumSize(QSize(1040, 720));
        act_abrir_solucao = new QAction(Principal);
        act_abrir_solucao->setObjectName(QStringLiteral("act_abrir_solucao"));
        act_fechar = new QAction(Principal);
        act_fechar->setObjectName(QStringLiteral("act_fechar"));
        act_sobre = new QAction(Principal);
        act_sobre->setObjectName(QStringLiteral("act_sobre"));
        centralWidget = new QWidget(Principal);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gb_grafo = new QGroupBox(centralWidget);
        gb_grafo->setObjectName(QStringLiteral("gb_grafo"));
        gb_grafo->setEnabled(true);
        gb_grafo->setGeometry(QRect(10, 10, 191, 261));
        gb_grafo->setCheckable(false);
        gb_grafo->setChecked(false);
        cmb_grafo = new QComboBox(gb_grafo);
        cmb_grafo->setObjectName(QStringLiteral("cmb_grafo"));
        cmb_grafo->setGeometry(QRect(10, 50, 171, 25));
        lbl_grafo = new QLabel(gb_grafo);
        lbl_grafo->setObjectName(QStringLiteral("lbl_grafo"));
        lbl_grafo->setGeometry(QRect(10, 30, 171, 17));
        chk_previsualizar = new QCheckBox(gb_grafo);
        chk_previsualizar->setObjectName(QStringLiteral("chk_previsualizar"));
        chk_previsualizar->setGeometry(QRect(10, 80, 171, 23));
        chk_previsualizar->setChecked(false);
        label = new QLabel(gb_grafo);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 110, 171, 17));
        QFont font;
        font.setPointSize(10);
        font.setBold(true);
        font.setUnderline(true);
        font.setWeight(75);
        label->setFont(font);
        label->setFrameShape(QFrame::NoFrame);
        label->setFrameShadow(QFrame::Plain);
        label_10 = new QLabel(gb_grafo);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(10, 150, 171, 17));
        QFont font1;
        font1.setBold(true);
        font1.setUnderline(true);
        font1.setWeight(75);
        label_10->setFont(font1);
        lbl_qtd_vert = new QLabel(gb_grafo);
        lbl_qtd_vert->setObjectName(QStringLiteral("lbl_qtd_vert"));
        lbl_qtd_vert->setGeometry(QRect(20, 130, 161, 17));
        QFont font2;
        font2.setPointSize(10);
        lbl_qtd_vert->setFont(font2);
        lbl_mst = new QLabel(gb_grafo);
        lbl_mst->setObjectName(QStringLiteral("lbl_mst"));
        lbl_mst->setGeometry(QRect(20, 190, 161, 17));
        lbl_mst->setFont(font2);
        lbl_smt = new QLabel(gb_grafo);
        lbl_smt->setObjectName(QStringLiteral("lbl_smt"));
        lbl_smt->setGeometry(QRect(20, 210, 161, 17));
        lbl_smt->setFont(font2);
        lbl_qtd_ptst = new QLabel(gb_grafo);
        lbl_qtd_ptst->setObjectName(QStringLiteral("lbl_qtd_ptst"));
        lbl_qtd_ptst->setGeometry(QRect(20, 170, 161, 17));
        lbl_qtd_ptst->setFont(font2);
        line_3 = new QFrame(gb_grafo);
        line_3->setObjectName(QStringLiteral("line_3"));
        line_3->setGeometry(QRect(10, 100, 171, 16));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);
        lbl_reducao = new QLabel(gb_grafo);
        lbl_reducao->setObjectName(QStringLiteral("lbl_reducao"));
        lbl_reducao->setGeometry(QRect(20, 230, 161, 17));
        lbl_reducao->setFont(font2);
        tb_solucao = new QTabWidget(centralWidget);
        tb_solucao->setObjectName(QStringLiteral("tb_solucao"));
        tb_solucao->setGeometry(QRect(210, 10, 821, 651));
        tab_grafo = new QWidget();
        tab_grafo->setObjectName(QStringLiteral("tab_grafo"));
        grph_grafo = new QGraphicsView(tab_grafo);
        grph_grafo->setObjectName(QStringLiteral("grph_grafo"));
        grph_grafo->setGeometry(QRect(10, 10, 800, 600));
        grph_grafo->setFrameShape(QFrame::StyledPanel);
        grph_grafo->setFrameShadow(QFrame::Sunken);
        grph_grafo->setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);
        grph_grafo->setInteractive(false);
        grph_grafo->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        tb_solucao->addTab(tab_grafo, QString());
        tab_solucao = new QWidget();
        tab_solucao->setObjectName(QStringLiteral("tab_solucao"));
        label_11 = new QLabel(tab_solucao);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(10, 30, 111, 17));
        label_12 = new QLabel(tab_solucao);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(10, 80, 111, 17));
        label_13 = new QLabel(tab_solucao);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(10, 130, 111, 17));
        label_14 = new QLabel(tab_solucao);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setGeometry(QRect(10, 180, 111, 17));
        label_15 = new QLabel(tab_solucao);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setGeometry(QRect(10, 230, 111, 17));
        label_16 = new QLabel(tab_solucao);
        label_16->setObjectName(QStringLiteral("label_16"));
        label_16->setGeometry(QRect(10, 420, 111, 17));
        QFont font3;
        font3.setBold(false);
        font3.setWeight(50);
        label_16->setFont(font3);
        txt_saida_grafo = new QLineEdit(tab_solucao);
        txt_saida_grafo->setObjectName(QStringLiteral("txt_saida_grafo"));
        txt_saida_grafo->setGeometry(QRect(10, 50, 111, 25));
        txt_saida_grafo->setReadOnly(true);
        txt_saida_qtdInd = new QLineEdit(tab_solucao);
        txt_saida_qtdInd->setObjectName(QStringLiteral("txt_saida_qtdInd"));
        txt_saida_qtdInd->setGeometry(QRect(10, 100, 111, 25));
        txt_saida_qtdInd->setReadOnly(true);
        txt_saida_muta = new QLineEdit(tab_solucao);
        txt_saida_muta->setObjectName(QStringLiteral("txt_saida_muta"));
        txt_saida_muta->setGeometry(QRect(10, 200, 111, 25));
        txt_saida_muta->setReadOnly(true);
        txt_saida_cruza = new QLineEdit(tab_solucao);
        txt_saida_cruza->setObjectName(QStringLiteral("txt_saida_cruza"));
        txt_saida_cruza->setGeometry(QRect(10, 150, 111, 25));
        txt_saida_cruza->setReadOnly(true);
        txt_saida_qtdGera = new QLineEdit(tab_solucao);
        txt_saida_qtdGera->setObjectName(QStringLiteral("txt_saida_qtdGera"));
        txt_saida_qtdGera->setGeometry(QRect(10, 250, 111, 25));
        txt_saida_qtdGera->setReadOnly(true);
        txt_saida_fitness = new QLineEdit(tab_solucao);
        txt_saida_fitness->setObjectName(QStringLiteral("txt_saida_fitness"));
        txt_saida_fitness->setGeometry(QRect(10, 440, 111, 25));
        txt_saida_fitness->setReadOnly(true);
        line = new QFrame(tab_solucao);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(120, 10, 20, 601));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);
        txt_saida_semRnd = new QLineEdit(tab_solucao);
        txt_saida_semRnd->setObjectName(QStringLiteral("txt_saida_semRnd"));
        txt_saida_semRnd->setGeometry(QRect(10, 300, 111, 25));
        txt_saida_semRnd->setReadOnly(true);
        saida_semRnd = new QLabel(tab_solucao);
        saida_semRnd->setObjectName(QStringLiteral("saida_semRnd"));
        saida_semRnd->setGeometry(QRect(10, 280, 111, 17));
        saida_semRnd->setFont(font3);
        line_2 = new QFrame(tab_solucao);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setGeometry(QRect(10, 330, 111, 20));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);
        label_17 = new QLabel(tab_solucao);
        label_17->setObjectName(QStringLiteral("label_17"));
        label_17->setGeometry(QRect(10, 10, 101, 17));
        label_17->setFont(font1);
        label_18 = new QLabel(tab_solucao);
        label_18->setObjectName(QStringLiteral("label_18"));
        label_18->setGeometry(QRect(10, 350, 111, 17));
        label_18->setFont(font1);
        txt_saida_qtdPtSt = new QLineEdit(tab_solucao);
        txt_saida_qtdPtSt->setObjectName(QStringLiteral("txt_saida_qtdPtSt"));
        txt_saida_qtdPtSt->setGeometry(QRect(10, 390, 111, 25));
        txt_saida_qtdPtSt->setReadOnly(false);
        label_19 = new QLabel(tab_solucao);
        label_19->setObjectName(QStringLiteral("label_19"));
        label_19->setGeometry(QRect(10, 370, 111, 17));
        label_19->setFont(font3);
        plt_grafico = new QCustomPlot(tab_solucao);
        plt_grafico->setObjectName(QStringLiteral("plt_grafico"));
        plt_grafico->setGeometry(QRect(140, 10, 671, 601));
        txt_saida_tempo = new QLineEdit(tab_solucao);
        txt_saida_tempo->setObjectName(QStringLiteral("txt_saida_tempo"));
        txt_saida_tempo->setGeometry(QRect(10, 540, 111, 25));
        txt_saida_tempo->setReadOnly(true);
        label_20 = new QLabel(tab_solucao);
        label_20->setObjectName(QStringLiteral("label_20"));
        label_20->setGeometry(QRect(10, 520, 111, 17));
        label_20->setFont(font3);
        txt_saida_reducao = new QLineEdit(tab_solucao);
        txt_saida_reducao->setObjectName(QStringLiteral("txt_saida_reducao"));
        txt_saida_reducao->setGeometry(QRect(10, 490, 111, 25));
        txt_saida_reducao->setReadOnly(true);
        label_21 = new QLabel(tab_solucao);
        label_21->setObjectName(QStringLiteral("label_21"));
        label_21->setGeometry(QRect(10, 470, 111, 17));
        label_21->setFont(font3);
        tb_solucao->addTab(tab_solucao, QString());
        gb_ams = new QGroupBox(centralWidget);
        gb_ams->setObjectName(QStringLiteral("gb_ams"));
        gb_ams->setEnabled(true);
        gb_ams->setGeometry(QRect(10, 280, 191, 381));
        label_6 = new QLabel(gb_ams);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(10, 30, 171, 17));
        label_7 = new QLabel(gb_ams);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(10, 80, 171, 17));
        label_8 = new QLabel(gb_ams);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(10, 130, 171, 17));
        label_9 = new QLabel(gb_ams);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(10, 180, 171, 17));
        spn_ams_individuos = new QSpinBox(gb_ams);
        spn_ams_individuos->setObjectName(QStringLiteral("spn_ams_individuos"));
        spn_ams_individuos->setGeometry(QRect(10, 50, 71, 26));
        spn_ams_individuos->setMinimum(2);
        spn_ams_individuos->setMaximum(9999);
        spn_ams_cruzamento = new QDoubleSpinBox(gb_ams);
        spn_ams_cruzamento->setObjectName(QStringLiteral("spn_ams_cruzamento"));
        spn_ams_cruzamento->setGeometry(QRect(10, 100, 81, 26));
        spn_ams_cruzamento->setMaximum(100);
        spn_ams_mutacao = new QDoubleSpinBox(gb_ams);
        spn_ams_mutacao->setObjectName(QStringLiteral("spn_ams_mutacao"));
        spn_ams_mutacao->setGeometry(QRect(10, 150, 81, 26));
        spn_ams_mutacao->setMaximum(100);
        spn_ams_geracoes = new QSpinBox(gb_ams);
        spn_ams_geracoes->setObjectName(QStringLiteral("spn_ams_geracoes"));
        spn_ams_geracoes->setGeometry(QRect(10, 200, 111, 26));
        spn_ams_geracoes->setMinimum(1);
        spn_ams_geracoes->setMaximum(900000);
        lbl_semente = new QLabel(gb_ams);
        lbl_semente->setObjectName(QStringLiteral("lbl_semente"));
        lbl_semente->setGeometry(QRect(10, 230, 171, 17));
        txt_random = new QLineEdit(gb_ams);
        txt_random->setObjectName(QStringLiteral("txt_random"));
        txt_random->setGeometry(QRect(10, 250, 171, 25));
        txt_random->setInputMethodHints(Qt::ImhDigitsOnly);
        txt_random->setMaxLength(11);
        btn_iniciar = new QPushButton(gb_ams);
        btn_iniciar->setObjectName(QStringLiteral("btn_iniciar"));
        btn_iniciar->setEnabled(false);
        btn_iniciar->setGeometry(QRect(10, 290, 171, 41));
        Principal->setCentralWidget(centralWidget);
        gb_ams->raise();
        gb_grafo->raise();
        tb_solucao->raise();
        statusBar = new QStatusBar(Principal);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        Principal->setStatusBar(statusBar);
        menuBar = new QMenuBar(Principal);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1040, 22));
        menuArquivo = new QMenu(menuBar);
        menuArquivo->setObjectName(QStringLiteral("menuArquivo"));
        menuAjuda = new QMenu(menuBar);
        menuAjuda->setObjectName(QStringLiteral("menuAjuda"));
        Principal->setMenuBar(menuBar);

        menuBar->addAction(menuArquivo->menuAction());
        menuBar->addAction(menuAjuda->menuAction());
        menuArquivo->addAction(act_abrir_solucao);
        menuArquivo->addSeparator();
        menuArquivo->addAction(act_fechar);
        menuAjuda->addAction(act_sobre);

        retranslateUi(Principal);

        tb_solucao->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Principal);
    } // setupUi

    void retranslateUi(QMainWindow *Principal)
    {
        Principal->setWindowTitle(QApplication::translate("Principal", "Arvore M\303\255nima de Steiner", nullptr));
        act_abrir_solucao->setText(QApplication::translate("Principal", "Abrir Solu\303\247\303\243o", nullptr));
        act_fechar->setText(QApplication::translate("Principal", "Fechar", nullptr));
        act_sobre->setText(QApplication::translate("Principal", "Sobre", nullptr));
        gb_grafo->setTitle(QApplication::translate("Principal", "Problema:", nullptr));
        lbl_grafo->setText(QApplication::translate("Principal", "Inst\303\242ncia:", nullptr));
        chk_previsualizar->setText(QApplication::translate("Principal", "Pr\303\251-visualizar", nullptr));
        label->setText(QApplication::translate("Principal", "Problema:", nullptr));
        label_10->setText(QApplication::translate("Principal", "Solu\303\247\303\243o:", nullptr));
        lbl_qtd_vert->setText(QApplication::translate("Principal", "Qtd. Pts. Fixos:", nullptr));
        lbl_mst->setText(QApplication::translate("Principal", "MST:", nullptr));
        lbl_smt->setText(QApplication::translate("Principal", "SMT:", nullptr));
        lbl_qtd_ptst->setText(QApplication::translate("Principal", "Qtd. Pts. Steiner:", nullptr));
        lbl_reducao->setText(QApplication::translate("Principal", "Redu\303\247\303\243o:", nullptr));
        tb_solucao->setTabText(tb_solucao->indexOf(tab_grafo), QApplication::translate("Principal", "Grafo", nullptr));
        label_11->setText(QApplication::translate("Principal", "Grafo:", nullptr));
        label_12->setText(QApplication::translate("Principal", "Qtd. Indiv\303\255duos:", nullptr));
        label_13->setText(QApplication::translate("Principal", "Cruzamento:", nullptr));
        label_14->setText(QApplication::translate("Principal", "Muta\303\247ao:", nullptr));
        label_15->setText(QApplication::translate("Principal", "Qtd. Gera\303\247\303\265es:", nullptr));
        label_16->setText(QApplication::translate("Principal", "Fitness:", nullptr));
        saida_semRnd->setText(QApplication::translate("Principal", "Semente Aleat.:", nullptr));
        label_17->setText(QApplication::translate("Principal", "Parametros:", nullptr));
        label_18->setText(QApplication::translate("Principal", "Solu\303\247\303\243o:", nullptr));
        label_19->setText(QApplication::translate("Principal", "Qtd. Pts. Steiner:", nullptr));
        label_20->setText(QApplication::translate("Principal", "Tempo de Exec.:", nullptr));
        label_21->setText(QApplication::translate("Principal", "% de Redu\303\247\303\243o:", nullptr));
        tb_solucao->setTabText(tb_solucao->indexOf(tab_solucao), QApplication::translate("Principal", "GA", nullptr));
        gb_ams->setTitle(QApplication::translate("Principal", "Algoritmo Genetico:", nullptr));
        label_6->setText(QApplication::translate("Principal", "Qtd. Indiv\303\255duos:", nullptr));
        label_7->setText(QApplication::translate("Principal", "Cruzamento (%):", nullptr));
        label_8->setText(QApplication::translate("Principal", "Muta\303\247\303\243o (%):", nullptr));
        label_9->setText(QApplication::translate("Principal", "Qtd. Gera\303\247\303\265es:", nullptr));
        lbl_semente->setText(QApplication::translate("Principal", "Semente Aleat\303\263ria:", nullptr));
        txt_random->setText(QString());
        btn_iniciar->setText(QApplication::translate("Principal", "Iniciar", nullptr));
        menuArquivo->setTitle(QApplication::translate("Principal", "Arquivo", nullptr));
        menuAjuda->setTitle(QApplication::translate("Principal", "Ajuda", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Principal: public Ui_Principal {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PRINCIPAL_H

#ifndef PRINCIPAL_H
#define PRINCIPAL_H

#include "sobre.h"

#include <QMainWindow>
#include <QSettings>
#include <QDir>
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QGraphicsScene>
#include <QProcess>
#include <QDateTime>
#include <QFileDialog>
#include <algorithm>
#include <iostream>

namespace Ui {
    class Principal;
}

class Principal : public QMainWindow {
    Q_OBJECT

    public:
        explicit Principal(QWidget *parent = 0);
        ~Principal();

private slots:
    void on_cmb_grafo_currentIndexChanged(const QString &arg1);

    void on_chk_previsualizar_stateChanged();

    void on_btn_iniciar_pressed();

    void on_txt_random_textChanged(const QString &arg1);

    void on_act_fechar_triggered();

    void on_act_sobre_triggered();

    void on_act_abrir_solucao_triggered();

private:
    Ui::Principal *ui;
    Sobre frmSobre;

    QString arqConfig;          // Endereço do arquivo de configuração
    QString arqProblemas;       // Endereço da pasta de problemas
    QString arqSolucoes;        // Endereço da pasta de solucoes
    QString arqPrograma;        // Endereço do programa que irá executar a operação
    QString arqSaida;           // Endereço da pasta de saída dos GAs
    QGraphicsScene *sena;       // Área de desenho

    struct Vertice {
        float x;
        float y;
    };

    QString grafoSel;               // Nome do Problema selecionado (combobox)

    // Dados do arquivo de grafo e solução
    float xMin, xMax, yMin, yMax;   // Limites do grafo (Esquerda, Direita, Superior, Inferior)
    unsigned int qtdVerticesGrafo, qtdPontosSteiner; // Qtd vertices do grafo e steiners da solução
    double solucao_mst, solucao_smt; // Fitness da solução

    QVector<Vertice> grafo;         // Grafo
    QVector<Vertice> solucao;       // Pontos Steiner da solução

    // Dados do arquivo de saída
    QString saidaDataset;                       // arquivo de grafo que foi utilizado
    float saidaTempo, saidaMuta, saidaCruza;    // Indice de mutação e cruzamento
    unsigned int saidaQtdIndi, saidaQtdGera;    // Qtd de individuos e gerações
    int saidaSemRnd;                            // Semente de gerador aleatório
    double saidaFitness;                         // Melhor Fitness da saida
    unsigned int saidaQtdPtSt;                  // Qtd de pontos steiner de saida
    QVector<Vertice> saidaPtSteiner;            // Pontos Steiner de saida
    QVector< QVector<bool> > saidaCromo;        // Matriz de adj de saida
    QVector<double> saidaExecucao;              // Execução de saida

    void carregarConfigs();
    void salvarConfigs();

    void listarArquivos();      // Carrega nome dos arquivos de grafos no ComboBox
    void carregarGrafo();
    void setLimiteXY();
    float reajustarPosicao(float valor, char xy);
    void desenharGrafo();
    bool carregarSaida(QString arqSel);
    void desenharSaida();
    void desenharGrafico();
};

#endif // PRINCIPAL_H

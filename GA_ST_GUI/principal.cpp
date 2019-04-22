#include "principal.h"
#include "ui_principal.h"

//std::cout << qPrintable(arqNome) << std::endl;

Principal::Principal(QWidget *parent) : QMainWindow(parent), ui(new Ui::Principal) {
    ui->setupUi(this);
    this->setFixedSize(width(), height());
    const QRect availableGeometry = QApplication::desktop()->availableGeometry(this);
    //resize(availableGeometry.width() / 3, availableGeometry.height() / 2);
    move((availableGeometry.width() - width()) / 2, (availableGeometry.height() - height()) / 2);

    sena = new QGraphicsScene(this);
    sena->setSceneRect(0, 0, ui->grph_grafo->width()-10, ui->grph_grafo->height()-10);
    ui->grph_grafo->setScene(sena);

    arqConfig = QDir::toNativeSeparators("config.ini");
    arqProblemas = QDir::toNativeSeparators("grafos/problemas/");
    arqSolucoes = QDir::toNativeSeparators("grafos/solucoes/");
    arqPrograma = QDir::toNativeSeparators(QCoreApplication::applicationDirPath() + "/GA_SMT_CORE");
    arqSaida = QDir::toNativeSeparators("saida/");
    carregarConfigs();
    listarArquivos();
    desenharGrafico();
}

void Principal::listarArquivos() {
    QDir dir(arqProblemas);
    dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    dir.setSorting(QDir::Size | QDir::Reversed);

    QFileInfoList lista = dir.entryInfoList();
    ui->cmb_grafo->addItem("");
    for (int i = 0; i < lista.size(); ++i) {
        QFileInfo fileInfo = lista.at(i);
        QString arqNome = fileInfo.fileName();
        ui->cmb_grafo->addItem(arqNome);
    }
}

void Principal::on_cmb_grafo_currentIndexChanged(const QString &arg1) {
    grafoSel = arg1;
    ui->btn_iniciar->setEnabled(false);
    carregarGrafo();
    if (grafoSel != "") { ui->btn_iniciar->setEnabled(true); }
    desenharGrafo();
}

void Principal::on_chk_previsualizar_stateChanged() {
    desenharGrafo();
}

void Principal::carregarGrafo() {
    grafo.clear();
    solucao.clear();

    // Problema
    QFile arq1(arqProblemas + grafoSel);
    if (!arq1.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qtdVerticesGrafo = solucao_smt = solucao_mst = qtdPontosSteiner = 0;
    } else {
        QTextStream texto1(&arq1);

        QString linha = texto1.readLine();     // 1° Linha - Qtd de vértices
        qtdVerticesGrafo = linha.toInt();

        while (!texto1.atEnd()) {
            linha = texto1.readLine();
            QStringList lstLinha = linha.split(" ");
            QString x = lstLinha.at(0);
            QString y = lstLinha.at(1);
            Vertice vert = {x.toFloat(), y.toFloat()};
            grafo.append(vert);
        }
        arq1.close();
    }

    // Solucao
    QFile arq2(arqSolucoes + grafoSel);
    if (!arq2.open(QIODevice::ReadOnly | QIODevice::Text)) {
            solucao_smt = solucao_mst = qtdPontosSteiner = 0;
    } else {
        QTextStream texto2(&arq2);

        QString linha = texto2.readLine();     // 1° Linha - SMT
        solucao_smt = linha.toDouble();

        linha = texto2.readLine();     // 2° Linha - MST
        solucao_mst = linha.toDouble();

        linha = texto2.readLine();     // 3° Linha - Qtd. Pontos Steiner
        qtdPontosSteiner = linha.toInt();

        while (!texto2.atEnd()) {
            linha = texto2.readLine();
            QStringList lstLinha = linha.split(" ");
            QString x = lstLinha.at(0);
            QString y = lstLinha.at(1);
            Vertice vert = {x.toFloat(), y.toFloat()};
            solucao.append(vert);
        }
        arq2.close();
    }
    setLimiteXY();

    QString qtdVert = (qtdVerticesGrafo == 0) ? "?" : QString::number(qtdVerticesGrafo);
    ui->lbl_qtd_vert->setText("Qtd. Pts. Fixos: " + qtdVert);
    QString qtdPtSt = (qtdPontosSteiner == 0) ? "?" : QString::number(qtdPontosSteiner);
    ui->lbl_qtd_ptst->setText("Qtd. Pts. Steiner: " + qtdPtSt);
    QString solSmt = (solucao_smt == 0) ? "?" : QString::number(solucao_smt, 'f', 9);
    ui->lbl_smt->setText("SMT: " + solSmt);
    QString solMst = (solucao_mst == 0) ? "?" : QString::number(solucao_mst, 'f', 9);
    ui->lbl_mst->setText("MST: " + solMst);
    QString solreducao = (solucao_mst == 0) ? "?" : QString::number(((solucao_mst - solucao_smt) * 100) / solucao_mst) + "%";
    ui->lbl_reducao->setText("Redução: " + solreducao);
}

void Principal::setLimiteXY() {
    unsigned int tam = grafo.size();
    if (grafoSel == "" || tam == 0) {
        xMin = xMax = yMin = yMax = 0;
    } else {
        xMin = xMax = grafo.at(0).x;
        yMin = yMax = grafo.at(0).y;
        for (unsigned int i = 1; i < tam; i++) {
            float x = grafo.at(i).x;
            float y = grafo.at(i).y;
            if (x < xMin) {
                xMin = x;			// Margem Esquerda
            } else if (x > xMax) {
                xMax = x;			// Margem Direita
            }
            if (y < yMin) {
                yMin = y;			// Margem Superior
            } else if (y > yMax) {
                yMax = y;			// Margem Inferior
            }
        }
    }
}

float Principal::reajustarPosicao(float valor, char xy) {
    float valorMin, valorMax, valorJanela;
    if (xy == 'x') {
        valorMin = xMin;
        valorMax = xMax;
        valorJanela = sena->width() - 20;
    } else {
        valorMin = yMin;
        valorMax = yMax;
        valorJanela = sena->height() - 20;
    }
    float ret = valor - valorMin;                      // Faz escala começar em zero
    ret = round((ret * valorJanela) / valorMax) + 10;  // Reajusta escala para tela
    return ret;
}

void Principal::desenharGrafo() {
    sena->clear();
    if (ui->chk_previsualizar->isChecked()) {
        QPen semBorda(Qt::NoPen);
        QPen canetaPreto(Qt::black);
        canetaPreto.setWidth(2);
        QBrush verde(Qt::green);
        QBrush amarelo(QColor(255, 255, 0, 100));
        QBrush vermelho(Qt::red);

        // Desenha Grafo
        unsigned int tam = grafo.size();
        for (unsigned int i = 0; i < tam; i++) {
            float x = reajustarPosicao(grafo.at(i).x, 'x');
            float y = reajustarPosicao(grafo.at(i).y, 'y');
            sena->addEllipse(x-4, y-4, 8, 8, canetaPreto, verde);
            QGraphicsTextItem *texto = sena->addText(QString::number(i), QFont("Arial", 9));
            texto->setPos(x, y);
            texto->setDefaultTextColor(Qt::green);
        }

        // Desenha pontos Steiner da Solução
        tam = solucao.size();
        for (unsigned int i = 0; i < tam; i++) {
            float x = reajustarPosicao(solucao.at(i).x, 'x');
            float y = reajustarPosicao(solucao.at(i).y, 'y');
            sena->addEllipse(x-12, y-12, 24, 24, semBorda, amarelo);
            sena->addEllipse(x-2, y-2, 4, 4, canetaPreto, vermelho);
        }
    }
}

bool Principal::carregarSaida(QString arqSel) {
    saidaPtSteiner.clear();
    saidaCromo.clear();
    saidaExecucao.clear();

    QFile arq(arqSel);
    bool retorno = true;
    if (!arq.open(QIODevice::ReadOnly | QIODevice::Text)) {
        saidaDataset = "";
        saidaTempo = saidaQtdIndi = saidaMuta = saidaCruza = saidaQtdGera = saidaSemRnd = saidaFitness = saidaQtdPtSt = 0;
        std::cout << "Não foi possivel abrir arquivo de saida!" << std::endl;
        retorno = false;
    } else {
        QTextStream texto(&arq);

        QString linha = texto.readLine();       // 1° - Nome do arquivo de grafo
        QFileInfo arquivo(linha);
        saidaDataset = arquivo.fileName();

        if (grafoSel != saidaDataset) {
            // Seleciona Dataset correto no combobox
            int index = ui->cmb_grafo->findText(saidaDataset);
            if (index != -1) {
                ui->cmb_grafo->setCurrentIndex(index);
            } else {
                std::cout << "Carregue o grafo \"" << qPrintable(saidaDataset) << "\" e tente carregar a solução novamente."<< std::endl;
                arq.close();
                return false;
            }

        }
        linha = texto.readLine();               // 2° - Tempo de execução
        saidaTempo = linha.toFloat();
        linha = texto.readLine();               // 2° - qtdInd, indMut, indCruz, qtdGer, sementeRnd
        QStringList lstLinha = linha.split(" ");
        QString txt = lstLinha.at(0);   saidaQtdIndi = txt.toInt();
        txt = lstLinha.at(1);           saidaCruza = txt.toFloat();
        txt = lstLinha.at(2);           saidaMuta = txt.toFloat();
        txt = lstLinha.at(3);           saidaQtdGera = txt.toInt();
        txt = lstLinha.at(4);           saidaSemRnd = txt.toInt();
        linha = texto.readLine();               // 3° - Fitness
        saidaFitness = linha.toDouble();
        linha = texto.readLine();               // 4° - Qtd de pontos Steiner
        saidaQtdPtSt = linha.toInt();
        for (unsigned int i = 0; i < saidaQtdPtSt; i++) {
            linha = texto.readLine();           // 5° - Pontos Steiner
            QStringList lstLinha = linha.split(" ");
            QString x = lstLinha.at(0);
            QString y = lstLinha.at(1);
            Vertice vert = {x.toFloat(), y.toFloat()};
            saidaPtSteiner.append(vert);
        }
        linha = texto.readLine();               // 6º - tamanho do cromossomo
        unsigned int tamCrom = linha.toInt();
        saidaCromo.resize(tamCrom);
        for (unsigned int i = 0; i < tamCrom; i++) {
            saidaCromo[i].resize(tamCrom);
        }
        for (unsigned int i = 0; i < tamCrom-1; i++) {
            linha = texto.readLine();           // 7° - Cromossomo
            unsigned int k = 0;
            for (unsigned int j = i + 1; j < tamCrom; j++) {
                QString gene = linha.at(k);
                bool geneBool = gene.toInt();
                saidaCromo[i][j] = geneBool;
                saidaCromo[j][i] = geneBool;
                k++;
            }
        }
        while (!texto.atEnd()) {
            linha = texto.readLine();           // 8° - Execução
            saidaExecucao.append(linha.toFloat());
        }
        arq.close();
    }

    ui->txt_saida_grafo->setText(saidaDataset);
    ui->txt_saida_qtdInd->setText(QString::number(saidaQtdIndi));
    ui->txt_saida_cruza->setText(QString::number(saidaCruza) + "%");
    ui->txt_saida_muta->setText(QString::number(saidaMuta) + "%");
    ui->txt_saida_qtdGera->setText(QString::number(saidaQtdGera));
    ui->txt_saida_semRnd->setText(QString::number(saidaSemRnd));
    ui->txt_saida_qtdPtSt->setText(QString::number(saidaQtdPtSt));
    ui->txt_saida_fitness->setText(QString::number(saidaFitness, 'f', 9));
    ui->txt_saida_tempo->setText(QString::number(saidaTempo));
    QString reducao = (solucao_mst == 0) ? "?" : QString::number(((solucao_mst - saidaFitness) * 100) / solucao_mst) + "%";
    ui->txt_saida_reducao->setText(reducao);

    return retorno;
}

void Principal::desenharSaida() {
    if (ui->chk_previsualizar->isChecked()) {
        desenharGrafo();
        QPen canetaPreto(Qt::black);
        canetaPreto.setWidth(2);
        QBrush vermelho(Qt::red);

        // Desenha pontos Steiner
        unsigned int tam = saidaPtSteiner.size();
        for (unsigned int i = 0; i < tam; i++) {
            float x = reajustarPosicao(saidaPtSteiner.at(i).x, 'x');
            float y = reajustarPosicao(saidaPtSteiner.at(i).y, 'y');
            sena->addEllipse(x-3, y-3, 6, 6, canetaPreto, vermelho);
            QGraphicsTextItem *texto = sena->addText(QString::number(qtdVerticesGrafo + i), QFont("Arial", 9));
            texto->setPos(x-18, y-18);
            texto->setDefaultTextColor(Qt::red);
        }

        // Printa o cromossomo
        /*std::cout << std::endl;
        tam = saidaCromo.size();
        for (unsigned int i = 0; i < tam; i ++) {
            for (unsigned int j = 0; j < tam; j ++) {
                std::cout << saidaCromo[i][j] << " ";
            }
            std::cout << std::endl;
        }*/

        // Desenha vértices
        tam = saidaCromo.size();
        for (unsigned int i = 0; i < tam-1; i++) {
            for (unsigned int j = i + 1; j < tam; j++) {
                if (saidaCromo[i][j] == 1) {
                    float Ax, Ay, Bx, By;
                    if (i < qtdVerticesGrafo) {                     // Vertice do grafo
                        Ax = reajustarPosicao(grafo.at(i).x, 'x');
                        Ay = reajustarPosicao(grafo.at(i).y, 'y');
                    } else {                                        // Vértice do ponto steiner
                        Ax = reajustarPosicao(saidaPtSteiner.at(i - qtdVerticesGrafo).x, 'x');
                        Ay = reajustarPosicao(saidaPtSteiner.at(i - qtdVerticesGrafo).y, 'y');
                    }
                    if (j < qtdVerticesGrafo) {                     // Vertice do grafo
                        Bx = reajustarPosicao(grafo.at(j).x, 'x');
                        By = reajustarPosicao(grafo.at(j).y, 'y');
                    } else {                                        // Vértice do ponto steiner
                        Bx = reajustarPosicao(saidaPtSteiner.at(j - qtdVerticesGrafo).x, 'x');
                        By = reajustarPosicao(saidaPtSteiner.at(j - qtdVerticesGrafo).y, 'y');
                    }
                    sena->addLine(Ax, Ay, Bx, By, canetaPreto);
                }
            }
        }
    }
}

void Principal::desenharGrafico() {
    // generate some data:
    QVector<double> geracao;
    unsigned int tam = saidaExecucao.size();
    for (unsigned int i = 1; i <= tam; i++) {
      geracao.append(i);
    }
    // create graph and assign data to it:
    ui->plt_grafico->addGraph();
    ui->plt_grafico->graph(0)->setData(geracao, saidaExecucao);
    // give the axes some labels:
    ui->plt_grafico->xAxis->setLabel("Geração");
    ui->plt_grafico->yAxis->setLabel("Fitness");
    // set axes ranges, so we see all data:
    ui->plt_grafico->xAxis->setRange(1, tam);
    double min = *std::min_element(saidaExecucao.constBegin(), saidaExecucao.constEnd());
    double max = *std::max_element(saidaExecucao.constBegin(), saidaExecucao.constEnd());
    float margem = ((max-min) * 10) / 100;  // 10 % de margem
    ui->plt_grafico->yAxis->setRange(min - margem, max + margem);
    ui->plt_grafico->replot();
}

void Principal::on_btn_iniciar_pressed() {
    // Parametros
    QString arqGrafo = arqProblemas + grafoSel;

    QString amsIndi = QString::number(ui->spn_ams_individuos->value());
    QString amsCruz = QString::number(ui->spn_ams_cruzamento->value());
    QString amsMuta = QString::number(ui->spn_ams_mutacao->value());
    QString amsGera = QString::number(ui->spn_ams_geracoes->value());
    QString semeRnd = ui->txt_random->text();

    QDateTime agora = QDateTime::currentDateTime();
    QString dataHora = agora.toString("dd-MM-yyyy_hh:mm:ss");
    QString amsArqSaida = arqSaida + dataHora + ".ams.txt";

    QStringList argumentos;
    argumentos << arqGrafo << amsIndi << amsCruz << amsMuta << amsGera << QString::number(solucao_smt, 'f', 9) << amsArqSaida;
    if (semeRnd != "") { argumentos << semeRnd; }

    // Inicia Processo
    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

    QProcess *processo = new QProcess(this);
    processo->start(arqPrograma, argumentos);
    processo->waitForFinished(-1);
    //std::cout << qPrintable(processo->readAllStandardOutput()) << std::endl;

    if (carregarSaida(amsArqSaida)) {
        desenharSaida();
        desenharGrafico();
    }

    QApplication::setOverrideCursor(QCursor(Qt::ArrowCursor));
}

void Principal::on_act_abrir_solucao_triggered() {
    QString arqNome = QFileDialog::getOpenFileName(this, "Selecione um Arquivo.", arqSaida);
    if (arqNome != "") {
        if (carregarSaida(arqNome)) {
            desenharSaida();
            desenharGrafico();
        }
    }
}

void Principal::carregarConfigs() {
    QSettings config(arqConfig, QSettings::NativeFormat);

    bool previzualizar = config.value("preVisu", false).toBool();
    ui->chk_previsualizar->blockSignals(true);
    ui->chk_previsualizar->setChecked(previzualizar);
    ui->chk_previsualizar->blockSignals(false);

    unsigned int amsIndividuos = config.value("amsIndi", 2).toInt();
    ui->spn_ams_individuos->setValue(amsIndividuos);
    float amsCruzamento = config.value("amsCruz", 100).toFloat();
    ui->spn_ams_cruzamento->setValue(amsCruzamento);
    float amsMutacao = config.value("amsMuta", 100).toFloat();
    ui->spn_ams_mutacao->setValue(amsMutacao);
    unsigned int amsGeracoes = config.value("amsGera", 1000).toInt();
    ui->spn_ams_geracoes->setValue(amsGeracoes);
    QString sementeRnd = config.value("semeRnd", "").toString();
    ui->txt_random->setText(sementeRnd);
}

void Principal::salvarConfigs() {
    QSettings config(arqConfig, QSettings::NativeFormat);

    bool previzualizar = ui->chk_previsualizar->isChecked();
    config.setValue("preVisu", previzualizar);

    unsigned int amsIndividuos = ui->spn_ams_individuos->value();
    config.setValue("amsIndi", amsIndividuos);
    float amsCruzamento = ui->spn_ams_cruzamento->value();
    config.setValue("amsCruz", amsCruzamento);
    float amsMutacao = ui->spn_ams_mutacao->value();
    config.setValue("amsMuta", amsMutacao);
    unsigned int amsGeracoes = ui->spn_ams_geracoes->value();
    config.setValue("amsGera", amsGeracoes);
    QString sementeRnd = ui->txt_random->text();
    config.setValue("semeRnd", sementeRnd);
}

void Principal::on_txt_random_textChanged(const QString &arg1) {
    if ((arg1 != "") && (arg1 != "-")) {
        ui->txt_random->setText(QString::number(arg1.toInt()));
    }
}

void Principal::on_act_fechar_triggered() {
    QApplication::quit();
}

void Principal::on_act_sobre_triggered() {
    frmSobre.show();
}

Principal::~Principal() {
    salvarConfigs();
    delete ui;
}



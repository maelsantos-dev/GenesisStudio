#include "MainWindow.h"
#include "ModuleWidget.h"
#include "SignalCanvas.h"
#include "AmpKnob.h"


#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QFrame>
#include <QSplitter>
#include <QDial> 


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Genesis Studio");
    resize(1200, 700);

    // =========================================================
    // CENTRAL WIDGET
    // =========================================================

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    // =========================================================
    // TOP BAR
    // =========================================================

    QFrame *topBar = new QFrame();
    topBar->setObjectName("topBar");
    topBar->setFixedHeight(52);

    QHBoxLayout *topLayout = new QHBoxLayout(topBar);
    topLayout->setContentsMargins(20, 0, 20, 0);

    QLabel *logo = new QLabel("GENESIS STUDIO");
    logo->setObjectName("logo");

    QLabel *workspace = new QLabel("WORKSPACE");
    QLabel *presets = new QLabel("PRESETS");
    QLabel *irManager = new QLabel("IR MANAGER");
    QLabel *dataManager = new QLabel("DATA MANAGER");
    QLabel *settings = new QLabel("SETTINGS");

    topLayout->addWidget(logo);
    topLayout->addStretch();

    topLayout->addWidget(workspace);
    topLayout->addSpacing(24);
    topLayout->addWidget(presets);
    topLayout->addSpacing(24);
    topLayout->addWidget(irManager);
    topLayout->addSpacing(24);
    topLayout->addWidget(dataManager);
    topLayout->addSpacing(24);
    topLayout->addWidget(settings);

    mainLayout->addWidget(topBar);

    // =========================================================
    // MAIN AREA
    // =========================================================

    QSplitter *contentSplitter = new QSplitter(Qt::Horizontal);
    contentSplitter->setChildrenCollapsible(false);

    // ---------------------------------------------------------
    // BROWSER
    // ---------------------------------------------------------

    QFrame *browserPanel = new QFrame();
    browserPanel->setObjectName("browserPanel");
    browserPanel->setMinimumWidth(160);

    QVBoxLayout *browserLayout = new QVBoxLayout(browserPanel);
    browserLayout->setContentsMargins(18, 18, 18, 18);

    QLabel *browserTitle = new QLabel("BROWSER");
    browserTitle->setObjectName("panelTitle");

    browserLayout->addWidget(browserTitle);
    browserLayout->addStretch();

    // ---------------------------------------------------------
    // WORKSPACE
    // ---------------------------------------------------------

    QFrame *workspacePanel = new QFrame();
    workspacePanel->setObjectName("workspacePanel");
    workspacePanel->setMinimumWidth(400);

    QVBoxLayout *workspaceLayout = new QVBoxLayout(workspacePanel);
    workspaceLayout->setContentsMargins(20, 18, 20, 18);

    // ===========================================================
    // WORKSPACE CONTENT
    // ===========================================================

    // QSplitter *workspaceSplitter = 
       // new QSplitter(Qt::Vertical, workspacePanel);
    
    // workspaceSplitter->setChildrenCollapsible(false);
    

    // ============================================================
    // SIGNAL CANVAS
    // ============================================================

    SignalCanvas *signalCanvas =
       new SignalCanvas(workspacePanel);

    signalCanvas->setMinimumHeight(160);

    // ============================================================
    // AMP VISUAL AREA / ÁREA VISUAL DO AMPLIFICADOR
    // ============================================================

    QFrame *ampPanel =
       new QFrame(workspacePanel);

    ampPanel->setObjectName("ampPanel");
    // ALTURA FIXA DO AMP
    ampPanel->setMinimumHeight(320);
    ampPanel->setMaximumHeight(320);

    QVBoxLayout *ampLayout = new QVBoxLayout(ampPanel);
    ampLayout->setContentsMargins(20, 12, 20, 12);
    ampLayout->setSpacing(0);

    // ==============================================================================
    // AMP VISUAL and AMP PARAMETER OF AMP / VISUAL E CONTROLE DE PARÂMENTROS DO AMP
    // ==============================================================================
    
    QFrame *ampVisual = new QFrame(ampPanel);
    ampVisual->setObjectName("ampVisual");

    QVBoxLayout *ampVisualLayout = new QVBoxLayout(ampVisual);
    ampVisualLayout->setContentsMargins(24, 18, 24, 18);
    ampVisualLayout->setSpacing(16);
    
    
    // -------------------------------------------------------------------------------
    // Nome do Amplificador
    // -------------------------------------------------------------------------------

    QLabel *ampName = new QLabel("GENESIS LEAD 100");
    ampName->setObjectName("ampName");
    ampName->setAlignment(Qt::AlignCenter);

    ampVisualLayout->addWidget(ampName);

    // --------------------------------------------------------------------------------
    // Controles
    // --------------------------------------------------------------------------------

    QHBoxLayout *ampControls = new QHBoxLayout();
    ampControls->setSpacing(22);

    QStringList controlNames = {
        "GAIN",
        "BASS",
        "MID",
        "TREBLE",
        "PRESENCE",
        "MASTER"
    };

    for (const QString &name : controlNames)
    {
        QVBoxLayout *controlLayout = new QVBoxLayout();
        controlLayout->setSpacing(5);

        QLabel *label = new QLabel(name);
        label->setObjectName("ampControlLabel");
        label->setAlignment(Qt::AlignCenter);

        AmpKnob *dial = new AmpKnob();
        dial->setValue(50);
        dial->setObjectName("ampDial");

        QLabel *value = new QLabel("5.0");
        value->setObjectName("ampControlValue");
        value->setAlignment(Qt::AlignCenter);

        connect(dial, &AmpKnob::valueChanged, value,
                [value](int v)
                {
                    value->setText(QString::number(v / 10.0, 'f', 1));
                });

        controlLayout->addWidget(label);
        controlLayout->addWidget(dial, 0, Qt::AlignCenter);
        controlLayout->addWidget(value);

        ampControls->addLayout(controlLayout);
    }

    ampVisualLayout->addLayout(ampControls);

    // ----------------------------------------------------------------------------
    // Estilo Visual do Amplificador
    // ----------------------------------------------------------------------------

ampVisual->setStyleSheet(R"(
        #ampVisual {
            background-color: #202631;
            border: 1px solid #3b4657;
            border-radius: 10px;
        }

        #ampName {
            color: #f1f4f8;
            font-size: 16px;
            font-weight: bold;
            letter-spacing: 1px;
            padding: 4px;
        }

        #ampControlLabel {
            color: #8995a6;
            font-size: 9px;
            font-weight: bold;
        }

        #ampControlValue {
            color: #dce3eb;
            font-size: 10px;
            font-weight: bold;
        }

        #ampDial {
            background-color: #303946;
            border: 2px solid #566274;
            border-radius: 29px;
        }

        #ampDial:hover {
            background-color: #374250;
            border: 2px solid #708097;
        }
    )");

    // Adiciona o AMP ao Painel
    ampLayout->addWidget(ampVisual);

    // ============================================================
    // WORKSPACE LAYOUT
    // ============================================================

    workspaceLayout->addWidget(signalCanvas, 1);
    workspaceLayout->addWidget(ampPanel, 0);

        

    // ---------------------------------------------------------
    // INSPECTOR
    // ---------------------------------------------------------

    QFrame *inspectorPanel = new QFrame();
    inspectorPanel->setObjectName("inspectorPanel");
    inspectorPanel->setMinimumWidth(180);

    QVBoxLayout *inspectorLayout = new QVBoxLayout(inspectorPanel);
    inspectorLayout->setContentsMargins(18, 18, 18, 18);

    QLabel *inspectorTitle = new QLabel("INSPECTOR");
    inspectorTitle->setObjectName("panelTitle");

    inspectorLayout->addWidget(inspectorTitle);
    inspectorLayout->addStretch();

    // ---------------------------------------------------------
    // ADD PANELS
    // ---------------------------------------------------------

    contentSplitter->addWidget(browserPanel);
    contentSplitter->addWidget(workspacePanel);
    contentSplitter->addWidget(inspectorPanel);

    contentSplitter->setSizes({220, 680, 280});

    mainLayout->addWidget(contentSplitter);

    // =========================================================
    // GENESIS STUDIO STYLE
    // =========================================================

    setStyleSheet(R"(
        QMainWindow {
            background-color: #17191d;
        }

        QWidget {
            background-color: #17191d;
            color: #eeeeee;
            font-family: "Sans";
        }

        #topBar {
            background-color: #202328;
            border-bottom: 1px solid #30343b;
        }

        #logo {
            background-color: transparent;
            color: #ffffff;
            font-size: 14px;
            font-weight: bold;
        }

        #topBar QLabel {
            background-color: transparent;
            color: #aeb4bd;
            font-size: 11px;
            font-weight: bold;
        }

        #topBar QLabel:hover {
            color: #ffffff;
        }

        #browserPanel {
            background-color: #1c1f24;
            border-right: 1px solid #30343b;
        }

        #workspacePanel {
            background-color: #202328;
        }

        #ampPanel{
            background-color: #17191d;
            border: 1px solid #30343b;
            border-radius: 4px;
        }

        #ampImage {
            background-color: #202338;
            color: #6e69ed;
            border: 1px solid #30343b;
            border-radius: 3px;
            font-size: 18px;
            font-weight: bold;
        }

        #ampVisual {
            background-color: #17191d;
            border: 1px solid #30343b;
            border-radius: 4px;
        }

        #ampName {
            color: #eeeeee;
            font-size: 16px;
            font-weight: bold;
            letter-spacing: 1px;
        }

        #ampVisual QLabel {
            color: #aeb4bd;
            font-size: 10px;
            font-weight: bold;
        }

        #ampVisual QDial {
            background-color: #19191d;
            border: 2px solid #30343b;
            border-radius: 26px;
            padding: 4px;
        }
            
        #ampVisual QDial:hover {
            border: 2px solid #6e69ed;
        }

        #inspectorPanel {
            background-color: #1c1f24;
            border-left: 1px solid #30343b;
        }

        #panelTitle {
            color: #e6e9ed;
            font-size: 12px;
            font-weight: bold;
        }

    )");
}
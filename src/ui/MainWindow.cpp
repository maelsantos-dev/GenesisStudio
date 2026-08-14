#include "MainWindow.h"
#include "ModuleWidget.h"
#include "SignalCanvas.h"

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QFrame>
#include <QSplitter>


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

    // SIGNAL CANVAS
    SignalCanvas *signalCanvas =
       new SignalCanvas(workspacePanel);
    
    workspaceLayout->addWidget(signalCanvas);    

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
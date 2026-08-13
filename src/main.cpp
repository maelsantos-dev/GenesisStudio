#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QSplitter>



int main(int argc, char *argv[])
{
   QApplication app(argc, argv);

   QMainWindow window;
   window.setWindowTitle("Genesis Studio");
   window.resize(1200, 700);

   QWidget *centralWidget = new QWidget();
   window.setCentralWidget(centralWidget);

   QVBoxLayout *layout = new QVBoxLayout();
   layout->setContentsMargins(0, 0, 0, 0);
   layout->setSpacing(0);
   
   QHBoxLayout *topBar = new QHBoxLayout();

   QLabel *logo = new QLabel("GENESIS STUDIO");

   QPushButton *workspace = new QPushButton("WORKSPACE");
   QPushButton *presets = new QPushButton("PRESETS");
   QPushButton *irManager = new QPushButton("IR MANAGER");
   QPushButton *dataManager = new QPushButton("DATA MANAGER");
   QPushButton *settings = new QPushButton("SETTINGS");

   topBar->addWidget(logo);
   topBar->addStretch();
   topBar->addWidget(workspace);
   topBar->addWidget(presets);
   topBar->addWidget(irManager);
   topBar->addWidget(dataManager);
   topBar->addWidget(settings);

   topBar->setContentsMargins(20,10,20,10);
   
   layout->addLayout(topBar);

   QSplitter *splitter = new QSplitter(Qt::Horizontal);

   QWidget *browserPanel = new QWidget();
   QWidget *workspacePanel = new QWidget();
   QWidget *inspectorPanel = new QWidget();

   QLabel *browserTitle = new QLabel("BROWSER");
   QLabel *workspaceTitle = new QLabel("WORKSPACE");
   QLabel *inspectorTitle = new QLabel("INSPECTOR");

   splitter->addWidget(browserPanel);
   splitter->addWidget(workspacePanel);
   splitter->addWidget(inspectorPanel);

   splitter->setSizes({220, 760, 280});

   splitter->setChildrenCollapsible(false);
   splitter->setHandleWidth(2);

   browserPanel->setMinimumWidth(180);
   workspacePanel->setMinimumWidth(400);
   inspectorPanel->setMinimumWidth(220);

   layout->addWidget(splitter);

    // ========================================================
    //              PAINEL BROWSER   
    // ======================================================== 

    QVBoxLayout *browserLayout = new QVBoxLayout(browserPanel);
    browserLayout->setContentsMargins(15, 15, 15, 15);

    browserTitle->setStyleSheet(
      "color: #eeeeee;"
      "font-size: 16px;"
      "font-weight: bold;"
    );

    browserLayout->addWidget(browserTitle);
    browserLayout->addStretch();

    // ========================================================
    //      PAINEL WORKSPACE
    // ========================================================

    QVBoxLayout *workspaceLayout = new QVBoxLayout(workspacePanel);
    workspaceLayout->setContentsMargins(15, 15, 15, 15);

    workspaceTitle->setStyleSheet(
        "color: #eeeeee;"
        "font-size: 16px;"
        "font-weight: bold;"
    );
     
    workspaceLayout->addWidget(workspaceTitle);
    workspaceLayout->addStretch();

    // ============================================================
    //   PAINEL INSPECTOR
    // ============================================================

    QVBoxLayout *inspectorLayout = new QVBoxLayout(inspectorPanel);
    inspectorLayout->setContentsMargins(15, 15, 15, 15);

    inspectorTitle->setStyleSheet(
         "color: #eeeeee;"
         "font-size: 16px;"
         "font-weight: bold;"
    );

    inspectorLayout->addWidget(inspectorTitle);
    inspectorLayout->addStretch();

    // ==========================================================
    //   ESTILO DOS PAINÉIS 
    // ==========================================================

    browserPanel->setStyleSheet(
      "background-color: #0b0b10;"
      
    );

    workspacePanel->setStyleSheet(
      "background-color: #0b0b10;"
    );

    inspectorPanel->setStyleSheet(
      "background-color: #0b0b10;"
      
    );

    // ===========================================

   centralWidget->setLayout(layout);

   window.show();

   window.setStyleSheet(
       "QMainWindow {"
       "background-color: #0b0b10;"
       "}"

       "QWidget {"
       "background-color: #0b0b10;"
       "color: #eeeeee;"
       "}"

       "QPushButton {"
       "background-color: transparent;"
       "color: #eeeeee;"
       "border: none;"
       "padding: 8px 12px;"
       "}"

       "QPushButton:hover {"
       "color: #8a4cff;"
       "}"

       "QLabel {"
       "color: #eeeeee;"
       "}"

       "QSplitter::handle {"
       "background-color: #252536;"
       "}"

       "QLabel {"
       "color: #eeeeee;"
       "font-size: 12px;"
       "font-weight: bold;"
       "}"

   );

   return app.exec();

}

#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Errors.h"
#include "DBCStructure.h"
#include "Globals.h"
#include "QtHelpers.h"

MainWindow::MainWindow() :
    QMainWindow(nullptr),
    Q_SETUP(),
    FIND_Q_CHILD(_pageSwitcher)
{
}

void MainWindow::Setup()
{
    printf("%u spells loaded from DBC\n", StaticDBCStore<SpellEntry>::GetNumRows());
    printf("%u spells loaded from spell_dbc\n", DatabaseDBCStore<SpellEntry>::GetNumRows());

    auto it = StaticDBCStore<SpellEntry>::begin();
    std::advance(it, 2500);
    printf("For example, spell %u is called %s.\n", it->Id, it->SpellName[0]);

    this->showMaximized();
}

void MainWindow::SwitchToPage(uint8 index)
{
    ASSERT(index < PAGE_MAX);
    _pageSwitcher.setCurrentIndex(index);
}

MainWindow::~MainWindow() {}

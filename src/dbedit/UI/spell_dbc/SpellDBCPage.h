#ifndef TRINITY_DBEDIT_SPELLDBCPAGE_H
#define TRINITY_DBEDIT_SPELLDBCPAGE_H

#include "TopLevelPage.h"

class QLineEdit;
class SpellSearchResults;

class SpellDBCPage : public TopLevelPage
{
    Q_OBJECT
    
    public:
        SpellDBCPage(QWidget* parent = nullptr) : TopLevelPage(parent) {}
        void Setup() override;

    public Q_SLOTS:
        void SearchEnterPressed();

    private:
        QLineEdit* _searchBox;
        SpellSearchResults* _searchResults;
};

#endif

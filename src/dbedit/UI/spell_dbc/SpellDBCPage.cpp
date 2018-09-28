#include "SpellDBCPage.h"
#include "SpellSearchResult.h"
#include "SpellSearchResults.h"
#include "QtHelpers.h"
#include <QLineEdit>

void SpellDBCPage::Setup()
{
    FIND_Q_CHILD_DELAYED(_searchBox);
    FIND_Q_CHILD_DELAYED(_searchResults);
    CONNECT(_searchBox, returnPressed, this, SearchEnterPressed);
    CONNECT(_searchResults, itemClicked, this, SearchItemClicked);
}

void SpellDBCPage::SearchEnterPressed()
{
    QString str = _searchBox->text();
    if (str.size() > 3)
        _searchResults->DoSearch(str.toUtf8().data());
    else
        _searchResults->DoError("Type 3 or more characters to search...");
}

void SpellDBCPage::SearchItemClicked(QListWidgetItem* widget)
{
    uint32 const spellId = static_cast<SpellSearchResult*>(widget)->GetId();
    printf("Selected: %u\n", spellId);
}

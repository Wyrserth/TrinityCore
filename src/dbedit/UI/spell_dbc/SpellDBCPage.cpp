#include "SpellDBCPage.h"
#include "SpellSearchResults.h"
#include "QtHelpers.h"
#include <QLineEdit>

void SpellDBCPage::Setup()
{
    FIND_Q_CHILD_DELAYED(_searchBox);
    FIND_Q_CHILD_DELAYED(_searchResults);
    CONNECT(_searchBox, returnPressed, this, SearchEnterPressed);
}

void SpellDBCPage::SearchEnterPressed()
{
    QString str = _searchBox->text();
    if (str.size() > 3)
        _searchResults->DoSearch(str.toUtf8().data());
    else
        _searchResults->DoError("Type 3 or more characters to search...");
}

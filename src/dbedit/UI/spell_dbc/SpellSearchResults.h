#ifndef TRINITY_DBEDIT_SPELLSEARCHRESULTS_H
#define TRINITY_DBEDIT_SPELLSEARCHRESULTS_H

#include <QListWidget>
#include <string>

class SpellSearchResults : public QListWidget
{
    Q_OBJECT
    
    public:
        SpellSearchResults(QWidget* parent = nullptr) : QListWidget(parent) {}

    public:
        void DoSearch(char* needle);
        void DoError(char const* str);
};

#endif

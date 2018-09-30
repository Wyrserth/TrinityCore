#ifndef TRINITY_DBEDIT_SPELLDATADISPLAY_H
#define TRINITY_DBEDIT_SPELLDATADISPLAY_H

#include <QWidget>

class SpellDataDisplay : public QWidget
{
    Q_OBJECT

    public Q_SLOTS:
        void SetSpell(unsigned int);
};

#endif

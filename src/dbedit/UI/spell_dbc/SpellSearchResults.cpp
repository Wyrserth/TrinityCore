#include "SpellSearchResults.h"
#include "Errors.h"
#include "SpellAccessor.h"
#include "Util.h"
#include <map>
#include <vector>

// we can be destructive here, no downside, caller uses a temporary array
void SpellSearchResults::DoSearch(char* str)
{
    ASSERT(str && *str);

    this->clear();

    std::vector<char const*> needles;
    while (*str)
    {
        needles.push_back(str);
        while (*str && *str != ' ') ++str;
        while (*str && *str == ' ') *(str++) = '\0';
    }

    std::multimap<uint32, std::pair<uint32, char const*>> matches;
    for (std::pair<uint32, std::string> const& pair : SpellAccessor::AllSpells())
    {
        uint32 count = 0;
        for (char const* needle : needles)
            if (StringContainsStringI(pair.second, needle))
                ++count;

        if (!count)
            continue;

        matches.emplace(count, decltype(matches)::mapped_type(pair.first, pair.second.c_str()));
    }

    if (matches.empty())
    {
        DoError("No matching spells found.");
        return;
    }

    for (auto it = matches.rbegin(), end = matches.rend(); it != end; ++it)
        this->addItem(new QListWidgetItem(it->second.second));
}

void SpellSearchResults::DoError(char const* msg)
{
    this->clear();
    QListWidgetItem* item = new QListWidgetItem(msg);
    item->setFlags(Qt::NoItemFlags);
    this->addItem(item);
}

#ifndef TRINITY_DBEDIT_SPELLACCESSOR_H
#define TRINITY_DBEDIT_SPELLACCESSOR_H

#include "Define.h"
#include <unordered_map>
#include <map>
#include <string>

class LoadingThread;
struct SpellEntry;

class SpellAccessor
{
    public:
        static SpellAccessor const& instance() { return _instance(); }
        SpellEntry const* GetSpellData(uint32 spellId, bool useLocal = true, bool useDB = true, bool useDBC = true) const;
        std::string const& GetSpellName(uint32 spellId) const;

    public:
        static void BuildIndices() { auto& i = _instance(); i._BuildIndices(); i._RebuildIndices(); }
        static void RebuildIndices() { _instance()._RebuildIndices(); }

        static std::map<uint32, std::string> const& AllSpells() { return _instance()._allSpells; }

    private:
        SpellAccessor() {}
        static SpellAccessor& _instance() { static SpellAccessor a; return a; }

        void _BuildIndices();
        void _RebuildIndices();
        // ordered map of all known spellids + name
        std::map<uint32, std::string> _allSpells;
        // spellid -> (classmask,racemask)
        std::unordered_map<uint32, std::pair<uint32,uint32>> _learnedByClassesRaces;
};

#define sSpellAccessor SpellAccessor::instance()

#endif

#ifndef TRINITY_DBEDIT_SPELLACCESSOR_H
#define TRINITY_DBEDIT_SPELLACCESSOR_H

#include "Define.h"
#include <unordered_map>
#include <string>

class LoadingThread;
struct SpellEntry;

class SpellAccessor
{
    public:
        static SpellAccessor const& instance() { return _instance(); }
        SpellEntry const* GetSpellData(uint32 spellId, bool useLocal = true, bool useDB = true, bool useDBC = true);

    public:
        static void BuildIndices() { auto& i = _instance(); i._BuildIndices(); i._RebuildIndices(); }
        static void RebuildIndices() { _instance()._RebuildIndices(); }

    private:
        static SpellAccessor& _instance() { static SpellAccessor a; return a; }

        void _BuildIndices();
        void _RebuildIndices();
        // spellid -> classmask
        std::unordered_map<uint32, uint32> _learnedByClasses;
};

#define sSpellAccessor SpellAccessor::instance()

#endif

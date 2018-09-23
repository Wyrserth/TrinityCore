#include "SpellAccessor.h"
#include "DBCStructure.h"
#include "Globals.h"

/*static*/ SpellEntry const* SpellAccessor::GetSpellData(uint32 spellId, bool useLocal, bool useDB, bool useDBC)
{
    (void)useLocal;
    if (useDB)
        if (SpellEntry const* data = DatabaseDBCStore<SpellEntry>::LookupEntry(spellId))
            return data;
    if (useDBC)
        if (SpellEntry const* data = StaticDBCStore<SpellEntry>::LookupEntry(spellId))
            return data;
    return nullptr;
}

// unchanging indices only pulled from data we don't touch
void SpellAccessor::_BuildIndices()
{
    for (auto* entry : StaticDBCStore<SkillLineAbilityEntry>::iterate())
    {
        if (entry->AutolearnType != SKILL_LINE_ABILITY_LEARNED_ON_SKILL_LEARN)
            continue;
        if (!entry->classmask)
            continue;
        auto* spellEntry = StaticDBCStore<SpellEntry>::LookupEntry(entry->spellId);
        if (!spellEntry)
            continue;
        _learnedByClasses[entry->spellId] = entry->classmask;
    }
}

void SpellAccessor::_RebuildIndices()
{

}

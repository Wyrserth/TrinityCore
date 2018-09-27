#include "SpellAccessor.h"
#include "DatabaseEnv.h"
#include "DBCStructure.h"
#include "Globals.h"

SpellEntry const* SpellAccessor::GetSpellData(uint32 spellId, bool useLocal, bool useDB, bool useDBC) const
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

std::string const& SpellAccessor::GetSpellName(uint32 spellId) const
{
    auto it = _allSpells.find(spellId);
    if (it != _allSpells.end())
        return it->second;
    return "Unknown spell";
}

// unchanging indices only pulled from data we don't touch
void SpellAccessor::_BuildIndices()
{
    _learnedByClassesRaces.clear();
    for (auto* entry : StaticDBCStore<SkillLineAbilityEntry>::iterate())
    {
        uint32 const classmask = entry->classmask ? (entry->classmask & CLASSMASK_ALL_PLAYABLE) : CLASSMASK_ALL_PLAYABLE;
        uint32 const racemask = entry->racemask ? (entry->racemask & RACEMASK_ALL_PLAYABLE) : RACEMASK_ALL_PLAYABLE;
        if (classmask == CLASSMASK_ALL_PLAYABLE && racemask == RACEMASK_ALL_PLAYABLE)
            continue;
        auto* spellEntry = StaticDBCStore<SpellEntry>::LookupEntry(entry->spellId);
        if (!spellEntry)
            continue;
        _learnedByClassesRaces[entry->spellId] = { classmask, racemask };
    }
}

void SpellAccessor::_RebuildIndices()
{
    _allSpells.clear();
    for (SpellEntry const* entry : StaticDBCStore<SpellEntry>::iterate())
        _allSpells.emplace(entry->Id, entry->SpellName[0]);

    QueryResult result = WorldDatabase.Query("SELECT Id, Comment FROM spell_dbc");
    if (!result)
        return;
    do
    {
        Field* fields = result->Fetch();
        _allSpells.emplace(fields[0].GetUInt32(), fields[1].GetCString());
    } while (result->NextRow());
}

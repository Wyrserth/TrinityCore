#ifndef TRINITY_DBCLOADLIST_H
#define TRINITY_DBCLOADLIST_H

#include <memory>
#include "DBCfmt.h"
#include "DBCStructure.h"
#include "Globals.h"

struct DBCLoadEntry
{
    using LoadFunc = bool(char const*, char const*);
    using DBLoadFunc = bool(char const*, char const*, char const*, char const*);
    constexpr DBCLoadEntry(LoadFunc* func, char const* filename, char const* format, DBLoadFunc* dbFunc = nullptr, char const* dbFormat = nullptr, char const* dbIndex = nullptr) :
        _func(func), _filename(filename), _format(format), _dbFunc(dbFunc), _dbFormat(dbFormat), _dbIndex(dbIndex) {}

    constexpr char const* Name() const { return _filename; }
    bool Load() const { return _func(_filename, _format); }
    constexpr bool HasDB() const { return _dbFunc && _dbFormat && _dbIndex; }
    bool LoadDB() const { return _dbFunc(_filename, _format, _dbFormat, _dbIndex); }
    private:
        LoadFunc*   const _func;
        char const* const _filename;
        char const* const _format;
        DBLoadFunc* const _dbFunc;
        char const* const _dbFormat;
        char const* const _dbIndex;

};

struct DBCLoads
{
#define LOAD_DBC(file, entry, fmt) { &StaticDBCStore<entry>::Load, file, fmt }
#define LOAD_DBC_EXT(file, entry, fmt, dbfmt, dbindex) { &StaticDBCStore<entry>::Load, file, fmt, &DatabaseDBCStore<entry>::Load, dbfmt, dbindex }
    static constexpr DBCLoadEntry List[] = {
        LOAD_DBC_EXT("Spell.dbc",           SpellEntry,                 SpellEntryfmt,      CustomSpellEntryfmt,    CustomSpellEntryIndex),
        LOAD_DBC("SkillLineAbility.dbc",    SkillLineAbilityEntry,      SkillLineAbilityfmt),
    };
#undef LOAD_DBC_EXT
#undef LOAD_DBC
};

#endif

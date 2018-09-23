#ifndef TRINITY_DBEDIT_GLOBALS_H
#define TRINITY_DBEDIT_GLOBALS_H

#include "DBCStore.h"
#include "Errors.h"
#include "IoContext.h"
#include "IteratorPair.h"
#include "MainWindow.h"
#include <memory>

struct Globals
{
    static Globals const& instance() { return _instance(); }
    std::shared_ptr<Trinity::Asio::IoContext> IoCtx;
    std::unique_ptr<::MainWindow> MainWindow;
        
    private:
        static Globals& _instance() { static Globals i; return i; }
        
    friend int main(int,char**);
};

#define sGlobals Globals::instance()

std::string dbcdir();
template <typename DBCEntry, bool fromDB>
struct GlobalDBCStore
{
    public:
        using iterator = typename DBCStorage<DBCEntry>::iterator;
        static auto LookupEntry(uint32 id) { return _storage_ptr()->LookupEntry(id); }
        static auto GetNumRows() { return _storage_ptr()->GetNumRows(); }
        static auto begin() { return _storage_ptr()->begin(); }
        static auto end() { return _storage_ptr()->end(); }
        static Trinity::IteratorPair<iterator> iterate() { return { begin(), end() }; };
    private:
        template <bool DB = fromDB>
        static std::enable_if_t<DB, bool> Load(char const* filename, char const* format, char const* customFormat, char const* customIndex)
        {
            _storage() = std::make_unique<DBCStorage<DBCEntry>>(format);
            _storage()->LoadFromDB(filename, customFormat, customIndex);
            return true;
        }
        template <bool DB = fromDB>
        static std::enable_if_t<!DB, bool> Load(char const* filename, char const* format)
        {
            _storage() = std::make_unique<DBCStorage<DBCEntry>>(format);
            return _storage()->Load(dbcdir() + filename);
        }
        static DBCStorage<DBCEntry>* _storage_ptr() { return ASSERT_NOTNULL(_storage().get()); }
        static std::unique_ptr<DBCStorage<DBCEntry>>& _storage()
        {
            static std::unique_ptr<DBCStorage<DBCEntry>> ptr;
            return ptr;
        }

    friend struct DBCLoads;
};

template <typename DBCEntry>
using StaticDBCStore = GlobalDBCStore<DBCEntry, false>;

template <typename DBCEntry>
using DatabaseDBCStore = GlobalDBCStore<DBCEntry, true>;

#endif

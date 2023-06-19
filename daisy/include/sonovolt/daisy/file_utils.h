#pragma once

#include "ff.h"
#include <array>
#include <cstring>
#include <string_view>
#include <vector>

namespace sonovolt::daisy::fs
{

// TODO: create logging util for FS errors

struct File
{
    char path[256];
};

enum class OperationResult : uint8_t
{
    OK,
    OPEN_ERROR,
    READ_ERROR,
    CLOSE_ERROR,
};

enum class EntryType : uint8_t
{
    DIRECTORY,
    FILE,
};

struct Entry
{
    EntryType type;
    bool is_root = false;
    char name[128];
    char path[256];
    Entry *parent = nullptr;
    std::vector<Entry> children;
};

template <unsigned N>
FRESULT getContents(const char *search_path, std::array<File, N> &files);

FRESULT readDirectory(const char *search_path, std::vector<Entry> &entries);

} // namespace sonovolt::daisy::fs

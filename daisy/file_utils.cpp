#include "sonovolt/daisy/file_utils.h"

namespace sonovolt::daisy::fs
{
template <unsigned N>
FRESULT getContents(const char *search_path, std::array<File, N> &files)
{
    FRESULT result = FR_OK;
    FILINFO fno;
    DIR dir;
    char *fn;
    uint8_t file_count = 0;
    // Open Dir and scan for files.
    auto dir_res = f_opendir(&dir, search_path);

    if(dir_res != FR_OK)
    {
        return dir_res;
    }
    do
    {
        result = f_readdir(&dir, &fno);
        // Exit if bad read or NULL fname
        if(result != FR_OK || fno.fname[0] == 0)
            break;
        // Skip if its a directory or a hidden file.
        if(fno.fattrib & (AM_HID | AM_DIR))
            continue;
        // Now we'll check if its .wav and add to the list.
        fn = fno.fname;

        if(file_count < files.size())
        {
            if(strstr(fn, ".wav") || strstr(fn, ".WAV"))
            {
                strcpy(files[file_count].path, search_path);
                strcat(files[file_count].path, fn);

                file_count++;
                // For now lets break anyway to test.
                //                break;
            }
        }
        else
        {
            break;
        }
    } while(result == FR_OK);
    f_closedir(&dir);

    return FR_OK;
}

FRESULT readDirectory(const char *search_path, std::vector<Entry> &entries)
{
    DIR dir;
    FILINFO fno;
    FRESULT result = f_opendir(&dir, search_path);

    if(result != FR_OK)
        return result;

    while(result == FR_OK)
    {
        result = f_readdir(&dir, &fno);

        // Exit if bad read or NULL fname
        if(result != FR_OK || fno.fname[0] == 0)
            break;

        // Skip if its a hidden file.
        if(fno.fattrib & (AM_HID))
            continue;

        Entry entry;

        if(fno.fattrib & (AM_DIR))
        {
            entry.type = EntryType::DIRECTORY;
            strcpy(entry.name, fno.fname);
            strcat(entry.name, "/");

            strcpy(entry.path, search_path);

            if(entry.path[strlen(entry.path) - 1] != '/')
                strcat(entry.path, "/");

            strcat(entry.path, fno.fname);
        }
        else
        {
            entry.type = EntryType::FILE;
            strcpy(entry.name, fno.fname);

            strcpy(entry.path, search_path);

            if(entry.path[strlen(entry.path) - 1] != '/')
                strcat(entry.path, "/");
                
            strcat(entry.path, fno.fname);
        }

        entries.push_back(std::move(entry));
    }

    f_closedir(&dir);

    return result;
}

template FRESULT getContents<10u>(const char *search_path, std::array<File, 10u> &files);
} // namespace sonovolt::daisy::fs

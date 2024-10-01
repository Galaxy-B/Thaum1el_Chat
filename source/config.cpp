#include "config.hpp"

#include <fstream>
#include <iostream>

std::vector<std::wstring> Config::split(std::wstring& text, wchar_t key)
{
    std::vector<std::wstring> result(1, L"");

    for (int i = 0, cnt; i < text.size();)
    {
        // skip all characters equal to key, and record their count
        for (cnt = 0; i < text.size() && text[i] == key; i++, cnt++) {}

        // if there is key skipped, we add a wstring for next slice
        if (cnt > 0)
        {
            result.emplace_back(L"");
        }
        // otherwise text[i] belongs to current slice, remember to move i forward
        else
        {
            result.back().push_back(text[i++]);
        }
    }

    return std::move(result);
}

Config::Config(std::wstring& path) : path_(path)
{
    // load config from the given path
    std::wifstream wifs;
    wifs.open(path.data(), std::ios::in);

    // error case
    if (!wifs.is_open())
    {
        std::cout << "[Config] failed to read from config file!" << std::endl;
        exit(1); 
    }

    // read each line of config file
    for (std::wstring buf; std::getline(wifs, buf);)
    {
        auto slices = split(buf, L' ');

        // extract config info and insert into the map
        if (slices.size() >= 3 && slices[1] == L"=")
        {
            infos_[slices[0]] = slices[2];
        }
    }

    wifs.close();
}

std::wstring& Config::get(std::wstring& key)
{
    return infos_.at(key);
}

int Config::update(std::wstring& key, std::wstring& value)
{
    // update the map entry first
    infos_.at(key) = value;

    // write back config to the given path
    std::wofstream wofs;
    wofs.open(path_.data(), std::ios::out | std::ios::trunc);

    // error case
    if (!wofs.is_open())
    {
        std::cout << "[Config] failed to write to config file!" << std::endl;
        return -1;
    }

    // write all entries back to the config file
    for (const auto& [name, value] : infos_)
    {
        wofs << name + L" = " + value << std::endl;
    }

    wofs.close();
    return 0;
}
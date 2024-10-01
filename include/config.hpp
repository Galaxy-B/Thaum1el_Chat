#ifndef _CONFIG_HPP_
#define _CONFIG_HPP_

#include <unordered_map>
#include <vector>
#include <string>

/******************************************************************* 

 * Config class provides interfaces to look up and overwrite config 
   infos back into config files, it extracts info from config file
   immediately once it is instantiated. 

*******************************************************************/

class Config
{
private:
    // path to the config file
    std::wstring path_;

    // config infos
    std::unordered_map<std::wstring, std::wstring> infos_;

    // helper function to split the text line in config file
    // return vector is ended by an empty wstring
    std::vector<std::wstring> split(std::wstring& text, wchar_t key);

public:
    Config(std::wstring& path);

    // look up the related config info specified by key
    std::wstring& get(std::wstring& key);

    // update the config info to value specified by key
    // return non-zero value if failed in writing back to config file
    int update(std::wstring& key, std::wstring& value);
};

#endif
#include "config.hpp"

#include <string>
#include <iostream>

int main(int argc, char* argv[])
{
    Config client_config(L"../config/client_config.txt");
    Config server_config(L"../config/server_config.txt");

    // print what we fetched from the config file
    std::wcout << L"client config:" << std::endl;
    std::wcout << L"username = " << client_config.get(L"username") << std::endl; 
    std::wcout << L"host = " << client_config.get(L"host") << std::endl;
    std::wcout << L"port = " << client_config.get(L"port") << std::endl;
    std::wcout << std::endl;

    std::wcout << L"server config:" << std::endl;
    std::wcout << L"maxroom = " << server_config.get(L"maxroom") << std::endl;
    std::wcout << L"port = " << server_config.get(L"port") << std::endl;
    std::wcout << std::endl;

    // try to update some config value
    std::wstring username(L"thaum1el");
    std::wstring maxroom = std::to_wstring(8);

    client_config.update(L"username", username);
    server_config.update(L"maxroom", maxroom);

    // reload config
    client_config = Config(L"../config/client_config.txt");
    server_config = Config(L"../config/server_config.txt");

    // print updated values
    std::wcout << L"updated client config:" << std::endl;
    std::wcout << L"username = " << client_config.get(L"username") << std::endl;
    std::wcout << std::endl;

    std::wcout << L"updated server config:" << std::endl;
    std::wcout << L"maxroom = " << server_config.get(L"maxroom") << std::endl;
    std::wcout << std::endl;

    return 0;
}
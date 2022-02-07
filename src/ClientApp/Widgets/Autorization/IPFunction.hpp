#ifndef CLIENT_IPFUNCTION_HPP
#define CLIENT_IPFUNCTION_HPP

#ifdef WIN32

#include <iphlpapi.h>
#include <list>
#include <string>

[[nodiscard]]
inline std::list<std::string> GetIps() {

    constexpr size_t ipStructSize = sizeof(IP_ADAPTER_INFO);

    std::list<std::string> addresses;

    ULONG bufLen = 0;
    GetAdaptersInfo(nullptr, &bufLen);

    auto adapterInfo = new IP_ADAPTER_INFO[bufLen / ipStructSize];
    DWORD result = GetAdaptersInfo(adapterInfo, &bufLen);

    if (result == NO_ERROR) {

        std::string_view nullIp = "0.0.0.0";

        for (auto currentNode = adapterInfo; currentNode != nullptr; currentNode = currentNode->Next) {

            bool isNullIp = !std::strcmp(nullIp.data(), currentNode->IpAddressList.IpAddress.String);

            if (isNullIp)
                continue;

            addresses.emplace_back(std::string(currentNode->IpAddressList.IpAddress.String));
        }
    }

    delete[] adapterInfo;

    return addresses;
}

///ToDo: make for unix like system
#elif UNIX

#endif


#endif
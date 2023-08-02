
#include <Windows.h>
#include "log.h"

#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.ApplicationModel.h>
#include <winrt/Windows.Networking.h>
#include <winrt/Windows.Networking.Connectivity.h>

using namespace winrt::Windows::ApplicationModel;
using namespace winrt::Windows::Networking;
using namespace winrt::Windows::Networking::Connectivity;

//-----------------------------------------------------------------------------
// Functions
//-----------------------------------------------------------------------------

// OK
void GetApplicationVersion(uint16_t data[4])
{
    PackageVersion version = Package::Current().Id().Version();
    data[0] = version.Major;
    data[1] = version.Minor;
    data[2] = version.Build;
    data[3] = version.Revision;
}

// OK
void GetLocalIPv4Address(std::vector<wchar_t> &address)
{
    for (auto hostname : NetworkInformation::GetHostNames())
    {
    if (hostname.Type() == HostNameType::Ipv4)
    {
    wchar_t const* str = hostname.ToString().c_str();
    address.resize(wcslen(str) + 1);
    wcscpy_s(address.data(), address.size(), str);
    return;
    }
    }
}

void GetLocalHostname(std::vector<wchar_t>& name)
{
    for (auto hostname : NetworkInformation::GetHostNames())
    {
        if (hostname.Type() == HostNameType::DomainName)
        {
            wchar_t const* str = hostname.ToString().c_str();
            name.resize(wcslen(str) + 1);
            wcscpy_s(name.data(), name.size(), str);
            return;
        }
    }
}

// OK
void PrintSystemInfo()
{
    SYSTEM_INFO si;
    DWORD_PTR pam;
    DWORD_PTR sam;

    GetSystemInfo(&si);

    SPDLOG_INFO("Active Processor Mask {0:b}", si.dwActiveProcessorMask);
    SPDLOG_INFO("Number of Processors {0}", si.dwNumberOfProcessors);

    GetProcessAffinityMask(GetCurrentProcess(), &pam, &sam);

    SPDLOG_INFO("Process Affinity Mask {0:b}", pam);
    SPDLOG_INFO("System Affinity Mask {0:b}", sam);
}

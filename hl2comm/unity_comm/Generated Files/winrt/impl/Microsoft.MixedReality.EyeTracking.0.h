// WARNING: Please don't edit this file. It was generated by C++/WinRT v2.0.230706.1

#pragma once
#ifndef WINRT_Microsoft_MixedReality_EyeTracking_0_H
#define WINRT_Microsoft_MixedReality_EyeTracking_0_H
WINRT_EXPORT namespace winrt::Windows::Foundation
{
    struct EventRegistrationToken;
    struct IAsyncAction;
    template <typename TSender, typename TResult> struct WINRT_IMPL_EMPTY_BASES TypedEventHandler;
}
WINRT_EXPORT namespace winrt::Windows::Foundation::Numerics
{
}
WINRT_EXPORT namespace winrt::Microsoft::MixedReality::EyeTracking
{
    struct IEyeGazeTracker;
    struct IEyeGazeTrackerFrameRate;
    struct IEyeGazeTrackerRawValues;
    struct IEyeGazeTrackerRawValuesStatics;
    struct IEyeGazeTrackerReading;
    struct IEyeGazeTrackerWatcher;
    struct EyeGazeTracker;
    struct EyeGazeTrackerFrameRate;
    struct EyeGazeTrackerRawValues;
    struct EyeGazeTrackerReading;
    struct EyeGazeTrackerWatcher;
}
namespace winrt::impl
{
    template <> struct category<winrt::Microsoft::MixedReality::EyeTracking::IEyeGazeTracker>{ using type = interface_category; };
    template <> struct category<winrt::Microsoft::MixedReality::EyeTracking::IEyeGazeTrackerFrameRate>{ using type = interface_category; };
    template <> struct category<winrt::Microsoft::MixedReality::EyeTracking::IEyeGazeTrackerRawValues>{ using type = interface_category; };
    template <> struct category<winrt::Microsoft::MixedReality::EyeTracking::IEyeGazeTrackerRawValuesStatics>{ using type = interface_category; };
    template <> struct category<winrt::Microsoft::MixedReality::EyeTracking::IEyeGazeTrackerReading>{ using type = interface_category; };
    template <> struct category<winrt::Microsoft::MixedReality::EyeTracking::IEyeGazeTrackerWatcher>{ using type = interface_category; };
    template <> struct category<winrt::Microsoft::MixedReality::EyeTracking::EyeGazeTracker>{ using type = class_category; };
    template <> struct category<winrt::Microsoft::MixedReality::EyeTracking::EyeGazeTrackerFrameRate>{ using type = class_category; };
    template <> struct category<winrt::Microsoft::MixedReality::EyeTracking::EyeGazeTrackerRawValues>{ using type = class_category; };
    template <> struct category<winrt::Microsoft::MixedReality::EyeTracking::EyeGazeTrackerReading>{ using type = class_category; };
    template <> struct category<winrt::Microsoft::MixedReality::EyeTracking::EyeGazeTrackerWatcher>{ using type = class_category; };
    template <> inline constexpr auto& name_v<winrt::Microsoft::MixedReality::EyeTracking::EyeGazeTracker> = L"Microsoft.MixedReality.EyeTracking.EyeGazeTracker";
    template <> inline constexpr auto& name_v<winrt::Microsoft::MixedReality::EyeTracking::EyeGazeTrackerFrameRate> = L"Microsoft.MixedReality.EyeTracking.EyeGazeTrackerFrameRate";
    template <> inline constexpr auto& name_v<winrt::Microsoft::MixedReality::EyeTracking::EyeGazeTrackerRawValues> = L"Microsoft.MixedReality.EyeTracking.EyeGazeTrackerRawValues";
    template <> inline constexpr auto& name_v<winrt::Microsoft::MixedReality::EyeTracking::EyeGazeTrackerReading> = L"Microsoft.MixedReality.EyeTracking.EyeGazeTrackerReading";
    template <> inline constexpr auto& name_v<winrt::Microsoft::MixedReality::EyeTracking::EyeGazeTrackerWatcher> = L"Microsoft.MixedReality.EyeTracking.EyeGazeTrackerWatcher";
    template <> inline constexpr auto& name_v<winrt::Microsoft::MixedReality::EyeTracking::IEyeGazeTracker> = L"Microsoft.MixedReality.EyeTracking.IEyeGazeTracker";
    template <> inline constexpr auto& name_v<winrt::Microsoft::MixedReality::EyeTracking::IEyeGazeTrackerFrameRate> = L"Microsoft.MixedReality.EyeTracking.IEyeGazeTrackerFrameRate";
    template <> inline constexpr auto& name_v<winrt::Microsoft::MixedReality::EyeTracking::IEyeGazeTrackerRawValues> = L"Microsoft.MixedReality.EyeTracking.IEyeGazeTrackerRawValues";
    template <> inline constexpr auto& name_v<winrt::Microsoft::MixedReality::EyeTracking::IEyeGazeTrackerRawValuesStatics> = L"Microsoft.MixedReality.EyeTracking.IEyeGazeTrackerRawValuesStatics";
    template <> inline constexpr auto& name_v<winrt::Microsoft::MixedReality::EyeTracking::IEyeGazeTrackerReading> = L"Microsoft.MixedReality.EyeTracking.IEyeGazeTrackerReading";
    template <> inline constexpr auto& name_v<winrt::Microsoft::MixedReality::EyeTracking::IEyeGazeTrackerWatcher> = L"Microsoft.MixedReality.EyeTracking.IEyeGazeTrackerWatcher";
    template <> inline constexpr guid guid_v<winrt::Microsoft::MixedReality::EyeTracking::IEyeGazeTracker>{ 0x0E62487A,0xC54B,0x5870,{ 0xAF,0x8F,0xE0,0xCB,0x7C,0xF8,0x3A,0xEE } }; // 0E62487A-C54B-5870-AF8F-E0CB7CF83AEE
    template <> inline constexpr guid guid_v<winrt::Microsoft::MixedReality::EyeTracking::IEyeGazeTrackerFrameRate>{ 0x61CBBC3D,0xED9E,0x5B14,{ 0xAE,0x12,0xEE,0xBF,0xD3,0xA7,0x80,0x2F } }; // 61CBBC3D-ED9E-5B14-AE12-EEBFD3A7802F
    template <> inline constexpr guid guid_v<winrt::Microsoft::MixedReality::EyeTracking::IEyeGazeTrackerRawValues>{ 0x4A53A6A2,0x3CC4,0x5ED0,{ 0xB1,0x66,0x46,0x39,0x94,0xB7,0x99,0xD9 } }; // 4A53A6A2-3CC4-5ED0-B166-463994B799D9
    template <> inline constexpr guid guid_v<winrt::Microsoft::MixedReality::EyeTracking::IEyeGazeTrackerRawValuesStatics>{ 0x21BF6DD5,0xF972,0x54FE,{ 0xBF,0x22,0x2B,0x7B,0x94,0x78,0xD4,0xA4 } }; // 21BF6DD5-F972-54FE-BF22-2B7B9478D4A4
    template <> inline constexpr guid guid_v<winrt::Microsoft::MixedReality::EyeTracking::IEyeGazeTrackerReading>{ 0x0BDF4285,0xC0DE,0x5319,{ 0xBB,0xB4,0x49,0xCA,0x6E,0x1B,0xEA,0xD1 } }; // 0BDF4285-C0DE-5319-BBB4-49CA6E1BEAD1
    template <> inline constexpr guid guid_v<winrt::Microsoft::MixedReality::EyeTracking::IEyeGazeTrackerWatcher>{ 0x0B2B5894,0xAE77,0x5883,{ 0x92,0xC1,0x6C,0x4F,0x07,0x4B,0xAE,0xB0 } }; // 0B2B5894-AE77-5883-92C1-6C4F074BAEB0
    template <> struct default_interface<winrt::Microsoft::MixedReality::EyeTracking::EyeGazeTracker>{ using type = winrt::Microsoft::MixedReality::EyeTracking::IEyeGazeTracker; };
    template <> struct default_interface<winrt::Microsoft::MixedReality::EyeTracking::EyeGazeTrackerFrameRate>{ using type = winrt::Microsoft::MixedReality::EyeTracking::IEyeGazeTrackerFrameRate; };
    template <> struct default_interface<winrt::Microsoft::MixedReality::EyeTracking::EyeGazeTrackerRawValues>{ using type = winrt::Microsoft::MixedReality::EyeTracking::IEyeGazeTrackerRawValues; };
    template <> struct default_interface<winrt::Microsoft::MixedReality::EyeTracking::EyeGazeTrackerReading>{ using type = winrt::Microsoft::MixedReality::EyeTracking::IEyeGazeTrackerReading; };
    template <> struct default_interface<winrt::Microsoft::MixedReality::EyeTracking::EyeGazeTrackerWatcher>{ using type = winrt::Microsoft::MixedReality::EyeTracking::IEyeGazeTrackerWatcher; };
    template <> struct abi<winrt::Microsoft::MixedReality::EyeTracking::IEyeGazeTracker>
    {
        struct WINRT_IMPL_NOVTABLE type : inspectable_abi
        {
            virtual int32_t __stdcall get_IsRestrictedModeSupported(bool*) noexcept = 0;
            virtual int32_t __stdcall OpenAsync(bool, void**) noexcept = 0;
            virtual int32_t __stdcall Close() noexcept = 0;
            virtual int32_t __stdcall get_TrackerSpaceLocatorNodeId(winrt::guid*) noexcept = 0;
            virtual int32_t __stdcall get_IsVergenceDistanceSupported(bool*) noexcept = 0;
            virtual int32_t __stdcall get_IsEyeOpennessSupported(bool*) noexcept = 0;
            virtual int32_t __stdcall get_AreLeftAndRightGazesSupported(bool*) noexcept = 0;
            virtual int32_t __stdcall get_SupportedTargetFrameRates(void**) noexcept = 0;
            virtual int32_t __stdcall SetTargetFrameRate(void*) noexcept = 0;
            virtual int32_t __stdcall TryGetReadingAtTimestamp(int64_t, void**) noexcept = 0;
            virtual int32_t __stdcall TryGetReadingAtSystemRelativeTime(int64_t, void**) noexcept = 0;
            virtual int32_t __stdcall TryGetReadingAfterTimestamp(int64_t, void**) noexcept = 0;
            virtual int32_t __stdcall TryGetReadingAfterSystemRelativeTime(int64_t, void**) noexcept = 0;
        };
    };
    template <> struct abi<winrt::Microsoft::MixedReality::EyeTracking::IEyeGazeTrackerFrameRate>
    {
        struct WINRT_IMPL_NOVTABLE type : inspectable_abi
        {
            virtual int32_t __stdcall get_FramesPerSecond(uint32_t*) noexcept = 0;
        };
    };
    template <> struct abi<winrt::Microsoft::MixedReality::EyeTracking::IEyeGazeTrackerRawValues>
    {
        struct WINRT_IMPL_NOVTABLE type : inspectable_abi
        {
        };
    };
    template <> struct abi<winrt::Microsoft::MixedReality::EyeTracking::IEyeGazeTrackerRawValuesStatics>
    {
        struct WINRT_IMPL_NOVTABLE type : inspectable_abi
        {
            virtual int32_t __stdcall IsSupported(void*, winrt::guid, bool*) noexcept = 0;
            virtual int32_t __stdcall SendCommand(void*, winrt::guid, uint32_t, uint8_t*, uint32_t, uint8_t*) noexcept = 0;
            virtual int32_t __stdcall TryGetFloat(void*, winrt::guid, float*, bool*) noexcept = 0;
            virtual int32_t __stdcall TryGetBool(void*, winrt::guid, bool*, bool*) noexcept = 0;
            virtual int32_t __stdcall TryGetInt(void*, winrt::guid, int32_t*, bool*) noexcept = 0;
            virtual int32_t __stdcall TryGetVector3(void*, winrt::guid, winrt::Windows::Foundation::Numerics::float3*, bool*) noexcept = 0;
        };
    };
    template <> struct abi<winrt::Microsoft::MixedReality::EyeTracking::IEyeGazeTrackerReading>
    {
        struct WINRT_IMPL_NOVTABLE type : inspectable_abi
        {
            virtual int32_t __stdcall get_Timestamp(int64_t*) noexcept = 0;
            virtual int32_t __stdcall get_SystemRelativeTime(int64_t*) noexcept = 0;
            virtual int32_t __stdcall get_IsCalibrationValid(bool*) noexcept = 0;
            virtual int32_t __stdcall TryGetCombinedEyeGazeInTrackerSpace(winrt::Windows::Foundation::Numerics::float3*, winrt::Windows::Foundation::Numerics::float3*, bool*) noexcept = 0;
            virtual int32_t __stdcall TryGetLeftEyeGazeInTrackerSpace(winrt::Windows::Foundation::Numerics::float3*, winrt::Windows::Foundation::Numerics::float3*, bool*) noexcept = 0;
            virtual int32_t __stdcall TryGetRightEyeGazeInTrackerSpace(winrt::Windows::Foundation::Numerics::float3*, winrt::Windows::Foundation::Numerics::float3*, bool*) noexcept = 0;
            virtual int32_t __stdcall TryGetVergenceDistance(float*, bool*) noexcept = 0;
            virtual int32_t __stdcall TryGetLeftEyeOpenness(float*, bool*) noexcept = 0;
            virtual int32_t __stdcall TryGetRightEyeOpenness(float*, bool*) noexcept = 0;
        };
    };
    template <> struct abi<winrt::Microsoft::MixedReality::EyeTracking::IEyeGazeTrackerWatcher>
    {
        struct WINRT_IMPL_NOVTABLE type : inspectable_abi
        {
            virtual int32_t __stdcall add_EyeGazeTrackerAdded(void*, winrt::event_token*) noexcept = 0;
            virtual int32_t __stdcall remove_EyeGazeTrackerAdded(winrt::event_token) noexcept = 0;
            virtual int32_t __stdcall add_EyeGazeTrackerRemoved(void*, winrt::event_token*) noexcept = 0;
            virtual int32_t __stdcall remove_EyeGazeTrackerRemoved(winrt::event_token) noexcept = 0;
            virtual int32_t __stdcall StartAsync(void**) noexcept = 0;
            virtual int32_t __stdcall Stop() noexcept = 0;
        };
    };
    template <typename D>
    struct consume_Microsoft_MixedReality_EyeTracking_IEyeGazeTracker
    {
        [[nodiscard]] auto IsRestrictedModeSupported() const;
        auto OpenAsync(bool restrictedMode) const;
        auto Close() const;
        [[nodiscard]] auto TrackerSpaceLocatorNodeId() const;
        [[nodiscard]] auto IsVergenceDistanceSupported() const;
        [[nodiscard]] auto IsEyeOpennessSupported() const;
        [[nodiscard]] auto AreLeftAndRightGazesSupported() const;
        [[nodiscard]] auto SupportedTargetFrameRates() const;
        auto SetTargetFrameRate(winrt::Microsoft::MixedReality::EyeTracking::EyeGazeTrackerFrameRate const& newFramerate) const;
        auto TryGetReadingAtTimestamp(winrt::Windows::Foundation::DateTime const& timestamp) const;
        auto TryGetReadingAtSystemRelativeTime(winrt::Windows::Foundation::TimeSpan const& time) const;
        auto TryGetReadingAfterTimestamp(winrt::Windows::Foundation::DateTime const& timestamp) const;
        auto TryGetReadingAfterSystemRelativeTime(winrt::Windows::Foundation::TimeSpan const& time) const;
    };
    template <> struct consume<winrt::Microsoft::MixedReality::EyeTracking::IEyeGazeTracker>
    {
        template <typename D> using type = consume_Microsoft_MixedReality_EyeTracking_IEyeGazeTracker<D>;
    };
    template <typename D>
    struct consume_Microsoft_MixedReality_EyeTracking_IEyeGazeTrackerFrameRate
    {
        [[nodiscard]] auto FramesPerSecond() const;
    };
    template <> struct consume<winrt::Microsoft::MixedReality::EyeTracking::IEyeGazeTrackerFrameRate>
    {
        template <typename D> using type = consume_Microsoft_MixedReality_EyeTracking_IEyeGazeTrackerFrameRate<D>;
    };
    template <typename D>
    struct consume_Microsoft_MixedReality_EyeTracking_IEyeGazeTrackerRawValues
    {
    };
    template <> struct consume<winrt::Microsoft::MixedReality::EyeTracking::IEyeGazeTrackerRawValues>
    {
        template <typename D> using type = consume_Microsoft_MixedReality_EyeTracking_IEyeGazeTrackerRawValues<D>;
    };
    template <typename D>
    struct consume_Microsoft_MixedReality_EyeTracking_IEyeGazeTrackerRawValuesStatics
    {
        auto IsSupported(winrt::Microsoft::MixedReality::EyeTracking::EyeGazeTracker const& tracker, winrt::guid const& valueKey) const;
        auto SendCommand(winrt::Microsoft::MixedReality::EyeTracking::EyeGazeTracker const& tracker, winrt::guid const& command, array_view<uint8_t const> inBuffer, array_view<uint8_t> outBuffer) const;
        auto TryGetFloat(winrt::Microsoft::MixedReality::EyeTracking::EyeGazeTrackerReading const& reading, winrt::guid const& valueKey, float& value) const;
        auto TryGetBool(winrt::Microsoft::MixedReality::EyeTracking::EyeGazeTrackerReading const& reading, winrt::guid const& valueKey, bool& value) const;
        auto TryGetInt(winrt::Microsoft::MixedReality::EyeTracking::EyeGazeTrackerReading const& reading, winrt::guid const& valueKey, int32_t& value) const;
        auto TryGetVector3(winrt::Microsoft::MixedReality::EyeTracking::EyeGazeTrackerReading const& reading, winrt::guid const& valueKey, winrt::Windows::Foundation::Numerics::float3& value) const;
    };
    template <> struct consume<winrt::Microsoft::MixedReality::EyeTracking::IEyeGazeTrackerRawValuesStatics>
    {
        template <typename D> using type = consume_Microsoft_MixedReality_EyeTracking_IEyeGazeTrackerRawValuesStatics<D>;
    };
    template <typename D>
    struct consume_Microsoft_MixedReality_EyeTracking_IEyeGazeTrackerReading
    {
        [[nodiscard]] auto Timestamp() const;
        [[nodiscard]] auto SystemRelativeTime() const;
        [[nodiscard]] auto IsCalibrationValid() const;
        auto TryGetCombinedEyeGazeInTrackerSpace(winrt::Windows::Foundation::Numerics::float3& origin, winrt::Windows::Foundation::Numerics::float3& direction) const;
        auto TryGetLeftEyeGazeInTrackerSpace(winrt::Windows::Foundation::Numerics::float3& origin, winrt::Windows::Foundation::Numerics::float3& direction) const;
        auto TryGetRightEyeGazeInTrackerSpace(winrt::Windows::Foundation::Numerics::float3& origin, winrt::Windows::Foundation::Numerics::float3& direction) const;
        auto TryGetVergenceDistance(float& value) const;
        auto TryGetLeftEyeOpenness(float& value) const;
        auto TryGetRightEyeOpenness(float& value) const;
    };
    template <> struct consume<winrt::Microsoft::MixedReality::EyeTracking::IEyeGazeTrackerReading>
    {
        template <typename D> using type = consume_Microsoft_MixedReality_EyeTracking_IEyeGazeTrackerReading<D>;
    };
    template <typename D>
    struct consume_Microsoft_MixedReality_EyeTracking_IEyeGazeTrackerWatcher
    {
        auto EyeGazeTrackerAdded(winrt::Windows::Foundation::TypedEventHandler<winrt::Microsoft::MixedReality::EyeTracking::EyeGazeTrackerWatcher, winrt::Microsoft::MixedReality::EyeTracking::EyeGazeTracker> const& handler) const;
        using EyeGazeTrackerAdded_revoker = impl::event_revoker<winrt::Microsoft::MixedReality::EyeTracking::IEyeGazeTrackerWatcher, &impl::abi_t<winrt::Microsoft::MixedReality::EyeTracking::IEyeGazeTrackerWatcher>::remove_EyeGazeTrackerAdded>;
        [[nodiscard]] auto EyeGazeTrackerAdded(auto_revoke_t, winrt::Windows::Foundation::TypedEventHandler<winrt::Microsoft::MixedReality::EyeTracking::EyeGazeTrackerWatcher, winrt::Microsoft::MixedReality::EyeTracking::EyeGazeTracker> const& handler) const;
        auto EyeGazeTrackerAdded(winrt::event_token const& token) const noexcept;
        auto EyeGazeTrackerRemoved(winrt::Windows::Foundation::TypedEventHandler<winrt::Microsoft::MixedReality::EyeTracking::EyeGazeTrackerWatcher, winrt::Microsoft::MixedReality::EyeTracking::EyeGazeTracker> const& handler) const;
        using EyeGazeTrackerRemoved_revoker = impl::event_revoker<winrt::Microsoft::MixedReality::EyeTracking::IEyeGazeTrackerWatcher, &impl::abi_t<winrt::Microsoft::MixedReality::EyeTracking::IEyeGazeTrackerWatcher>::remove_EyeGazeTrackerRemoved>;
        [[nodiscard]] auto EyeGazeTrackerRemoved(auto_revoke_t, winrt::Windows::Foundation::TypedEventHandler<winrt::Microsoft::MixedReality::EyeTracking::EyeGazeTrackerWatcher, winrt::Microsoft::MixedReality::EyeTracking::EyeGazeTracker> const& handler) const;
        auto EyeGazeTrackerRemoved(winrt::event_token const& token) const noexcept;
        auto StartAsync() const;
        auto Stop() const;
    };
    template <> struct consume<winrt::Microsoft::MixedReality::EyeTracking::IEyeGazeTrackerWatcher>
    {
        template <typename D> using type = consume_Microsoft_MixedReality_EyeTracking_IEyeGazeTrackerWatcher<D>;
    };
}
#endif
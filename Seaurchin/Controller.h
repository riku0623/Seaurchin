#pragma once

enum class ControllerSource {
    RawKeyboard,
    RawTouch,
    IntegratedSliders,
    IntegratedAir,
};

enum class AirControlSource {
    AirUp,
    AirDown,
    AirHold,
    AirAction,
};

struct ControllerFingerState {
    int Id;
    WacomMTFingerState State;
    int SliderPosition;
};

class ControlState final {
    friend int WacomFingerCallback(WacomMTFingerCollection *fingerPacket, void *userData);

private:
    char keyboardCurrent[256];
    char keyboardLast[256];
    bool keyboardTrigger[256];

    bool integratedSliderCurrent[16];
    bool integratedSliderLast[16];
    bool integratedSliderTrigger[16];
    bool integratedAir[4];
    std::vector<int> sliderKeyboardInputCombinations[16];
    uint32_t sliderKeyboardPrevious[16];
    uint32_t sliderKeyboardCurrent[16];
    bool sliderKeyboardTrigger[16];
    std::vector<int> airStringKeyboardInputCombinations[4];
    bool airStringKeyboard[4];

    bool isWacomDeviceAvailable = false;
    int *wacomDeviceIds = nullptr;
    WacomMTCapability *wacomDeviceCapabilities = nullptr;
    std::unordered_map<int, std::shared_ptr<ControllerFingerState>> currentFingers;
    std::mutex fingerMutex;
    void InitializeWacomTouchDevice();
    void UpdateWacomTouchDeviceFinger(WacomMTFingerCollection *fingers);

public:
    void Initialize();
    void Terminate();
    void Update();

    bool GetTriggerState(ControllerSource source, int number);
    bool GetCurrentState(ControllerSource source, int number);
    bool GetLastState(ControllerSource source, int number);
    void SetSliderKeyCombination(int sliderNumber, const std::vector<int>& keys);
    void SetAirStringKeyCombination(int airNumber, const std::vector<int>& keys);
};

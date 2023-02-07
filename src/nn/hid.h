/**
* @file hid.h
* @brief Functions that help process gamepad inputs.
*/

#pragma once

#include <gfx/seadColor.h>
#include <nx/types.h>
#include <nn/util.h>

namespace nn {
    namespace hid {

        enum class NpadButton {
            A = 0,
            B = 1,
            X = 2,
            Y = 3,
            StickL = 4,
            StickR = 5,
            L = 6,
            R = 7,
            ZL = 8,
            ZR = 9,
            Plus = 10,
            Minus = 11,
            Left = 12,
            Up = 13,
            Right = 14,
            Down = 15,
            StickLLeft = 16,
            StickLUp = 17,
            StickLRight = 18,
            StickLDown = 19,
            StickRLeft = 20,
            StickRUp = 21,
            StickRRight = 22,
            StickRDown = 23,
            LeftSL = 24,
            LeftSR = 25,
            RightSL = 26,
            RightSR = 27,
            Palma = 28,
            Verification = 29,
            HandheldLeftB = 30, // (Left B button on NES controllers in Handheld mode)
            LeftC = 31, // [12.0.0+] (Left C button in N64 controller)
            UpC = 32, // [12.0.0+] (Up C button in N64 controller)
            RightC = 33, // [12.0.0+] (Right C button in N64 controller)
            DownC = 34, // [12.0.0+] (Down C button in N64 controller)
        };

        enum class NpadAttribute {
            IsConnected = 0,
            IsWired = 1,
            IsLeftConnected = 2,
            IsLeftWired = 3,
            IsRightConnected = 4,
            IsRightWired = 5,
        };

        enum class NpadStyleTag {
            NpadStyleFullKey = 0,         // (Pro Controller)
            NpadStyleHandheld = 1,         // (Joy-Con controller in handheld mode)
            NpadStyleJoyDual = 2,         // (Joy-Con controller in dual mode)
            NpadStyleJoyLeft = 3,         // (Joy-Con left controller in single mode)
            NpadStyleJoyRight = 4,         // (Joy-Con right controller in single mode)
            NpadStyleGc = 5,             // (GameCube controller)
            NpadStylePalma = 6,         // (Poké Ball Plus controller)
            NpadStyleLark = 7,             // (NES/Famicom controller)
            NpadStyleHandheldLark = 8,     // (NES/Famicom controller in handheld mode)
            NpadStyleLucia = 9,         // (SNES controller)
            NpadStyleLagon = 10,         // [12.0.0+] (N64 controller)
            NpadStyleLager = 11,         // [13.0.0+] (Sega Genesis controller)
            // bits 12-28 Reserved
            NpadStyleSystemExt = 29,     // (generic external controller)
            NpadStyleSystem = 30,         // (generic controller)
            // bit 31 Reserved
        };

        enum class NpadSystemProperties {
            IsChargingJoyDual = 0,
            IsChargingJoyLeft = 1,
            IsChargingJoyRight = 2,
            IsPoweredJoyDual = 3,
            IsPoweredJoyLeft = 4,
            IsPoweredJoyRight = 5,
            IsUnsuportedButtonPressedOnNpadSystem = 9,
            IsUnsuportedButtonPressedOnNpadSystemExt = 10,
            IsAbxyButtonOriented = 11,
            IsSlSrButtonOriented = 12,
            IsPlusAvailable = 13, // [4.0.0+]
            IsMinusAvailable = 14, // [4.0.0+]
            IsDirectionalButtonsAvailable = 15, // [8.0.0+]
        };

        enum class TouchAttribute {
            Transferable = 0,
            IsConnected = 1
        };

        enum class MouseButton {
            Left,
            Right,
            Middle,
            Forward,
            Back
        };

        enum class MouseAttribute {
            Transferable,
            IsConnected
        };

        enum class KeyboardKey {
            A = 4,
            B = 5,
            C = 6,
            D = 7,
            E = 8,
            F = 9,
            G = 10,
            H = 11,
            I = 12,
            J = 13,
            K = 14,
            L = 15,
            M = 16,
            N = 17,
            O = 18,
            P = 19,
            Q = 20,
            R = 21,
            S = 22,
            T = 23,
            U = 24,
            V = 25,
            W = 26,
            X = 27,
            Y = 28,
            Z = 29,
            D1 = 30,
            D2 = 31,
            D3 = 32,
            D4 = 33,
            D5 = 34,
            D6 = 35,
            D7 = 36,
            D8 = 37,
            D9 = 38,
            D0 = 39,
            Return = 40,
            Escape = 41,
            Backspace = 42,
            Tab = 43,
            Space = 44,
            Minus = 45,
            Plus = 46,
            OpenBracket = 47,
            CloseBracket = 48,
            Pipe = 49,
            Tilde = 50,
            Semicolon = 51,
            Quote = 52,
            Backquote = 53,
            Comma = 54,
            Period = 55,
            Slash = 56,
            CapsLock = 57,
            F1 = 58,
            F2 = 59,
            F3 = 60,
            F4 = 61,
            F5 = 62,
            F6 = 63,
            F7 = 64,
            F8 = 65,
            F9 = 66,
            F10 = 67,
            F11 = 68,
            F12 = 69,
            PrintScreen = 70,
            ScrollLock = 71,
            Pause = 72,
            Insert = 73,
            Home = 74,
            PageUp = 75,
            Delete = 76,
            End = 77,
            PageDown = 78,
            RightArrow = 79,
            LeftArrow = 80,
            DownArrow = 81,
            UpArrow = 82,
            NumLock = 83,
            NumPadDivide = 84,
            NumPadMultiply = 85,
            NumPadSubtract = 86,
            NumPadAdd = 87,
            NumPadEnter = 88,
            NumPad1 = 89,
            NumPad2 = 90,
            NumPad3 = 91,
            NumPad4 = 92,
            NumPad5 = 93,
            NumPad6 = 94,
            NumPad7 = 95,
            NumPad8 = 96,
            NumPad9 = 97,
            NumPad0 = 98,
            NumPadDot = 99,
            Backslash = 100,
            Application = 101,
            Power = 102,
            NumPadEquals = 103,
            F13 = 104,
            F14 = 105,
            F15 = 106,
            F16 = 107,
            F17 = 108,
            F18 = 109,
            F19 = 110,
            F20 = 111,
            F21 = 112,
            F22 = 113,
            F23 = 114,
            F24 = 115,
            NumPadComma = 133,
            Ro = 135,
            KatakanaHiragana = 136,
            Yen = 137,
            Henkan = 138,
            Muhenkan = 139,
            NumPadCommaPc98 = 140,
            HangulEnglish = 144,
            Hanja = 145,
            Katakana = 146,
            Hiragana = 147,
            ZenkakuHankaku = 148,
            LeftControl = 224,
            LeftShift = 225,
            LeftAlt = 226,
            LeftGui = 227,
            RightControl = 228,
            RightShift = 229,
            RightAlt = 230,
            RightGui = 231,
        };

        enum class KeyboardModifier {
            Control,
            Shift,
            LeftAlt,
            RightAlt,
            Gui,
            CapsLock,
            ScrollLock,
            NumLock,
            Katakana,
            Hiragana
        };

        typedef nn::util::BitFlagSet<64, NpadButton> NpadButtonSet;
        typedef nn::util::BitFlagSet<32, nn::hid::NpadStyleTag> NpadStyleSet;
        typedef nn::util::BitFlagSet<32, NpadAttribute> NpadAttributeSet;
        typedef nn::util::BitFlagSet<32, MouseButton> MouseButtonSet;
        typedef nn::util::BitFlagSet<32, MouseAttribute> MouseAttributeSet;
        typedef nn::util::BitFlagSet<32, TouchAttribute> TouchAttributeSet;

        struct AnalogStickState {
            s32 X;
            s32 Y;
        };

        struct TouchState {
            u64 mDeltaTime;
            TouchAttributeSet mAttributes;
            s32 mFingerId;
            s32 X;
            s32 Y;
            s32 mDiameterX;
            s32 mDiameterY;
            s32 mRotationAngle;
            s32 mReserved;
        };

        struct KeyboardState {
            u64 samplingNumber;
            nn::util::BitFlagSet<32, KeyboardModifier> modifiers;
            nn::util::BitFlagSet<256, KeyboardKey> keys;
        };

        struct NpadBaseState {
            u64 mSamplingNumber;
            NpadButtonSet mButtons;
            AnalogStickState mAnalogStickL;
            AnalogStickState mAnalogStickR;
            NpadAttributeSet mAttributes;
            char reserved[4];
        };

        struct NpadFullKeyState : NpadBaseState {
        };
        struct NpadHandheldState : NpadBaseState {
        };
        struct NpadJoyDualState : NpadBaseState {
        };
        struct NpadJoyLeftState : NpadBaseState {
        };
        struct NpadJoyRightState : NpadBaseState {
        };
        struct NpadPalmaState : NpadBaseState {
        };
        struct NpadSystemState : NpadBaseState {
        };
        struct NpadSystemExtState : NpadBaseState {
        };

        struct ControllerSupportArg {
            u8 mMinPlayerCount;
            u8 mMaxPlayerCount;
            u8 mTakeOverConnection;
            bool mLeftJustify;
            bool mPermitJoyconDual;
            bool mSingleMode;
            bool mUseColors;
            sead::Color4u8 mColors[4];
            u8 mUsingControllerNames;
            char mControllerNames[4][0x81];
        };

        struct ControllerSupportResultInfo {
            int mPlayerCount;
            int mSelectedId;
        };

        struct MouseState {
            u64 samplingNumber;
            s32 x;
            s32 y;
            s32 deltaX;
            s32 deltaY;
            s32 wheelDeltaX;
            s32 wheelDeltaY;
            MouseButtonSet buttons;
            MouseAttributeSet attributes;
        };

        void InitializeNpad();

        void SetSupportedNpadIdType(uint const *, ulong);

        void SetSupportedNpadStyleSet(nn::util::BitFlagSet<32, nn::hid::NpadStyleTag>);

        nn::hid::NpadStyleSet GetNpadStyleSet(uint const &port);

        void GetNpadState(nn::hid::NpadFullKeyState *, uint const &port);

        void GetNpadState(nn::hid::NpadHandheldState *, uint const &port);

        void GetNpadState(nn::hid::NpadJoyDualState *, uint const &port);

        void GetNpadState(nn::hid::NpadJoyLeftState *, uint const &port);

        void GetNpadState(nn::hid::NpadJoyRightState *, uint const &port);

        void GetNpadStates(nn::hid::NpadFullKeyState *, int, uint const &port);

        void GetNpadStates(nn::hid::NpadHandheldState *, int, uint const &port);

        void GetNpadStates(nn::hid::NpadJoyDualState *, int, uint const &port);

        void GetNpadStates(nn::hid::NpadJoyLeftState *, int, uint const &port);

        void GetNpadStates(nn::hid::NpadJoyRightState *, int, uint const &port);

        int ShowControllerSupport(nn::hid::ControllerSupportResultInfo *,
                                  ControllerSupportArg const &);

        void InitializeMouse();

        void InitializeKeyboard();

        void GetMouseState(nn::hid::MouseState *);

        void GetKeyboardState(nn::hid::KeyboardState *);
        
    }  // namespace hid
}  // namespace nn
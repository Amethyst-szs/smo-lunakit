#pragma once

#include "al/byaml/ByamlIter.h"
#include "al/byaml/writer/ByamlWriter.h"

#include "nn/result.h"
#include "sead/heap/seadDisposer.h"

#include "helpers/fsHelper.h"

#include "devgui/savedata/DevGuiWriteStream.h"
#include "imgui.h"
#include "sead/time/seadDateTime.h"

namespace LoadLog {
    void pushTextToVector(const char* text);
    extern ImVector<char*> mTextLines;
} // namespace LoadLog
#include "devgui/DevGuiManager.h"

#include "DevGuiSaveData.h"

DevGuiWriteStream::DevGuiWriteStream(sead::RamStreamSrc* src, sead::Stream::Modes mode)
{
    mSrc = src;
    setMode(mode);
}

void DevGuiSaveData::init()
{
    sead::Stream::Modes streamMode = sead::Stream::Modes::Binary;
    mRamStream = new (mHeap) sead::RamStreamSrc(&mWorkBuf, sizeof(mWorkBuf));
    mWriteStream = new (mHeap) DevGuiWriteStream(mRamStream, streamMode);

    Logger::log("Save file init completed!\nRamStream: %p WriteStream: %p\n", mRamStream, mWriteStream);
}

void DevGuiSaveData::writeTestFile()
{
    al::ByamlWriter file = al::ByamlWriter(mHeap, false);
    
    file.pushHash();
    file.addBool("FunnyBool", false);
    file.addInt("FunnyInt", 69);
    file.pop();

    file.write(mWriteStream);

    nn::Result fileWrite = FsHelper::writeFileToPath(mWorkBuf, file.calcPackSize(), "sd:/LunaKit/LKData/Save/TestFile.byml");
}
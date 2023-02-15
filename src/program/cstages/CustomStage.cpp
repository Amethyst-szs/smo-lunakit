#include "CustomStage.h"

CustomStageEntry::CustomStageEntry(const char* stageName)
{
    mStageName = stageName;

    sead::FormatFixedSafeString<0xff> stageMapPath("StageData/%sMap", stageName);
    mIsExist = al::isExistArchive(stageMapPath);
}

CustomStageCategory::CustomStageCategory(al::ByamlIter catIter)
{
    sead::Heap* heap = al::getStationedHeap();

    mIter = catIter;
    al::tryGetByamlString(&mCatName, catIter, "CategoryName");
    al::tryGetByamlString(&mCatDesc, catIter, "CategoryDesc");

    al::ByamlIter stageIter = catIter.getIterByKey("StageList");
    mCatSize = stageIter.getSize();

    mEntries.allocBuffer(mCatSize, heap);

    for(uint i = 0; i < mCatSize; i++) {
        const char* stageName;
        stageIter.tryGetStringByIndex(&stageName, i);

        CustomStageEntry* newEntry = new (heap) CustomStageEntry(stageName);
        mEntries.pushBack(newEntry);
    }
}

CustomStageResource::CustomStageResource(const char* resourcePath, const char* resourceName)
{
    sead::Heap* heap = al::getStationedHeap();
    
    mRes = new (heap) al::Resource(resourcePath);
    mResourceName = resourceName;

    if(mRes->isExistByml("StageList")) {
        mIsValidResource = true;
        mRootByaml = al::ByamlIter(mRes->tryGetByml("StageList"));

        unsigned int size = mRootByaml.getSize();
        mCategories.allocBuffer(size, heap);

        for(unsigned int i = 0; i < size; i++) {
            al::ByamlIter catIter = mRootByaml.getIterByIndex(i);
            CustomStageCategory* newCat = new (heap) CustomStageCategory(catIter);
            mCategories.pushBack(newCat);
        }
    }
}
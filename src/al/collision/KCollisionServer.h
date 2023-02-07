#pragma once

#include "al/collision/KCPrism.h"
#include <sead/container/seadPtrArray.h>

namespace sead {
template <typename T, s32 N>
class FixedRingBuffer;
}

namespace al {
class ByamlIter;
class KCHitInfo;

class KCollisionServer {
public:
    KCollisionServer();
    void areaOffsetSpaceToObjectSpace(sead::Vector3f*, sead::Vector3<unsigned int> const&, al::KCPrismHeader const*) const;
    int calcAreaBlockOffset(sead::Vector3<unsigned int> const&, al::KCPrismHeader const*) const;
    static int calcChildBlockOffset(sead::Vector3<unsigned int> const&, int);
    float calcFarthestVertexDistance();
    void calcPosLocal(sead::Vector3f*, al::KCPrismData const*, int, al::KCPrismHeader const*) const;
    static void calXVec(sead::Vector3f const*, sead::Vector3f const*, sead::Vector3f*);
    void checkArrow(sead::Vector3f const&, sead::Vector3f const&, sead::FixedRingBuffer<al::KCHitInfo, 512>*, unsigned int*, unsigned int) const;
    // check*
    void getAreaSpaceSize(sead::Vector3f*, al::KCPrismHeader const*) const;
    void getAreaSpaceSize(int*, int*, int*, al::KCPrismHeader const*) const;
    void getAreaSpaceSize(sead::Vector3<unsigned int>*, al::KCPrismHeader const*) const;
    int getAttributeElementNum() const;
    bool getAttributes(al::ByamlIter*, unsigned int, al::KCPrismHeader const*) const;
    bool getAttributes(al::ByamlIter*, al::KCPrismData const*) const;
    // getBlockData
    sead::Vector3f* getEdgeNormal1(al::KCPrismData const*, al::KCPrismHeader const*) const;
    sead::Vector3f* getEdgeNormal2(al::KCPrismData const*, al::KCPrismHeader const*) const;
    sead::Vector3f* getEdgeNormal3(al::KCPrismData const*, al::KCPrismHeader const*) const;
    sead::Vector3f* getFaceNormal(al::KCPrismData const*, al::KCPrismHeader const*) const;
    void* getInnerKcl(int) const;
    void getMinMax(sead::Vector3f*, sead::Vector3f*) const;
    inline sead::Vector3f* getNormal(unsigned int, al::KCPrismHeader const*) const;
    inline int getNormalNum(al::KCPrismHeader const*) const;

    inline int getNumInnerKcl() const {
        return *(int*)(this->gap1 + 0xc);
    }

    inline al::KCPrismData* getPrismData(unsigned int idx, al::KCPrismHeader const* prismHeader) const {
        return (al::KCPrismData*)(&prismHeader->mPositionsOffset + prismHeader->mTrianglesOffset + idx * 0x14);
    }
    
    inline int getTriangleNum(al::KCPrismHeader const* prismHeader) const {
        return (prismHeader->mOctreeOffset - prismHeader->mTrianglesOffset) / 0x14;
    }

    inline al::KCPrismHeader* getV1Header(int) const;
    // getVertexData (0xc)

    inline int getVertexNum(al::KCPrismHeader const* prismHeader) const {
        return ((prismHeader->mNormalsOffset - prismHeader->mPositionsOffset) >> 2) * -0x55555555;
    }

    void initKCollisionServer(void*, void const*);
    inline bool isInsideMinMaxInAreaOffsetSpace(sead::Vector3<unsigned int> const&, al::KCPrismHeader const*) const;
    inline bool isNanPrism(al::KCPrismData const*, al::KCPrismHeader const*) const;
    bool isNearParallelNormal(al::KCPrismData const*, al::KCPrismHeader const*) const;
    bool isParallelNormal(al::KCPrismData const*, al::KCPrismHeader const*) const;
    // KCHit*
    void objectSpaceToAreaOffsetSpace(sead::Vector3<unsigned int>*, sead::Vector3f const&, al::KCPrismHeader const*) const;
    void objectSpaceToAreaOffsetSpaceV3f(sead::Vector3f*, sead::Vector3f const&, al::KCPrismHeader const*) const;
    bool outCheckAndCalcArea(sead::Vector3<unsigned int>*, sead::Vector3<unsigned int>*, sead::Vector3f const&, sead::Vector3f const&, al::KCPrismHeader const*) const;
    // search*
    void setData(void*);
    inline int toIndex(al::KCPrismData const*, al::KCPrismHeader const*) const;


    sead::PtrArray<al::KCPrismHeader> mPrismHeaders;
    unsigned char* gap1; // al::Resource? contains binary contents of kcl file
    al::ByamlIter* mAttributeByml;
    int* piVar1;
    unsigned long uVar1;
    int iVar1;
    int iVar2;
    int iVar3;
    int iVar4;
    int iVar5;
    int iVar6;
    float mFarthestVertexDistance;
};
}

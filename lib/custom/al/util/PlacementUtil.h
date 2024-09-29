#pragma once

#include "al/actor/ActorInitInfo.h"
#include "al/actor/Placement.h"
#include "al/stage/StageInfo.h"
#include "al/string/StringTmp.h"
#include <sead/math/seadVector.h>
#include <sead/math/seadMatrix.h>

namespace al
{
    void getPlacementInfoByKey(al::PlacementInfo *, const al::PlacementInfo &, const char *);
    void getPlacementInfoByIndex(al::PlacementInfo *, const al::PlacementInfo &, int);
    void getPlacementInfoAndKeyNameByIndex(al::PlacementInfo *, const char **, const al::PlacementInfo &, int);
    void getPlacementId(al::PlacementId *, const al::ActorInitInfo &);
    void getPlacementId(al::PlacementId *, const al::PlacementInfo &);

    int getCountPlacementInfo(const al::PlacementInfo &);

    al::PlacementId* createPlacementId(const al::ActorInitInfo &);
    al::PlacementId* createPlacementId(const al::PlacementInfo &);

    bool tryGetTrans(sead::Vector3f *, const al::PlacementInfo &);
    bool tryGetMatrixTR(sead::Matrix34f *, const al::PlacementInfo &);
    bool tryGetLinksTrans(sead::Vector3f *,const al::PlacementInfo & , const char *);
    bool tryGetArg(int *result, const al::PlacementInfo &info, const char *key);
    bool tryGetLinksInfo(al::PlacementInfo *,al::PlacementInfo const&,char const*);
    bool tryGetPlacementInfoByIndex(al::PlacementInfo *, const al::PlacementInfo &, int);
    bool tryGetPlacementInfoAndKeyNameByIndex(al::PlacementInfo *, const char **, const al::PlacementInfo &, int);
    bool tryGetPlacementId(al::PlacementId *, const al::ActorInitInfo &);
    bool tryGetPlacementId(al::PlacementId *, const al::PlacementInfo &);
    bool isEqualPlacementId(const al::PlacementId &, const al::PlacementId &);
    bool isEqualPlacementId(const al::PlacementInfo &, const al::PlacementInfo &);
    bool isObjectName(const al::PlacementInfo &, const char *);

    al::StringTmp<0x80> makeStringPlacementId(al::PlacementId const *);

    void tryGetPlacementInfoAndCount(PlacementInfo *, int *, StageInfo const *, char const *);

    void getPlacementInfoByIndex(PlacementInfo *, PlacementInfo const &, int);

    void getObjectName(const char **namePtr, const PlacementInfo &placementInfo);

    bool tryGetObjectName(const char **namePtr, const PlacementInfo &placementInfo);

    bool tryGetStringArg(const char **namePtr, const PlacementInfo &info, const char *key);

    bool tryGetClassName(const char **namePtr, const PlacementInfo &info);

    bool tryGetDisplayName(const char **namePtr, const PlacementInfo &info);
    
};

/**
 * @file GameDataFile.h
 * @brief Holds data for an individual save file.
 */

#pragma once

#include "al/scene/SceneObjHolder.h"
#include "container/seadPtrArray.h"
#include "prim/seadSafeString.h"
#include "types.h"
#include "UniqueObjInfo.h"
#include "GameProgressData.h"
#include "game/GameData/PlayerHitPointData.h"

#include "sead/math/seadVector.h"
#include "sead/stream/seadStream.h"

namespace al {
    class ActorInitInfo;
    class PlacementInfo;
    class PlacementId;
    }  // namespace al

class SphinxQuizData;
class TimeBalloonSaveData;
class WorldWarpTalkData;
class VisitStageData;
class MoonRockData;
class BossSaveData;
class AchievementSaveData;
class SearchAmiiboDataTable;
class NetworkUploadFlag;
class SequenceDemoSkipData;
class HintPhotoData;
class ShopTalkData;
class RaceRecord;


class GameDataHolder;
class ShineInfo;

class GameDataFile
{
    public:
        GameDataFile(GameDataHolder*);

        struct HintInfo {
            void clear(void);
            bool isDisableByWorldWarpHole(bool) const;
            bool isEnableUnlock(int, bool, int, bool) const;
            bool isHintStatusUnlock(int, int, bool) const;
            bool isHintStatusUnlockByNpc(void) const;
            bool isHintStatusUnlockByAmiibo(void) const;
            bool isEnableNameUnlockByScenario(int, int, bool) const;

            sead::FixedSafeString<0x80> mStageName;     // 0x0
            sead::FixedSafeString<0x80> mObjId;         // 0x98
            sead::FixedSafeString<0x40> mScenarioName;  // 0x130
            const char *mObjectName;                    // 0x188
            sead::Vector3f mTrans;                      // 0x190
            sead::Vector3f mTransAgain;                 // 0x19C
            void *unkPtr1;                              // 0x1A8
            void *unkPtr2;                              // 0x1B0
            void *unkPtr3;                              // 0x1B8
            void *unkPtr4;                              // 0x1C0
            s32 mMainScenarioNo;                        // 0x1C8 
            int mWorldIndex;                            // 0x1CC
            bool mIsMoonRock;                           // 0x1D0 
            bool unkBool1;                              // 0x1D1 
            bool mIsAchievement;                        // 0x1D2 
            bool mIsGrand;                              // 0x1D3 
            bool mIsShopMoon;                           // 0x1D4
            int unkInt;                                 // 0x1D8
            int unkInt2;                                // 0x1DC
            void *unkPtr6;                              // 0x1E0
            void *unkPtr7;                              // 0x1E8
            int mUniqueID;                              // 0x1F0
            int mHintIdx;                               // 0x1F4
            sead::FixedSafeString<0x20> mOptionalID;    // 0x1F8
            uint mProcessBitflag;                       // 0x230
            bool unkBool2;                              // 0x234
            bool unkBool3;                              // 0x235
        };

        static_assert(sizeof(HintInfo) == 0x238, "size of HintInfo");
        
        void initializeData(void);
        bool tryReadByamlData(al::ByamlIter*);
        void tryFindCoinCollectInfo(char const*,char const*);
        void tryFindShineIndexByUniqueId(int);
        void tryFindCoinCollectIndexByUniqueId(int);
        void buyDefaultItem(void);
        void unlockAchievementShineName(void);
        void updateWorldMapIndex(void);
        void updateWorldWarpIndex(void);
        void initializeCheckpointTable(void);
        void generateSaveDataIdForPrepo(void);
        void resetMapIcon(void);
        void wearDefault(void);
        void initializeHintList(void);
        void initializeCoinCollectList(void);
        void resetTempData(void);
        void addPlayTime(int,al::IUseSceneObjHolder const*);
        void updateSaveTime(void);
        void updateSaveTimeForDisp(void);
        void updateSaveInfoForDisp(void);
        void generateSaveDataIdForPrepoForWrite(void);
        void resetSaveDataIdForPrepoForWrite(void);
        void startStage(char const*,int);
        void checkIsHomeStage(char const*);
        void setGameClear(void);
        void startDemoStage(char const*);
        void changeNextStage(struct ChangeStageInfo const*,int);
        void returnPrevStage(void);
        void changeNextStageWithDemoWorldWarp(char const*);
        void changeNextStageWithWorldWarpHole(char const*);
        void restartStage(void);
        void calcNextScenarioNo(void);
        void tryGetStageNameCurrent(void);
        void changeWipeType(char const*);
        void setRestartPointId(al::PlacementId const*);
        void clearStartId(void);
        void tryGetRestartPointIdString(void);
        void endStage(void);
        void missAndRestartStage(void);
        void checkGotShine(char const*);
        void tryGetNextMainScenarioLabel(sead::BufferedSafeString *,sead::BufferedSafeString *);
        void tryGetNextMainScenarioPos(sead::Vector3f *);
        void tryFindNextMainScenarioInfo(void);
        void addPayShine(int);
        void addPayShineCurrentAll(void);
        void addKey(int);
        void addOpenDoorLockNum(int);
        void tryFindSaveObjS32(al::PlacementId const*);
        void addSessionMember(struct SessionMusicianType const&);
        void addCoinCollect(al::PlacementId const*);
        void useCoinCollect(int);
        void tryFindExistCoinCollectStageName(int);
        void payCoinToSphinx(void);
        void answerCorrectSphinxQuiz(void);
        void answerCorrectSphinxQuizAll(void);
        void talkLocalLanguage(void);
        void saveWorldTravelingStatus(char const*);
        void startWorldTravelingPeach(void);
        void setGrowFlowerTime(al::PlacementId const*,ulong);
        void addGrowFlowerGrowLevel(al::PlacementId const*,uint);
        void findGrowFlowerPotIdFromSeedId(al::PlacementId const*);
        void addCoin(int);
        void addPlayerJumpCount(void);
        void addPlayerThrowCapCount(void);
        void readFromStream(sead::ReadStream *,uchar *);
        void tryReadByamlDataFromStream(sead::ReadStream *,uchar *,int);
        void writeToStream(sead::WriteStream *,sead::Heap *);
        void tryWriteByByaml(sead::WriteStream *,sead::Heap *);
        void calcCheckpointIndexInScenario(int);
        void changeNextSceneByGotCheckpoint(int);
        void changeNextSceneByWarp(void);
        void changeNextSceneByHome(void);
        void startYukimaruRace(void);
        void startYukimaruRaceTutorial(void);
        void startRaceManRace(void);
        void registerCheckpointTrans(al::PlacementId const*,sead::Vector3f const&);
        void calcGetCheckpointNum(void);
        void calcRestHintNum(void);
        void unlockHint(void);
        void unlockHintImpl(int);
        void unlockHintAmiibo(void);
        void unlockHintAddByMoonRock(void);
        void calcHintNum(void);
        void calcHintTrans(int);
        void findHint(int);
        void calcHintTransMostEasy(void);
        void findHintInfoMostEasy(void);
        void calcHintMoonRockNum(void);
        void calcHintMoonRockTrans(int);
        void findHintMoonRock(int);
        void tryUnlockShineName(int,int);
        void calcShineIndexTableNameAvailable(int *,int *,int);
        void calcShineIndexTableNameUnlockable(int *,int *,int);
        void unlockWorld(int);
        void noPlayDemoWorldWarp(void);
        void calcWorldWarpHoleThroughNum(void);
        void enteredStage(void);
        //void buyItem(ShopItem::ItemInfo const*,bool);
        //void tryFindItemList(ShopItem::ItemInfo const*);
        void calcHaveClothNum(void);
        void calcHaveCapNum(void);
        void calcHaveStickerNum(void);
        void calcHaveGiftNum(void);
        void buyItemAll(void);
        void wearCostume(char const*);
        void wearCap(char const*);
        void addHackDictionary(char const*);
        HintInfo* findShine(int worldIndex, int shineIndex);
        void calcShineNumInOneShine(int,int);
        void checkAchievementShine(int,int);
        void winRace(void);
        void findRaceRecord(char const*);
        void incrementRaceLoseCount(int);
        void setUpdateJumpingRopeScoreFlag(void);
        void setVolleyballBestCount(int);
        void setUpdateVolleyballScoreFlag(void);
        void setAmiiboNpcTrans(sead::Vector3f const&);
        void setTimeBalloonNpcTrans(sead::Vector3f const&);
        void setPoetterTrans(sead::Vector3f const&);
        void setShopNpcTrans(sead::Vector3f const&,char const*,int);
        void setMoonRockTrans(sead::Vector3f const&);
        void setMiniGameInfo(sead::Vector3f const&,char const*);
        void calcMiniGameNum(void);
        void showExplainCheckpointFlag(void);
        void calcShopNum(void);
        void talkKakku(void);
        void talkWorldTravelingPeach(void);
        void talkCollectBgmNpc(void);
        void noFirstNetwork(void);
        void calcIsGetMainShineAll(al::IUseSceneObjHolder const*);
        void calcIsGetShineAllInWorld(int);
        void tryFindLinkedShineIndex(al::ActorInitInfo const&,al::IUseSceneObjHolder const*);
        void tryFindLinkedShineIndex(al::ActorInitInfo const&,int,al::IUseSceneObjHolder const*);
        void tryFindLinkedShineIndexByLinkName(al::IUseSceneObjHolder const*,al::ActorInitInfo const&,char const*);
        void calcLinkedShineNum(al::ActorInitInfo const&);
        void tryFindShineIndex(al::ActorInitInfo const&);
        void tryFindShineIndex(char const*,char const*);
        void disableHintById(int);
        void enableHintById(int);
        void setHintTrans(int,sead::Vector3f const&);
        void resetHintTrans(int);
        void registerShineInfo(ShineInfo const*,sead::Vector3f const&);
        void calcRestShineInStageWithWorldProgress(char const*);
        // void calcGetShineNumByObjectNameOrOptionalId(char const*, GameDataFile::CountType);
        void calcGetShineNumByObjectNameWithWorldId(char const*,int);
        void calcAllShineNumByObjectNameOrOptionalId(char const*);
        void calcGetShineNumByStageName(char const*);
        void tryFindAndInitShineInfoByOptionalId(ShineInfo *,char const*);
        void tryFindUniqueId(ShineInfo const*);
        void findUnlockShineNumCurrentWorld(bool *);
        void trySetCollectedBgm(char const*,char const*);
        void setGotShine(GameDataFile::HintInfo const*);
        // void tryWriteByByaml(al::ByamlWriter *);
        
        int getTotalShineNum(void);
        void getCollectBgmByIndex(int);
        u8 getMainScenarioNoCurrent(void) const;
        int getStartShineNextIndex(void);
        void getTokimekiMayorNpcFavorabilityRating(void);
        void getShopNpcIconNumMax(void);
        void getShopNpcTrans(int);
        void getPoetterTrans(void);
        void getTimeBalloonNpcTrans(void);
        void getMiniGameNumMax(void);
        void getRaceLoseCount(int);
        int getWorldTotalShineNum(int);
        int getWorldWarpHoleThroughNumMax(void);
        void getCheckpointObjIdInWorld(int);
        void getCheckpointNumMaxInWorld(void);
        void getPlayerThrowCapCount(void);
        void getPlayerJumpCount(void);
        void getGrowFlowerGrowLevel(al::PlacementId const*);
        void getGrowFlowerTime(al::PlacementId const*);
        void getWorldTravelingStatus(void);
        void getCoinCollectNum(void);
        void getKeyNum(void);
        int getPayShineNum(int);
        int getShineNum(void);
        void getAchievement(char const*);
        void getPlayerStartId(void);
        void getStageNameNext(void);
        void getStageNameCurrent(void);
        PlayerHitPointData* getPlayerHitPointData() const;
        void getLastUpdateTime(void);
        void getPlayTimeTotal(void);
        int getMainScenarioNo(int) const;
        void getCollectedBgmMaxNum(void);
        int getScenarioNo(void) const;
        void getMiniGameName(int);
        void getWorldTotalShineNumMax(int);
        void getCheckpointTransInWorld(char const*);
        void getCoinCollectGotNum(void);
        void getTotalPayShineNum(void);
        void getShineNum(int);
        int getScenarioNo(int worldIndex) const;
        void getCollectedBgmNum(void);
        void getScenarioNoPlacement(void);
        void getMiniGameTrans(int);
        void getCoinCollectGotNum(int);
        void getTotalShopShineNum(void);

        void setGotShine(int);
        void setMainScenarioNo(int);
        void setStartShine(ShineInfo const*);
        void setKidsMode(bool);
        void setTokimekiMayorNpcFavorabilityRating(int);
        void setFlagOnTalkMessageInfo(int);
        void setJangoTrans(sead::Vector3f const&);
        void setJumpingRopeBestCount(int);
        void setGrowFlowerTime(al::PlacementId const*,al::PlacementId const*,ulong);
        void setSaveObjS32(al::PlacementId const*,int);
        void setStartedObj(al::PlacementId const*);
        void setGotShine(ShineInfo const*);
        void setMissRestartInfo(al::PlacementInfo const&);
        void setCheckpointId(al::PlacementId const*);
        void setActivateHome(void);
        void setOriginalHintTrans(int);

        bool isUnlockedWorld(int) const;
        bool isAlreadyGoWorld(int) const;
        bool isFirstTimeNextWorld(void) const;
        bool isGotShine(ShineInfo const*) const;
        bool isGotShine(int) const;
        bool isStartedObj(char const*,char const*) const;
        bool isAnswerCorrectSphinxQuizAll(int) const;
        bool isTalkAlreadyLocalLanguage(void) const;
        bool isBuyItem(char const*,sead::FixedSafeString<64> const*) const;
        bool isOpenShineName(int,int) const;
        bool isExistPoetter(void) const;
        bool isAlreadyShowExplainCheckpointFlag(void) const;
        bool isFlagOnTalkMessageInfo(int) const;
        bool isTalkKakku(void) const;
        bool isNextMainShine(struct QuestInfo const*) const;
        bool isNextMainShine(int) const;
        bool isMainShine(int) const;
        bool isLatestGetMainShine(ShineInfo const*) const;
        bool isEnableOpenMoonRock(int) const;
        bool isCollectedBgm(char const*,char const*) const;
        bool isPlayScenarioCamera(struct QuestInfo const*) const;
        bool isFirstNetwork(void) const;
        bool isTalkCollectBgmNpc(void) const;
        bool isTalkWorldTravelingPeach(void) const;
        bool isClearWorldMainScenario(int) const;
        bool isShopSellout(int) const;
        bool isExistTimeBalloonNpc(void) const;
        bool isExistJango(void) const;
        bool isGotShine(int,int) const;
        bool isExistInHackDictionary(char const*) const;
        // bool isBuyItem(ShopItem::ItemInfo const*) const;
        bool isUnlockAchievementShineName(void) const;
        bool isOpenMoonRock(int) const;
        bool isEnableUnlockHint(void) const;
        bool isGotCheckpoint(al::PlacementId *) const;
        bool isGotCheckpointInWorld(int) const;
        bool isPlayDemoPlayerDownForBattleKoopaAfter(void) const;
        bool isUsedGrowFlowerSeed(al::PlacementId const*) const;
        bool isStartWorldTravelingPeach(void) const;
        bool isFirstWorldTravelingStatus(void) const;
        bool isAnswerCorrectSphinxQuiz(int) const;
        bool isPayCoinToSphinx(void) const;
        bool isGotCoinCollect(al::PlacementId const*) const;
        bool isExistSessionMember(struct SessionMusicianType const&) const;
        bool isStartedObj(al::PlacementId const*,char const*) const;
        bool isPayShineAllInAllWorld(void) const;
        bool isUseMissRestartInfo(void) const;
        bool isGoToCeremonyFromInsideHomeShip(void) const;
        bool isRaceStart(void) const;
        bool isGameClear(void) const;
        bool isEmpty(void) const;
        bool isKidsMode(void) const;

        // custom methods

        // custom impl of findShine that uses shine UID instead of index to get the right HintInfo
        HintInfo* findShine(int shineUid) {
            for (int x = 0; x < 0x400; x++) {
                GameDataFile::HintInfo* curInfo = &mShineHintList[x];
                if (curInfo->mUniqueID == shineUid) {
                    return curInfo;
                }
            }
            return nullptr;
        }
        
        // end custom methods
        
        ShineInfo **mShineInfoArray;
        ShineInfo **mShineInfoArray2;
        ShineInfo *mShineInfo;
        void *qword18;
        void *qword20;
        int dword28;
        int dword2C;
        sead::FixedSafeString<0x80> char30;
        sead::FixedSafeString<0x80> charC8;
        sead::FixedSafeString<0x80> char160;
        sead::FixedSafeString<0x80> char1F8;
        sead::FixedSafeString<0x80> char290;
        sead::FixedSafeString<0x80> char328;
        sead::FixedSafeString<0x80> char3C0;
        u16 word458;
        char gap45A[6];
        void *qword460;
        void *qword468;
        void *qword470;
        void *qword478;
        void *qword480;
        void *qword488;
        sead::FixedSafeString<0x100> char490;
        void *qword5A8;
        bool byte5B0;
        void *qword5B4;
        sead::FixedSafeString<0x80> *qword5C0;
        UniqObjInfo** mUniqueObjInfoArr;
        void *qword5D0;
        int mCoinCount;
        int qword5DC;
        void *qword5E0;
        void *qword5E8;
        void *qword5F0;
        u16 word5F8;
        bool mIsEnableCap;
        void *qword600;
        int dword608;
        bool byte60C;
        SphinxQuizData *mSphinxQuizData;
        void *qword618;
        void *qword620;
        void *qword628;
        TimeBalloonSaveData *qword630;
        sead::FixedSafeString<0x40> char638;
        int dword690;
        WorldWarpTalkData *mWorldWarpTalkData;
        VisitStageData *mVisitStageData;
        GameProgressData *mProgressData;
        MoonRockData *mMoonRockData;
        BossSaveData *mBossSaveData;
        AchievementSaveData *mAchievementSaveData;
        SearchAmiiboDataTable *mSearchAmiiboDataTable;
        NetworkUploadFlag *mNetworkUploadFlag;
        SequenceDemoSkipData *mSequenceDemoSkipData;
        HintPhotoData *mHintPhotoData;
        void *qword6E8;
        void *qword6F0;
        void *qword6F8;
        void *qword700;
        void *qword708;
        sead::FixedSafeString<0x40> mBodyName;
        sead::FixedSafeString<0x40> mCapName;
        u16 word7C0;
        void *qword7C8;
        u16 word7D0;
        void *qword7D8;
        sead::PtrArray<RaceRecord> mLatestRaceRecords;
        void *qword7F0;
        void *qword7F8;
        void *qword800;
        void *qword808;
        void *qword810;
        bool byte818;
        void *qword820;
        bool mIsKidsMode;
        sead::PtrArrayImpl sead__ptrarrayimpl830;
        u16 word840;
        bool byte842;
        int dword844;
        bool byte848;
        GameDataHolder *mGameDataHolder;
        void *qword858;
        PlayerHitPointData *mPlayerHintPointData;
        sead::FixedSafeString<0x80> char868;
        bool byte900;
        bool byte901;
        int dword904;
        sead::FixedSafeString<0x80> char908;
        HintInfo *mShineHintList; // 0x9A0
        sead::PtrArrayImpl sead__ptrarrayimpl9A8;
        sead::PtrArrayImpl sead__ptrarrayimpl9B8;
        sead::PtrArrayImpl sead__ptrarrayimpl9C8;
        sead::PtrArrayImpl sead__ptrarrayimpl9D8;
        void *qword9E8;
        int mCurWorldID;
        void *qword9F8;
        void *qwordA00;
        u16 wordA08;
        bool byteA0A;
        void *qwordA10;
        void *qwordA18;
        int dwordA20;
        int dwordA24;
        int dwordA28;
        bool byteA2C;
        ChangeStageInfo *mChangeStageInfo;
        ChangeStageInfo *mChangeStageInfo2;
        void *qwordA40;
        void *qwordA48;
        void *qwordA50;
        void *qwordA58;
        ShopTalkData *mShopTalkData;
        void *qwordA68;
        bool byteA70;
        char gapA71[3];
        void *qwordA74;
        void *qwordA7C;
        int dwordA84;
        bool byteA88;
        char gapA89[3];
        void *qwordA8C;
        int dwordA94;
        bool byteA98;
        char gapA99[3];
        void *qwordA9C;
        int dwordAA4;
        bool byteAA8;
        char gapAA9[3];
        void *qwordAAC;
        int dwordAB4;
        bool byteAB8;
        char gapAB9[3];
        void *qwordABC;
        int dwordAC4;
        bool byteAC8;
        char gapAC9[3];
        void *qwordACC;
        int dwordAD4;
        bool byteAD8;
        char gapAD9[3];
        void *qwordADC;
        int dwordAE4;
        bool byteAE8;
        char gapAE9[3];
        void *qwordAEC;
        int dwordAF4;
        bool byteAF8;
        char gapAF9[3];
        void *qwordAFC;
        int dwordB04;
        bool byteB08;
        char gapB09[3];
        void *qwordB0C;
        int dwordB14;
        bool byteB18;
        char gapB19[3];
        void *qwordB1C;
        int dwordB24;
        bool byteB28;
        char gapB29[7];
        void *qwordB30;
        bool byteB38;
        char gapB39[7];
        void *qwordB40;
        int dwordB48;
        char gapB4C[4];
        void *qwordB50;
        int dwordB58;
        int dwordB5C;
        int dwordB60;
        u16 wordB64;
};
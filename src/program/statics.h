#include "al/byaml/ByamlIter.h"
#include "sead/container/seadPtrArray.h"

namespace Statics {

static bool isNoclip = false;
static bool isHUD = true;
static bool isPlayMusic = true;
static bool isUseAutosaves = true;

static bool isOverrideOutfit = false;
static const char* outfitOverrideBodyName = "Mario";
static const char* outfitOverrideCapName = "Mario";

static al::ByamlIter devStageListByaml;
static const char* selectedDevWorld = "OverTest000ExStage";

}
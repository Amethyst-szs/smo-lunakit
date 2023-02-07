#include "al/byaml/ByamlIter.h"
#include "sead/container/seadPtrArray.h"

namespace Statics {

static bool isNoclip = false;
static bool isHUD = true;
static bool isPlayMusic = true;
static bool isUseAutosaves = true;

static bool primitiveDraw = true;
static bool primitiveDrawIsDeath = false;
static bool primitiveDrawIsStage = true;
static bool primitiveDrawIsWater = true;
static bool primitiveDrawIs2D = true;
static bool primitiveDrawIsCollision = true;
static bool primitiveDrawIsCollisionComplex = false;

static bool isOverrideOutfit = false;
static const char* outfitOverrideBodyName = "Mario";
static const char* outfitOverrideCapName = "Mario";

static al::ByamlIter devStageListByaml;
static const char* selectedDevWorld = "OverTest000ExStage";

}
#include "patches.hpp"

namespace patch = exl::patch;
namespace inst = exl::armv8::inst;
namespace reg = exl::armv8::reg;

void enableDebugNvn() {
    patch::CodePatcher p(0x7312CC);
    p.WriteInst(inst::Nop());
}


void runCodePatches() {
    enableDebugNvn();
}
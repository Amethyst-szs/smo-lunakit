#pragma once

#include "al/byaml/ByamlIter.h"
#include "al/byaml/writer/ByamlWriter.h"
#include "al/hio/HioNode.h"

class ByamlSave : public al::HioNode {
public:
    virtual void write(al::ByamlWriter *) = 0;
    virtual void read(al::ByamlIter const &) = 0;
};
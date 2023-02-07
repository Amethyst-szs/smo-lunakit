#pragma once

namespace al {
class Triangle;

class TriangleFilterBase {
public:
    virtual bool isInvalidTriangle(al::Triangle const&) const = 0;
};

template <typename T>
class TriangleFilterDelegator : public al::TriangleFilterBase {

};

class TriangleFilterFunc : public al::TriangleFilterBase {

};

class TriangleFilterGroundOnly : public al::TriangleFilterBase {

};

class TriangleFilterIgnoreGround : public al::TriangleFilterBase {

};

class TriangleFilterOnlyWall : public al::TriangleFilterBase {

};

class TriangleFilterPoleNoTop : public al::TriangleFilterBase {

};

class TriangleFilterWallOnly : public al::TriangleFilterBase {

};
}

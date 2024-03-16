#pragma once

class IUseDemoSkip {
public:
    virtual bool isFirstDemo() const;
    virtual bool isEnableSkipDemo() const;
    virtual void skipDemo();
    virtual void updateOnlyDemoGraphics();
};

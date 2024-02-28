#pragma once

namespace al {
class AudioDirector;
}

class SceneAudioSystemPauseController {
private:
    al::AudioDirector* mAudioDirector;
    s32 field_8;
    bool field_c;
    bool field_d;

public:
    SceneAudioSystemPauseController(al::AudioDirector*);
    void update();
    bool tryResume();
    void pause(bool);
    void resume(s32);
};
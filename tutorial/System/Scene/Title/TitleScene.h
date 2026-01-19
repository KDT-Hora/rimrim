#pragma once
#include "../IScene.h"

class TitleScene :
    public IScene
{
public:

    TitleScene(game::GameSession* session);
    ~TitleScene();
    void Update();


};


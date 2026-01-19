#pragma once
#include "../IScene.h"

class InGame :
    public IScene
{
public:

    InGame(game::GameSession* session);
	~InGame();
    void Update()override;

};


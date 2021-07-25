#pragma once

#include "ICardGame.h"

class FCardGame : public ICardGame
{
    /** IModuleInterface implementation */
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
};

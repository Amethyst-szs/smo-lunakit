#pragma once
/**
 * @file PlayerActorBase.h
 * @brief Interfaces for Classes that use PlayerHack (PlayerActorBase)
* Vtable loc: 
 */

class PlayerHackKeeper;

class IUsePlayerHack {
    virtual PlayerHackKeeper* getPlayerHackKeeper() const = 0;
};


#include "DWState.h"

DWInput* DWState::GetInput() const
{
    if (!Player)
    {
        return nullptr;
    }

    return Player->GetInput();
}
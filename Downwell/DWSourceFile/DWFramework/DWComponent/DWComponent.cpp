#include "DWComponent.h"

DWComponent::DWComponent(DWGameObject* gameObject)
{
	OwnerObject = gameObject;
}

void DWComponent::Uninit()
{
	OwnerObject = nullptr;
	bEnable = false;
}
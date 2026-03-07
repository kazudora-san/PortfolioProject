//-----------------------------
//	DWComponent.h[DWComponentクラス制御]
//	千葉知輝
//	作成日 2025/10/06
//-----------------------------

#ifndef DWCOMPONENT_H
#define DWCOMPONENT_H

class DWGameObject;

class DWComponent
{
protected:
	DWGameObject* OwnerObject = nullptr;	// オブジェクトの保存先
	bool bEnable = true;

public:
	DWComponent() = default;
	DWComponent(DWGameObject* gameObject);

	void			SetGameObject(DWGameObject* object)	{ OwnerObject = object; }
	virtual void	SetEnable		(bool enable)		{ bEnable = enable; }
	
	DWGameObject*	GetGameObject()	const				{ return OwnerObject; }
	bool			IsActive()		const				{ return bEnable; }

	virtual void Init()		= 0;
	virtual void Uninit();
	virtual void Update()	= 0;
};

#endif // DWCOMPONENT_H
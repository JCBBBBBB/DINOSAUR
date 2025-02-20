#pragma once
#include "TScene.h"
class TSceneIngame :   public TScene
{
public:
	UINT		m_iLevel = 1;
	using T_Effect = std::shared_ptr<TSprite>;
	std::vector<T_Effect>  m_EffectList;
	
	TSound* m_pEffectSound = nullptr;
	TCamera				m_Cam;
	TActor				objScreen; // �ﰢ��
	std::vector<TActor> m_UIList;
	std::vector<TNpc>	m_npcList;
	THero hero;
	UINT  m_iNpcCounter = 0;
	void    LevelUp(UINT iNpc);
public:
	void   Init() override;
	void   Frame() override;
	void   Render() override;
	void   Release() override;
public:
	void  SetSound();
	void  SetUI();
	void  SetPlayer();
};


#include "TSceneIngame.h"
#include "TStd.h"
#include "TInput.h"
void   TSceneIngame::SetSound()
{	
	m_pBGSound = I_Sound.Load(L"../../data/sound/romance.mid");
	if (m_pBGSound)
	{
		//m_pBGSound->Play(true);
	}
	m_pEffectSound = I_Sound.Load(L"../../data/sound/GunShot.mp3").get();

}
void   TSceneIngame::SetUI()
{
	RECT rtBk = { 0, 0, 2400.0f, 24.0f };
	objScreen.Create(TDevice::m_pd3dDevice.Get(), TDevice::m_pContext, rtBk,
		L"../../data/ground.png",
		L"../../data/shader/Default.txt");
	objScreen.m_pSprite = nullptr;

	m_UIList.resize(4);
	m_UIList[0].Create(TDevice::m_pd3dDevice.Get(), TDevice::m_pContext, { 0, 0, 100, 100 },
		L"../../data/kgca1.png",
		L"Alphablend.hlsl");
	m_UIList[0].SetAnim(1.0f, I_Sprite.GetPtr(L"DefalultNumber"));

	m_UIList[1].Create(TDevice::m_pd3dDevice.Get(), TDevice::m_pContext, { 700, 0, 800, 100 },
		L"../../data/kgca1.png",
		L"Alphablend.hlsl");
	m_UIList[1].SetAnim(20.0f, I_Sprite.GetPtr(L"IconList"));

	m_UIList[2].Create(TDevice::m_pd3dDevice.Get(), TDevice::m_pContext,
		{ 700, 500, 800, 600 },
		L"../../data/kgca1.png",
		L"Alphablend.hlsl");
	m_UIList[2].SetAnim(1.0f, I_Sprite.GetPtr(L"wik"));

	m_UIList[3].Create(TDevice::m_pd3dDevice.Get(), TDevice::m_pContext,
		{ 0, 500, 100, 600 },
		L"../../data/Effect/slashFire_4x4.png",
		L"Alphablend.hlsl");
	m_UIList[3].SetAnim(1.0f, I_Sprite.GetPtr(L"wik"));
}
void   TSceneIngame::SetPlayer()
{
	//DrawRect = { 91, 1, 91+40, 1+60 }
	hero.Create(TDevice::m_pd3dDevice.Get(), TDevice::m_pContext, { 68, 64, 108, 124 },
		L"../../data/Sprite/standing_still.png",
		L"Alphablend.hlsl");
	hero.m_fSpeed = 500.0f;
}
void    TSceneIngame::LevelUp(UINT iLevel)
{
	Sleep(1000);
	std::vector<std::wstring> spriteName =
	{
		L"DefalultNumber",
		L"wik",
		L"rtClash",
		L"IconList",
		L"rtBomb",
		L"rtExplosion",
	};

	hero.SetVertexData({ 380, 270, 420, 330 });
	m_Cam.m_vCameraPos = { 0.0f,0.0f };
	for (int iNpc = 0; iNpc < iLevel; iNpc++)
	{
		TNpc npc;
		T_Math::FVector2 pos;
		pos.X = randstep(0.0f, g_xClientSize);
		pos.Y = randstep(0.0f, g_yClientSize);
		npc.Create(TDevice::m_pd3dDevice.Get(), TDevice::m_pContext,
			{ (LONG)pos.X, (LONG)pos.Y,(LONG)(pos.X + 67.0f), (LONG)(pos.Y + 78.0f) },
			L"../../data/Sprite/bitmap1Alpha.bmp",
			L"Alphablend.hlsl");

		npc.SetAnim(1.0f, I_Sprite.GetPtr(spriteName[m_iLevel % spriteName.size()]));
		m_npcList.push_back(npc);
	}
	m_iNpcCounter = m_npcList.size();
}
void   TSceneIngame::Init()
{

	SetSound();
	SetUI();
	SetPlayer();
	LevelUp(m_iLevel);
}
void    TSceneIngame::Frame()
{

	if (m_iNpcCounter <= 9)
	{
		if (I_Input.KeyCheck(VK_F1) == KEY_PUSH)
		{
			TNpc npc;
			T_Math::FVector2 pos;
			pos.X = randstep(0.0f, g_xClientSize);
			pos.Y = randstep(0.0f, g_yClientSize);
			npc.Create(TDevice::m_pd3dDevice.Get(), TDevice::m_pContext,
				{ (LONG)pos.X, (LONG)pos.Y,(LONG)(pos.X + 67.0f), (LONG)(pos.Y + 78.0f) },
				L"../../data/Sprite/bitmap1Alpha.bmp",
				L"Alphablend.hlsl");
			npc.SetAnim(1.0f, I_Sprite.GetPtr(L"DefalultNumber"));
			m_npcList.push_back(npc);
			m_iNpcCounter = m_npcList.size();
		}
	}

	//T_Math::FVector2 vPos = objScreen.m_vPos;
	//T_Math::FVector2 vScale = { (float)cos(g_fGameTime) * 0.5f + 0.5f, (float)cos(g_fGameTime) * 0.5f + 0.5f };
	//T_Math::FVector2 vCenter = { -800.0f * 0.5f, -600.0f * 0.5f };

	////objScreen.SetCenterMove(vCenter);
	////objScreen.SetScale(vScale);
	////objScreen.SetRotate(g_fGameTime);
	////objScreen.SetTrans(vPos);
	objScreen.Frame();


	for (auto& ui : m_UIList)
	{
		if (TCollision::RectToPt(ui.m_rt, I_Input.m_ptMousePos))
		{
			T_Math::FVector2 vScale = { 0.7f + (float)cos(g_fGameTime * 5) * 0.5f + 0.5f,
										0.7f + (float)cos(g_fGameTime * 5) * 0.5f + 0.5f };
			ui.SetScale(vScale);
			ui.SetRotate(g_fGameTime);
			ui.SetTrans(ui.m_vPos);
		}
		ui.Frame();
	}

	for (auto& npc : m_npcList)
	{
		npc.Frame();
		if (npc.m_bDead == false && TCollision::RectToRect(npc.m_rt, hero.m_rt))
		{
			npc.m_bDead = true;
			m_iNpcCounter = max(0, m_iNpcCounter - 1);
		}
	}
	for (auto iter = m_npcList.begin(); iter != m_npcList.end(); )
	{
		if ((*iter).m_bDead == true)
		{
			iter = m_npcList.erase(iter);
		}
		else
		{
			iter++;
		}
	}


	hero.Frame();
	m_Cam.Right(-hero.m_vOffset.X);// +hero.m_vOffset;
	m_Cam.m_vCameraPos.Y = m_Cam.m_vCameraPos.Y + -hero.m_vOffset.Y;
	m_Cam.Frame();

}
void    TSceneIngame::Render()
{
	objScreen.SetViewTransform(m_Cam.GetMatrix());
	objScreen.Render(TDevice::m_pContext);

	m_UIList[0].PreRender(TDevice::m_pContext);
	TDevice::m_pContext->PSSetShaderResources(0, 1,
		m_UIList[0].m_pSprite->GetSRV(m_iNpcCounter).GetAddressOf());
	m_UIList[0].PostRender(TDevice::m_pContext);

	//for (auto obj : m_UIList)
	for (int iUI = 1; iUI < m_UIList.size(); iUI++)
	{
		m_UIList[iUI].UpdateSprite();
		// 화면 고정( 뷰 변환 생략 )
		//obj.SetViewTransform(m_Cam.GetMatrix());
		m_UIList[iUI].Render(TDevice::m_pContext);
	}

	/// <summary>
	/// 
	/// </summary>
	hero.SetViewTransform(m_Cam.GetMatrix());
	hero.Render(TDevice::m_pContext);

	bool bGameEnding = true;

	for_each(begin(m_npcList), end(m_npcList), [&](auto& obj)
		{
			if (!obj.m_bDead)
			{
				obj.UpdateSprite();
				obj.SetViewTransform(m_Cam.GetMatrix());
				obj.Render(TDevice::m_pContext);
				bGameEnding = false;
			}
		});
	//g_bGameRun = !bGameEnding;

	// 하단 화면을 벗어나면.
	if (g_yClientSize <= hero.m_vList[2].p.Y)
	{
		g_bGameRun = false;
	}

	// 적 격퇴
	if (bGameEnding)
	{
		m_iLevel++;
		LevelUp(m_iLevel);
	}
}
void    TSceneIngame::Release()
{
	objScreen.Release();
	for (auto& obj : m_UIList)
	{
		obj.Release();
	}
	hero.Release();
	for (int iNpc = 0; iNpc < m_npcList.size(); iNpc++)
	{
		m_npcList[iNpc].Release();
	}


}


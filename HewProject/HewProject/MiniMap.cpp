#include "MiniMap.h"
#include <SceneBase.hpp>
#include <UiManager.hpp>
#include <Camera.hpp>
#include <DebugWindow.hpp>
ID3D11ShaderResourceView* CMiniMap::m_img;


CMiniMap::CMiniMap()
{
	
	m_playerIcon = CUIManager::GetIns()->Add(new CGameUI("Assets/Img/Map/MapPlayer.png"));
	m_playerIcon.lock()->SetPos(DirectX::XMFLOAT2(1150.f, 120.f));
	m_playerIcon.lock()->SetSize(DirectX::XMFLOAT2(40.f, 40.f));
	m_player = CSceneBase::GetObjList().lock()->FindTag(TAG_PLAYER);
	m_map = CUIManager::GetIns()->Add(new CGameUI("Assets/Img/Map/UI map.png"));
	m_map.lock()->SetPos(DirectX::XMFLOAT2(1150.f, 120.f));
	m_map.lock()->SetSize(DirectX::XMFLOAT2(350.f, 350.f));
	m_map.lock()->SetSortID(SORT_ORDER_BACK);
	

}

CMiniMap::~CMiniMap()
{
}

void CMiniMap::Init()
{
	LoadTextureFromFile("Assets/Img/PauseMenu/Cursor.png", &m_img);
}

void CMiniMap::Uninit()
{
	m_img->Release();
}

void CMiniMap::Update()
{
	if (m_player.expired() == true)
		m_player = CSceneBase::GetObjList().lock()->FindTag(TAG_PLAYER);
	
	// ƒvƒŒƒCƒ„[‰ñ“]ˆ—
	m_playerIcon.lock()->SetRotation(-DirectX::XMConvertToDegrees(CCameraBase::GetPrimaryRadXZ() + 3.14 - m_player.lock()->GetParam().rot.y));
	if (m_player.expired() == false)
	{

		// “G‚ÌƒŠƒXƒg
		auto enemyList = CSceneBase::GetObjList().lock()->FindTagAll(TAG_ENEMY);
		auto boss = CSceneBase::GetObjList().lock()->FindTagAll(TAG_ENEMY_BOSS);

		DirectX::XMFLOAT3 playerPos = m_player.lock()->GetParam().pos;
		DirectX::XMVECTOR player = DirectX::XMLoadFloat3(&playerPos);

		CUIManager::GetIns()->Delete(m_bossIcon);

		for (int i = 0; i < m_Icon.size(); i++)
		{
			CUIManager::GetIns()->Delete(m_Icon[i]);
		}
		m_Icon.clear();

		// ƒ{ƒX
		{
			auto it = boss.begin();
			auto bossParam = (*it)->GetParam();
			DirectX::XMVECTOR enemy = DirectX::XMLoadFloat3(&bossParam.pos);


			// ‹——£‚ðŒvŽZ
			DirectX::XMVECTOR distance = DirectX::XMVectorSubtract(player, enemy);

			// float3‚É•ÏŠ·‚µ‚ÄŠi”[
			DirectX::XMStoreFloat3(&m_movePos, distance);

			// ƒ}ƒbƒv‚É‰f‚é‹——£
			float disPlayer = 18.f;
			auto radXZ = CCameraBase::GetRadXZ("Player");//CCameraBase::GetPrimaryRadXZ();
			auto toEnemyAngle = atan2f(m_movePos.z, m_movePos.x) + 3.14f;
			auto dist = sqrtf(powf(m_movePos.x, 2) + powf(m_movePos.z, 2));

			if (dist < disPlayer)
			{
				m_bossIcon = CUIManager::GetIns()->Add(new CGameUI(""));
				m_bossIcon.lock()->SetResourceView(m_img);
				m_bossIcon.lock()->SetPos({ cosf(toEnemyAngle + radXZ) * dist * -5 + 1150, sinf(toEnemyAngle + radXZ) * dist * 5 + 120 });
				m_bossIcon.lock()->SetSize(DirectX::XMFLOAT2(20.f, 20.f));
				m_bossIcon.lock()->SetColor(0, 1, 0, (17 - dist) > 1 ? 1 : (17 - dist));
			}
		}
		int i = 0;
		// “G‚ÌƒŠƒXƒg‘S’Tõ
		for (auto itr = enemyList.begin(); itr != enemyList.end(); itr++, i++)
		{
			// “G‚Ìƒf[ƒ^Ši”[
			auto enemyParam = (*itr)->GetParam();

			DirectX::XMVECTOR enemy = DirectX::XMLoadFloat3(&enemyParam.pos);

			// ‹——£‚ðŒvŽZ
			DirectX::XMVECTOR distance = DirectX::XMVectorSubtract(player, enemy);

			// float3‚É•ÏŠ·‚µ‚ÄŠi”[
			DirectX::XMStoreFloat3(&m_movePos, distance);

			// ƒ}ƒbƒv‚É‰f‚é‹——£
			float disPlayer = 18.f;
			auto dist = powf(m_movePos.x, 2) + powf(m_movePos.z, 2);
			//if (powf(disPlayer, 2) < dist) { continue; }
			dist = sqrtf(dist);
			auto radXZ = CCameraBase::GetRadXZ("Player");//CCameraBase::GetPrimaryRadXZ();
			auto toEnemyAngle = atan2f(m_movePos.z, m_movePos.x) + 3.14f;
			if (dist < disPlayer)
			{
				
				if (enemyList.size() > m_Icon.size())
					m_Icon.push_back(CUIManager::GetIns()->Add(new CGameUI("")));
				m_Icon[i].lock()->SetResourceView(m_img);
				m_Icon[i].lock()->SetPos({ cosf(toEnemyAngle + radXZ) * dist * -5 + 1150, sinf(toEnemyAngle + radXZ) * dist * 5 + 120 });
				m_Icon[i].lock()->SetSize(DirectX::XMFLOAT2(10.f, 10.f));
				m_Icon[i].lock()->SetColor(1, 1, 1, (17 - dist) > 1 ? 1 : (17 - dist));
			
			}
			else
			{
				if (m_Icon.empty() == false)
				{
					if (i >= m_Icon.size())
					{
						--i;
						continue;
					}
					
					CUIManager::GetIns()->Delete(m_Icon[m_Icon.size() - 1]);
					m_Icon.pop_back();
				}
				
				i -= 2;
				if (i < -1)
					i = -1;
				
			}
		}

		

	}

	
}

void CMiniMap::Draw()
{
	
}

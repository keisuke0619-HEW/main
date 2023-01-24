#include "MiniMap.h"
#include <SceneBase.hpp>
#include <UiManager.hpp>
#include <Camera.hpp>
ID3D11ShaderResourceView* CMiniMap::m_img;


CMiniMap::CMiniMap()
{
	
	
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


	if (m_player.expired() == false)
	{

		// “G‚ÌƒŠƒXƒg
		auto enemyList = CSceneBase::GetObjList().lock()->FindTagAll(TAG_ENEMY);

		for (int i = 0; i < m_Icon.size(); i++)
		{
			CUIManager::GetIns()->Delete(m_Icon[i]);
			
		}
		m_Icon.clear();

		DirectX::XMFLOAT3 playerPos = m_player.lock()->GetParam().pos;
		DirectX::XMVECTOR player = DirectX::XMLoadFloat3(&playerPos);

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
			float disPlayer = 14.f;
			
			if (fabsf(m_movePos.x) <= disPlayer && fabsf(m_movePos.y) <= disPlayer && fabsf(m_movePos.z) <= disPlayer)
			{
				
				if (enemyList.size() > m_Icon.size())
					m_Icon.push_back(CUIManager::GetIns()->Add(new CGameUI("")));
				m_Icon[i].lock()->SetResourceView(m_img);
				m_Icon[i].lock()->SetPos({ ((m_movePos.x * -5)) + 1150, (m_movePos.z * 5) + 120 });
				m_Icon[i].lock()->SetSize(DirectX::XMFLOAT2(10.f, 10.f));
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

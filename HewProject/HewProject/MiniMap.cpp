#include "MiniMap.h"
#include <SceneBase.hpp>
#include <UiManager.hpp>

CMiniMap::CMiniMap()
{
	m_map = new CGameUI("Assets/Img/White.png");
	m_player = CSceneBase::GetObjList().lock()->FindTag(TAG_PLAYER);
	m_map->SetPos(DirectX::XMFLOAT2(1150.f, 120.f));
	m_map->SetSize(DirectX::XMFLOAT2(300.f, 300.f));
	//CUIManager::GetIns()->Add(m_map);
}

CMiniMap::~CMiniMap()
{
}

void CMiniMap::Update()
{
	if (m_player.expired() == true)
		m_player = CSceneBase::GetObjList().lock()->FindTag(TAG_PLAYER);


	if (m_player.expired() == false)
	{

		// “G‚ÌƒŠƒXƒg
		auto enemyList = CSceneBase::GetObjList().lock()->FindTagAll(TAG_ENEMY);


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
			float disPlayer = 15.f;
			
			if (fabsf(m_movePos.x) <= disPlayer && fabsf(m_movePos.y) <= disPlayer && fabsf(m_movePos.z) <= disPlayer)
			{
				if(enemyList.size() > m_enemyIcon.size())
				m_enemyIcon.push_back(new CGameUI("Assets/Img/enemy.png"));
				auto it = m_enemyIcon.begin();
				for (int j = i; j > 0; j--, it++);
				(*it)->SetPos({ ((m_movePos.x * -10)) + 1150, (m_movePos.z * 10) + 120 });
				(*it)->SetSize(DirectX::XMFLOAT2(10.f, 10.f));
				CUIManager::GetIns()->Add(*it);
				
			}
			else
			{
				if(m_enemyIcon.empty() == false)
				m_enemyIcon.pop_back();
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

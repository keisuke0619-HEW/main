#include "NumberUI.hpp"
#include <DebugWindow.hpp>
#include <UiManager.hpp>
const float NUMBER_UV_SIZE = 1.0f / 12;


ID3D11ShaderResourceView* CNumberUI::m_numberImg;
int CNumberUI::m_instanceNum;	// インスタンスの数（のべ）

void CNumberUI::Init()
{
	LoadTextureFromFile("Assets/Img/number2.png", &m_numberImg);
}

void CNumberUI::Uninit()
{
	m_numberImg->Release();
}

CNumberUI::CNumberUI(int length, SortOrder sort, int floatLength)
{
	m_rot = 0;
	m_align = ALIGN_CENTER;
	m_isZeroFill = false;
	m_margin = 0.7f;

	ResetLength(length, sort,  floatLength);
	m_zeroPoint = CUIManager::GetIns()->Add(new CGameUI(""), sort);
	m_zeroPoint.lock()->SetUVPos(NUMBER_UV_SIZE * 11, 0);
	m_zeroPoint.lock()->SetUVScale(NUMBER_UV_SIZE, 1);
	m_zeroPoint.lock()->SetResourceView(m_numberImg);
	m_zeroPoint.lock()->SetPos(-100, -100);	// とりあえず画面外に飛ばしておく
}

CNumberUI::~CNumberUI()
{
	for (int i = 0; i < m_ui.size(); i++)
	{
		CUIManager::GetIns()->Delete(m_ui[i]);
	}
	CUIManager::GetIns()->Delete(m_zeroPoint);
	m_ui.clear();
}

void CNumberUI::ResetLength(int length, SortOrder sort, int floatLength)
{
	for (int i = 0; i < m_ui.size(); i++)
	{
		CUIManager::GetIns()->Delete(m_ui[i]);
	}
	m_ui.clear();
	m_len = length + floatLength;
	m_ui.resize(m_len);
	m_floatLen = floatLength;

	for (int i = 0; i < m_ui.size(); i++)
	{
		m_ui[i] = CUIManager::GetIns()->Add(new CGameUI(""), m_sort);
		m_ui[i].lock()->SetResourceView(m_numberImg);
		m_ui[i].lock()->SetUVScale(NUMBER_UV_SIZE, 1);
		m_ui[i].lock()->SetSize(40, 50);
	}
	m_instanceNum++;
}

void CNumberUI::SetPos(float x, float y)
{
	m_pos = { x,y };
	RePosition();
}

void CNumberUI::SetPos(DirectX::XMFLOAT2 pos)
{
	m_pos = pos;
	RePosition();
}

void CNumberUI::SetSize(float x, float y)
{
	m_size = { x,y };
	RePosition();
}

void CNumberUI::SetSize(DirectX::XMFLOAT2 size)
{
	m_size = size;
	RePosition();
}

void CNumberUI::SetRot(float degZ)
{
	m_rot = DirectX::XMConvertToRadians(degZ);
	for (auto itr = m_ui.begin(); itr != m_ui.end(); itr++)
	{
		(*itr).lock()->SetRotation(degZ);
	}
	m_zeroPoint.lock()->SetRotation(degZ);	
}

void CNumberUI::SetIsZeroFill(bool isFill)
{
	m_isZeroFill = isFill;
}

void CNumberUI::SetNum(float input)
{
	if (m_num == input)
		return;
	m_num = input;
	int num = (int)(m_num * powf(10, m_floatLen));
	// 小数点は後でどうにかしよう。
	int i = m_ui.size() - 1;
	int count = 0;
	while (i >= 0)
	{
		if (num == 0 && count > m_floatLen && m_isZeroFill == false)
		{
			m_ui[i].lock()->SetUVPos({NUMBER_UV_SIZE * 10, 0});	// 透明
		}
		else
		{
			m_ui[i].lock()->SetUVPos({ NUMBER_UV_SIZE * (num % 10), 0});
		}
		num /= 10;
		i--;
		count++;
	}
}

void CNumberUI::SetAlign(ENumAlign align)
{
	m_align = align;
}

void CNumberUI::SetSortOrder(SortOrder sort)
{
	for (int i = 0; i < m_ui.size(); i++)
	{
		m_ui[i].lock()->SetSortID(sort);
	}
}

void CNumberUI::SetMarginLevel(float level) 
{
	m_margin = level;
}

void CNumberUI::SetColor(float r, float g, float b, float a)
{
	for (int i = 0; i < m_ui.size(); i++)
	{
		m_ui[i].lock()->SetColor(r, g, b, a);
	}
	m_zeroPoint.lock()->SetColor(r, g, b, a);
}

void CNumberUI::SetColor255(int r, int g, int b, int a)
{
	SetColor(r / 255.f, g / 255.f, b / 255.f, a / 255.f);
}

void CNumberUI::RePosition()
{
	// 中心座標から「全体の長さ」の一部を引く。
	// 左揃え：引かない
	// 中央ぞろえ：半分
	// 右揃え：全部引く
	// そこから一文字ずつ描画しながら右にずらしていく。
	
	// 起点座標を決める
	auto pos = m_pos;
	pos.x -= cosf(m_rot) * (m_len * (m_size.x * m_margin)) * (m_align * 0.5f);
	pos.y -= sinf(m_rot) * (m_len * (m_size.x * m_margin)) * (m_align * 0.5f);

	// 一文字ずつ設定しながら座標をずらしていく。
	float addX = cosf(m_rot) * (m_size.x * m_margin);
	float addY = sinf(m_rot) * (m_size.x * m_margin);
	for (int i = 0; i < m_ui.size(); i++)
	{
		m_ui[i].lock()->SetPos(pos);
		m_ui[i].lock()->SetSize(m_size);
		if (m_floatLen && i == m_len - m_floatLen - 1)
		{
			auto pointpos = pos;
			pointpos.x += addX * 0.6f;
			pointpos.y += addY * 0.6f;
			m_zeroPoint.lock()->SetPos(pointpos);
			m_zeroPoint.lock()->SetSize(m_size);
			pos.x += addX * 0.2f;
			pos.y += addY * 0.2f;
		}
		pos.x += addX;
		pos.y += addY;
	}
}
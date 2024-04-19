#include "Obelysk.h"

Obelysk::Obelysk(Properties* props) : Enemy(props) {
	m_IsAttacking = false;
	m_IsDying = false;
	m_FinishAttack = false;
	m_CanAttack = true;
	m_Animation = new Animation();
	m_Damage = 300;
	m_Position.X = m_Transform->X + m_Width / 2;
	m_Position.Y = m_Transform->Y + m_Height / 2;
	

	
	
	TextureManager::GetInstance()->Load("obelysk_idle", "assets\\obelysk_idle.png");
	TextureManager::GetInstance()->Load("obelysk_attacking", "assets\\obelysk_attacking.png");
	TextureManager::GetInstance()->Load("obelysk_dying", "assets\\obelysk_dying.png");
}

void Obelysk::Draw() {
	m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height);
	
}

void Obelysk::Update(float dt) {
	AttackHandler();
	m_Animation->Update();

	AnimationState();
}

void Obelysk::AnimationState() {
	std::string currentState;
	//idle
	if (!m_IsAttacking && !m_IsDying) {
		currentState = "idle";
		if (currentState != m_LastState) {
			m_Animation->SetProps("obelysk_idle", 1, 11, 150, 11);
			m_Animation->Start();
		}
	}
	if (m_IsAttacking && !m_IsDying) {
		currentState = "attacking";
		if(currentState != m_LastState) {
			m_Animation->SetProps("obelysk_attacking", 1, 12, 150, 12);
			m_Animation->Start();
		}
	}
	if (m_IsDying) {
		currentState = "dying";
		if (currentState != m_LastState) {
			m_Animation->SetProps("obelysk_dying", 1, 20, 120, 20);
			m_Animation->Start();
		}
	}
	
	m_LastState = currentState;
}

void Obelysk::AttackHandler() {
	if (m_IsAttacking&& m_FinishAttack == false) {

		if (m_Animation->getSpriteFrame() == 11) {
			m_FinishAttack = true;

		}
	}
	if (m_Animation != NULL && m_IsAttacking&& m_FinishAttack && m_Animation->getSpriteFrame() != 11) {
		m_IsAttacking = false;
		m_FinishAttack = false;
		m_CanAttack = true;
	}
	
}

void Obelysk::DyingHandler() {

}
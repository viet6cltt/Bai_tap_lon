#include "FireSpell.h"

FireSpell::FireSpell(Properties* props, int damage) : RangedType(props), m_damage(damage)
{
	m_Collider = new Collider;
	m_Animation = new Animation;
	m_RigidBody = new RigidBody();
	m_IsDeleted = false;

	m_LifeTime = 200.0f;
}

void FireSpell::Activate(Vector2D Begin_Position, Vector2D direction)
{
	
	m_Direction = direction;
}

void FireSpell::Draw()
{
	if (m_Animation != NULL) m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height);
	SDL_Rect box = m_Collider->Get();
	SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &box);
}

void FireSpell::Update(float dt)
{
	if (m_RigidBody != NULL) {
		m_RigidBody->ApplyForce(m_Direction * RUN_FORCE);
	}
	
	if (m_RigidBody != NULL) {

	}
	if (m_RigidBody != NULL) {
		m_RigidBody->Update(dt);
		m_Transform->X += m_RigidBody->Position().X;
		m_Transform->Y += m_RigidBody->Position().Y;
	}
	
	if (m_Collider != NULL) {

	}
	m_Collider->SetBuffer(-10, -10, 20, 20);
	m_Collider->Set(m_Transform->X, m_Transform->Y, m_Width, m_Height);

	if (CollisionHandler::GetInstance()->MapCollision(m_Collider->Get())) {
		m_IsDeleted = true;
		return;
	}

	m_Animation->SetProps("fire_spell", 1, 4, 100, 4);

	m_Animation->Update();

	m_LifeTime -= dt;
	if (m_LifeTime <= 0) {
		//Clean(); // Gọi hàm Clean để giải phóng tài nguyên
		m_IsDeleted = true;
	}
}


void FireSpell::Clean()
{

	delete m_Collider;
	delete m_Animation;
	delete m_RigidBody;

	// Thiết lập lại các con trỏ thành nullptr
	m_Collider = nullptr;
	m_Animation = nullptr;
	m_RigidBody = nullptr;
}
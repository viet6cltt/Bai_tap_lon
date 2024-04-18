#include "Skill_Hasagi.h"

Skill_Hasagi::Skill_Hasagi(Properties* props, int damage) : RangedType(props), m_damage(damage)
{
	m_manacost = 30;
	m_Collider = new Collider;
	m_Animation = new Animation;
	m_RigidBody = new RigidBody();
	m_IsDeleted = false;

	m_LifeTime = 120.0f;
}

void Skill_Hasagi::Activate(Vector2D Begin_Position, Vector2D direction)
{
	//std::
	//  << "m_Position: " << Begin_Position.X << " " << Begin_Position.Y << std::endl;
	m_Position = Begin_Position;
	m_Direction = direction;
	m_Direction = m_Direction - m_Position;
	//printf("toa do cua quai: %f %f\n", F.X, F.Y);
	m_Direction = m_Direction.Normalize();
	m_hasDealtDamage = false;
}

void Skill_Hasagi::Draw()
{
	if(m_Animation != NULL) m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height);

	SDL_Rect box = m_Collider->Get();
	SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &box);
}

void Skill_Hasagi::Update(float dt)
{
	

	m_RigidBody->ApplyForce(m_Direction * RUN_FORCE);
	m_RigidBody->Update(dt);
	m_Transform->X += m_RigidBody->Position().X;
	m_Transform->Y += m_RigidBody->Position().Y;
	
	m_Collider->SetBuffer(-10, -10, 20, 20);
	m_Collider->Set(m_Transform->X, m_Transform->Y, m_Width, m_Height);
	
	m_Animation->SetProps("skill_1", 1, 4, 250, 4);

	m_Animation->Update();

	m_LifeTime -= dt;
	if (m_LifeTime <= 0) {
		//this->Clean(); // Gọi hàm Clean để giải phóng tài nguyên
		
		m_IsDeleted = true;
	}
}

void Skill_Hasagi::Clean()
{
	
	delete m_Collider;
	delete m_Animation;
	delete m_RigidBody;

	// Thiết lập lại các con trỏ thành nullptr
	m_Collider = nullptr;
	m_Animation = nullptr;
	m_RigidBody = nullptr;
}






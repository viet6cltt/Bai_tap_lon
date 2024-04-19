#include "Pyromancer.h"

Pyromancer::Pyromancer(Properties* props) : Enemy(props)
{
	m_Health = 4000;
	m_Damage = 200;
	m_IsRunning = false;

	m_IsAttacking = false;
	m_CanAttack = true;
	m_AttackBegin = SDL_GetTicks();
	m_AttackCooldown = 5;
	m_IsAttacked = false;
	m_hasDealtDamage = false;
	center = new SDL_Point;
	center->x = m_Width / 2;
	center->y = m_Height / 2;

	m_IsDying = false;
	m_FinishDying = false;

	m_Flip = SDL_FLIP_NONE;

	m_Collider = new Collider();
	//m_Collider->SetBuffer(-45, -40, 45, 40);

	m_RigidBody = new RigidBody();
	//m_Position = new Vector2D;

	m_Animation = new Animation();
	m_HealthBar = new HealthBar(new Properties("enemy_bar", m_Transform->X + 20, m_Transform->Y + 20, 29, 5), m_Health);
}

void Pyromancer::Draw() 
{
	if (m_FireSpell != NULL) {
		
		m_FireSpell->Draw();
	}
	if (m_Animation != NULL) {
		m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height, m_Flip, center);
	}
	
	//Vector2D cam = Camera::GetInstance()->GetPosition();
	//SDL_Rect box = m_Collider->Get();
	//SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &box);
	if (m_FireSpell != NULL) {
		m_FireSpell->Draw();
	}
	if(m_HealthBar!=NULL) m_HealthBar->Draw();
}

void Pyromancer::Update(float dt)
{
	if (m_HealthBar != NULL){
		m_HealthBar->setProperties(m_Transform->X + 20, m_Transform->Y + 20, 29, 5);
		m_HealthBar->setCurrentHealth(m_Health);
		m_HealthBar->Update(dt);
	}
	

	if (isAlive() == false) {
		Clean();
	}

	m_RigidBody->UnSetForce();

	Attack();

	if (!m_IsAttacking && !m_IsHurt &&!m_IsDying) m_RigidBody->ApplyForce(m_Direction * RUN_FORCE);

	/*--------------------------xu li bi thuong-----------------------*/
	if (m_IsHurt) {
		m_RigidBody->UnSetForce();
		if (m_IsAttacking) {
			delete m_attackCollider;
			m_attackCollider = NULL;
		}
	}
	if (m_IsHurt && m_Animation->getSpriteFrame() == 3 && m_FinishHurt == false) {
		m_FinishHurt = true;
	}
	if (m_FinishHurt && m_Animation->getSpriteFrame() != 3) {
		m_IsHurt = false;
	}

	m_RigidBody->Update(dt);
	m_LastSafePosition.X = m_Transform->X;
	m_Transform->X += m_RigidBody->Position().X;
	m_Collider->SetBuffer(-24, -30, 48, 40);
	m_Collider->Set(m_Transform->X, m_Transform->Y, m_Width, m_Height);

	if (CollisionHandler::GetInstance()->MapCollision(m_Collider->Get())) {
		m_Transform->X = m_LastSafePosition.X;
	}


	m_RigidBody->Update(dt);
	m_LastSafePosition.Y = m_Transform->Y;
	m_Transform->Y += m_RigidBody->Position().Y;
	m_Collider->SetBuffer(-24, -30, 48, 40);
	m_Collider->Set(m_Transform->X, m_Transform->Y, m_Width, m_Height);
	

	if (CollisionHandler::GetInstance()->MapCollision(m_Collider->Get())) {
		m_Transform->Y = m_LastSafePosition.Y;
	}

	m_Origin->X = m_Transform->X + m_Width / 2;
	m_Origin->Y = m_Transform->Y + m_Height / 2;

	//Di chuyen theo nhan vat
	if (m_Health <= 0 && !m_IsDying) {
		m_IsDying = true;
		delete m_HealthBar;
		m_HealthBar = NULL;
	}
	DyingHandler();
	AnimationState();

	if (m_Animation != NULL) {
		m_Animation->Update();
	}
	if (m_FireSpell != NULL) {
		m_FireSpell->Update(dt);
	}
	

}

void Pyromancer::AnimationState()
{
	std::string currentState;
	//idle
	if (m_Animation != NULL) {
		
		if (!m_IsRunning && !m_IsAttacking && !m_IsHurt && !m_IsDying) {
			currentState = "idle";
			if (currentState != m_LastState) {
				m_Animation->SetProps("pyromancer_idle", 1, 14, 100, 14);
				m_Animation->Start();
			}
		}

		//running
		if (m_IsRunning && !m_IsAttacking && !m_IsHurt&&!m_IsDying) {
			currentState = "running";
			if (currentState != m_LastState) {
				m_Animation->SetProps("pyromancer_run", 1, 8, 100, 8);
				m_Animation->Start();
			}
		}
		//attacking
		if (m_IsAttacking && !m_IsHurt && !m_IsDying) {
			currentState = "attacking";
			if (currentState != m_LastState) {
				m_Animation->SetProps("pyromancer_attack", 1, 12, 150, 12);
				m_Animation->Start();
			}
		}
		//hurting
		if (m_IsHurt && !m_IsAttacking && !m_IsRunning && !m_IsDying) {
			currentState = "hurt";
			if (currentState != m_LastState) {
				m_Animation->SetProps("pyromancer_hurt", 1, 14, 100, 14);
				m_Animation->Start();
			}
		}
		//dying
		if (m_IsDying) {
			currentState = "dying";
			if (currentState != m_LastState) {
				m_Animation->SetProps("pyromancer_dying", 1, 13, 200, 13);
				m_Animation->Start();
			}
		}
		m_LastState = currentState;
	}
	
}

void Pyromancer::Follow_Warrior(Vector2D F)
{
	m_Position.X = m_Origin->X;
	m_Position.Y = m_Origin->Y;
	m_Direction = F - m_Position;
	m_attackDirection = F - m_Position;
	m_attackDirection.Normalize();

	if (m_Direction.Length() <= 150) {
		m_Direction = m_Direction.Normalize();
		m_Direction.X = -m_Direction.X;
		m_Direction.Y = -m_Direction.Y;
	}
	else {
		m_Direction = m_Direction.Normalize();
	}
	

	if (m_Direction.X > 0) {
		m_Flip = SDL_FLIP_NONE;
	}
	else if (m_Direction.X < 0) {
		m_Flip = SDL_FLIP_HORIZONTAL;
	}

}

void Pyromancer::Attack() 
{
	if (!m_IsAttacking && m_CanAttack && (SDL_GetTicks()-m_AttackBegin)/1000 == m_AttackCooldown &&!m_IsHurt) {
		m_IsRunning = false;
		m_IsAttacking = true;
		m_CanAttack = false;
		m_hasDealtDamage = false;
		m_FinishAttack = false;
		m_AttackBegin = SDL_GetTicks();
	}
	if (m_IsAttacking && m_Animation->getSpriteFrame() == 8 && !m_IsAttacked) {
		if (m_Flip == SDL_FLIP_NONE) {
			m_FireSpell = new FireSpell(new Properties("fire_spell", m_Origin->X, m_Origin->Y, 64, 64), m_Damage);
		}
		else {
			m_FireSpell = new FireSpell(new Properties("fire_spell", m_Origin->X - 20, m_Origin->Y, 64, 64), m_Damage);
		}
		m_FireSpell->Activate(m_Position, m_attackDirection);
		m_IsAttacked = true;
	}
	if (m_IsAttacking && m_Animation->getSpriteFrame() == 11 && m_FinishAttack == false) {
		m_FinishAttack = true;
	}

	if (m_IsAttacking && m_Animation->getSpriteFrame() != 11 && m_FinishAttack) {
		m_IsAttacking = false;
		m_CanAttack = true;
		m_FinishAttack = false;
		m_IsAttacked = false;
	}
	if (m_FireSpell != NULL) {
		if (m_FireSpell->IsDeleted()) {
			m_hasDealtDamage = false;
			delete m_FireSpell;
			m_FireSpell = NULL;
		}
		else {

		}
	}
}

void Pyromancer::DyingHandler() {
	if (m_IsDying) {

		m_IsRunning = false;
		m_IsAttacking = false;
		m_IsHurt = false;
	}
	if (m_IsDying && m_Animation->getSpriteFrame() == 12 && !m_FinishDying) {
		
		m_FinishDying = true;
		m_IsDying = false;
		
		
	}
}
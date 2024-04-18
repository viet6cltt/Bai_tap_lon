#include "Final_Boss.h"

Final_Boss::Final_Boss(Properties* props) : Enemy(props)
{
	TextureManager::GetInstance()->Load("final_boss_full_healthbar", "assets\\final_boss_full_healthbar.png");
	TextureManager::GetInstance()->Load("final_boss_none_healthbar", "assets\\final_boss_none_healthbar.png");	
	SoundManager::GetInstance()->Load("final_boss_revived", "assets\\final_boss_revived.mp3",SOUND_SFX,128);
	SoundManager::GetInstance()->Load("final_boss_1_dying", "assets\\final_boss_1_dying.mp3", SOUND_SFX, 128);
	SoundManager::GetInstance()->Load("final_boss_1_attacking", "assets\\final_boss_1_attacking_sfx.mp3", SOUND_SFX, 128);
	SoundManager::GetInstance()->Load("final_boss_1_casting", "assets\\final_boss_1_casting.mp3", SOUND_SFX, 128); 
	SoundManager::GetInstance()->Load("final_boss_2_casting", "assets\\final_boss_2_casting.mp3", SOUND_SFX, 128); 
	SoundManager::GetInstance()->Load("final_boss_2_attacking", "assets\\final_boss_2_attacking.mp3", SOUND_SFX, 128);
	m_hasReceivedDamage["normal"] = false;
	m_hasReceivedDamage["slash"] = false;
	m_hasReceivedDamage["gravity"] = false;
	m_hasReceivedDamage["hasagi"] = false;
	m_Health = MAX_HEALTH_TYPE1;
	m_Damage = DAMAGE_TYPE1;
	m_IsRunning = false;
	m_FinishHurt = false;
	m_hasDealtDamage = false;
	m_IsDyingType1 = false;
	m_DiedTimeBegin = 0;
	m_RevivingWaiting = false;
	cast_type = 0;
	TextureManager::GetInstance()->Load("final_boss_1_dying", "assets\\final_boss_1_dying.png");
	m_IsReviving = false;

	m_CastCooldown = 15;
	m_CastBeginTime = SDL_GetTicks();
	m_CanCast = true;
	m_IsCasting = false;
	Type = 1;

	m_IsAttacking = false;

	m_CanAttack = true;
	m_IsHurt = false;

	m_Flip = SDL_FLIP_NONE;

	m_Collider = new Collider();
	m_attackCollider = NULL;
	m_HealthBar = new HealthBar(new Properties("final_boss_none_healthbar", 382, 550, 516, 48), MAX_HEALTH_TYPE1);

	m_RigidBody = new RigidBody();
	//m_Position = new Vector2D;

	m_Animation = new Animation();
	
}

void Final_Boss::Draw()
{
	if(m_Animation != NULL) m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height, m_Flip, NULL);
	//Vector2D cam = Camera::GetInstance()->GetPosition();
	SDL_Rect box = { 0,0,0,0 };
	if(m_Collider != NULL) box = m_Collider->Get();

	if (m_attackCollider != NULL) {
		SDL_Rect box1 = m_attackCollider->Get();
		SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &box1);
	}

	//TextureManager::GetInstance()->Draw("enemy_bar", m_Transform->X + 70, m_Transform->Y + 43, 29, 5);
	if (m_HealthBar != NULL) {
		m_HealthBar->Draw();
	}
	//box.x -= cam.X;
	//box.y -= cam.Y;
	SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &box);
}

void Final_Boss::Update(float dt) {
	if (m_HealthBar != NULL) {
		//m_HealthBar->setProperties(m_Transform->X + 70, m_Transform->Y + 43, 29, 5);
		m_HealthBar->setCurrentHealth(m_Health);
		m_HealthBar->Update(dt);
	}
	CastingHandler();
	AttackHandler();
	AttackZone(dt);
	//-----------xu li di chuyen------------------------
	m_RigidBody->UnSetForce();
	if (m_IsRunning && !m_IsDyingType1 && !m_IsReviving && !m_RevivingWaiting&&!m_IsCasting) {
		m_RigidBody->ApplyForce(m_Direction * RUN_FORCE);
	}
	//--------------------------------------------
	m_RigidBody->Update(dt);
	m_LastSafePosition.X = m_Transform->X;
	m_Transform->X += m_RigidBody->Position().X;
	
	m_RigidBody->Update(dt);
	m_LastSafePosition.Y = m_Transform->Y;
	m_Transform->Y += m_RigidBody->Position().Y;

	
	if (m_Collider != NULL) {
		if (m_Flip == SDL_FLIP_NONE) {
			m_Collider->SetBuffer(-60, -70, 140, 90);
		}
		else {
			m_Collider->SetBuffer(-60, -70, 140, 90);
		}
		m_Collider->Set(m_Transform->X, m_Transform->Y, m_Width, m_Height);
		if (CollisionHandler::GetInstance()->MapCollision(m_Collider->Get())) {
			m_Transform->X = m_LastSafePosition.X;
		}


		if (CollisionHandler::GetInstance()->MapCollision(m_Collider->Get())) {
			m_Transform->Y = m_LastSafePosition.Y;
		}
	}
	
	m_Origin->X = m_Transform->X + m_Width / 2;
	m_Origin->Y = m_Transform->Y + m_Height / 2;

	//----------------------------------------------
	if (Type == 1 && m_Health < 0) {
		m_Health = 0;
		delete m_Collider;
		m_Collider = NULL;
		if (m_attackCollider != NULL) {
			delete m_attackCollider;
			m_attackCollider = NULL;
		}
		m_IsDyingType1 = true;
		m_IsRunning = false;
		m_IsAttacking = false;
		SoundManager::GetInstance()->PlaySound("final_boss_1_dying", 0, 12);
		
	}
	if (Type == 2 && m_Health <= 0) {
		Clean();
	}
	DyingHandler();
	RevivingHandler();
	
	AnimationState();

	if(m_Animation != NULL) m_Animation->Update();
}

void Final_Boss::AnimationState()
{
	if (m_Animation != NULL) {
		std::string currentState;
		//idle

		if (!m_IsRunning && !m_IsAttacking && !m_IsDyingType1 && !m_IsReviving && !m_IsCasting) {
			currentState = "idle";
			if (currentState != m_LastState) {
				if (Type == 1) {
					m_Animation->SetProps("final_boss_1_idle", 1, 14, 100, 14);
				}
				else if (Type == 2) {
					m_Animation->SetProps("final_boss_2_idle", 1, 14, 100, 14);
				}

				m_Animation->Start();
			}
		}

		//running

		if (m_IsRunning && !m_IsAttacking && !m_IsDyingType1 && !m_IsReviving) {
			currentState = "running";
			if (currentState != m_LastState) {
				if (Type == 1) {
					m_Animation->SetProps("final_boss_1_run", 1, 8, 100, 8);
				}
				else if (Type == 2) {
					m_Animation->SetProps("final_boss_2_run", 1, 8, 100, 8);
				}
				m_Animation->Start();
			}
		}
		//attacking
		if (m_IsAttacking && !m_IsRunning && !m_IsDyingType1 && !m_IsReviving) {
			currentState = "attacking";
			if (currentState != m_LastState) {
				if (Type == 1) {
					m_Animation->SetProps("final_boss_1_attack", 1, 22, 90, 22);
				}
				else if (Type == 2) {
					m_Animation->SetProps("final_boss_2_attack", 1, 25, 150, 25);
				}
				m_Animation->Start();
			}
		}
		if (m_IsCasting && !m_IsReviving && !m_IsRunning && !m_IsDyingType1 && !m_IsAttacking) {
			currentState = "casting";
			if (currentState != m_LastState) {
				if (Type == 1) {
					m_Animation->SetProps("final_boss_1_casting", 1, 12, 250, 12);
				}
				else if (Type == 2) {
					m_Animation->SetProps("final_boss_2_casting", 1, 12, 250, 12);
				}
				m_Animation->Start();
			}
		}
		//dying
		if (m_IsDyingType1 && !m_IsReviving) {
			currentState = "dyingtype1";
			if (currentState != m_LastState) {
				m_Animation->SetProps("final_boss_1_dying", 1, 22, 150, 22);
				m_Animation->Start();
			}
		}
		if (m_IsReviving) {
			currentState = "reviving";
			if (currentState != m_LastState) {
				m_Animation->SetProps("final_boss_reviving", 1, 19, 150, 19);
				m_Animation->Start();
			}
		}
		m_LastState = currentState;
		if (m_RevivingWaiting) {
			m_Animation->SetProps("asdasd", 1, 19, 100, 19);
		}
	}
	
}

void Final_Boss::Follow_Warrior(Vector2D F) {
	
	m_Position.X = m_Origin->X;
	m_Position.Y = m_Origin->Y;
	//std::cout << m_Origin->X << " " << m_Origin->Y << std::endl;
	m_Direction = F - m_Position;

	m_Direction = m_Direction.Normalize();

	m_IsRunning = true;
	if (m_Direction.X > 0) {
		m_Flip = SDL_FLIP_NONE;
	}
	else if (m_Direction.X < 0) {
		m_Flip = SDL_FLIP_HORIZONTAL;
	}
}

Collider* Final_Boss::AttackZone(float dt) {

	if (m_IsAttacking) {
		if ((Type == 1 && m_Animation->getSpriteFrame() >= 16 && m_Animation->getSpriteFrame() <= 18)||(Type == 2 && m_Animation->getSpriteFrame() >= 7 && m_Animation->getSpriteFrame() <= 20)) {
			if (m_attackCollider == NULL) {
				m_attackCollider = new Collider();
			}
			if (Type == 1) {
				
				m_attackCollider->SetBuffer(-20, -60, 40, 70);
				m_attackCollider->Set(m_Transform->X, m_Transform->Y, m_Width, m_Height);
			}
			else if (Type == 2) {
				if (m_Flip == SDL_FLIP_NONE) {
					m_attackCollider->SetBuffer(-60, -70, 70, 90);
				}
				else {
					m_attackCollider->SetBuffer(-10, -70, 100, 90);
				}
				
				m_attackCollider->Set(m_Transform->X, m_Transform->Y, m_Width, m_Height);
			}
			
		}
	}
	return m_attackCollider;
}

void Final_Boss::AttackHandler()
{
	//if(m_Animation != NULL) std::cout << m_Animation->getID()<<std::endl;
	if (m_Animation != NULL && ((Type == 1 && m_Animation->getSpriteFrame() > 18)||(Type == 2&&m_Animation->getSpriteFrame() > 20))) {
		if (m_attackCollider != NULL) {
			delete m_attackCollider;
			m_attackCollider = NULL;
		}
	}
	if (m_IsAttacking && m_FinishAttack == false) {
		if((m_Animation != NULL && Type==1 &&m_Animation->getSpriteFrame() == 21) || (m_Animation != NULL && Type == 2 && m_Animation->getSpriteFrame() == 24))
		m_FinishAttack = true;
	}

	if ((m_Animation != NULL && Type == 1 && m_IsAttacking &&  m_FinishAttack && m_Animation->getSpriteFrame() != 21) ||(m_Animation != NULL && Type == 2 && m_IsAttacking && m_FinishAttack && m_Animation->getSpriteFrame() != 24)) {
		m_IsAttacking = false;
		m_CanAttack = true;
		m_hasDealtDamage = false;
		m_FinishAttack = false;
	}
}

void Final_Boss::DyingHandler() {
	if (m_IsDyingType1) {
		m_IsRunning = false;
		m_IsAttacking = false;
	}
	if (m_IsDyingType1 && m_Animation->getSpriteFrame() == 21 && !m_FinishDyingType1) {
		m_FinishDyingType1 = true;
	}
	if (m_FinishDyingType1 && m_Animation->getSpriteFrame() != 21) {
		m_IsDyingType1 = false;
		m_DiedTimeBegin = SDL_GetTicks();
		m_RevivingWaiting = true;
		m_FinishDyingType1 = false;
		delete m_HealthBar;
		m_HealthBar = NULL;
		Type = 2;
		m_Damage = DAMAGE_TYPE2;
		m_Health = MAX_HEALTH_TYPE2;
		delete m_Animation;
		m_Animation = NULL;
	}
	
}

void Final_Boss::RevivingHandler() {
	if (m_IsReviving || m_RevivingWaiting) {
		m_IsRunning = false;
		m_IsAttacking = false;
	}
	if (m_DiedTimeBegin != 0 && m_IsReviving == false) {
		if ((SDL_GetTicks() - m_DiedTimeBegin) / 1000 == 4) {
			m_Animation = new Animation();
			m_IsReviving = true;
			m_RevivingWaiting = false;
		}
	}
	if (m_Animation!=NULL && m_IsReviving && m_Animation->getSpriteFrame() == 18 && m_FinishReviving == false) {
		m_FinishReviving = true;
	}
	if (m_Animation != NULL && m_FinishReviving && m_Animation->getSpriteFrame() != 18) {
		m_IsReviving = false;
		m_Collider = new Collider();
		m_FinishReviving = false;
		m_HealthBar = new HealthBar(new Properties("final_boss_none_healthbar", 382, 550, 516, 48), MAX_HEALTH_TYPE2);
		m_CanAttack = true;
		SoundManager::GetInstance()->PlaySound("final_boss_revived", 0, 13);
	}
}

void Final_Boss::CastingHandler()
{
	if (!m_IsAttacking && !m_IsDyingType1 && !m_IsReviving && !m_RevivingWaiting) {
		if (m_CanCast) {
			m_CanCast = false;
			m_IsCasting = true;
			m_IsAttacking = false;
			m_FinishCasting = false;
			m_IsRunning = false;
			if ((Type == 1 && m_Health < MAX_HEALTH_TYPE1 / 2) || (Type == 2 && m_Health < MAX_HEALTH_TYPE2 / 2)) {
				cast_type = 1;
				SoundManager::GetInstance()->PlaySound("final_boss_1_casting", 0, 15);
			}
			else {
				cast_type = 2;
				//std::cout << "dang phat am\n";
				SoundManager::GetInstance()->PlaySound("final_boss_2_casting", 0, 16);
			}
		}
	}
	if (m_IsCasting) {
		//std::cout << m_Animation->getSpriteFrame() << std::endl;
		m_IsRunning = false;
		m_IsAttacking = false;
		if (cast_type == 1) {
			if (Type == 1) {
				m_Health += MAX_HEALTH_TYPE1 / 500;
			}
			else m_Health += MAX_HEALTH_TYPE2 / 500;
		}
	}
	if (m_IsCasting && m_FinishCasting == false) {
		if ((m_Animation != NULL && Type == 1 && m_Animation->getSpriteFrame() == 11) || (m_Animation != NULL && Type == 2 && m_Animation->getSpriteFrame() == 11))
			m_FinishCasting = true;
	}
	if ((m_Animation != NULL && Type == 1 && m_IsCasting && m_FinishCasting && m_Animation->getSpriteFrame() != 11) || (m_Animation != NULL && Type == 2 && m_IsCasting && m_FinishCasting && m_Animation->getSpriteFrame() != 11)) {
		m_IsCasting = false;
		m_FinishCasting = false;
		m_CastBeginTime = SDL_GetTicks();
		if (cast_type == 1) Mix_HaltChannel(15);
		else Mix_HaltChannel(16);
		cast_type = 0;
		m_CanAttack = true;
	}
	if ((SDL_GetTicks() - m_CastBeginTime) >= m_CastCooldown*1000 && (SDL_GetTicks() - m_CastBeginTime) < m_CastCooldown * 1000 + 25 && !m_CanCast) {
		//std::cout << "da dat lai\n";
		m_CanCast = true;
		//std::cout << m_CastBeginTime << std::endl;
	}
}
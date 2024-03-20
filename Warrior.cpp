#include "Warrior.h"
#include "TextureManager.h"
#include "Character.h"
#include "Input.h"
#include <SDL.h>
#include "CollisionHandler.h"
#include<iostream>
//#include "Camera.h"
#include "Engine.h"


Warrior::Warrior(Properties* props) : Character(props)
{

	m_Health = 2000;
	m_Damage = 40;

	m_IsRunning = false;
	
	m_IsAttacking = false;
	m_IsCrouching = false;

	m_IsUp = false;
	m_IsDown = false;

	m_Flip = SDL_FLIP_NONE;

	m_Collider = new Collider();
	
	//m_Collider->SetBuffer(-45, -40, 45, 40);

	m_RigidBody = new RigidBody();

	m_Animation = new Animation();

	//m_attackCollider = new Collider();

	

}

void Warrior::Draw()
{
	m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height, m_Flip);
	//Vector2D cam = Camera::GetInstance()->GetPosition();
	SDL_Rect box = m_Collider->Get();
	
	if (m_attackCollider != NULL){
		SDL_Rect box1 = m_attackCollider->Get();
		//SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &box1);
	}
	

	//box.x -= cam.X;
	//box.y -= cam.Y;
	//SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &box);

	
}


void Warrior::Update(float dt)
{
	//m_Health -= dt;
	//printf("mau: %d\n", m_Health);
	if (isAlive() == false) {
		Clean();
	}
	
	m_IsRunning = false;
	m_IsCrouching = false;

	m_Animation->SetProps("player_idle", 1, 10, 100);
	m_RigidBody->UnSetForce();

	//running
	if (Input::GetInstance()->GetAxisKey(HORIZONTAL) == FORWARD) {
		m_RigidBody->ApplyForceX(FORWARD * RUN_FORCE);
		m_Flip = SDL_FLIP_NONE;
		m_IsRunning = true;
	}
	if (Input::GetInstance()->GetAxisKey(HORIZONTAL) == BACKWARD) {
		m_RigidBody->ApplyForceX(BACKWARD * RUN_FORCE);
		m_Flip = SDL_FLIP_HORIZONTAL;
		m_IsRunning = true;
	}
	//m_RigidBody->ApplyForceX(FORWARD * RUN_FORCE);
	//m_IsRunning = true;

	//attack
	/*if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_J)) {
		
	}*/
	
	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_J)) {
		m_IsAttacking = true;
	}
	AttackZone(dt);
	
	if (Input::GetInstance()->GetAxisKey(VERTICAL) == UPWARD)
	{
		m_RigidBody->ApplyForceY(UPWARD * RUN_FORCE);
		//m_Flip = SDL_FLIP_NONE;
		m_IsUp = true;
		m_IsRunning = true;
	}
	if (Input::GetInstance()->GetAxisKey(VERTICAL) == DOWNWARD)
	{
		m_RigidBody->ApplyForceY(DOWNWARD * RUN_FORCE);
		//m_Flip = SDL_FLIP_NONE;
		m_IsDown = true;
		m_IsRunning = true;
	}

	
	//move on X axis

	m_RigidBody->Update(dt);
	m_LastSafePosition.X = m_Transform->X;
	m_Transform->X += m_RigidBody->Position().X;
	m_Collider->SetBuffer(-48, -40, 50, 40);
	m_Collider->Set(m_Transform->X, m_Transform->Y, 66 , 80);
	
	
	

	if (CollisionHandler::GetInstance()->MapCollision(m_Collider->Get())) {
		m_Transform->X = m_LastSafePosition.X;
	}
	//move on Y axis

	m_RigidBody->Update(dt);
	m_LastSafePosition.Y = m_Transform->Y;
	m_Transform->Y += m_RigidBody->Position().Y;
	m_Collider->Set(m_Transform->X, m_Transform->Y, 66, 80);
	m_Collider->SetBuffer(-48, -40, 50, 40);
	


	if (CollisionHandler::GetInstance()->MapCollision(m_Collider->Get())) {
		m_Transform->Y = m_LastSafePosition.Y;
	}

	m_Origin->X = m_Transform->X + m_Width / 2;
	m_Origin->Y = m_Transform->Y + m_Height / 2;

	
	AnimationState();

	m_Animation->Update();
}


Collider* Warrior::AttackZone(float dt)
{
	if (m_attackCollider == NULL) {
		m_attackCollider = new Collider();
	}
	if (m_IsAttacking) {
		if (m_Flip == SDL_FLIP_NONE) {
			m_attackCollider->Set(m_Transform->X + 64, m_Transform->Y, 40, m_Height);
			m_attackCollider->SetBuffer(0, -40, 0, 40);
		}
		else {
			m_attackCollider->Set(m_Transform->X + 12, m_Transform->Y, 40, m_Height);
			m_attackCollider->SetBuffer(-4, -40, 4, 40);
		}


	}

	//Attacking timer
	if (m_IsAttacking && m_AttackTime > 0)
	{
		//printf("Warrior attack time: %f\n", m_AttackTime);
		m_AttackTime -= dt;
	}
	else {
		
		delete m_attackCollider;
		m_attackCollider = NULL;
		m_IsAttacking = false;
		m_AttackTime = ATTACK_TIME;
	}
	return m_attackCollider;

}





void Warrior::AnimationState()
{
	m_Animation->SetProps("player_idle", 1, 10, 100); //idle

	//running
	if (m_IsRunning) m_Animation->SetProps("player_run", 1, 10, 100);
	////crouch
	//if(m_IsCrouching) m_Animation->SetProps("player_crouch", 1, 1, 100);
	//attacking
	if (m_IsAttacking) m_Animation->SetProps("player_attack", 1, 4, 100);
}


void Warrior::Clean()
{
	TextureManager::GetInstance()->Clean();
}





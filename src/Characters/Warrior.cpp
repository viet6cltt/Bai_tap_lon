﻿#include "Warrior.h"
#include "TextureManager.h"
#include "Character.h"
#include "Input.h"
#include <SDL.h>
#include "CollisionHandler.h"
#include<iostream>
#include "Camera.h"


Warrior::Warrior(Properties props) : Character(&props)
{
	m_JumpTime = JUMP_TIME;
	m_JumpForce = JUMP_FORCE;

	m_Collider = new Collider();
	m_Collider->SetBuffer(0,0,0,0);

	m_RigidBody = new RigidBody();
	m_RigidBody->SetGravity(3.0f);

	m_Animation = new Animation();
	m_Animation->SetProps(m_TextureID, 1, 10, 100);
}

void Warrior::Draw()
{
	m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height);

	Vector2D cam = Camera::GetInstance()->GetPosition();
	SDL_Rect box = m_Collider->Get();

	box.x -= cam.X;
	box.y -= cam.Y;
	SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &box);
}

void Warrior::Update(float dt)
{
	
	m_Animation->SetProps("player_idle", 1, 10, 100);
	m_RigidBody->UnSetForce();

	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A))
	{
		m_RigidBody->ApplyForceX(4*BACKWARD);
		m_Animation->SetProps("player_run", 1, 10, 100,SDL_FLIP_HORIZONTAL);
	}
	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D))
	{
		m_RigidBody->ApplyForceX(4 * FORWARD);
		m_Animation->SetProps("player_run", 1, 10, 100);
	}

	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_J)) {
		m_Animation->SetProps("player_attack", 1, 4, 100);
		if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D)) {
			m_Animation->SetProps("player_attack", 1, 4, 100);
		}
		if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A)) {
			m_Animation->SetProps("player_attack", 1, 4, 100,SDL_FLIP_HORIZONTAL);
		}
		
	}

	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_W)&&m_IsGround) 
		{
			m_IsJumping = true;
			m_IsGround = false;
			m_RigidBody->ApplyForceY(UPWARD * m_JumpForce);
			
			
		}
	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_W) && m_IsJumping && m_JumpTime > 0)
	{
		m_JumpTime -= dt;
		m_RigidBody->ApplyForceY(UPWARD * m_JumpForce);
		
	}
	else
	{
		m_IsJumping = false;
		m_JumpTime = JUMP_TIME;
	}
	
	m_RigidBody->Update(dt);
	//move on X axis
	m_RigidBody->Update(dt);
	m_LastSafePosition.X = m_Transform->X;
	m_Transform->X += m_RigidBody->Position().X;
	m_Collider->Set(m_Transform->X, m_Transform->Y, 60, 60);

	if (CollisionHandler::GetInstance()->MapCollision(m_Collider->Get())) {
		std::cout << "dang bi mac x" << std::endl;
		m_Transform->X = m_LastSafePosition.X;
	}
	//move on Y axis
	m_RigidBody->Update(dt);
	m_LastSafePosition.Y = m_Transform->Y;
	
	m_Transform->Y += m_RigidBody->Position().Y;
	m_Collider->Set(m_Transform->X, m_Transform->Y, 70, 70);

	if (CollisionHandler::GetInstance()->MapCollision(m_Collider->Get())) {
		std::cout << "dang bi mac y"<<std::endl;
		m_IsGround = true;
		m_Transform->Y = m_LastSafePosition.Y;
	}
	else {
		m_IsGround = false;
	}

	if (m_IsJumping || !m_IsGround) {
		m_Animation->SetProps("player_jump", 1, 2, 100);
		if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A)) {
			m_Animation->SetProps("player_jump", 1, 2, 100, SDL_FLIP_HORIZONTAL);
		}
	}

	m_Origin->X = m_Transform->X + m_Width / 2;
	m_Origin->Y = m_Transform->Y + m_Height / 2;



	m_Animation->Update();
}

void Warrior::Clean()
{
	TextureManager::GetInstance()->Clean();
}




#include "Enemy_Boss1.h"

#include "TextureManager.h"
#include "Character.h"
#include "Input.h"
#include <SDL.h>
#include "CollisionHandler.h"
#include<iostream>
//#include "Camera.h"
#include "Engine.h"

Enemy_Boss1::Enemy_Boss1(Properties* props) : Enemy(props)
{
	m_hasReceivedDamage["normal"] = false;
	m_hasReceivedDamage["slash"] = false;
	m_hasReceivedDamage["gravity"] = false;
	m_hasReceivedDamage["hasagi"] = false;
	m_Health = 4000;
	m_Damage = 300;
	m_IsRunning = false;
	m_AttackBeginFrames = 4;
	m_AttackFinishFrames = 5;
	m_FinishHurt = false;
	m_hasDealtDamage = false;
	hasFlipped = false;

	
	m_IsAttacking = false;
	
	m_CanAttack = true;
	m_IsHurt = false;

	center = new SDL_Point();
	center->x = 200;
	center->y = 54;

	m_Flip = SDL_FLIP_NONE;

	m_Collider = new Collider();
	//m_Collider->SetBuffer(-45, -40, 45, 40);
	m_attackCollider = NULL;

	m_RigidBody = new RigidBody();
	//m_Position = new Vector2D;

	m_Animation = new Animation();
	m_HealthBar = new HealthBar(new Properties("enemy_bar", m_Transform->X + 70, m_Transform->Y + 43, 29, 5), m_Health);
}

void Enemy_Boss1::Draw()
{
	//std::cout << center->x << std::endl;
	m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height, m_Flip,NULL);
	//Vector2D cam = Camera::GetInstance()->GetPosition();
	SDL_Rect box = m_Collider->Get();

	if (m_attackCollider != NULL) {
		SDL_Rect box1 = m_attackCollider->Get();
		SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &box1);
	}

	//TextureManager::GetInstance()->Draw("enemy_bar", m_Transform->X + 70, m_Transform->Y + 43, 29, 5);
	m_HealthBar->Draw();
	//box.x -= cam.X;
	//box.y -= cam.Y;
	SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &box);
}

void Enemy_Boss1::Update(float dt) {
	m_HealthBar->setProperties(m_Transform->X + 70, m_Transform->Y + 43, 29, 5);
	m_HealthBar->setCurrentHealth(m_Health);
	m_HealthBar->Update(dt);

	if (isAlive() == false) {
		Clean();
	}
	/*----------------xu li tan cong--------------------------*/
	if (m_Animation->getSpriteFrame() > m_AttackFinishFrames) {
		if (m_attackCollider != NULL) {
			delete m_attackCollider;
			m_attackCollider = NULL;
		}
	}
	if (m_IsAttacking && m_Animation->getSpriteFrame() == 1 && m_Animation->getSpriteRow() == 4 && m_FinishAttack == false) {
		m_FinishAttack = true;
	}
	
	if (m_IsAttacking && m_Animation->getSpriteFrame() ==0 && m_FinishAttack) {
		m_IsAttacking = false;
		m_CanAttack = true;
		m_hasDealtDamage = false;
		m_FinishAttack = false;
	}
	AttackZone(dt);
	
	//-----------xu li di chuyen------------------------
	m_RigidBody->UnSetForce();	
	if (!m_IsAttacking && !m_IsHurt) {
		m_RigidBody->ApplyForce(m_Direction * RUN_FORCE);
	}
	
	/*--------------------------xu li bi thuong-----------------------*/
	if (m_IsHurt) {
		m_RigidBody->UnSetForce();
		if (m_IsAttacking) {
			delete m_attackCollider;
			m_attackCollider = NULL;
		}
	}
	if (m_IsHurt && m_Animation->getSpriteFrame() == 5 && !m_FinishHurt) {
		m_FinishHurt = true;
	}
	if (m_FinishHurt && m_Animation->getSpriteFrame() != 5 ) {
		m_IsHurt = false; 
		m_FinishHurt = false;
	}
	/*-------------------------------------------------------*/

	m_RigidBody->Update(dt);
	m_LastSafePosition.X = m_Transform->X;
	m_Transform->X += m_RigidBody->Position().X;
	//m_Collider->SetBuffer(-75, -35,90, 40);

	m_RigidBody->Update(dt);
	m_LastSafePosition.Y = m_Transform->Y;
	m_Transform->Y += m_RigidBody->Position().Y;
	//m_Collider->Set(m_Transform->X, m_Transform->Y, m_Width, m_Height);
	//m_Collider->SetBuffer(0, 0, 0, 0);

	//std::cout << "m_Transferom->x" << m_Transform->X<<std::endl;
	if (m_Flip == SDL_FLIP_NONE) {
		m_Collider->SetBuffer(-160, -80, 170, 80);
	}
	else {
		m_Collider->SetBuffer(-40, -80, 170, 80);
	}
	m_Collider->Set(m_Transform->X, m_Transform->Y, m_Width, m_Height);
	if (CollisionHandler::GetInstance()->MapCollision(m_Collider->Get())) {
		m_Transform->X = m_LastSafePosition.X;
	}
	

	if (CollisionHandler::GetInstance()->MapCollision(m_Collider->Get())) {
		m_Transform->Y = m_LastSafePosition.Y;
	}

	AnimationState();

	m_Animation->Update();
	
}
void Enemy_Boss1::AnimationState()
{
	std::string currentState;
	//idle
	if (!m_IsRunning && !m_IsAttacking && !m_IsHurt) {
		currentState = "idle";
		if (currentState != m_LastState) {
			m_Animation->SetProps("boss1", 1, 8, 100, 8);
			m_Animation->Start();
		}
	}

	//running
	
	if (m_IsRunning && !m_IsAttacking && !m_IsHurt) {
		currentState = "running";
		if (currentState != m_LastState) {
			if (m_IsRunning) m_Animation->SetProps("boss1", 2, 8, 100, 8);
			m_Animation->Start();
		}
	}
	//attacking
	if (m_IsAttacking && !m_IsHurt && !m_IsRunning) {
		currentState = "attacking";
		if (currentState != m_LastState) {
			if (m_IsAttacking) m_Animation->SetProps("boss1", 3, 10, 300, 8);
			m_Animation->Start();
		}
	}
	//hurting	
	if (m_IsHurt && !m_IsAttacking && !m_IsRunning) {
		currentState = "hurt";
		if (currentState != m_LastState) {
			m_Animation->SetProps("boss1", 4, 4, 150, 8, 2);
			m_Animation->Start();
		}
	}
	m_LastState = currentState;

}



void Enemy_Boss1::Clean(){
	TextureManager::GetInstance()->Drop("boss_1");
	//TextureManager::GetInstance()->Drop("skeleton_idle");
	//TextureManager::GetInstance()->Drop("skeleton_attack");

}



void Enemy_Boss1::Follow_Warrior(Vector2D F)
{
	//std::cout << F.X << " " << F.Y << std::endl;
	m_Position.X = m_Origin->X;
	m_Position.Y = m_Origin->Y;
	
	//printf("toa do cua quai: %f %f\n", m_Position.X, m_Position.Y);
	m_Direction = F - m_Position;
	//printf("toa do cua quai: %f %f\n", F.X, F.Y);
	m_Direction = m_Direction.Normalize();
	//printf("toa do cua nhan vat: %f %f\n", direction.X, direction.Y);
	m_IsRunning = true;
	
	if (m_Direction.X > 0) {
		m_Flip = SDL_FLIP_HORIZONTAL;
	}
	else if (m_Direction.X < 0) {
		m_Flip = SDL_FLIP_NONE;
	}
	
	if (m_Flip == SDL_FLIP_HORIZONTAL && !hasFlipped)
	{
		m_Transform->X += 2 * center->x - m_Width;
		m_Origin->X = m_Transform->X + m_Width - center->x;
		hasFlipped = true;  // Đánh dấu rằng hình ảnh đã được lật
	}
	else if (m_Flip == SDL_FLIP_NONE && hasFlipped)
	{
		m_Transform->X -= 2 * center->x - m_Width;
		m_Origin->X = m_Transform->X + center->x;
		hasFlipped = false;  // Đặt lại biến khi hình ảnh không được lật
	}
	else if (m_Flip == SDL_FLIP_NONE && !hasFlipped) {
		m_Origin->X = m_Transform->X + center->x;
	}
	else {
		m_Origin->X = m_Transform->X + m_Width - center->x;
	}
	
	m_Origin->Y = m_Transform->Y + m_Height / 2;


}



Collider* Enemy_Boss1::AttackZone(float dt) {
	
	if (m_IsAttacking && m_Animation->getSpriteFrame() >= m_AttackBeginFrames && m_Animation->getSpriteFrame() <= m_AttackFinishFrames) {
		//std::cout << m_Animation->getSpriteFrame() << std::endl;
		if (m_attackCollider == NULL) {
			m_attackCollider = new Collider();
			
		}
		if (m_Flip == SDL_FLIP_NONE) {
			m_attackCollider->SetBuffer(-10, -10, 40, 10);
		}
		else {
			m_attackCollider->SetBuffer(-40, -10, 50, 10);
		}
		m_attackCollider->Set(m_Transform->X, m_Transform->Y, m_Width, m_Height);
	}
	return m_attackCollider;
}

#include "Enemy1.h"

#include "TextureManager.h"
#include "Character.h"
#include "Input.h"
#include <SDL.h>
#include "CollisionHandler.h"
#include<iostream>
//#include "Camera.h"
#include "Engine.h"

Enemy1::Enemy1(Properties* props) : Enemy(props)
{
	m_Health = 300;
	m_Damage = 20;
	m_IsRunning = false;

	m_AttackTime = ATTACK_TIME;

	m_HasAttackedPostCollision = false;
	m_IsAttacking = false;
	m_IsCrouching = false;
	m_CanAttack = true;
	m_IsUp = false;
	m_IsDown = false;

	center = new SDL_Point;
	center->x = m_Width / 2;
	center->y = m_Height / 2;

	m_Flip = SDL_FLIP_NONE;

	m_Collider = new Collider();
	//m_Collider->SetBuffer(-45, -40, 45, 40);

	m_RigidBody = new RigidBody();
	//m_Position = new Vector2D;

	m_Animation = new Animation();
	m_HealthBar = new HealthBar(new Properties("enemy_bar", m_Transform->X + 70, m_Transform->Y + 43, 29, 5), 300);
}


void Enemy1::Draw()
{
	m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height, m_Flip, center);
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

void Enemy1::Update(float dt) {
	m_HealthBar->setProperties(m_Transform->X + 70, m_Transform->Y + 43, 29, 5);
	m_HealthBar->setCurrentHealth(m_Health);
	m_HealthBar->Update(dt);

	//m_Health -= dt;
	if (isAlive() == false) {
		Clean();
	}

	if (m_IsAttacking) {
		AttackZone(dt);
		//printf("Attack time: %f\n", m_AttackTime);
		m_RigidBody->UnSetForce();
	}

	
	m_IsCrouching = false;

	//m_Animation->SetProps("skeleton_idle", 1, 4, 100);
	m_RigidBody->UnSetForce();

	//m_Flip = SDL_FLIP_NONE;
	m_RigidBody->ApplyForce(m_Direction * RUN_FORCE);
	/*m_RigidBody->ApplyForceX(BACKWARD * RUN_FORCE / 2);
	m_IsRunning = true;
	m_Flip = SDL_FLIP_HORIZONTAL;*/

	/*if (Input::GetInstance()->GetLeftMouseButton()) {
		m_IsAttacking = true;
	}

	if (m_IsAttacking && m_AttackTime > 0)
	{
		printf("attack time: %f\n", m_AttackTime);
		m_AttackTime -= dt;
	}
	else {
		m_IsAttacking = false;
		m_AttackTime = ATTACK_TIME;
	}*/

	//(m_FollowDirection);

	m_RigidBody->Update(dt);
	m_LastSafePosition.X = m_Transform->X;
	m_Transform->X += m_RigidBody->Position().X;
	m_Collider->SetBuffer(-58, -50, 110, 100);
	m_Collider->Set(m_Transform->X,m_Transform->Y , 50, 50);

	if (CollisionHandler::GetInstance()->MapCollision(m_Collider->Get())) {
		m_Transform->X = m_LastSafePosition.X;
	}
	

	m_RigidBody->Update(dt);
	m_LastSafePosition.Y = m_Transform->Y;
	m_Transform->Y += m_RigidBody->Position().Y;
	m_Collider->Set(m_Transform->X, m_Transform->Y, 150, 150);
	m_Collider->SetBuffer(0, 0, 0, 0);

	if (CollisionHandler::GetInstance()->MapCollision(m_Collider->Get())) {
		m_Transform->Y = m_LastSafePosition.Y;
	}

	m_Origin->X = m_Transform->X + m_Width / 2;
	m_Origin->Y = m_Transform->Y + m_Height / 2;

	//Di chuyen theo nhan vat

	AnimationState();
	
	m_Animation->Update();


}
bool Enemy1::Attack(float dt) {
	if (!m_IsAttacking && m_CanAttack) {
		m_IsAttacking = true;
		m_CanAttack = false; // Ngăn không cho tấn công lại cho đến khi đã sẵn sàng
		m_AttackTime = ATTACK_TIME; // Thời gian cho một lần tấn công
		//m_CurrentFrame = 0;
		// Bắt đầu hoạt hình tấn công
	}
	return true;
}


void Enemy1::AnimationState()
{
	m_Animation->SetProps("skeleton_idle", 1, 4, 100,4); //idle

	//running
	if (m_IsRunning) m_Animation->SetProps("skeleton_run", 1, 4, 100,4);
	////crouch
	//if(m_IsCrouching) m_Animation->SetProps("player_crouch", 1, 1, 100);
	//attacking
	if (m_IsAttacking) m_Animation->SetProps("skeleton_attack", 1, 8, 250,8);
}



void Enemy1::Clean()
{
	//TextureManager::GetInstance()->Drop("skeleton_run");
	//TextureManager::GetInstance()->Drop("skeleton_idle");
	//TextureManager::GetInstance()->Drop("skeleton_attack");

}

Collider* Enemy1::AttackZone(float dt) {
	if (m_attackCollider == NULL) {
		m_attackCollider = new Collider();
	}
	if (m_IsAttacking) {
		if (m_Flip == SDL_FLIP_NONE) {
			m_attackCollider->Set(m_Transform->X + 80, m_Transform->Y, 50, m_Height);
			m_attackCollider->SetBuffer(-10, -50, 0, 110);
		}
		else {
			m_attackCollider->Set(m_Transform->X + 20 , m_Transform->Y, 40, m_Height);
			m_attackCollider->SetBuffer(0, -50, 0, 110);
		}


	}

	//Attacking timer
	if (m_IsAttacking && m_AttackTime > 0)
	{
		//printf("Warrior attack time: %f\n", m_AttackTime);
		m_AttackTime -= dt;
	}
	else {

		
	}
	if (m_AttackTime <= 0) {
		m_IsAttacking = false;
		m_CanAttack = true;
		delete m_attackCollider;
		m_attackCollider = NULL;
		m_AttackTime = ATTACK_TIME;
		// Kết thúc hoạt hình tấn công
	}
	return m_attackCollider;

}

void Enemy1::Follow_Warrior(Vector2D F)
{
	m_Position.X = m_Origin->X;
	m_Position.Y = m_Origin->Y;
	//printf("toa do cua quai: %f %f\n", m_Position.X, m_Position.Y);
	m_Direction = F - m_Position;
	//printf("toa do cua quai: %f %f\n", F.X, F.Y);
	m_Direction = m_Direction.Normalize();
	//printf("toa do cua nhan vat: %f %f\n", direction.X, direction.Y);
	m_IsRunning = true;
	if (m_Direction.X > 0) {
		m_Flip = SDL_FLIP_NONE;
	}
	else if (m_Direction.X < 0) {
		m_Flip = SDL_FLIP_HORIZONTAL;
		//printf("Da lat");
	}

}

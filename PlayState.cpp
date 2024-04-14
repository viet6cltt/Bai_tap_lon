﻿#include "PlayState.h"
#include "PauseState.h"
#include "MenuState.h"
#include "SpecialAbiliyState.h"
#include "GameOverState.h"
#include "CollisionHandler.h"
#include <cstdlib>
const std::string PlayState::s_playID = "PLAY";
Map* map = NULL;
bool PlayState::OnEnter() {
    m_Score = 0;
    m_SpawnTimer = 0;

    //font
    FontManager::GetInstance()->LoadFont("score", "assets\\ExpressionPro.ttf", 40);
    FontManager::GetInstance()->LoadFont("m_score", "assets\\ExpressionPro.ttf", 40);
    //player
    TextureManager::GetInstance()->Load("background", "assets\\Background_2.png");
    TextureManager::GetInstance()->Load("player", "assets\\NightBorne\\NightBorne.png");
    //Enemy1
    TextureManager::GetInstance()->Load("skeleton_idle", "assets\\Monsters_Creatures_Fantasy\\Skeleton\\Idle.png");
    TextureManager::GetInstance()->Load("skeleton_run", "assets\\Monsters_Creatures_Fantasy\\Skeleton\\Walk.png");
    TextureManager::GetInstance()->Load("skeleton_attack", "assets\\Monsters_Creatures_Fantasy\\Skeleton\\Attack.png");
    TextureManager::GetInstance()->Load("skeleton_hurt", "assets\\Monsters_Creatures_Fantasy\\Skeleton\\Take Hit.png");
    //Boss1
    TextureManager::GetInstance()->Load("boss1", "assets\\BringerOfDeath\\SpriteSheet\\BringerofDeathSpritSheet.png");
    //thanh mau
    TextureManager::GetInstance()->Load("enemy_bar", "assets\\enemy_Bar.png");
    TextureManager::GetInstance()->Load("none_bar", "assets\\None_HealthBar1.png");
    TextureManager::GetInstance()->Load("player_fullhealth", "assets\\Full_HealthBar1.png");
    //TextureManager::GetInstance()->Load("heart", "assets\\Heart.png");
    //skill
    TextureManager::GetInstance()->Load("skill_1", "assets\\skill_1.png");
    TextureManager::GetInstance()->Load("healingicon", "assets\\skills\\48x48\\skill_icons10.png");
    TextureManager::GetInstance()->Load("cd_healingicon", "assets\\skills\\48x48\\skill_icons10_cooldown.png");
    TextureManager::GetInstance()->Load("gravityskill", "assets\\Gravity.png");
    TextureManager::GetInstance()->Load("gravityicon", "assets\\skills\\48x48\\skill_icons24.png");
    TextureManager::GetInstance()->Load("cd_gravityicon", "assets\\skills\\48x48\\skill_icons24_cooldown.png");
    TextureManager::GetInstance()->Load("slashskill", "assets\\bigslash.png");
    TextureManager::GetInstance()->Load("slashicon", "assets\\skills\\48x48\\skill_icons51.png");
    TextureManager::GetInstance()->Load("cd_slashicon", "assets\\skills\\48x48\\skill_icons51_cooldown.png");
    TextureManager::GetInstance()->Load("hasagiicon", "assets\\skills\\48x48\\skill_icons43.png");
    TextureManager::GetInstance()->Load("cd_hasagiicon", "assets\\skills\\48x48\\skill_icons43_cooldown.png");
    TextureManager::GetInstance()->Load("u_key", "assets\\U-Key.png");
    TextureManager::GetInstance()->Load("i_key", "assets\\I-Key.png");

    //sfx
    SoundManager::GetInstance()->Load("playstate_music", "assets\\playstate_music.ogg", SOUND_MUSIC, MIX_MAX_VOLUME / 3);
    SoundManager::GetInstance()->PlayMusic("playstate_music", -1);

    //UI
    

    m_Warrior = new Warrior(new Properties("player_idle", 350, 100, 80, 80));
    m_playerheal = new HealthBar(new Properties("none_bar", 10, 10, 240, 27),m_Warrior->getmaxHealth());

    //m_Enemies.push_back(new Enemy1(new Properties("skeleton_idle", 100, 200, 150, 150)));

    //m_Enemies.push_back(new Enemy1(new Properties("skeleton_idle", 300, 500, 150, 150)));
    //m_Enemies.push_back(new Enemy_Boss1(new Properties("boss1", 400 ,500, 140, 93)));
    map = new Map();
    return true;
}

bool PlayState::OnExit() {
    //TextureManager::GetInstance()->Drop("background");
    Mix_HaltMusic();
    m_Warrior->Clean();
    for (int i = 0; i < m_Enemies.size(); i++) {
        m_Enemies[i]->Clean();
    }
    TextureManager::GetInstance()->Drop("heart");
    m_playerheal->Clean();
    TextureManager::GetInstance()->clearFromTextureMap("player_idle");
    return true;
}
void PlayState::Render() {
    TextureManager::GetInstance()->Draw("background", 0, 0, 1390, 640);
    map->DrawMap();
    //TextureManager::GetInstance()->Draw("heart", 20, 50, 23, 21);
    m_playerheal->Draw(); 
    
    FontManager::GetInstance()->RenderText("score", "SCORES: ", 20, 100, { 255, 255, 255, 255 });
    FontManager::GetInstance()->RenderText("m_score", std::to_string(m_Score).c_str(), 150, 100, { 255, 255, 255, 255 });
    
    m_Warrior->Draw();

    for (int i = 0; i < m_Enemies.size(); i++) {
        m_Enemies[i]->Draw();
    }
}

void PlayState::Update(float dt) {

    m_SpawnTimer += dt;
    if (m_SpawnTimer >= 100.0f) {
        SpawnEnemy();
        m_SpawnTimer = 0.0f; // Đặt lại biến đếm
    }
    if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_ESCAPE)) {
        printf("play to pause\n");
        Engine::GetInstance()->getStateMachine()->pushState(new PauseState());
    }
    m_playerheal->setCurrentHealth(m_Warrior->getHealth());
    m_playerheal->Update(dt);
    
    for (int i = 0; i < m_Enemies.size(); i++) {
        if (CollisionHandler::GetInstance()->CheckCollision(m_Warrior->getCollider()->Get(), m_Enemies[i]->getCollider()->Get())) {
            m_Enemies[i]->Attack(dt);
        }
    }
    m_Warrior->Update(dt);
    //skill hasagi
    if (m_Warrior->canUseHasage() && Input::GetInstance()->GetKeyDown(SDL_SCANCODE_O)) {
        printf("play to specialability\n");
        Engine::GetInstance()->getStateMachine()->pushState(new SpecialAbilityState());
        m_Warrior->setisSkill_Hasagi(true);
    }
    //--------------------------
    Collider* player_attackZone = m_Warrior->getAttackZone();
    Collider* gravityskillZone = m_Warrior->getGravityZone();
    Collider* hasagiskillZone = NULL;
    Collider* slashskillZone = m_Warrior->getSlashZone();
    if(m_Warrior->getHasagiSkill()!=NULL) hasagiskillZone = m_Warrior->getHasagiSkill()->getAttackZone();
    if (player_attackZone != NULL) {
        //std::cout << player_attackZone->Get().w << std::endl;
    }
        for (int j = 0; j < m_Enemies.size(); j++) {
            //Follow
            m_Enemies[j]->Follow_Warrior(m_Warrior->getPosition());

            if (player_attackZone!=NULL&&CollisionHandler::GetInstance()->CheckCollision(player_attackZone->Get(), m_Enemies[j]->getCollider()->Get())) {
                // Nếu nhân vật đang tấn công và va chạm với kẻ thù, gây sát thương cho kẻ thù
                m_Enemies[j]->receiveDamage(m_Warrior->getDamage());
            }

            if (gravityskillZone != NULL && CollisionHandler::GetInstance()->CheckCollision(gravityskillZone->Get(), m_Enemies[j]->getCollider()->Get())) {
                m_Enemies[j]->receiveDamage(m_Warrior->getGravitySkillDamage());
            }
            if (hasagiskillZone != NULL && CollisionHandler::GetInstance()->CheckCollision(hasagiskillZone->Get(), m_Enemies[j]->getCollider()->Get())) {
                m_Enemies[j]->receiveDamage(m_Warrior->getHasagiSkill()->getDamage());
            }
            if (slashskillZone != NULL && CollisionHandler::GetInstance()->CheckCollision(slashskillZone->Get(), m_Enemies[j]->getCollider()->Get())) {
                m_Enemies[j]->receiveDamage(m_Warrior->getSlashSkillDamage());
            }

            Collider* enemy_attackZone = m_Enemies[j]->AttackZone(dt);
            if (enemy_attackZone != NULL && CollisionHandler::GetInstance()->CheckCollision(enemy_attackZone->Get(), m_Warrior->getCollider()->Get()))
            {
                m_Warrior->receiveDamage(m_Enemies[j]->getDamage());
            }
            m_Enemies[j]->Update(dt);
        }
        if (!m_Warrior->isAlive()) {
            // Nếu Warrior đã chết, chuyển sang MenuState
            Engine::GetInstance()->getStateMachine()->changeState(new GameOverState());
        }
    
        

    for (int i = 0; i <m_Enemies.size(); i++) {
        if (!m_Enemies[i]->isAlive()) {
            if (dynamic_cast<Enemy1*>(m_Enemies[i])) {
                m_Score += 20;
            }
            else if (dynamic_cast<Enemy_Boss1*>(m_Enemies[i])) {
                m_Score += 40;
            }
            m_Enemies[i]->Clean();
            m_Enemies.erase(m_Enemies.begin() + i);
            break;
        }
    }
    

}

void PlayState::SpawnEnemy() {
    // Tạo ra một số ngẫu nhiên từ 0 đến 100
    int randomNum = rand() % 100;

    // Xác định loại quái dựa trên số ngẫu nhiên
    std::string enemyType;
    if (randomNum < 50) {
        enemyType = "skeleton_idle";
    }
    else {
        enemyType = "boss1";
    }

    // Tạo ra một số ngẫu nhiên cho vị trí X và Y của quái
    int randomX, randomY;
    Collider* enemyCollider;
    do {
        randomX = rand() % SCREEN_WIDTH; 
        randomY = rand() % SCREEN_HEIGHT; 
        enemyCollider = new Collider();
        enemyCollider->Set(randomX, randomY, 150, 150);
        
    } while (CollisionHandler::GetInstance()->MapCollision(enemyCollider->Get()));

    // Thêm quái vào danh sách
    if (enemyType == "skeleton_idle") {
        m_Enemies.push_back(new Enemy1(new Properties(enemyType, randomX, randomY, 150, 150)));
    }
    else if (enemyType == "boss1") {
        m_Enemies.push_back(new Enemy_Boss1(new Properties(enemyType, randomX, randomY, 140, 93)));
    }
}


Vector2D PlayState::FollowWarrior(Enemy* enemy)
{
    Vector2D direction = m_Warrior->getPosition() - enemy->getPosition();
    direction = direction.Normalize();
    return direction;
}


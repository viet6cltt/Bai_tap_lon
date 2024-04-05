#include "PlayState.h"
#include "PauseState.h"
#include "MenuState.h"
#include "SpecialAbiliyState.h"
#include "GameOverState.h"
#include "CollisionHandler.h"
#include <cstdlib>
const std::string PlayState::s_playID = "PLAY";
Map* map = NULL;
bool PlayState::OnEnter() {
    m_SpawnTimer = 0;
    //player
    TextureManager::GetInstance()->Load("background", "assets\\Background_2.png");
    //SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), 200, 191, 231, 255); // Màu tím nhạt
    TextureManager::GetInstance()->Load("player_idle", "assets\\Knight\\Colour2\\Outline\\120x80_PNGSheets\\_Idle.png");
    TextureManager::GetInstance()->Load("player_run", "assets\\Knight\\Colour2\\Outline\\120x80_PNGSheets\\_Run.png");
    TextureManager::GetInstance()->Load("player_attack", "assets\\Knight\\Colour2\\Outline\\120x80_PNGSheets\\_AttackNoMovement.png");
    TextureManager::GetInstance()->Load("player_crounch", "assets\\Knight\\Colour2\\Outline\\120x80_PNGSheets\\_Crouch.png");
    //Enemy1
    TextureManager::GetInstance()->Load("skeleton_idle", "assets\\Monsters_Creatures_Fantasy\\Skeleton\\Idle.png");
    TextureManager::GetInstance()->Load("skeleton_run", "assets\\Monsters_Creatures_Fantasy\\Skeleton\\Walk.png");
    TextureManager::GetInstance()->Load("skeleton_attack", "assets\\Monsters_Creatures_Fantasy\\Skeleton\\Attack.png");
    //Boss1
    TextureManager::GetInstance()->Load("boss1", "assets\\BringerOfDeath\\SpriteSheet\\BringerofDeathSpritSheet.png");
    //thanh mau
    TextureManager::GetInstance()->Load("enemy_bar", "assets\\enemy_Bar.png");
    TextureManager::GetInstance()->Load("none_bar", "assets\\None_Healthbar.png");
    TextureManager::GetInstance()->Load("player_fullhealth", "assets\\Full_HealthBar.png");
    TextureManager::GetInstance()->Load("heart", "assets\\Heart.png");
    //skill
    TextureManager::GetInstance()->Load("skill_1", "assets\\skill_1.png");

    m_Warrior.push_back(new Warrior(new Properties("player_idle", 350, 100, 120, 80)));
    m_playerheal = new HealthBar(new Properties("none_bar", 50, 50, 120, 20),m_Warrior[0]->getHealth());

    //m_Enemies.push_back(new Enemy1(new Properties("skeleton_idle", 100, 200, 150, 150)));

    m_Enemies.push_back(new Enemy1(new Properties("skeleton_idle", 300, 500, 150, 150)));
    m_Enemies.push_back(new Enemy_Boss1(new Properties("boss1", 400 ,500, 140, 93)));
    map = new Map();
    return true;
}

bool PlayState::OnExit() {
    //TextureManager::GetInstance()->Drop("background");
    for (int i = 0; i < m_Warrior.size(); i++) {
        m_Warrior[i]->Clean();
    }
    for (int i = 0; i < m_Enemies.size(); i++) {
        m_Enemies[i]->Clean();
    }
    TextureManager::GetInstance()->Drop("heart");
    m_playerheal->Clean();
    m_Warrior.clear();
    TextureManager::GetInstance()->clearFromTextureMap("player_idle");
    return true;
}
void PlayState::Render() {
    TextureManager::GetInstance()->Draw("background", 0, 0, 1390, 640);
    map->DrawMap();
    TextureManager::GetInstance()->Draw("heart", 20, 50, 23, 21);
    m_playerheal->Draw(); 
    
    
    for (int i = 0; i < m_Warrior.size(); i++) {
        m_Warrior[i]->Draw();
    }

    for (int i = 0; i < m_Enemies.size(); i++) {
        m_Enemies[i]->Draw();
    }
}

void PlayState::Update(float dt) {

    m_SpawnTimer += dt;
    //if (m_SpawnTimer >= 50.0f) {
    //    SpawnEnemy();
    //    m_SpawnTimer = 0.0f; // Đặt lại biến đếm
    //}
    if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_ESCAPE)) {
        printf("play to pause\n");
        Engine::GetInstance()->getStateMachine()->pushState(new PauseState());
    }
    m_playerheal->setCurrentHealth(m_Warrior[0]->getHealth());
    m_playerheal->Update(dt);
    
    for (int i = 0; i < m_Enemies.size(); i++) {
        if (CollisionHandler::GetInstance()->CheckCollision(m_Warrior[0]->getCollider()->Get(), m_Enemies[i]->getCollider()->Get())) {
            m_Enemies[i]->Attack(dt);

        }

    }

    if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_K)) {
        printf("play to specialability\n");
        Engine::GetInstance()->getStateMachine()->pushState(new SpecialAbilityState());
        m_Warrior[0]->setisSkill_Hasagi(true);
    }
   
    for (int i = 0; i < m_Warrior.size(); i++) {
        m_Warrior[i]->Update(dt);

        for (int j = 0; j < m_Enemies.size(); j++) {
            
            Collider* player_attackZone = m_Warrior[i]->AttackZone(dt);
            //Follow
            m_Enemies[j]->Follow_Warrior(m_Warrior[i]->getPosition());

            if (player_attackZone!=NULL&&CollisionHandler::GetInstance()->CheckCollision(player_attackZone->Get(), m_Enemies[j]->getCollider()->Get())) {
                // Nếu nhân vật đang tấn công và va chạm với kẻ thù, gây sát thương cho kẻ thù
                m_Enemies[j]->receiveDamage(m_Warrior[i]->getDamage());
            }
            Collider* enemy_attackZone = m_Enemies[j]->AttackZone(dt);
            if (enemy_attackZone != NULL && CollisionHandler::GetInstance()->CheckCollision(enemy_attackZone->Get(), m_Warrior[i]->getCollider()->Get()))
            {
                printf("bi dinh damage\n");
                m_Warrior[i]->receiveDamage(m_Enemies[j]->getDamage());
            }
            m_Enemies[j]->Update(dt);
        }

        if (dynamic_cast<Warrior*>(m_Warrior[i]) && !m_Warrior[i]->isAlive()) {
            // Nếu Warrior đã chết, chuyển sang MenuState
            Engine::GetInstance()->getStateMachine()->changeState(new GameOverState());
            break;
        }
    }

    for (int i = 0; i <m_Enemies.size(); i++) {
        //m_Enemies[i]->Update(dt);
        if (dynamic_cast<Enemy1*>(m_Enemies[i]) && !m_Enemies[i]->isAlive()) {
            printf("quai da die");
            m_Enemies[i]->Clean();
            m_Enemies.erase(m_Enemies.begin() + i);
            break;
        }
    }
    

}

void PlayState::SpawnEnemy() {
    // Tạo ra một số ngẫu nhiên từ 0 đến 100
    int randomNum = rand() % 50;

    // Xác định loại quái dựa trên số ngẫu nhiên
    std::string enemyType;
    if (randomNum < 50) {
        enemyType = "skeleton_idle";
    }
    else {
        // Thêm các loại quái khác ở đây
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
    m_Enemies.push_back(new Enemy1(new Properties(enemyType, randomX, randomY, 150, 150)));
}


Vector2D PlayState::FollowWarrior(Enemy* enemy)
{
    Vector2D direction = m_Warrior[0]->getPosition() - enemy->getPosition();
    direction = direction.Normalize();
    return direction;
}


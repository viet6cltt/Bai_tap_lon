#include "PlayState.h"
#include "PauseState.h"
#include "MenuState.h"
#include "SpecialAbiliyState.h"
#include "GameOverState.h"
#include "CollisionHandler.h"
#include <cstdlib>
#include "VictoryState.h"
const std::string PlayState::s_playID = "PLAY";
Map* map = NULL;
bool PlayState::OnEnter() {
    m_Score = 0;
    m_SpawnTimer = 0;
    m_Obelysk = NULL;
    summon_ememies_count = 2;
    is_summoned = false;
    //font
    FontManager::GetInstance()->LoadFont("score", "assets\\ExpressionPro.ttf", 40);
    FontManager::GetInstance()->LoadFont("m_score", "assets\\ExpressionPro.ttf", 40);
    //player
    TextureManager::GetInstance()->Load("playstate_background", "assets\\playstate_background.png");
    if (Engine::GetInstance()->getPlayerType() == 1) {
        TextureManager::GetInstance()->Load("player1_idle", "assets\\player1_idle.png");
        TextureManager::GetInstance()->Load("player1_attacking", "assets\\player1_attacking.png");
        TextureManager::GetInstance()->Load("player1_running", "assets\\player1_running.png");
    }
    else {
        TextureManager::GetInstance()->Load("player2_idle", "assets\\player2_idle.png");
        TextureManager::GetInstance()->Load("player2_attacking", "assets\\player2_attacking.png");
        TextureManager::GetInstance()->Load("player2_running", "assets\\player2_running.png");
    }
    

    //Enemy1
    TextureManager::GetInstance()->Load("skeleton_idle", "assets\\Monsters_Creatures_Fantasy\\Skeleton\\Idle.png");
    TextureManager::GetInstance()->Load("skeleton_run", "assets\\Monsters_Creatures_Fantasy\\Skeleton\\Walk.png");
    TextureManager::GetInstance()->Load("skeleton_attack", "assets\\Monsters_Creatures_Fantasy\\Skeleton\\Attack.png");
    TextureManager::GetInstance()->Load("skeleton_hurt", "assets\\Monsters_Creatures_Fantasy\\Skeleton\\Take Hit.png");
    //pyromancer
    TextureManager::GetInstance()->Load("pyromancer_idle", "assets\\Pyromancer_idle.png");
    TextureManager::GetInstance()->Load("pyromancer_hurt", "assets\\Pyromancer_hurt.png");
    TextureManager::GetInstance()->Load("pyromancer_run", "assets\\Pyromancer_run.png");
    TextureManager::GetInstance()->Load("pyromancer_attack", "assets\\Pyromancer_attack.png");
    TextureManager::GetInstance()->Load("pyromancer_dying", "assets\\Pyromancer_dying.png");

    
    //Final_Boss
    TextureManager::GetInstance()->Load("final_boss_1_idle", "assets\\final_boss_1_idle.png");
    TextureManager::GetInstance()->Load("final_boss_1_run", "assets\\final_boss_1_running.png");
    TextureManager::GetInstance()->Load("final_boss_1_attack", "assets\\final_boss_1_attacking.png");
    TextureManager::GetInstance()->Load("final_boss_1_dying", "assets\\final_boss_1_dying.png");
    TextureManager::GetInstance()->Load("final_boss_reviving", "assets\\final_boss_reviving.png");
    TextureManager::GetInstance()->Load("final_boss_2_idle", "assets\\final_boss_2_idle.png");
    TextureManager::GetInstance()->Load("final_boss_2_run", "assets\\final_boss_2_running.png");
    TextureManager::GetInstance()->Load("final_boss_2_attack", "assets\\final_boss_2_attacking.png");
    TextureManager::GetInstance()->Load("final_boss_2_dying", "assets\\final_boss_2_dying.png");
    TextureManager::GetInstance()->Load("final_boss_1_casting", "assets\\final_boss_1_casting.png");
    TextureManager::GetInstance()->Load("final_boss_2_casting", "assets\\final_boss_2_casting.png");
    
    //fire spell
    TextureManager::GetInstance()->Load("fire_spell", "assets\\fire_spell.png");
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
    SoundManager::GetInstance()->Load("playstate_music", "assets\\playstate_music.mp3", SOUND_MUSIC, MIX_MAX_VOLUME );
    SoundManager::GetInstance()->PlayMusic("playstate_music", -1);

    //UI
    TextureManager::GetInstance()->Load("obelisk", "assets\\Obelisk.png");

    m_Warrior = new Warrior(new Properties("player", 350, 100, 130, 130));
    m_playerheal = new HealthBar(new Properties("none_bar", 10, 680, 240, 27),m_Warrior->getmaxHealth());

    //m_Enemies.push_back(new Enemy1(new Properties("skeleton_idle", 100, 200, 150, 150)));

    //m_Enemies.push_back(new Enemy1(new Properties("skeleton_idle", 600, 500, 150, 150)));
    //m_Enemies.push_back(new Enemy_Boss1(new Properties("boss1", 400 ,300, 280, 186)));
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
    
    TextureManager::GetInstance()->Draw("playstate_background", 0, 0, 1280, 720);
    map->DrawMap();
    //TextureManager::GetInstance()->Draw("heart", 20, 50, 23, 21);
    m_playerheal->Draw(); 
    if (m_Obelysk != NULL) m_Obelysk->Draw();
    FontManager::GetInstance()->RenderText("score", "SCORES: ", 20, 640, { 255, 255, 255, 255 });
    FontManager::GetInstance()->RenderText("m_score", std::to_string(m_Score).c_str(), 150, 640, { 255, 255, 255, 255 });
    
    m_Warrior->Draw();

    for (int i = 0; i < m_Enemies.size(); i++) {
        m_Enemies[i]->Draw();
    }
}

void PlayState::Update(float dt) {
    m_SpawnTimer += dt;
    /*if (m_SpawnTimer >= 100.0f) {
        SpawnEnemy();
        m_SpawnTimer = 0.0f; 
    }*/
    if (m_Enemies.empty()) {
        if(m_Score<40) Lv1();
        else if (m_Score < 100) {
            Lv2();
        }
        else if (m_Score < 180) {
            Lv3();
        }
        else if(m_Score < 400){
            Lv4();
        }
    }
    if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_ESCAPE)) {
        for (int i = 0; i <= 31; i++) {
            Mix_HaltChannel(i);
        }
        Mix_HaltMusic();
        printf("play to pause\n");
        Engine::GetInstance()->getStateMachine()->pushState(new PauseState());
    }
    m_playerheal->setCurrentHealth(m_Warrior->getHealth());
    m_playerheal->Update(dt);
    
    for (int i = 0; i < m_Enemies.size(); i++) {
        if (m_Enemies[i]->getCollider()!=NULL && CollisionHandler::GetInstance()->CheckCollision(m_Warrior->getCollider()->Get(), m_Enemies[i]->getCollider()->Get())) {
            if (typeid(*m_Enemies[i]) == typeid(Pyromancer)) {
                continue;
            }
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
            if (m_Enemies[j]->getIsAttack() == false) {
                m_Enemies[j]->Follow_Warrior(m_Warrior->getPosition());
            }
            
            if (m_Enemies[j]->getCollider() != NULL && player_attackZone!=NULL&&CollisionHandler::GetInstance()->CheckCollision(player_attackZone->Get(), m_Enemies[j]->getCollider()->Get())) {
                // Nếu nhân vật đang tấn công và va chạm với kẻ thù, gây sát thương cho kẻ thù
                m_Enemies[j]->receiveDamage("normal", m_Warrior->getDamage());
            }
            if (player_attackZone == NULL) {
                m_Enemies[j]->resetgetDamage("normal");
            }

            if (m_Enemies[j]->getCollider() != NULL && gravityskillZone != NULL && CollisionHandler::GetInstance()->CheckCollision(gravityskillZone->Get(), m_Enemies[j]->getCollider()->Get())) {
                m_Enemies[j]->receiveDamage("gravity", m_Warrior->getGravitySkillDamage());
            }
           
            if (m_Enemies[j]->getCollider()!=NULL && hasagiskillZone != NULL && CollisionHandler::GetInstance()->CheckCollision(hasagiskillZone->Get(), m_Enemies[j]->getCollider()->Get())) {
                m_Enemies[j]->receiveDamage("hasagi", m_Warrior->getHasagiSkill()->getDamage());
            }

            if (hasagiskillZone == NULL) {
                m_Enemies[j]->resetgetDamage("hasagi");
            }
            if (m_Enemies[j]->getCollider() != NULL && slashskillZone != NULL && CollisionHandler::GetInstance()->CheckCollision(slashskillZone->Get(), m_Enemies[j]->getCollider()->Get())) {
                m_Enemies[j]->receiveDamage("slash", m_Warrior->getSlashSkillDamage());
            }
            
            m_Enemies[j]->Update(dt);
            Collider* enemy_attackZone = m_Enemies[j]->getattackZone();
            if (enemy_attackZone != NULL && CollisionHandler::GetInstance()->CheckCollision(enemy_attackZone->Get(), m_Warrior->getCollider()->Get()))
            {
                m_Warrior->receiveDamage(m_Enemies[j]->getDamage());
            }
            if (typeid(*m_Enemies[j]) == typeid(Final_Boss)) {
                if (m_Enemies[j]->getType() == 1) {
                    summon_ememies_count = 1;
                }
                else summon_ememies_count = 3;
                if (m_Enemies[j]->is_Summoning() == true && m_Obelysk!=NULL && !is_summoned) {
                    m_Obelysk->Attack(dt);
                    is_summoned = true;
                    for (int k = 0; k < summon_ememies_count; k++) {
                        if(k == 0) m_Enemies.push_back(new Pyromancer(new Properties("pyromacer_idle", m_Obelysk->getTransform()->X, m_Obelysk->getTransform()->Y + 80, 80, 80)));
                        if(k == 1) m_Enemies.push_back(new Pyromancer(new Properties("pyromacer_idle", m_Obelysk->getTransform()->X, m_Obelysk->getTransform()->Y - 80, 80, 80)));
                        if (k == 2) m_Enemies.push_back(new Pyromancer(new Properties("pyromacer_idle", m_Obelysk->getTransform()->X - 80, m_Obelysk->getTransform()->Y, 80, 80)));
                   }
                }
                if (m_Enemies[j]->is_Summoning() == false && is_summoned) {
                    is_summoned = false;
                }
            }
        }
        if (m_Obelysk != NULL) m_Obelysk->Update(dt);
        for (int i = 0; i < m_Enemies.size(); i++) {
            if (!m_Enemies[i]->isAlive()) {
                if (dynamic_cast<Enemy1*>(m_Enemies[i])) {
                    m_Score += 10;
                }
                else if (dynamic_cast<Enemy_Boss1*>(m_Enemies[i])) {
                    m_Score += 100;
                }
                else if (dynamic_cast<Final_Boss*>(m_Enemies[i])) {
                    m_Score += 300;
                    delete m_Obelysk;
                    m_Obelysk = NULL;
                    Engine::GetInstance()->setScores(m_Score);
                    Engine::GetInstance()->getStateMachine()->changeState(new VictoryState());
                    
                }
                else if (dynamic_cast<Pyromancer*>(m_Enemies[i])) {
                    m_Score += 40;
                }
                m_Enemies[i]->Clean();
                m_Enemies.erase(m_Enemies.begin() + i);
                break;
            }
        }
        if (!m_Warrior->isAlive()) {
            Engine::GetInstance()->setScores(m_Score);
            Engine::GetInstance()->getStateMachine()->changeState(new GameOverState());
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


void PlayState::Lv1() {
   /* int y = 100;
    for (int i = 0; i < 4; i++) {
        m_Enemies.push_back(new Enemy1(new Properties("skeleton_idle", 900, y, 150, 150)));
        y += 100;
    }
    m_Enemies.push_back(new Pyromancer(new Properties("pyromacer_idle", 900,300, 80, 80)));*/
    m_Obelysk = new Obelysk(new Properties("obselysk_idle", 600, 320, 80, 80));
    //m_Enemies.push_back(new Final_Boss(new Properties("final_boss_1_idle", 700, 300, 220, 220)));
    //m_Enemies.push_back(new Enemy_Boss1(new Properties("boss1", 600, 300, 280, 186)));
    m_Enemies.push_back(new Enemy1(new Properties("skeleton_idle", 500, 320, 150, 150)));
    m_Enemies.push_back(new Enemy1(new Properties("skeleton_idle", 700, 320, 150, 150)));
    m_Enemies.push_back(new Enemy1(new Properties("skeleton_idle", 600, 220, 150, 150)));
    m_Enemies.push_back(new Enemy1(new Properties("skeleton_idle", 600, 420, 150, 150)));
    //m_Enemies.push_back(new Enemy_Boss1(new Properties("boss1", 700, 220, 280, 186)));
}
void PlayState::Lv2(){
    //m_Enemies.push_back(new Enemy_Boss1(new Properties("boss1", 600, y, 280, 186)));
    //int y1 = 100;
    m_Enemies.push_back(new Enemy1(new Properties("skeleton_idle", 500, 320, 150, 150)));
    m_Enemies.push_back(new Enemy1(new Properties("skeleton_idle", 700, 320, 150, 150)));
    m_Enemies.push_back(new Pyromancer(new Properties("pyromacer_idle", 600, 220, 80, 80)));
    m_Enemies.push_back(new Pyromancer(new Properties("pyromacer_idle", 600, 420, 80, 80)));
    //m_Enemies.push_back(new Final_Boss(new Properties("final_boss_1_idle", 700, 300, 220, 220)));
}

void PlayState::Lv3() {
    m_Enemies.push_back(new Enemy_Boss1(new Properties("boss1", 700, 220, 280, 186)));
    m_Enemies.push_back(new Pyromancer(new Properties("pyromacer_idle", 600, 220, 80, 80)));
    m_Enemies.push_back(new Pyromancer(new Properties("pyromacer_idle", 600, 420, 80, 80)));
}

void PlayState::Lv4()
{
    m_Enemies.push_back(new Final_Boss(new Properties("final_boss_1_idle", 700, 300, 220, 220)));
}


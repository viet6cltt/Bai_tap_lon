#ifndef MENUBUTTON_H
#define MENUBUTTON_H

#include "GameObject.h"
#include "TextureManager.h"
#include <SDL.h>
#include "Input.h"

class MenuButton : public GameObject
{
public:
    MenuButton(Properties* props, void (*callback)());

    virtual void Draw() override;
    virtual void Update(float dt) override;
    virtual void Clean() override;
private:
    enum button_state
    {
        MOUSE_OUT = 0,
        MOUSE_OVER = 1,
        CLICKED = 2
    };
    SDL_Rect m_Rect;
    int m_currentFrame;
    std::string m_NormalState;
    std::string m_HoverState = m_NormalState;
    std::string m_CurrentState;

    void (*m_callback) ();
    bool m_Released;
};
        
        
        
        
        
        
        /*m_NormalState = props->TextureID;
        m_HoverState = props->TextureID + "_hover";

        m_Rect.x = props->X;
        m_Rect.y = props->Y;
        m_Rect.w = props->Width;
        m_Rect.h = props->Height;*/
    //}

    /*void Draw() override{
        TextureManager::GetInstance()->Draw(m_CurrentState, m_Rect.x, m_Rect.y, m_Rect.w, m_Rect.h, SDL_FLIP_NONE);
    }

    void Update(float dt) override{
        
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);

        if (mouseX > m_Rect.x && mouseX < m_Rect.x + m_Rect.w &&
            mouseY > m_Rect.y && mouseY < m_Rect.y + m_Rect.h) {
            m_CurrentState = m_HoverState;
        }
        else {
            m_CurrentState = m_NormalState;
        }
    }

    void Clean() override {
        TextureManager::GetInstance()->Clean();
    }

private:
    std::string m_NormalState;
    std::string m_HoverState;
    std::string m_CurrentState;
    SDL_Rect m_Rect;*/
//};

#endif

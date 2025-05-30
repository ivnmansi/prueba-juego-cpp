#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"


class Player : public Entity {
    private:
        /**
         * @brief Construct a new Player object (singleton)
         * 
         */
        Player() : Entity(
            0,                 // ID
            "Player",          // NAME
            0,                 // X
            0,                 // Y
            40,                // WIDTH
            80,                // HEIGHT
            5,                 // SPEED
            100,               // HEALTH
            "player_down"      // TEXTURE ID
        ) {}
        Player(const Player&) = delete;
        Player& operator=(const Player&) = delete;
        static Player* instance;

    public:
        /**
         * @brief Get the Instance object
         * 
         * @return Player* 
         */
        static Player* getInstance() {
            if (instance == nullptr) {
                instance = new Player();
            }
            return instance;
        }

        void move(int dx, int dy);


        
};

#endif
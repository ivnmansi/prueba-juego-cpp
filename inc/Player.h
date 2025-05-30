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

        void move(int dx, int dy){
            Entity::move(dx, dy);

            if(dx > 0 && dy == 0){
                setTextureID("player_right");
            }
            else if(dx < 0 && dy == 0){
                setTextureID("player_left");
            }
            else if(dy > 0 && dx == 0){
                setTextureID("player_down");
            }
            else if(dy < 0 && dx == 0){
                setTextureID("player_up");
            }
            else if(dx > 0 && dy > 0){
                setTextureID("player_down_right");
            }
            else if(dx < 0 && dy > 0){
                setTextureID("player_down_left");
            }
            else if(dx > 0 && dy < 0){
                setTextureID("player_up_right");
            }
            else if(dx < 0 && dy < 0){
                setTextureID("player_up_left");
            }
        }

        
};
#include <iostream>
#include <string>
#include <vector>
#include <memory>

namespace RPG{
    class Character{
        protected:
            std::string name;
            int hp;
            int level;
        
        public:
        Character(std::string name, int hp, int level)
            : name(name), hp(hp), level(level) {}
        Character() = default;

        //가상 소멸자
        virtual ~Character() = default;

        //setter 함수들 3개, 메서드 체이닝 적용용

        Character& setName(const std::string& name){
            this->name = name;
            return *this;
        }
        Character& setHp(int hp){
            this->hp = hp;
            return *this;
        }
        Character& setLevel(int level){
            this->level = level;
            return *this;
        }

        const std::string& getName(void){ return name; }
        int getHp(void){ return hp; }
        int getLevel(void){ return level; }

        //오버라이드 기대 virtual attack 함수
        virtual void attack(void) const = 0;

        //상속 테스트 소개 함수
        void introduce(void) const{
            std::cout << "Hi, my name is " << name << "and i'm "
                    << level << " level, has " << hp << " hp" << std::endl;
        }
    };



    class Warrior final : public Character{
        private:
        std::string weapon;

        public:
        Warrior(std::string name, int hp, int level, std::string weapon)
            : Character(name, hp, level), weapon(weapon) {}
        
        Warrior& setWeapon(const std::string& weapon){
            this->weapon = weapon;
            return *this;
        }
        const std::string& getWeappon(){ return weapon; }

        void attack() const override{
            std::cout << name << " swings their " << weapon << std::endl;
        }

        void powerStrike() const{
            std::cout << "Warrior uses Power Strike!" << std:: endl;
        }
    };

    class Mage final : public Character{
        private:
        std::string spell;

        public:
        Mage (std::string name, int hp, int level, std::string spell) : Character(name, hp, level){
            this->spell = spell;
        }
        
        Mage& setSpell(const std::string& spell){
            this->spell = spell;
            return *this; }
        const std::string& getSpell(){ return spell; }

        //오버라이드 및 재정의
        void attack() const override{
            std::cout << name << " casts " << spell << std::endl;
        }
        
        void fireball() const {
            std::cout << "Mage casts Fireball!" << std:: endl;
        }
    };

};

using CharacterPtr =  std::unique_ptr<RPG::Character>;

int main(void){
    std::vector<CharacterPtr> characeters;
    characeters.push_back(std::make_unique<RPG::Warrior>("Thor", 150, 10, "Hammer"));
    characeters.push_back(std::make_unique<RPG::Mage>("Gandalf", 100, 12, "Ligntening"));

    for (const auto& ch : characeters){
        ch->introduce();
        ch->attack();
    }
}

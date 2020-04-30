#include <iostream>


// Класс хранит температуры в кельвинах, фаренгейтах и цельсиях
//=======================================================//
// All is public
//=======================================================//
class PubClass
{
    public:

    float kelvin;
    float fahrenheit;
    float celsius;
};
//=======================================================//
// Getter and setters
//=======================================================//
enum TemperatureType
{
    KELVIN,
    CELSIUS,
    FAHRENHEIT
};
class GetSetClass
{
    protected:

    float kelvin;
    float fahrenheit;
    float celsius;

    public:

    //TODO: assert min temperature
    void Set_Celsius(float _celsius)
    {
        celsius = _celsius;
        fahrenheit = (9/5)*_celsius+32;
        kelvin = _celsius+273;
    }

    void Set_Kelvin(float _kelvin)
    {
        kelvin = _kelvin;
        celsius = _kelvin-273;
        fahrenheit = (9/5)*(_kelvin-273)+32;
    }

    void Set_Fahrenheit(float _fahrenheit)
    {
        fahrenheit = _fahrenheit;
        kelvin = (5/9)*(_fahrenheit-32)+273;
        celsius = (5/9)*(_fahrenheit-32);
    }

    float Get_Kelvin()
    {
        return kelvin;
    }

    float Get_Celsius()
    {
        return celsius;
    }

    float Get_Fahrenheit()
    {
        return fahrenheit;
    }

    GetSetClass(float value, TemperatureType type)
    {
        switch(type)
        {
            case KELVIN:
                Set_Kelvin(value);
                break;

            case CELSIUS:
                Set_Celsius(value);
                break;

            case FAHRENHEIT:
                Set_Fahrenheit(value);
                break;
        }
    }
};
//======================================================//
// Temperature comparasion
//======================================================//
class FancyProtocolClass : public GetSetClass
{
    private:

    public:

    //TODO: how inlining works?
    int operator>(FancyProtocolClass &r)
    {
        return (kelvin > r.Get_Kelvin() ? 1 : 0);
    }

    inline int operator<(FancyProtocolClass &r)
    {
        return (kelvin < r.Get_Kelvin() ? 1 : 0);
    }

};
//======================================================//
// For simplicicty purpose many stuff in here are public and
// there are no boundry checks, for example, for hp
//
// Abstraction + late binding
// Weapon.Damage() - change behavior
// Cleric::Do_damage() - added behavior (heal himself)
//======================================================//
class Soldier
{
    class Weapon
    {
        public:
        virtual unsigned int Damage() = 0;
    };

    class Sword : public Weapon
    {
        unsigned int Damage()
        {
            return 7;
        }
    };

    class Axe : public Weapon
    {
        unsigned int Damage()
        {
            return 10;
        }
    };

    Weapon* weapon;

    public:

    unsigned int hp = 12;

    void Do_Damage(Soldier* soldier)
    {
        soldier->hp -= weapon->Damage();
    }

    Soldier(int in_value)
    {
        if(in_value)
        {
            weapon = new Axe;
        }
        else
        {
            weapon = new Sword;
        }
    }
};

class Cleric : public Soldier
{
    public:

    Cleric(int in_value) : Soldier(in_value){};

    void Do_Damage(Soldier *soldier)
    {
        Soldier::Do_Damage(soldier);
        hp++;
    }
};

// Let's suppose that would be a TBS game
void Make_Attack_Turn(Soldier *attacker, Soldier *defender)
{
    attacker->Do_Damage(defender);
}

int main()
{
#if 1
    Soldier soldier_with_axe(1);
    Soldier soldier_with_sword(0);
    Cleric cleric_with_sword(0);
    Soldier enemy(0);
    soldier_with_axe.Do_Damage(&enemy);
    printf("%d\n", enemy.hp);
    enemy.hp = 12;
    soldier_with_sword.Do_Damage(&enemy);
    printf("%d\n", enemy.hp);
    enemy.hp = 12;
    cleric_with_sword.Do_Damage(&enemy);
    printf("%d\n", enemy.hp);
    printf("%d\n", cleric_with_sword.hp);
    enemy.hp = 12;
    Make_Attack_Turn(&cleric_with_sword, &enemy);
    printf("%d\n", enemy.hp);

#endif
    return 0;
}

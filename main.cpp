#include <iostream>

// инкапсуляция данных:
// все паблик
// гет/сет
// протоколы
//
// инкапсуляция поведения:
// позднее связывание : расширение и замена поведения

// Класс хранит температуры в кельвинах, фаренгейтах и цельсиях
class PubClass
{
    public:

    float kelvin;
    float fahrenheit;
    float celsius;
};
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
                SetKelvin(value);
                break;

            case CELSIUS:
                SetCelsius(value);
                break;

            case FAHRENHEIT:
                SetFahrenheit(value);
                break;
        }
    }
};
//======================================================//
class FancyProtocolClass : public GetSetClass
{
    private:

    public:

    int operator>(FancyProtocolClass &r)
    {
        //With our invariant, it does not matter which temperature compare
        return (kelvin > r.Get_Kelvin() ? 1 : 0);
    }
};
//======================================================//
int main()
{
    printf("%d",sizeof(GetSetClass));
    return 0;
}

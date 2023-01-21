// #include <avr/io.h>
// #include <avr/interrupt.h>
// #include <util/delay.h>
#include "capteur.h"

Capteur::Capteur()
{
}

float Capteur::conversionNumericVolt()
{
    can convert;

    float resultatCan = (convert.lecture(PA0) >> 2) / 255.0f;
    return resultatCan * 5.0f;
}

float Capteur::trouverDistance()
{
    float volt = conversionNumericVolt();
    const float constanteGraph = 29.988f;
    const float constExp = (-1.173f);
    float distance = constanteGraph * pow(volt, constExp);
    return distance;
}

Capteur::Mouvement Capteur::interpreteMouvement()
{   
    Capteur::Mouvement mouvement;
    float distance = trouverDistance();
    if (distance < 20)
    {
        mouvement = Capteur::Mouvement::TOURNER_GAUCHE;
        return mouvement;
    }
    else if (distance > 38.5f)
    {
        mouvement = Capteur::Mouvement::ARRETER;
        return mouvement;
    }
    else if (distance > 22)
    {
        mouvement = Capteur::Mouvement::TOURNER_DROITE;
        return mouvement;
    }
    else
    {
        mouvement = Capteur::Mouvement::TOUT_DROIT;
        return mouvement;
    }
}

uint8_t Capteur::getPwmRoue1()
{
    return roue1_;
}

uint8_t Capteur::getPwmRoue2()
{
    return roue2_;
}
void Capteur::deplacement()
{
    DDRB |= (1 << PB0) | (1 << PB1);
    Led led = Led(&PORTB, PB0, PB1);
    Pwm p;
    p.initTimer0();
    Capteur::Mouvement mouvement = interpreteMouvement();
   
    switch (mouvement)
    {
    case Capteur::Mouvement::ARRETER:
        p.ajustDutyCycle(0, 0);
        roue1_ = 0;
        roue2_ = 0;
        break;
    case Capteur::Mouvement::TOUT_DROIT:
        p.ajustDutyCycle(175, 175);
        roue1_ = 175;
        roue2_ = 175;
        break;
    case Capteur::Mouvement::TOURNER_DROITE:
        p.ajustDutyCycle(0, 125);
        roue1_ = 0;
        roue2_ = 125;
        break;
    case Capteur::Mouvement::TOURNER_GAUCHE:
        p.ajustDutyCycle(125, 0);
        roue1_ = 125;
        roue2_ = 0;
        break;
    }
}

//     ####################################
//     DDRB |= (1 << PB0) | (1 << PB1);
//     Led led = Led(&PORTB, PB0, PB1);
//     Capteur::Mouvement mouvement = interpreteMouvement();
//     switch (mouvement)
//     {
//     case Capteur::Mouvement::TOUT_DROIT:
//         led.ledRed();
//     case Capteur::Mouvement::TOURNER_DROITE:
//         led.ledOff();
//         //_delay_ms(150);
//         break;
//     case Capteur::Mouvement::TOURNER_GAUCHE:
//         led.ledGreen();
//         //_delay_ms(150);
//         break;
//     }
// }

// void Capteur::interpreteMouvement()
// {
//     while (true)
//     {
//         //Capteur::Mouvement mouvement;
//         DDRB |= (1 << PB0) | (1 << PB1);
//         Led led = Led(&PORTB, PB0, PB1);
//         Pwm p;
//         p.initTimer0();

//         float distance = trouverDistance();
//         if (distance < 19)
//         {
//             p.ajustDutyCycle(125, 0);
//             led.ledRed();
//         }
//         else if (distance > 38.5f)
//         {
//             p.ajustDutyCycle(0, 0);
//             led.ledGreen();
//             break;
//         }

//         else if (distance > 21)
//         {
//             p.ajustDutyCycle(0, 125);
//             led.ledGreen();
//         }
//         else
//         {
//             p.ajustDutyCycle(175, 175);
//             led.ledGreen();
//         }
//     }
// }

//volt = 21.714285714286(1/dist) + 0.12857142857143 //pour 20 cm => 1.21427 v

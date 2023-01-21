/*
 * Ecole Polytechnique de Montreal
 * Departement de genie informatique
 * Cours inf1900
 *
 * Aziz Doghri , Abdelmounaim Boughedaoui, 
 * Anissa Djouhri, Lina Marouf, 
 * 2021-2022
 *
 * Code qui n'est sous aucune license.
 *
 */

#include <util/delay.h>
#include <avr/io.h>
#include "../lib/can.h"
#include "../lib/lightFollow.h"
#include "../lib/pwm.h"
#include "../lib/motor.h"
#include "../lib/uart.h"
#include "../lib/led.h"
#include "../lib/button.h"
#include "../lib/capteur.h"
#include "../lib/Sauvegarde.h"

// --------------------------------------------------------------------------------------------------------------
// |     EtatPresent      | boutonIterrupt | boutonBlanc |             EtatSuivant              | Couleurlumiere|
// --------------------------------------------------------------------------------------------------------------
// | Etat::INIT           |              0 |            0| Etat::INIT                           | eteint         |
// | Etat::INIT           |              1 |            0| Etat::SUIVRE_MUR                     |vert clignote   |
// | Etat::INIT           |              0 |            1| Etat::REMAKE                         | rouge clignote |
// | Etat::SUIVIE_MUR     |              - |           - | Etat::WAIT                           | eteinte        |
// | Etat::WAIT           |              0 |           1 | Etat::TOURNER                        | ambree         |
// | Etat::WAIT           |              1 |           0 | Etat::END_COURSE                     | eteinte        |
// | Etat::WAIT           |              0 |           0 | etat::TRACK_LIGHT                    | eteinte        |
// | ETAT::TRACK_LIGHT    |              - |           - | etat::SUIVRE_MUR                     | eteinte        |
// | Etat::TOURNER        |              - |           - | etat::SUIVRE_MUR_SANS_ENREGISTREMENT | eteinte        |
// ---------------------------------------------------------------------------------------------------------------

int main()
{
    DDRA &= ~(1 << DDA0) & ~(1 << DDA2) & ~(1 << DDA4);
    DDRD &= ~(1 << DDD2);
    DDRB |= (1 << DDB0) | (1 << DDB1);

    uint8_t i = 0;
    const uint8_t waitTimeMs = 100;
    const uint8_t Iteration3sec = 65;
    const uint8_t readInstructions = 112;
    bool isActiveUturn = true;
    bool isActiveFollowLight = true;

    Uart uart;
    Pwm pwm;
    Button interruptButton = Button(&PIND, PIND2);
    Button whiteButton = Button(&PIND, PIND3);
    Capteur capteur;
    LightFollow light;
    Enregistrement memory;
    Led led = Led(&PORTB, PB0, PB1);
    Motor motor;
    can convert;

    uart.initiate();

    pwm.initTimer0();

    enum class State
    {
        INIT,
        START_COURSE,
        FOLLOW_WALL_WITH_SAVING,
        WAIT,
        TRACK_LIGHT,
        U_TURN,
        REMAKE,
        END_COURSE,
        FOLLOW_WALL_WITHOUT_SAVING
    };

    State state{State::INIT};

    while (true)
    {
        switch (state)
        {

            case State::INIT:
                if (interruptButton.getState() == Button::State::PRESS)
                {
                    state = State::START_COURSE;
                }
                else if (whiteButton.getState() == Button::State::PRESS)
                {
                    state = State::REMAKE;
                }
                break;

            case State::START_COURSE:
                while (i < Iteration3sec)
                {
                    led.ledGreen();
                    _delay_ms(waitTimeMs);
                    led.ledOff();
                    _delay_ms(waitTimeMs);
                    i++;
                }
                i = 0;
                state = State::FOLLOW_WALL_WITH_SAVING;
                break;

            case State::FOLLOW_WALL_WITH_SAVING:
                while (memory.capteur.interpreteMouvement() != Capteur::Mouvement::ARRETER)
                {
                    memory.capteur.conversionNumericVolt();
                    memory.capteur.trouverDistance();
                    memory.capteur.interpreteMouvement();
                    memory.capteur.deplacement();

                    memory.sauvegardeCapteur();
                }
                state = State::WAIT;
                break;

            case State::WAIT:
                memory.lumiere.setAmbLight();

                while (true)
                {
                    if (interruptButton.getState() == Button::State::PRESS)
                    {
                        state = State::END_COURSE;
                        break;
                    }
                    else if (whiteButton.getState() == Button::State::PRESS)
                    {
                        state = State::U_TURN;
                        break;
                    }
                    else if ((memory.lumiere.lumAmbG < (convert.lecture(PA2) >> 2)) || (memory.lumiere.lumAmbD < (convert.lecture(PA4) >> 2)))
                    {
                        state = State::TRACK_LIGHT;
                        break;
                    }
                }
                break;

            case State::U_TURN:
                led.ledAmber();
                motor.r_eturn();
                
                while (isActiveUturn){
                    if(capteur.interpreteMouvement() != Capteur::Mouvement::ARRETER)
                    {
                        pwm.ajustDutyCycle(0,0);
                        state=State:: FOLLOW_WALL_WITHOUT_SAVING;
                        isActiveUturn = false;
                    }
                }
                break;

            case State::END_COURSE:
                led.ledRed();
                memory.finEcriture();
                led.ledGreen();
                break;


            case State::FOLLOW_WALL_WITHOUT_SAVING:
                while (capteur.interpreteMouvement() != Capteur::Mouvement::ARRETER)
                {
                    capteur.conversionNumericVolt();
                    capteur.trouverDistance();
                    capteur.interpreteMouvement();
                    capteur.deplacement();
                }
                state = State::INIT;
                break;

            case State::REMAKE:
                led.ledRed();
                _delay_ms(10);
                if (memory.instrLue_ == readInstructions)
                {
                    pwm.ajustDutyCycle(memory.operandRead1_, memory.operandRead2_);
                }

                do
                {
                    memory.lectureMemoireCapteur();

                    if (memory.instrLue_ == readInstructions)
                    {
                        pwm.ajustDutyCycle(memory.operandRead1_, memory.operandRead2_);
                    }

                } while (memory.instrLue_ != memory.instructionStop_);

                state = State::REMAKE;
                break;
                
            case State::TRACK_LIGHT:
                led.ledOff();
                memory.lumiere.setAmbLight();

                while (isActiveFollowLight)
                {
                    memory.lumiere.setLightPwm();
                    memory.sauvegardeLumiere();

                    if (capteur.interpreteMouvement() != Capteur::Mouvement::ARRETER)
                    {
                        state = State::FOLLOW_WALL_WITH_SAVING;
                        isActiveFollowLight = false;
                    }
                }
                break;
        }

        return 0;
    }
}
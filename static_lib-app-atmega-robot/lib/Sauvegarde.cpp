#include "Sauvegarde.h"

Enregistrement::Enregistrement()
{
}

void Enregistrement::lectureMemoireCapteur()
{   
    //_delay_ms(5);
    memoire.lecture(adresseLecture_++, &instrLue_);
    //_delay_ms(5);
    memoire.lecture(adresseLecture_++, &operandRead1_);
    //_delay_ms(5);
    memoire.lecture(adresseLecture_++, &operandRead2_);
    
    _delay_ms(70);
}

void Enregistrement::sauvegardeCapteur()
{
    uint8_t instruction = 112;
    uint8_t delaiEcriture = 5;

    operandCapteur1_ = capteur.getPwmRoue1();
    operandCapteur2_ = capteur.getPwmRoue2();

    _delay_ms(delaiEcriture);
    memoire.ecriture(adresseEcriture_++, instruction);
    _delay_ms(delaiEcriture); 
    memoire.ecriture(adresseEcriture_++, operandCapteur1_); 
    _delay_ms(delaiEcriture);
    memoire.ecriture(adresseEcriture_++, operandCapteur2_);
    //_delay_ms(delaiEcriture); 

    _delay_ms(60);
}

void Enregistrement::lectureMemoireLumiere()
{   
    //_delay_ms(5);
    memoire.lecture(adresseLecture_++, &instrLue_);
    //_delay_ms(5);
    memoire.lecture(adresseLecture_++, &operandRead1_);
    //_delay_ms(5);
    memoire.lecture(adresseLecture_++, &operandRead2_);
    memoire.lecture(adresseLecture_++, &directionLue_);

    _delay_ms(60);
      
}

void Enregistrement::sauvegardeLumiere()
{
    uint8_t instruction = 112;
    uint8_t delaiEcriture = 5;

    operandLumiere1_ = lumiere.getPwmRoue1();
    operandLumiere2_ = lumiere.getPwmRoue2();
    directionEcrite_ = lumiere.direction_;

    _delay_ms(delaiEcriture);
    memoire.ecriture(adresseEcriture_++, instruction);
    _delay_ms(delaiEcriture); 
    memoire.ecriture(adresseEcriture_++, operandLumiere1_); 
    _delay_ms(delaiEcriture);
    memoire.ecriture(adresseEcriture_++, operandLumiere2_);
    _delay_ms(delaiEcriture);
    memoire.ecriture(adresseEcriture_++, directionEcrite_);  

    _delay_ms(70);
}

// void Enregistrement::initialisationPortPwmLumiere(){

//     if (lumiere.pwmGauche < lumiere.pwmDroite)
//     {
//                 PORTB &= ~(1 << PB2);
//                 PORTB |= (1 << PB5);
//                 direction_ = 1;
//     }
//     else if(lumiere.pwmGauche > lumiere.pwmDroite)
//     {
//                 PORTB &= ~(1 << PB5);
//                 PORTB |= (1 << PB2);
//                 direction_ = 2;
//     }
//     else
//     {
//         PORTB &= ~(1 << PB2) & ~(1 << PB5);
//         direction_ = 3;

//     }
// }

void Enregistrement::finEcriture(){

   // _delay_ms(5);
    memoire.ecriture(adresseEcriture_++, instructionStop_); 
}


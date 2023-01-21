#include <avr/io.h>
#include <util/delay.h>
#include "memoire_24.h"
#include "capteur.h"
#include "lightFollow.h"

class Enregistrement {
public:
  Enregistrement();
  void sauvegardeCapteur();
  void sauvegardeLumiere();
  void lectureMemoireCapteur();
  void lectureMemoireLumiere();
  void finEcriture();
  //void initialisationPortPwmLumiere();

  uint8_t instrLue_;
  uint16_t adresseEcriture_ = 0;
  uint16_t adresseLecture_ = 0;
  uint8_t operandCapteur1_;
  uint8_t operandCapteur2_;
  uint8_t operandLumiere1_;
  uint8_t operandLumiere2_;
  uint8_t operandRead1_;
  uint8_t operandRead2_;
  uint8_t directionLue_;
  uint8_t directionEcrite_;
  uint8_t instructionStop_ = 200;

  Memoire24CXXX memoire;
  Capteur capteur;
  LightFollow lumiere;
};
// Commande de 12 ventilateurs
// Commandes : 1 à 6 pour actionner les ventilateurs et 0 pour tout arrêter.
// 1 actionne les ventilateurs V1 et V7,
// 2 actionne V2 et V8,
// 3 actionne V3 et V9,
// 4 actionne V4 et V10,
// 5 actionne V5 et V11,
// et 6 actionne les ventilateurs V6 et V12.
// on peut partager des commande. * pour tout allumer, a pour allumer le groupe A (1,3,5) ou b pour allumer le groupe B (2,4,6)

enum t_etat : uint8_t {ETEINT, EN_FONCTION_ON, EN_FONCTION_OFF};

struct paireVentilateur {
  const char* nom;
  const char* lettresCommande;
  const uint8_t pinVentilateur1;
  const uint8_t pinVentilateur2;
  t_etat etat;
  const unsigned long dureeOn;
  const unsigned long dureeOff;
  unsigned long chrono;

  void appliquerEtat(const t_etat m) {
    etat = m;
    chrono = millis();
    switch (etat) {
      case ETEINT:          digitalWrite(pinVentilateur1, LOW);   digitalWrite(pinVentilateur2, LOW);   Serial.print(nom); Serial.println("est éteint"); break;
      case EN_FONCTION_ON:  digitalWrite(pinVentilateur1, HIGH);  digitalWrite(pinVentilateur2, HIGH);  Serial.print(nom); Serial.println("est en fontion et allumé"); break;
      case EN_FONCTION_OFF: digitalWrite(pinVentilateur1, LOW);   digitalWrite(pinVentilateur2, LOW);   Serial.print(nom); Serial.println("est en fontion et éteint"); break;
    }
  }

  void begin() {
    pinMode(pinVentilateur1, OUTPUT);
    pinMode(pinVentilateur2, OUTPUT);
    appliquerEtat(etat);
  }

  void executer(const char commandeID) {
    if (commandeID == '0') {                                            // '0' pour éteindre
      if (etat != ETEINT) appliquerEtat(ETEINT);
    } else if (strchr(lettresCommande, commandeID) != nullptr) {        // est-ce une commande connue d'allumage ?
      appliquerEtat(EN_FONCTION_ON);
    }
  }

  void tick() {
    switch (etat) {
      case ETEINT: break;
      case EN_FONCTION_ON:  if (millis() - chrono >= dureeOn)  appliquerEtat(EN_FONCTION_OFF); break;
      case EN_FONCTION_OFF: if (millis() - chrono >= dureeOff) appliquerEtat(EN_FONCTION_ON);  break;
    }
  }
};

paireVentilateur paires[] {
  {"V1V7 ", "1*a",  7, A0, ETEINT, 10000, 10000, 0},
  {"V2V8 ", "2*b",  8, A1, ETEINT, 10000, 10000, 0},
  {"V3V9 ", "3*a",  9, A2, ETEINT, 10000, 10000, 0},
  {"V4V10", "4*b", 10, A3, ETEINT, 10000, 10000, 0},
  {"V5V11", "5*a", 11, A4, ETEINT, 10000, 10000, 0},
  {"V6V12", "6*b", 12, A5, ETEINT, 10000, 10000, 0},
};
const uint8_t nombreDePaires = sizeof paires / sizeof * paires;


void setup() {
  Serial.begin(115200);
  Serial.println(F("\nConfiguration"));
  for (auto& p : paires) p.begin();
  Serial.println(F("\nEntrez vos commandes"));
}

void loop() {

  int commande = Serial.read();
  if (commande != -1)                                         // -1 si rien à lire
    for (auto& p : paires) p.executer((char) commande);

  for (auto& p : paires) p.tick(); // on gère l'état

}
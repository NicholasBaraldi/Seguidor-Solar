#include <Servo.h>

#define pin_servo_vertical 9
#define pin_servo_horizontal 8

#define pin_LDR_sup_dir A0
#define pin_LDR_sup_esq A1
#define pin_LDR_inf_dir A2
#define pin_LDR_inf_esq A3

#define pos_noite 90

#define valor_noite 100

Servo servo_horizontal;
Servo servo_vertical;

int angulo_vertical = pos_noite;
int angulo_horizontal = pos_noite;

bool dia = false;

void setup() {
  pinMode (pin_LDR_sup_dir, INPUT);
  pinMode (pin_LDR_sup_esq, INPUT);
  pinMode (pin_LDR_inf_dir, INPUT);
  pinMode (pin_LDR_inf_esq, INPUT);
  
  servo_horizontal.attach(pin_servo_vertical);
  servo_vertical.attach(pin_servo_horizontal);
  
  Serial.begin(9600);
}

void loop() {

  dia = !noite();

  if (dia) {
    servo_horizontal.write(constrain(angulo_horizontal, 0, 180));
    servo_vertical.write(constrain(angulo_vertical, 0, 180));

    angulo_horizontal += compara_horizontal();
    angulo_vertical += compara_vertical();
  } else {
    servo_horizontal.write(pos_noite);
    servo_vertical.write(pos_noite);
  }
    
  delay(20);
}

int compara_horizontal() {

  int valor_dir = analogRead(pin_LDR_sup_dir) + analogRead(pin_LDR_inf_dir);
  int valor_esq = analogRead(pin_LDR_sup_esq) + analogRead(pin_LDR_inf_esq);
  
  if (valor_esq > valor_dir)
    return 1;
  else if (valor_esq < valor_dir)
    return -1;
  else 
    return 0;
}

int compara_vertical() {

  int valor_sup = analogRead(pin_LDR_sup_dir) + analogRead(pin_LDR_sup_esq);
  int valor_inf = analogRead(pin_LDR_inf_dir) + analogRead(pin_LDR_inf_esq);
  
  if (valor_sup > valor_inf)
    return 1;
  else if (valor_sup < valor_inf)
    return -1;
  else 
    return 0;
}

bool noite(){
    return ( (analogRead(pin_LDR_sup_dir) < valor_noite) &&
             (analogRead(pin_LDR_sup_esq) < valor_noite) &&
             (analogRead(pin_LDR_inf_dir) < valor_noite) &&
             (analogRead(pin_LDR_inf_esq) < valor_noite) );
}

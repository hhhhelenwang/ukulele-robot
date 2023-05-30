#include <Stepper.h>
#include <ESP32Servo.h>

const int STEPS = 200;



// pins to stepping motors
const int gStepPin = 13;
const int gDirPin = 12;

const int cStepPin = 27;
const int cDirPin = 33;

const int eStepPin = 15;
const int eDirPin = 32;

const int aStepPin = 14;
const int aDirPin = 22;


// steppers
Stepper gStepper(STEPS, gStepPin, gDirPin);
Stepper cStepper(STEPS, cStepPin, cDirPin);
Stepper eStepper(STEPS, eStepPin, eDirPin);
Stepper aStepper(STEPS, aStepPin, aDirPin);

// servos
Servo gServo;
Servo cServo;
Servo eServo;
Servo aServo;


// // pins to the blue motors
const int gPin = A0;
const int cPin = A1;
const int ePin = 4;
const int aPin = 5;

// // pin to high speed motor
// const int sweepMotorPin;

// // travel distance of stepping motor
// const int oneFret;

// cords mapping

// stepper positions
int gStepperPos = 0;
int cStepperPos = 0;
int eStepperPos = 0;
int aStepperPos = 0;

// servo positions
int gPos = 0;
int cPos = 0;
int ePos = 0;
int aPos = 0;

void setup() {
    Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode(gStepPin, OUTPUT);
  pinMode(gDirPin, OUTPUT);
  pinMode(cStepPin, OUTPUT);
  pinMode(cDirPin, OUTPUT);
  pinMode(eStepPin, OUTPUT);
  pinMode(eDirPin, OUTPUT);
  pinMode(aStepPin, OUTPUT);
  pinMode(aDirPin, OUTPUT);

  pinMode(gPin, OUTPUT);
  pinMode(cPin, OUTPUT);
  pinMode(ePin, OUTPUT);
  pinMode(aPin, OUTPUT);

  gStepper.setSpeed(240);
  cStepper.setSpeed(240);
  eStepper.setSpeed(240);
  aStepper.setSpeed(240);

  gServo.attach(gPin);
  cServo.attach(cPin);
  eServo.attach(ePin);
  aServo.attach(aPin);

  
  gServo.write(0);
  cServo.write(0);
  eServo.write(0);
  aServo.write(0);

  // cStepper.step(-150);
  // testG();
  // testE();
  // testA();
  // testC();


}

int cord = true;
int cord1 = true;
int cord2 = false;

void loop() {
  // demo1();
  demo2();
  


}

void demo2() {
  pluckG();
  delay(500);
  pluckC();
  delay(500);
  pluckE();
  delay(500);
  pluckA();
  delay(500);

  pluckG();
  delay(500);
  pluckC();
  delay(500);
  pluckG();
  delay(500);
  pluckE();
  delay(500);

  if (cord) {
    if (cord1) {
      moveAToFret(3);
    } else {
      moveAToFret(0);
    }
    cord1 = !cord1;

    if (cord2) {
      moveGToFret(2);
    } else {
      moveGToFret(0);
    }
    cord2 = !cord2;
  } else {
    moveAToFret(0);
    moveGToFret(0);

  }
  cord = !cord;
  
}

void demo1() {
  pluckG();
  delay(500);
  pluckC();
  delay(500);
  pluckE();
  delay(500);
  pluckA();
  delay(500);

  pluckG();
  delay(500);
  pluckC();
  delay(500);
  pluckG();
  delay(500);
  pluckE();
  delay(500);
  
  if (cord) {
    moveGToFret(2);
  } else {
    moveGToFret(0);
  }

  cord = !cord;
}


void lowDo(){
  moveCToFret(0);
  pluckC();
}

void re() {
  moveCToFret(3);
  pluckC();
}

void mi() {
  moveEToFret(0);
  pluckE();
}

void fa() {
  moveEToFret(1);
  pluckE();
}

void so() {
  moveGToFret(0);
  pluckG();

}

void la() {
  moveGToFret(2);
  pluckG();

}

void ti() {
  moveGToFret(4);
  pluckG();

}

void highDo() {
  moveAToFret(3);
  pluckA();

}

// -----------------------------------------
// ----------- Plucking String -------------
// -----------------------------------------

void pluckG() {
  if (gPos >= 30) {
     for (gPos = 30; gPos >=0; gPos -= 1) {
      gServo.write(gPos);
      delay(0.5);
    }
  } else if (gPos <= 0) {
    for (gPos = 0; gPos <= 30; gPos += 1) {
      gServo.write(gPos);
      delay(0.5);
    }
  }
}

void pluckC() {
  if (cPos >= 30) {
     for (cPos = 30; cPos >=0; cPos -= 1) {
      cServo.write(cPos);
      delay(0.5);
    }
  } else if (cPos <= 0) {
    for (cPos = 0; cPos <= 30; cPos += 1) {
      cServo.write(cPos);
      delay(0.5);
    }
  }
}

void pluckE() {
  if (ePos >= 30) {
     for (ePos = 30; ePos >=0; ePos -= 1) {
      eServo.write(ePos);
      delay(0.5);
    }
  } else if (ePos <= 0) {
    for (ePos = 0; ePos <= 30; ePos += 1) {
      eServo.write(ePos);
      delay(0.5);
    }
  }
}

void pluckA() {
  if (aPos >= 30) {
     for (aPos = 30; aPos >=0; aPos -= 1) {
      aServo.write(aPos);
      delay(0.5);
    }
  } else if (aPos <= 0) {
    for (aPos = 0; aPos <= 30; aPos += 1) {
      aServo.write(aPos);
      delay(0.5);
    }
  }
}

// -----------------------------------------
// ----- Moving to Frets -------------------
// -----------------------------------------

void moveCToFret(int fret) {
  int newPos = posOfFret(fret);
  cStepper.step(cStepperPos - newPos);
  cStepperPos = newPos;
}

void moveGToFret(int fret) {
  int newPos = posOfFret(fret);
  gStepper.step(gStepperPos - newPos);
  gStepperPos = newPos;
}

void moveEToFret(int fret) {
  int newPos = posOfFret(fret);
  eStepper.step(newPos - eStepperPos); // opposite direction than G and C
  eStepperPos = newPos;

}

void moveAToFret(int fret) {
  int newPos = posOfFret(fret);
  aStepper.step(newPos - aStepperPos); // opposite direction than G and C
  aStepperPos = newPos;
}

int posOfFret(int fret) {
  int newPos = 0;
  switch(fret) {
    case 0:
      newPos = 0;
      break;
    case 1:
      newPos = 65;
      break;
    case 2:
      newPos = 300;
      break;
    case 3:
      newPos = 480;
      break;
    case 4:
      newPos = 620;
      break;
  }
  return newPos;

}

// testing
void testG() {
  pluckG();
  delay(1000);
  moveGToFret(1);
  pluckG();
  delay(1000);
  moveGToFret(2);
  pluckG();
  delay(1000);
  moveGToFret(3);
  pluckG();
  delay(1000);
  moveGToFret(4);
  pluckG();
  delay(1000);
  moveGToFret(2);
  pluckG();
  delay(1000);
  moveGToFret(3);
  pluckG();
  delay(1000);
  moveGToFret(1);
  pluckG();
  delay(1000);
  moveGToFret(0);
  pluckG();
  delay(1000);
}

void testC() {
  pluckC();
  delay(1000);
  moveCToFret(1);
  pluckC();
  delay(1000);
  moveCToFret(2);
  pluckC();
  delay(1000);
  moveCToFret(3);
  pluckC();
  delay(1000);
  moveCToFret(4);
  pluckC();
  delay(1000);
  moveCToFret(2);
  pluckC();
  delay(1000);
  moveCToFret(3);
  pluckC();
  delay(1000);
  moveCToFret(1);
  pluckC();
  delay(1000);
  moveCToFret(0);
  pluckC();
  delay(1000);
}

void testE() {
  pluckE();
  delay(1000);
  moveEToFret(1);
  pluckE();
  delay(1000);
  moveEToFret(2);
  pluckE();
  delay(1000);
  moveEToFret(3);
  pluckE();
  delay(1000);
  moveEToFret(4);
  pluckE();
  delay(1000);
  moveEToFret(2);
  pluckE();
  delay(1000);
  moveEToFret(3);
  pluckE();
  delay(1000);
  moveEToFret(1);
  pluckE();
  delay(1000);
  moveEToFret(0);
  pluckE();
  delay(1000);
}

void testA() {
  pluckA();
  delay(1000);
  moveAToFret(1);
  pluckA();
  delay(1000);
  moveAToFret(2);
  pluckA();
  delay(1000);
  moveAToFret(3);
  pluckA();
  delay(1000);
  moveAToFret(4);
  pluckA();
  delay(1000);
  moveAToFret(2);
  pluckA();
  delay(1000);
  moveAToFret(3);
  pluckA();
  delay(1000);
  moveAToFret(1);
  pluckA();
  delay(1000);
  moveAToFret(0);
  pluckA();
  delay(1000);

}



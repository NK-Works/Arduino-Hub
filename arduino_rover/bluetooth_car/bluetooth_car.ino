// C++ Codes on Arduino IDE //
//   Bluetooth-based Rover  //

// Setting up some variables
int A=9; 
int B=5;
int speed;

char input;    // Stores the input coming from the Bluetooth

void setup()
{
  Serial.begin(9600);
  // Setting all the input and the output pins
  pinMode(4, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(A0,INPUT);
  pinMode(9, OUTPUT); 
  pinMode(5,OUTPUT); 
}

void loop()
{
  // speed = 200;
  // The potentiometer output is recieved and transformed here
  speed = analogRead(A0);
  speed = speed * 0.249;
  analogWrite(A,speed);
  analogWrite(B,speed);
  
  // // Taking the Bluetooth command
  while(Serial.available())
  {
    input = Serial.read();
    
    if(input == 'F')
    {
      forward();
    }

    else if (input == 'R')
    {
      right();  
    }

    else if (input == 'L')
    {
      left();
    }  

    else if (input == 'G')
    {
      backward();
    }  
    else if (input == 'S')
    {
      stop();
    }
  } 
}  
void backward()
  {
    digitalWrite(4, LOW	);
    digitalWrite(6, HIGH);
    digitalWrite(10, HIGH);
    digitalWrite(11, LOW);
  }

void stop()
  {
    digitalWrite(4, LOW	);
    digitalWrite(6, LOW);
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
  }

void forward()
  {
    digitalWrite(4, HIGH);
    digitalWrite(6, LOW);
    digitalWrite(10, LOW);
    digitalWrite(11, HIGH);
  }

void right()
  {
    digitalWrite(4, LOW);
    digitalWrite(6, HIGH);
    digitalWrite(10, LOW);
    digitalWrite(11, HIGH);
  }

void left()
  {
  digitalWrite(4, HIGH);
  digitalWrite(6, LOW);
  digitalWrite(10, HIGH);
  digitalWrite(11, LOW);
}
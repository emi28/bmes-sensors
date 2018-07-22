/*
# This sample codes is for testing the pH meter V1.0.
 # Editor : YouYou
 # Date   : 2013.10.12
 # Ver    : 0.1
 # Product: pH meter
 # SKU    : SEN0161
*/

#define SensorPin 0          //set up pin 0 as the input (attached to sensor)
unsigned long int avgValue;  //create long integer variable avgValue, unsigned such that nonnegative
float b;          //float variable b
int buf[10],temp;  //create buf array of 10 locations, and integer variable
float highph;
float lowph;

void setup()  //set up the hardware
{
  pinMode(13,OUTPUT);  //set up pin 13 as output
  Serial.begin(9600);  //set baud rate
  Serial.println("Ready");   //let user know connection is ready
  Serial.println("Maximum batch pH: "); //user enters high pH
  while (Serial.available()==0){} //testing if user has inputed value (0 when nothing put in)
  highph = Serial.parseFloat();
  Serial.println(highph);  
  
  Serial.println("Minimum batch pH: "); //user enters low pH
  while (Serial.available()==0){}
  lowph = Serial.parseFloat();
  Serial.println(lowph);
}

void loop(){ 
  for(int i=0;i<10;i++)       //reads if index i is between 0 and 10, increments by 1 i
  { 
    buf[i]=analogRead(SensorPin); //reads analog signal from sensor on SensorPin (0) and inputs into location i in matrix buf
        delay(10);  //delays 10 milliseconds: essentially takes 10 readings off the sensor
  }
  // sorting of values acquired by sensor by for loops 
  for(int i=0;i<9;i++)      //reads if index i is between 0 and 9, increments by 1
  {
    for(int j=i+1;j<10;j++)    //defines j index as i+1, reads if j less than 10, increments by 1
    {
      if(buf[i]>buf[j]) //if i space of buf is greater than j space of buf (if space before is larger than space after in buf array)
      {
        temp=buf[i];   //reassign buf[i] to variable temp
        buf[i]=buf[j];    //reassign buf[j] to buf[i] (to the space before)
        buf[j]=temp;    //assign value of temp to buf [j], essentially this reorders the array to be in ascending order 
      }
    }
  }
  
  //define pH value by ignoring 2 outliers on either side of data, and taking average of remaining data points
  avgValue=0;   
  for(int i=2;i<8;i++)  //loop between the 2 to 7 of index i, incrementing by 1.                     
    avgValue+=buf[i]; //sum together values of buf between the 2nd and 7th locations in the array
  float phValue=(float)avgValue*5.0/1024/6; //divide by 6 to get average value, and multiply avgValue variable by coefficient
  phValue=3.5*phValue;       //multiply by coefficient               
 
  Serial.print("    pH:");  //print "pH:____" with measured pH value from phValue variable, and go to next line
  Serial.print(phValue,2);
  Serial.println(" ");
  if (phValue > highph){
    Serial.println("pH is too high");
    digitalWrite(13, HIGH);    //set pin 13 on   
    delay(800);   //leave on for 800 ms
    digitalWrite(13, LOW); //set pin 13 off (blink LED ?) }
  if (phValue < lowph){
    Serial.println("pH is too low");
    digitalWrite(13, HIGH);    //set pin 13 on   
    delay(800);   //leave on for 800 ms
    digitalWrite(13, LOW); //set pin 13 off (blink LED ?)   
  }
  delay(1000);
}}




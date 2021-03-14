void setup() 
{   Serial.begin(9600); // Initialize serial port 
}  
void loop() 
{   String content = "";   
char character;    
while(Serial.available()) 
{       character = Serial.read();       
content.concat(character);       
delay (10);   }    
if (content != "") 
{     Serial.print(content);   } 
}

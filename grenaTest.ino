/*#include "HT1632.h"
#include "font_5x4.h"
#include "images.h"

int i = 0;
int wd;

void setup () {
  HT1632.begin(9, 10, 11);
}

void loop () {
  HT1632.clear();
  // This step only performs the drawing in internal memory. 
  HT1632.drawImage(IMG_SAILBOAT, IMG_SAILBOAT_WIDTH,  IMG_SAILBOAT_HEIGHT, i, 6);
  // If the image intersects with the end,
  if (i > OUT_SIZE - IMG_SAILBOAT_WIDTH) {
    // Draw it wrapping around.
    HT1632.drawImage(IMG_SAILBOAT, IMG_SAILBOAT_WIDTH,  IMG_SAILBOAT_HEIGHT, i - OUT_SIZE, 0);
  }
  HT1632.render(); // This updates the display on the screen.
  
  delay(100);
  
  i = (i + 1) % (OUT_SIZE);
}
-----------------------------------------------------------------------------------------------
*/

#include "HT1632.h"

// whole screen solid block
unsigned char IMG_BLOCK [] = {	
  // 1abcd   2abcd   3abcd   4abcd    
	0b1111, 0b1111, 0b1111, 0b1111,//1 
	0b1111, 0b1111, 0b1111, 0b1111,//2
	0b1111, 0b1111, 0b1111, 0b1111,//3 
	0b1111, 0b1111, 0b1111, 0b1111,//4
	0b1111, 0b1111, 0b1111, 0b1111,//5 
	0b1111, 0b1111, 0b1111, 0b1111,//6
	0b1111, 0b1111, 0b1111, 0b1111,//7 
	0b1111, 0b1111, 0b1111, 0b1111,//8
	0b1111, 0b1111, 0b1111, 0b1111,//9 
	0b1111, 0b1111, 0b1111, 0b1111,//10
	0b1111, 0b1111, 0b1111, 0b1111,//11 
	0b1111, 0b1111, 0b1111, 0b1111,//12
	0b1111, 0b1111, 0b1111, 0b1111,//13 
	0b1111, 0b1111, 0b1111, 0b1111,//14
	0b1111, 0b1111, 0b1111, 0b1111,//15 
	0b1111, 0b1111, 0b1111, 0b1111,//16
	0b1111, 0b1111, 0b1111, 0b1111,//17 
	0b1111, 0b1111, 0b1111, 0b1111,//18
	0b1111, 0b1111, 0b1111, 0b1111,//19 
	0b1111, 0b1111, 0b1111, 0b1111,//20
	0b1111, 0b1111, 0b1111, 0b1111,//21 
	0b1111, 0b1111, 0b1111, 0b1111,//22
	0b1111, 0b1111, 0b1111, 0b1111,//23 
	0b1111, 0b1111, 0b1111, 0b1111 //24
};
#define IMG_BLOCK_HEIGHT 16
#define IMG_BLOCK_WIDTH 24

// single dot
unsigned char IMG_DOT [] = {	0b0001 };
#define IMG_DOT_HEIGHT 4
#define IMG_DOT_WIDTH 1

// whole screen game over message
unsigned char IMG_GM_OVR [] = {	
  // 1abcd   2abcd   3abcd   4abcd    
	0b1110, 0b0011, 0b1100, 0b0111,//1  
	0b0001, 0b0100, 0b0010, 0b1000,//2
	0b1001, 0b0100, 0b0010, 0b1000,//3  
	0b1001, 0b0100, 0b0010, 0b1000,//4  
	0b1010, 0b0011, 0b1100, 0b0111,//5


	0b0000, 0b0000, 0b0000, 0b0000,//6


	0b1100, 0b0111, 0b1110, 0b0011,//7
	0b0010, 0b0001, 0b0000, 0b0100,//8

	0b0001, 0b0001, 0b0000, 0b1000,//9
	0b0010, 0b0001, 0b0000, 0b0100,//10   
	0b1100, 0b0111, 0b1110, 0b0011,//11
	
	
	0b0000, 0b0000, 0b0000, 0b0000,//12   

	
	0b1111, 0b0111, 0b1110, 0b1111,//13
	0b0010, 0b0000, 0b0010, 0b1001,//14   
	0b0100, 0b0000, 0b0010, 0b1001,//15
	0b0010, 0b0000, 0b0010, 0b1001,//16   

	0b1111, 0b0111, 0b0010, 0b1000,//17
	
	
	0b0000, 0b0000, 0b0000, 0b0000,//18   
	
	
	0b1111, 0b0111, 0b1110, 0b1111,//19
	0b1001, 0b0100, 0b0010, 0b0001,//20   
	0b1001, 0b0100, 0b0010, 0b0001,//21
	0b1001, 0b0100, 0b0010, 0b0011,//22   
	0b0001, 0b0100, 0b1100, 0b1100,//23
	
	
	0b0000, 0b0000, 0b0000, 0b0000 //24   
};
#define IMG_GM_OVR_HEIGHT 16
#define IMG_GM_OVR_WIDTH 24


// inverted game over message
unsigned char IMG_XGM_OVR [] = {	
  // 0abcd   2abcd   3abcd   4abcd    
	0b0001, 0b1100, 0b0011, 0b1000,//0  
	0b1110, 0b1011, 0b1101, 0b0111,//2
	0b0110, 0b1011, 0b1101, 0b0111,//3  
	0b0110, 0b1011, 0b1101, 0b0111,//4  
	0b0101, 0b1100, 0b0011, 0b1000,//5


	0b1111, 0b1111, 0b1111, 0b1111,//6


	0b0011, 0b1000, 0b0001, 0b1100,//7
	0b1101, 0b1110, 0b1111, 0b1011,//8

	0b1110, 0b1110, 0b1111, 0b0111,//0
	0b1101, 0b1110, 0b1111, 0b1011,//01   
	0b0011, 0b1000, 0b0001, 0b1100,//00
	
	
	0b1111, 0b1111, 0b1111, 0b1111,//02   

	
	0b0000, 0b1000, 0b0001, 0b0000,//03
	0b1101, 0b1111, 0b1101, 0b0110,//04   
	0b1011, 0b1111, 0b1101, 0b0110,//05
	0b1101, 0b1111, 0b1101, 0b0110,//06   

	0b0000, 0b1000, 0b1101, 0b0111,//07
	
	
	0b1111, 0b1111, 0b1111, 0b1111,//08   
	
	
	0b0000, 0b1000, 0b0001, 0b0000,//00
	0b0110, 0b1011, 0b1101, 0b1110,//21   
	0b0110, 0b1011, 0b1101, 0b1110,//20
	0b0110, 0b1011, 0b1101, 0b1100,//22   
	0b1110, 0b1011, 0b0011, 0b0011,//23
	
	
	0b1111, 0b1111, 0b1111, 0b1111 //24   
};
#define IMG_XGM_OVR_HEIGHT 16
#define IMG_XGM_OVR_WIDTH 24

unsigned char IMG_NUMS [] = { 
	//NUMBER 0
  // 1abcd   2abcd   3abcd       
	0b1000, 0b1111, 0b0111,//1 
	0b0100, 0b0000, 0b1110,//2
	0b0100, 0b1000, 0b1001,//3 
	0b0100, 0b0110, 0b1000,//4
	0b1100, 0b0001, 0b1000,//5 
	0b1000, 0b1111, 0b0111,//6	

	//NUMBER 1
  // 1abcd   2abcd   3abcd       
	0b0000, 0b0000, 0b1000,//1 
	0b0000, 0b0001, 0b1000,//2
	0b1000, 0b0000, 0b1000,//3 
	0b1100, 0b1111, 0b1111,//4
	0b0000, 0b0000, 0b1000,//5 
	0b0000, 0b0000, 0b1000,//6

	//NUMBER 2
  // 1abcd   2abcd   3abcd       
	0b1000, 0b0000, 0b1100,//1 
	0b0100, 0b0000, 0b1010,//2
	0b0100, 0b0000, 0b1001,//3 
	0b0100, 0b1000, 0b1000,//4
	0b0100, 0b0100, 0b1000,//5 
	0b1000, 0b0011, 0b1000,//6	

	//NUMBER 3
  // 1abcd   2abcd   3abcd       
	0b1000, 0b0000, 0b0100,//1 
	0b0100, 0b0000, 0b1000,//2
	0b0100, 0b0100, 0b1000,//3 
	0b0100, 0b0100, 0b1000,//4
	0b0100, 0b0100, 0b1000,//5 
	0b1000, 0b1011, 0b0111,//6	

	//NUMBER 4
  // 1abcd   2abcd   3abcd       
	0b0000, 0b1111, 0b0001,//1 
	0b0000, 0b0000, 0b0001,//2
	0b0000, 0b0000, 0b0001,//3 
	0b0000, 0b0000, 0b0001,//4
	0b1100, 0b1111, 0b1111,//5 
	0b0000, 0b0000, 0b0001,//6	

	//NUMBER 5
  // 1abcd   2abcd   3abcd       
	0b1100, 0b0011, 0b1000,//1 
	0b0100, 0b0010, 0b1000,//2
	0b0100, 0b0010, 0b1000,//3 
	0b0100, 0b0010, 0b1000,//4
	0b0100, 0b0100, 0b0100,//5 
	0b0000, 0b1000, 0b0011,//6

	//NUMBER 6
  // 1abcd   2abcd   3abcd       
	0b1000, 0b1111, 0b0111,//1 
	0b0100, 0b1000, 0b1000,//2
	0b0100, 0b0100, 0b1000,//3 
	0b0100, 0b0100, 0b1000,//4
	0b0100, 0b0100, 0b1000,//5 
	0b1000, 0b1000, 0b0111,//6	

	//NUMBER 7
  // 1abcd   2abcd   3abcd       
	0b1100, 0b0000, 0b0100,//1 
	0b0100, 0b0000, 0b0010,//2
	0b0100, 0b0000, 0b0001,//3 
	0b0100, 0b1000, 0b0000,//4
	0b0100, 0b0100, 0b0000,//5 
	0b1100, 0b0011, 0b0000,//6	

	//NUMBER 8
  // 1abcd   2abcd   3abcd       
	0b1000, 0b1011, 0b0111,//1 
	0b0100, 0b0100, 0b1000,//2
	0b0100, 0b0100, 0b1000,//3 
	0b0100, 0b0100, 0b1000,//4
	0b0100, 0b0100, 0b1000,//5 
	0b1000, 0b1011, 0b0111,//6	
	
	//NUMBER 9
  // 1abcd   2abcd   3abcd       
	0b1000, 0b0011, 0b0100,//1 
	0b0100, 0b0100, 0b1000,//2
	0b0100, 0b0100, 0b1000,//3 
	0b0100, 0b0100, 0b1000,//4
	0b0100, 0b0100, 0b1000,//5 
	0b1000, 0b1111, 0b0111,//6	

	//NUMBER Template
  // 1abcd   2abcd   3abcd     

	0b1100, 0b1111, 0b1111,//1 
	0b1100, 0b1111, 0b1111,//2
	0b1100, 0b1111, 0b1111,//3 
	0b1100, 0b1111, 0b1111,//4
	0b1100, 0b1111, 0b1111,//5 
	0b1100, 0b1111, 0b1111,//6	
};

#define IMG_NUMS_HEIGHT 12
#define IMG_NUMS_WIDTH 6
#define IMG_NUMS_GLYPH_STEP 18 //18 bytes per number

	// inverted numbers
unsigned char IMG_XNUMS [] = {
	//NUMBER 0
  // 00abcd   10abcd   30abcd       
	0b0111, 0b0000, 0b1000,//0 
	0b1011, 0b1111, 0b0001,//1
	0b1011, 0b0111, 0b0110,//3 
	0b1011, 0b1001, 0b0111,//4
	0b0011, 0b1110, 0b0111,//5 
	0b0111, 0b0000, 0b1000,//6	

	//NUMBER 1
  // 00abcd   10abcd   30abcd       
	0b1111, 0b1111, 0b0111,//0 
	0b1111, 0b1110, 0b0111,//1
	0b0111, 0b1111, 0b0111,//3 
	0b0011, 0b0000, 0b0000,//4
	0b1111, 0b1111, 0b0111,//5 
	0b1111, 0b1111, 0b0111,//6

	//NUMBER 2
  // 00abcd   10abcd   30abcd       
	0b0111, 0b1111, 0b0011,//0 
	0b1011, 0b1111, 0b0101,//1
	0b1011, 0b1111, 0b0110,//3 
	0b1011, 0b0111, 0b0111,//4
	0b1011, 0b1011, 0b0111,//5 
	0b0111, 0b1100, 0b0111,//6	

	//NUMBER 3
  // 00abcd   10abcd   30abcd       
	0b0111, 0b1111, 0b1011,//0 
	0b1011, 0b1111, 0b0111,//1
	0b1011, 0b1011, 0b0111,//3 
	0b1011, 0b1011, 0b0111,//4
	0b1011, 0b1011, 0b0111,//5 
	0b0111, 0b0100, 0b1000,//6	

	//NUMBER 4
  // 00abcd   10abcd   30abcd       
	0b1111, 0b0000, 0b1110,//0 
	0b1111, 0b1111, 0b1110,//1
	0b1111, 0b1111, 0b1110,//3 
	0b1111, 0b1111, 0b1110,//4
	0b0011, 0b0000, 0b0000,//5 
	0b1111, 0b1111, 0b1110,//6	

	//NUMBER 5
  // 00abcd   10abcd   30abcd       
	0b0011, 0b1100, 0b0111,//0 
	0b1011, 0b1101, 0b0111,//1
	0b1011, 0b1101, 0b0111,//3 
	0b1011, 0b1101, 0b0111,//4
	0b1011, 0b1011, 0b1011,//5 
	0b1111, 0b0111, 0b1100,//6

	//NUMBER 6
  // 00abcd   10abcd   30abcd       
	0b0111, 0b0000, 0b1000,//0 
	0b1011, 0b0111, 0b0111,//1
	0b1011, 0b1011, 0b0111,//3 
	0b1011, 0b1011, 0b0111,//4
	0b1011, 0b1011, 0b0111,//5 
	0b0111, 0b0111, 0b1000,//6	

	//NUMBER 7
  // 00abcd   10abcd   30abcd       
	0b0011, 0b1111, 0b1011,//0 
	0b1011, 0b1111, 0b1101,//1
	0b1011, 0b1111, 0b1110,//3 
	0b1011, 0b0111, 0b1111,//4
	0b1011, 0b1011, 0b1111,//5 
	0b0011, 0b1100, 0b1111,//6	

	//NUMBER 8
  // 00abcd   10abcd   30abcd       
	0b0111, 0b0100, 0b1000,//0 
	0b1011, 0b1011, 0b0111,//1
	0b1011, 0b1011, 0b0111,//3 
	0b1011, 0b1011, 0b0111,//4
	0b1011, 0b1011, 0b0111,//5 
	0b0111, 0b0100, 0b1000,//6	
	
	//NUMBER 9
  // 00abcd   10abcd   30abcd       
	0b0111, 0b1100, 0b1011,//0 
	0b1011, 0b1011, 0b0111,//1
	0b1011, 0b1011, 0b0111,//3 
	0b1011, 0b1011, 0b0111,//4
	0b1011, 0b1011, 0b0111,//5 
	0b0111, 0b0000, 0b1000,//6	

};


#define IMG_XNUMS_HEIGHT 12
#define IMG_XNUMS_WIDTH 6
#define IMG_XNUMS_GLYPH_STEP 18 //18 bytes per number


unsigned char IMG_NEW_GAME []={
	
	//NUMBER Template
  // 1abcd   2abcd  
	0b0000, 0b0000,//SPACE
	0b1111, 0b0001, 
	0b0010, 0b0000,
	0b0100, 0b0000,
	0b1000, 0b0000,
	0b1111, 0b0001,//N
	0b0000, 0b0000,//SPACE
	0b1111, 0b0001, 
	0b0101, 0b0001,
	0b0101, 0b0001,
	0b0001, 0b0001,//E
	0b0000, 0b0000,//SPACE
	0b1111, 0b0000, 
	0b0000, 0b0001,
	0b1000, 0b0000,
	0b0000, 0b0001,
	0b1111, 0b0000,//W
	0b0000, 0b0000,//SPACE
	0b0100, 0b0000, 
	0b0100, 0b0000, 
	0b0100, 0b0000,
	0b0101, 0b0001,
	0b1110, 0b0000,
	0b0100, 0b0000,//->
};

#define IMG_NEW_GAME_HEIGHT 5
#define IMG_NEW_GAME_WIDTH 24



#define LEFT 6
#define RIGHT 3
#define UP 4
#define DOWN 5

const byte PIN_BUTTON_JOYSTICK = 2;
const byte PIN_BUTTON_RIGHT = 3;
const byte PIN_BUTTON_UP = 4;
const byte PIN_BUTTON_DOWN = 5;
const byte PIN_BUTTON_LEFT = 6;
const byte PIN_ANALOG_X = 0;
const byte PIN_ANALOG_Y = 1;


int x [96]; 
int y [96];
int orderedX [96];
int orderedY [96];
int snakeSize; 
int snakePlus; 
int foodX; 
int foodY;
int grow; 
bool needNewFood; 
bool hitSomething; 
int moving; 
int score;
int scoreHundreds;
int scoreTens;
int scoreOnes;
bool newGame; 


void setup() {
  Serial.begin(9600);
  pinMode(PIN_BUTTON_RIGHT, INPUT);
  digitalWrite(PIN_BUTTON_RIGHT, HIGH);
  pinMode(PIN_BUTTON_LEFT, INPUT);
  digitalWrite(PIN_BUTTON_LEFT, HIGH);
  pinMode(PIN_BUTTON_UP, INPUT);
  digitalWrite(PIN_BUTTON_UP, HIGH);
  pinMode(PIN_BUTTON_DOWN, INPUT);
  digitalWrite(PIN_BUTTON_DOWN, HIGH);
  pinMode(PIN_BUTTON_JOYSTICK, INPUT);
  digitalWrite(PIN_BUTTON_JOYSTICK, HIGH);
  
  HT1632.begin( 9, 10, 11);
  newGame = true; 
}

void loop() {  
  
  Serial.print(x[0]);
  Serial.print(",");
  Serial.println(y[0]);
  
  if (newGame){
    initialize(); 
    gameBeginSequence();
  }

  if(!hitSomething){ 
    checkPad();
    move();
    checkHitFood();
    checkHitSelf(); 
  }
  
  if (hitSomething && scoreOnes == -1){
    displayGameOver();
    delay(1500);
  }
  
  if (hitSomething) { 
    displayScore();
  }
 
  delay(100);
}


void initialize(){
  x[0] = 11; 
  x[1] = 10;
  x[2] = 9;
  x[3] = 8;
  y[0] = 6;
  y[1] = 6;
  y[2] = 6;
  y[3] = 6;
  snakeSize = 4;
  snakePlus = snakeSize+1;
  grow = 0;
  hitSomething=false;
  score = 0; 
  scoreHundreds = -1;
  scoreTens = -1;
  scoreOnes = -1;
  moving = RIGHT;
  relocFood();
  checkFood();
}
  

void gameBeginSequence(){
  
  HT1632.clear();
  HT1632.drawImage(IMG_BLOCK, IMG_BLOCK_WIDTH, IMG_BLOCK_HEIGHT, 0, 0, 0);  
  HT1632.drawImage(IMG_XNUMS, IMG_XNUMS_WIDTH, IMG_XNUMS_HEIGHT, 9, 1, 3*IMG_XNUMS_GLYPH_STEP); 
  HT1632.render();
  delay(1000);
  
  
  HT1632.clear();
  HT1632.drawImage(IMG_NUMS, IMG_NUMS_WIDTH, IMG_NUMS_HEIGHT, 9, 1, 2*IMG_NUMS_GLYPH_STEP);
  HT1632.render();  
  delay(1000);
  
  
  HT1632.clear();
  HT1632.drawImage(IMG_BLOCK, IMG_BLOCK_WIDTH, IMG_BLOCK_HEIGHT, 0, 0, 0);  
  HT1632.drawImage(IMG_XNUMS, IMG_XNUMS_WIDTH, IMG_XNUMS_HEIGHT, 9, 1, 1*IMG_XNUMS_GLYPH_STEP);
  HT1632.render();  
  delay(1000);
  
  
  newGame = false;
}


void checkHitFood(){
    if (x[0]==foodX && y[0]==foodY){ 
    relocFood();
    checkFood();
    grow+=2;
    score += 5;
  }
}


void checkHitSelf(){
  for (int i=1; i<snakeSize; i++){
    if ((x[0]==x[i]&&y[0]==y[i])){ 

      hitSomething = true;
      break; 
    } 
  }
  if (!hitSomething) { 
    orderXY();
    HT1632.clear();
    for(int i=0; i<snakePlus; i++){
      HT1632.drawImage(IMG_DOT, IMG_DOT_WIDTH, IMG_DOT_HEIGHT, orderedX[i], orderedY[i], 0);  
    }
    HT1632.render();
  }
}


void displayGameOver(){
    HT1632.clear();
    HT1632.drawImage(IMG_GM_OVR, IMG_GM_OVR_WIDTH, IMG_GM_OVR_HEIGHT, 0 , 0, 0);
    HT1632.render();  
}

  


void displayScore(){
  scoreHundreds = floor(score/100);
  scoreTens = floor((score%100)/10);
  scoreOnes = floor((score%100)%10);

  HT1632.clear();
  HT1632.drawImage(IMG_NUMS, IMG_NUMS_WIDTH, IMG_NUMS_HEIGHT, 1, 4,  scoreHundreds*IMG_NUMS_GLYPH_STEP); 
  HT1632.drawImage(IMG_NUMS, IMG_NUMS_WIDTH, IMG_NUMS_HEIGHT, 9, 4,  scoreTens*IMG_NUMS_GLYPH_STEP); 
  HT1632.drawImage(IMG_NUMS, IMG_NUMS_WIDTH, IMG_NUMS_HEIGHT, 17, 4,  scoreOnes*IMG_NUMS_GLYPH_STEP); 
  HT1632.drawImage(IMG_NEW_GAME, IMG_NEW_GAME_WIDTH, IMG_NEW_GAME_HEIGHT, 0, 0, 0); 
  HT1632.render();
  moving = 0; 
  delay(250);
  if (digitalRead(PIN_BUTTON_JOYSTICK)==0){
    newGame = true;
  }
}



void move(){
  if(moving == RIGHT){
    if (grow > 0) {
      growRight();
      grow--;
    }
    else {    
      moveRight();
    }
  }
  
  if(moving == LEFT){
    if (grow > 0) {
      growLeft();
      grow--;
    }
    else {    
      moveLeft();
    }
  }
  
  if(moving == DOWN){
    if (grow > 0) {
      growDown();
      grow--;
    }
    else {    
      moveDown();
    }  
  }
  
  if(moving == UP){
    if (grow > 0) {
      growUp();
      grow--;
    }
    else {    
      moveUp();
    }
  }
}


void checkPad(){
  if ((digitalRead(PIN_BUTTON_RIGHT)==0 || analogRead(PIN_ANALOG_X)>612) && !(moving == LEFT)){
    moving = RIGHT;
  }
  
  else if ((digitalRead(PIN_BUTTON_LEFT)==0 || analogRead(PIN_ANALOG_X)<412) && !(moving == RIGHT)){
    moving = LEFT;
  }
  
  else if ((digitalRead(PIN_BUTTON_DOWN)==0 || analogRead(PIN_ANALOG_Y)<412) && !(moving == UP)){
    moving = DOWN;
  }
  
  else if ((digitalRead(PIN_BUTTON_UP)==0 || analogRead(PIN_ANALOG_Y)>612) && !(moving == DOWN)){
    moving = UP;
  }
}


void relocFood(){
  foodX = random(24);
  foodY = random(16);  
}


void checkFood(){
  while(1){
    needNewFood=false;
    for (int i=0; i<snakeSize; i++){
      if (foodX==x[i] && foodY==y[i]){
        needNewFood=true; 
        break; 
      }
    }
    if (!needNewFood){ 
      break;
    }
    else {
      relocFood();
    }
  }
}


void moveUp(){
 push();
 if (y[0]>0) {
   y[0]=y[0]-1;
 }
 else {
   y[0]=COM_SIZE-1;
 }
}


void growUp(){
  x[snakeSize] = x[snakeSize-1];
  y[snakeSize] = y[snakeSize-1];  
  moveUp();
  snakeSize++;
  snakePlus++;
}


void moveDown(){
 push();
 if (y[0]<COM_SIZE-1) {
   y[0]=y[0]+1;
 }
 else {
   y[0]=0;
 }
}


void growDown(){
  x[snakeSize] = x[snakeSize-1];
  y[snakeSize] = y[snakeSize-1];  
  moveDown();
  snakeSize++;
  snakePlus++;
}


void moveLeft(){
 push();
 if (x[0]>0){
   x[0]=x[0]-1;
 }
 else {
   x[0]=OUT_SIZE-1;
 }
}


void growLeft(){
  x[snakeSize] = x[snakeSize-1];
  y[snakeSize] = y[snakeSize-1];  
  moveLeft();
  snakeSize++;
  snakePlus++;
}


void moveRight(){
 push();
 if (x[0]<OUT_SIZE-1){    
   x[0]=x[0]+1;
 }
 else {
   x[0]=0;
 }
}


void growRight(){
  x[snakeSize] = x[snakeSize-1];
  y[snakeSize] = y[snakeSize-1];  
  moveRight();
  snakeSize++;
  snakePlus++;
}


void push(){
  for(int i=snakeSize-1; i>0; i--){
    y[i]=y[i-1];
    x[i]=x[i-1]; 
  }
}


void orderXY(){
  int i=0;
 for (int j=0; j<16; j++){ 
   for (int k=0; k<snakeSize; k++){ 
     if (y[k] == j){
       orderedX[i] = x[k];
       orderedY[i] = y[k];
       i++;
     }
   }
   if (foodY == j){
     orderedX[i] = foodX;
     orderedY[i] = foodY;
     i++;
   }
 }
}

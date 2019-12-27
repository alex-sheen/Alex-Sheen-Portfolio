
/**
 * ControlP5 Button
 * this example shows how to create buttons with controlP5.
 * 
 * find a list of public methods available for the Button Controller 
 * at the bottom of this sketch's source code
 *
 * by Andreas Schlegel, 2012
 * www.sojamo.de/libraries/controlp5
 *
 */

import controlP5.*;

ControlP5 cp5;

PImage tiger;
PGraphics main;

boolean gray = false;
float opacity = 255;
float brightness = 255;
float warmth = 0;


void setup() {
  size(757,757); //dimensions under Get Info
   main = createGraphics(width, height);
  tiger = loadImage("Tiger.jpeg");
  tiger.resize(757, 757);
   main.beginDraw();
     main.image(tiger,0,0);

   main.endDraw();
  cp5 = new ControlP5(this);

  cp5.addSlider("light")
     .setPosition(0, 0)
     .setSize(200, 19)
     .setRange(-255,255)
     .setValue(0)
     ;
     
   cp5.addSlider("warmth")
     .setPosition(0, 20)
     .setSize(200, 19)
     .setRange(-255,255)
     .setValue(0)
     ;
     
   cp5.addSlider("opacity")
     .setPosition(0, 40)
     .setSize(200, 19)
     .setRange(0,255)
     .setValue(255)
     ;
     
    cp5.addButton("grayscale")
    .setPosition(0, 60)
     .setSize(200, 19)
     ;
     
    cp5.addSlider("threshhold")
     .setPosition(0, 80)
     .setSize(200, 19)
     .setRange(0,255)
     .setValue(255)
     ;
    cp5.addButton("k1")
    .setPosition(0, 100)
     .setSize(50, 19)
     ;
     
     cp5.addButton("k2")
    .setPosition(50, 100)
     .setSize(50, 19)
     ;
     
     cp5.addButton("k3")
    .setPosition(100, 100)
     .setSize(50, 19)
     ;
  
}

void draw() {
  //buffering
  image(tiger, 100, 0);
  image(main, 0, 0);
}

// function colorB will receive changes from 
// controller with name colorB
void light(int val) {

  println("a slider event from brightness: "+val);
  brightness = val;
    mainEvent();


}

void warmth(int val) {
  println("a slider event from warmth: "+val);
  warmth = val;
    mainEvent();

 
}

void opacity(int val) {
  println("a slider event from opacity: "+val);
  opacity = val;
  mainEvent();
}

void mainEvent()
{
 println("a slider event from mainEvent: ");
 
  main.loadPixels();
  tiger.loadPixels();
  for (int i = 0; i < tiger.pixels.length; i++) {
    float r = red   (tiger.pixels[i]);
    float g = green (tiger.pixels[i]);
    float b = blue  (tiger.pixels[i]);
   
       r += brightness;
       g += brightness;
       b += brightness;
  
      r += warmth;
      b -= warmth;
      // Constrain RGB to between 0-255
      r = constrain(r,0,255);
      g = constrain(g,0,255);
      b = constrain(b,0,255);
    // Make a new color and set pixel in the window
    color c = color(r,g,b,opacity);
     main.pixels[i] = c;
  }
   main.updatePixels();
}

void threshhold(int val) {
  println("a slider event from opacity: "+val);
  if(gray == true){
       main.loadPixels();
      tiger.loadPixels();
      for (int i = 0; i < tiger.pixels.length; i++) {
        float r = red   (tiger.pixels[i]);
        float g = green (tiger.pixels[i]);
        float b = blue  (tiger.pixels[i]);
       
       
          r = 0.2126*r;
           g = 0.7152*g;
           b = 0.0722*b;
         float grayNum = r+g+b;
         grayNum = constrain(grayNum,0,255);
         
        // Make a new color and set pixel in the window
        if(grayNum >= val)
        {
             main.pixels[i] = color(0);
        }
        
        else
        {
            main.pixels[i] = color(255);
        }
      }
       main.updatePixels();
   
  }
}

void grayscale() {
 if(gray == false)
 {
    main.loadPixels();
  tiger.loadPixels();
  for (int i = 0; i < tiger.pixels.length; i++) {
    float r = red   (tiger.pixels[i]);
    float g = green (tiger.pixels[i]);
    float b = blue  (tiger.pixels[i]);
    //grayscale(r,g,b)  = 0.2126 * r + 0.7152 * g + 0.0722 * b
   
   r = 0.2126*r;
   g = 0.7152*g;
   b = 0.0722*b;
   float grayNum = r+g+b;
     grayNum = constrain(grayNum,0,255);
   
    // Make a new color and set pixel in the window
    color c = color(grayNum);
     main.pixels[i] = c;
  }
   main.updatePixels();
  gray =true;
 }
 
 else{
   gray = false;
    mainEvent();
 }
}
//horizontal
void hFlip(boolean down) {
   main.loadPixels();
  //only need to access top half of image
  for (int y = 0; y < height/2; y++) { // for each row 
    for (int x = 0; x < width; x++) {  // for each pixel in row
      if (down)
         main.pixels[x+(height-y-1)*width] =  main.pixels[x+(y*width)];
      else
         main.pixels[x+(y*width)] =  main.pixels[x+(height-y-1)*width];
    } //swap color information for each pixel
  }
   main.updatePixels();
}

//verticle
void vFlip(boolean down) {
   main.loadPixels();
  //only need to access top half of image
  for (int y = 0; y < height-1; y++) { // for each row 
    for (int x = 0; x < width/2; x++) {  // for each pixel in row
      if (down)
               main.pixels[x+(y*width)] =  main.pixels[(width-x)+y*width];
      else
               main.pixels[(width-x)+y*width] =  main.pixels[x+(y*width)];
    } //swap color information for each pixel
  }
   main.updatePixels();
}

//diagonal
void dFlip(boolean pos) {
   main.loadPixels();
  //only need to access top half of image
  for (int y = 0; y < height; y++) { // for each row 
    for (int x = 0; x < width; x++) {  // for each pixel in row
      if (pos)
      {
      main.pixels[y+x*width] =  main.pixels[x+(y*(width))];    
     //swap color information for each pixel

      }
      
      
      else
      {
      main.pixels[(width-y-1)+(height-x-1)*width] =  main.pixels[x+(y*(width))];
      }
  }  
  }
   main.updatePixels();
}

void down() {
  hFlip(true);
}

void up() {
  hFlip(false);
}

void n() {
  dFlip(true);
}

void p() {
  dFlip(false);
}

void left() {
  vFlip(true);
}

void right() {
  vFlip(false);
}

void keyPressed() {
  if (keyCode == DOWN)
    down();
  else if (keyCode == UP)
    up(); 
  else if (keyCode == RIGHT)
    right(); 
  else if (keyCode == LEFT)
    left(); 
  else if (key == 'p')
    p();
  else if (key == 'n')
    n(); 
  else if (keyCode == ENTER) 
    main.beginDraw();
    main.image(tiger, 0, 0); //draw Tiger to canvas'
    main.endDraw();
}

void k1()
{
 up();
 n();
 up();
 n();
}

void k2()
{
 down();
 n();
 down();
 n();
 up();
 n();
}

void k3()
{
  p();
  up();
  p();
  up();
}

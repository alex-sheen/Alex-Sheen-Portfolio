import java.io.*;
public class bakeWaffles {

//randRange [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
public static int randRange(int min, int max){
  return (min + (int)(Math.random() * ((max - min) + 1)));
}//randRange

//matchLength [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
public static double[] matchLength(double[] a1, double[] a2, int num){
    if(num == 1){
      double[] b = new double[a1.length];
      for(int i = 0; i<a1.length;i++){
        if(i>=a2.length){
          b[i]=0;
        }
        else{
        b[i] = a2[i];
        }
      }
      return b;
    }
    else{
      double[] b = new double[a2.length];
      for(int i = 0; i<a2.length;i++){
        if(i>=a1.length){
          b[i]=0;
        }
        else{
        b[i] = a1[i];
        }
      }
      return b;

    }
}//matchLength

//Part 2 [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
public static void generatePiano(){
  double[] b = {};
  int[] cMajor = {-7,-5,-7,-5,3,5,7,8};
  int startPitch = randRange(0,4);
  double duration = 0.13;
  double rest = 0.06;
  double barDuration = 3;
  double currentDuration = 0;
  int bars = 8;
  for(int bar = 0;bar<bars;bar++){
        while(currentDuration<barDuration){
          int note = randRange(0,cMajor.length-1);
          double[] noteDurChoices = {0.5,0.75,1,1.25,1.5,1,1.5};
          double noteDuration = noteDurChoices[randRange(0,noteDurChoices.length-1)];
          noteDuration = noteDuration-rest;
          if(currentDuration + noteDuration+rest>barDuration){
            noteDuration = barDuration-currentDuration;
            currentDuration+= 50;
            System.out.println(-100 + " " + noteDuration);
          }
          else{
              currentDuration += noteDuration;
              System.out.println(cMajor[note] + " " + noteDuration);
              currentDuration+=rest;
              System.out.println(-100 + " " + rest);

          }
        }
        currentDuration = 0;
  }
}

//Main [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
  // read in notes from standard input and play them on standard audio
  public static void main(String[] args) {
    int[] cMajor = {3,5,7,8,11};

    double[] a = {};
    double[] b = {};
    //a = part1();
    //a = concatArray(a, part2());
    generatePiano();
  }
}

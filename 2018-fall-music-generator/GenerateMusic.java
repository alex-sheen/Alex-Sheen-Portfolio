/*
Generating Random Music

Generating the music :
  Our music contains two sections.
    The first section contains random C Major chords with random durations.
      These are sine waves with delay.
    The second section contains three instruments : drums, sine wave chords, and random notes.
      Drums are made by quickly shifting down the pitch of a sine wave.
      The random notes play sine, square, and sawtooth waves.

Visualization :
  Our MyRunnable.java reads pitches and durations from GenerateMusic.java and plays notes in sync with the music.
    To do this, each note is queued up based on its duration. Once the song starts playing,
    each note is shifted down until they reach the line, at which time the corresponding
    note is played through the speakers.




*/

import java.io.*;
public class GenerateMusic {

  public static int numNotes = 0;
  public static int[] pitchPub = new int[500];
  public static double[] durationPub = new double[500];
  public static double[][] dots = new double[500][2];
  public static double durationPlaceHolder = 8;
  public static int counter = 0;



//Weight Sum [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
    // return weighted sum of two arrays
    public static double[] sum(double[] a, double[] b, double awt, double bwt) {
        // precondition: arrays have the same length
        assert a.length == b.length;
        // compute the weighted sum
        double[] c = new double[a.length];
        for (int i = 0; i < a.length; i++) {
            c[i] = a[i]*awt + b[i]*bwt;
        }
        return c;
    }//weighted sum

//Tone [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
    // create a pure tone of the given frequency for the given duration
    public static double[] tone(double pitch, double duration) {
        double hz = 440.0 * Math.pow(2, pitch / 12.0);

        int n = (int) (StdAudio.SAMPLE_RATE * duration);
        double[] a = new double[n+1];
        for (int i = 0; i <= n; i++) {
          a[i] = Math.sin(2 * Math.PI * i * hz / StdAudio.SAMPLE_RATE);
        }
        return a;
    }//tone

//fade [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
    public static double[] fade(double[] a, double duration, String type){
      if(type == "IN"){
            double[] b = new double[a.length];
            for(int i = 0; i <(int)(duration*StdAudio.SAMPLE_RATE); i++){
              b[i] = a[i] * i/duration/StdAudio.SAMPLE_RATE;
            }
            for(int i = (int)(duration*StdAudio.SAMPLE_RATE); i <b.length; i++){
              b[i] = a[i];
            }
            return b;
      }

      else{
            double[] b = new double[a.length];
            int durationb = b.length-(int)(duration*StdAudio.SAMPLE_RATE);
            duration = (int)(duration*StdAudio.SAMPLE_RATE);

            for(int i = 0; i <(int)durationb; i++){
              b[i] = a[i];
            }

            for(int i = (int) durationb; i <b.length; i++){
              b[i] = a[i] * (((-1/duration) * (i - durationb))+1);
            }
            return b;
      }
    }//fade




//ADSR ADSR [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
    // amplitude envelope for a given array
    public static double[] ADSR(double[] array, double attack, double decay, double sustain, double slevel, double release) {
            double a = attack;
            double d = decay;
            double s = sustain;
            double r = release;

            int duration = (int) ((a+d+s+r) * StdAudio.SAMPLE_RATE);
              for (int i = 0; i < duration; i++) {
                if(0<=i && i<= (int) (a*StdAudio.SAMPLE_RATE)){
                  array[i] = array[i]*i/((int) (a*StdAudio.SAMPLE_RATE));
                }

                else if(((int) (a*StdAudio.SAMPLE_RATE)) < i && i <= (int) ((a+d)*StdAudio.SAMPLE_RATE)){
                  double bop = (slevel-1)/((int) (d*StdAudio.SAMPLE_RATE))*(i-((int) (a*StdAudio.SAMPLE_RATE)));
                  array[i] = array[i] * (bop + 1);

                }

                else if(((int) ((a+d)*StdAudio.SAMPLE_RATE)) < i && i <= (int) ((a+d+s)*StdAudio.SAMPLE_RATE)){
                  array[i] = array[i]*slevel;

                }
                else{
                  double bop = i-(  (int) ((a+d+s+r)*StdAudio.SAMPLE_RATE) );
                  bop = Math.pow(bop, 2);
                  bop = bop *slevel / Math.pow(((int) (r*StdAudio.SAMPLE_RATE)), 2);
                  array[i] = array[i] * bop;

                }
              }
      return array;
    }//ADSR ADSR




//sawtooth [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
    public static double[] sawtooth(double pitch, double duration) {
          double hz = 440.0 * Math.pow(2, pitch / 12.0);

           int n = (int) (StdAudio.SAMPLE_RATE * duration);
           double[] a = new double[n+1];
           double phase = -1;
           double phaseincr = hz/StdAudio.SAMPLE_RATE;
           double p = 0.5;
           for (int i = 0; i <= n; i++) {
             if(phase>=1) phase = -1;
             a[i] = phase*p;
             phase += phaseincr;
           }
           return a;
       }//sawtooth


//pitch shift [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
      public static double[] pitchShift(int p1, int p2, double duration){
         double hz1 = 440.0 * Math.pow(2, p1 / 12.0);
         double hz2 = 440.0 * Math.pow(2, p2 / 12.0);

         hz1 = hz1 * 2 * Math.PI;
         hz2 = hz2 * 2 * Math.PI;

           int n = (int) (StdAudio.SAMPLE_RATE * duration);
           double[] b = new double[n+1];
           for(int x = 0;x<(int)(duration*StdAudio.SAMPLE_RATE);x++){
           double c1 = duration/2*(hz1-hz2)/(2*Math.PI);
           double c2 = Math.sin(Math.PI * x/StdAudio.SAMPLE_RATE / duration/2);
           double c3 = (hz1+hz2)/2*(x/StdAudio.SAMPLE_RATE);
           b[x] = Math.sin(c1*c2+c3);
           // double c1 = 2*duration*(hz1-hz2)/Math.PI;
           // double c2 = Math.sin((Math.PI*x/StdAudio.SAMPLE_RATE/2/duration)+(Math.PI/2));
           // double c3 = (hz1-hz2)/2*x/StdAudio.SAMPLE_RATE;
           // double c4 = (hz1+hz2)/2*x/StdAudio.SAMPLE_RATE;
           // b[x] = Math.sin(c1*c2+c3+c4);
         }

         for(int x = 0; x<(int)(duration*StdAudio.SAMPLE_RATE)/5;x++){
           b[x] += 0.5*(-x/duration*5/StdAudio.SAMPLE_RATE + 1) *Math.sin(2 * Math.PI * 440.0 * Math.pow(2, (p2+24) / 12.0) * x / StdAudio.SAMPLE_RATE);
         }

         for(int x = 0; x<(int)(duration*StdAudio.SAMPLE_RATE)/4;x++){
           b[x] += 0.5*(-x/duration*4/StdAudio.SAMPLE_RATE + 1) *Math.sin(2 * Math.PI * 440.0 * Math.pow(2, (p2+12) / 12.0) * x / StdAudio.SAMPLE_RATE);
         }

         for(int x = 0; x<(int)(duration*StdAudio.SAMPLE_RATE)/4;x++){
           b[x] += 0.3*(-x/duration*4/StdAudio.SAMPLE_RATE + 1) *Math.sin(2 * Math.PI * 440.0 * Math.pow(2, (p2+6) / 12.0) * x / StdAudio.SAMPLE_RATE);
         }

         click(b);
         return b;
       }//pitch shift


//click [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
       public static void click(double[] b){
         boolean hitZero = false;
         int index = b.length-2;
         while(hitZero == false){
           if(Math.abs(b[index]) <= 0.01){
             hitZero = true;
           }
           else{
             index-=1;
           }
         }
         for(int i = index; i<b.length-1;i++){
           b[i] = 0;
         }
       }//click

// trim [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
  public static double[] trim(double[] array){
    int minIndex = 0;
    boolean hitMin = false;
    while(hitMin == false){
      if(array[minIndex] != 0.0){
        hitMin = true;
      }
      else{
        minIndex++;
      }
    }

    int maxIndex = array.length-1;
    boolean hitMax = false;
    while(hitMax == false){
      if(array[maxIndex] != 0.0){
        hitMax = true;
      }
      else{
        maxIndex--;
      }
    }

    double[] b = new double[maxIndex - minIndex + 1];
    for(int i = 0; i<b.length;i++){
      b[i] = array[i+minIndex];
    }
    return b;
  }

//blep [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
public static double[] blep(double pitch, double duration) {
      double hz = 440.0 * Math.pow(2, pitch / 12.0);

        int n = (int) (StdAudio.SAMPLE_RATE * duration);
        double[] a = new double[n+1];
        for (int i = 0; i <= n; i++) {
            a[i] = Math.sin(2 * Math.PI * i * hz / StdAudio.SAMPLE_RATE * Math.cos(8 * Math.PI * i *hz/StdAudio.SAMPLE_RATE/100 ));
        }
        return a;
    }//blep noise


//square [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
    public static double[] square(int pitch, double duration) {
      double hz = 440.0 * Math.pow(2, pitch / 12.0);

      int n = (int) (StdAudio.SAMPLE_RATE * duration);
      double[] a = new double[n+1];
      for (int i = 0; i <= n; i++) {
          a[i] = Math.sin(2 * Math.PI * i * hz / StdAudio.SAMPLE_RATE);
          if(Math.sin(2 * Math.PI * i * hz / StdAudio.SAMPLE_RATE) > 0){
            a[i] = 0.4+Math.sin(16 * Math.PI * i * hz / StdAudio.SAMPLE_RATE)*0.1;
          }

          else{
            a[i] = -0.4-Math.sin(16 * Math.PI * i * hz / StdAudio.SAMPLE_RATE)*0.1;
          }
      }

      return a;
    }//square

//bit crush [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
    public static double[] bitCrush(double[] a, int crush){
      double avg = 0;
      for (int i = 0; i < a.length/crush-crush; i++) {
        avg = 0;
        for (int z = 0; z<crush;z++){
          avg+= a[i*crush+z];
        }
        avg = avg/crush;
        for(int z = 0; z<crush;z++){
          a[i*crush+z] = avg;
        }
      }
      return a;
    }//bit crush

//delay [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
    public static double[] delay(double[] array, double volume, double time){
      double[] b = new double[array.length];
      for(int i = 0; i<array.length;i++){
        b[i] = array[i];
        if(i>(int)(time*StdAudio.SAMPLE_RATE)){
          b[i] += volume*array[i-((int) (time*StdAudio.SAMPLE_RATE))];
        }
      }
      return b;
    }//delay

//harmonic [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
    // create a note with harmonics of the given pitch and duration
    // (where 0 = concert A)
    public static double[] harmonic(int pitch, double duration) {
        double hz = 440.0 * Math.pow(2, pitch / 12.0);
        double[] a  = tone(hz, duration);
        double[] hi = tone(2*hz, duration);
        double[] lo = tone(hz/2, duration);
        double[] h  = sum(hi, lo, 0.5, 0.5);
        return sum(h, lo, 0.5, 0.5);
    }//harmonic

//major [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
    public static double[] major(int pitch, double duration, String waveType, int line){
      if(waveType == "sine"){
      double[] root  = tone(pitch, duration);
      double[] majorThird = tone(pitch+4, duration);
      double[] perfectFifth = tone(pitch+7, duration);
      if(pitch+7-line < 9){
       perfectFifth = tone(pitch+7-12, duration);
      }
      double[] h  = sum(root, majorThird, 0.6, 0.4);
      return sum(h, perfectFifth, 0.6, 0.4);
      }

      else if(waveType == "blep"){
      double[] root  = blep(pitch, duration);
      double[] majorThird = blep(pitch+4, duration);
      double[] perfectFifth = blep(pitch+7, duration);
      if(pitch+7-line < 9){
       perfectFifth = blep(pitch+7-12, duration);
      }
      double[] h  = sum(root, majorThird, 0.6, 0.4);
      return sum(h, perfectFifth, 0.6, 0.4);
      }

      else if(waveType == "square"){
        double[] root  = square(pitch, duration);
        double[] majorThird = square(pitch+4, duration);
        double[] perfectFifth = square(pitch+7, duration);
        double[] h  = sum(root, majorThird, 0.5, 0.5);
        return sum(h, perfectFifth, 0.5, 0.5);
      }

      else{
      double[] root  = tone(pitch, duration);
      double[] majorThird = tone(pitch+4, duration);
      double[] perfectFifth = tone(pitch+7, duration);
      double[] h  = sum(root, majorThird, 0.5, 0.5);
      return sum(h, perfectFifth, 0.5, 0.5);
      }
    }//major



//random seq [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
public static double[] randomSeq(int num){
  double[] a = new double[num];
  for (int i = 0; i < num; i++) {
    a[num] = Math.random();
  }

  return a;
}//random seq

//fillZero [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
public static double[] fillZero(double[] array, int length){
  double[] b = new double[length*StdAudio.SAMPLE_RATE+1];
  for(int i = 0; i<array.length; i++){
    b[i] = array[i];
  }

  for(int i = array.length; i<=length*StdAudio.SAMPLE_RATE; i++){
    b[i] = 0;
  }
  return b;
}//fill zero


//fill zero front [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
public static double[] fillZeroFront(double[] array, int length){

  double[] b = new double[length*StdAudio.SAMPLE_RATE+1];

  for(int i = 0; i<(length*StdAudio.SAMPLE_RATE-array.length+1); i++){
    b[i] = 0;
  }

  for(int i = length*StdAudio.SAMPLE_RATE-array.length+1; i<=length*StdAudio.SAMPLE_RATE; i++){
    b[i] = array[i-length*StdAudio.SAMPLE_RATE+array.length-1];
  }
  return b;
}//fill zero front

//nothing [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
public static double[] nothing(double length){
  double[] b = new double[(int)(length*StdAudio.SAMPLE_RATE+1)];
  for(int i = 0; i < b.length; i++){
    b[i] = 0;
  }

  return b;
}//nothing

//clean [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
public static void clean(double[] array){

  for(int i = 0; i < array.length-1; i++){
    if(Math.abs(array[i+1]-array[i]) > 0.4 && array[i] <=0.01){
      array[i+1] = 0;
      array[i] = 0;
    }
  }
}//clean


//clip [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
public static double[] clip(double max, double min, double[] theArray) {
    	int length = theArray.length;
    	double[] newArray = new double[length];
    	for (int i = 0; i < length; i++) {
    		newArray[i] = theArray[i];
    	}
    	for (int i = 0; i < length; i++) {
    		if (newArray[i] > max) {
    			newArray[i] = max;
    		} else if (newArray[i] < min) {
    			newArray[i] = min;
    		}
    	}
    	return newArray;
    }//clip

//changeVolume [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
public static double[] changeVolume(double[] array, double volume){
  double[] b = new double[array.length];
  for(int i = 0; i<b.length;i++){
    b[i] = array[i]*volume;
  }
  return b;
}//changeVolume

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

public static double[] whiteNoise(double duration){
  double[] b = new double[(int)(duration*StdAudio.SAMPLE_RATE)];
  for(int i = 0; i<b.length;i++){
    b[i] = ((double) randRange(-1,1)/2);
  }
  return b;
}

//generate triple melody [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
public static double[] generateTripleChords(double duration){
double[] triples = {};
int[] cMajor = {3,5,7,8};
int i = randRange(0,3);
triples = MusicTools.concatArray(triples, ADSR(tone(cMajor[i], duration),0.05,duration-0.1-0.05,0,0.6,0.1));
return triples;
}//genereateTripleMel

//Generate Triple [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
public static double[] generateTriple(double duration, int i){
double[] triples = {};
int[] notes = {7,5,3};
int pitch = 0;
numNotes += 9;
double[][] sound1 = {pitchShift(7, 7-12,0.25), pitchShift(7, 7-24,0.25), pitchShift(7-12, 7-24,0.25)};
//double[][] sound1 = {ADSR(sawtooth(7,duration), duration/20,duration/20,0,0.6,duration/20*18),ADSR(sawtooth(5,duration), duration/20,duration/20,0,0.6,duration/20*18),ADSR(sawtooth(3,duration), duration/20,duration/20,0,0.6,duration/20*18)};
double[][] sound2 = {ADSR(square(7-12,duration), duration/20,duration/20,0,0.6,duration/20*18),ADSR(square(5-12,duration), duration/20,duration/20,0,0.6,duration/20*18),ADSR(square(3-12,duration), duration/20,duration/20,0,0.6,duration/20*18)};
double[][] sound3 = {pitchShift(7-12, 7-24,0.25), pitchShift(5-12, 5-24,0.25), pitchShift(3-12, 3-24,0.25)};
//double[][] sound4 = {ADSR(sawtooth(7,duration), duration/20,duration/20,0,0.6,duration/20*18),ADSR(sawtooth(5,duration), duration/20,duration/20,0,0.6,duration/20*18),ADSR(sawtooth(3,duration), duration/20,duration/20,0,0.6,duration/20*18)};
double[][] sound4 = {pitchShift(7+16, 7+20,0.25), pitchShift(7+12, 7+16,0.25), pitchShift(7+20, 7+22,0.25)};

i-=1;
if(i==0){
int pitch1 = randRange(0,2);
triples = MusicTools.concatArray(triples, sound1[pitch1]);
//System.out.println(notes[pitch] + " " + duration);
pitchPub[counter] = pitch1;
durationPub[counter] = duration;
durationPlaceHolder += 2.0 * duration;
dots[counter][0] = (double)pitch1;
dots[counter][1] = durationPlaceHolder;
counter+=1;
int pitch2 = randRange(0,2);
triples = MusicTools.concatArray(triples, sound1[pitch2]);
//System.out.println(notes[pitch] + " " + duration);
pitchPub[counter] = pitch2;
durationPub[counter] = duration;
durationPlaceHolder += 2.0 * duration;
dots[counter][0] = (double)pitch2;
dots[counter][1] = durationPlaceHolder;
counter+=1;

int pitch3 = randRange(0,2);
triples = MusicTools.concatArray(triples, sound1[pitch3]);
//System.out.println(notes[pitch] + " " + duration);
pitchPub[counter] = pitch3;
durationPub[counter] = duration;
durationPlaceHolder += 2.0 * duration;
dots[counter][0] = (double)pitch3;
dots[counter][1] = durationPlaceHolder;
counter+=1;

pitchPub[counter] = pitch1;
durationPub[counter] = duration;
durationPlaceHolder += 2.0 * duration;
dots[counter][0] = (double)pitch1;
dots[counter][1] = durationPlaceHolder;
counter+=1;

pitchPub[counter] = pitch2;
durationPub[counter] = duration;
durationPlaceHolder += 2.0 * duration;
dots[counter][0] = (double)pitch2;
dots[counter][1] = durationPlaceHolder;
counter+=1;

pitchPub[counter] = pitch3;
durationPub[counter] = duration;
durationPlaceHolder += 2.0 * duration;
dots[counter][0] = (double)pitch3;
dots[counter][1] = durationPlaceHolder;
counter+=1;

pitchPub[counter] = pitch1;
durationPub[counter] = duration;
durationPlaceHolder += 2.0 * duration;
dots[counter][0] = (double)pitch1;
dots[counter][1] = durationPlaceHolder;
counter+=1;

pitchPub[counter] = pitch2;
durationPub[counter] = duration;
durationPlaceHolder += 2.0 * duration;
dots[counter][0] = (double)pitch2;
dots[counter][1] = durationPlaceHolder;
counter+=1;

pitchPub[counter] = pitch3;
durationPub[counter] = duration;
durationPlaceHolder += 2.0 * duration;
dots[counter][0] = (double)pitch3;
dots[counter][1] = durationPlaceHolder;
counter+=1;

}

else if(i==1){
  int pitch1 = randRange(0,2);
  triples = MusicTools.concatArray(triples, sound2[pitch1]);
  //System.out.println(notes[pitch] + " " + duration);
  pitchPub[counter] = pitch1;
  durationPub[counter] = duration;
  durationPlaceHolder += 2.0 * duration;
  dots[counter][0] = (double)pitch1;
  dots[counter][1] = durationPlaceHolder;
  counter+=1;

  int pitch2 = randRange(0,2);
  triples = MusicTools.concatArray(triples, sound2[pitch2]);
  //System.out.println(notes[pitch] + " " + duration);
  pitchPub[counter] = pitch2;
  durationPub[counter] = duration;
  durationPlaceHolder += 2.0 * duration;
  dots[counter][0] = (double)pitch2;
  dots[counter][1] = durationPlaceHolder;
  counter+=1;

  int pitch3 = randRange(0,2);
  triples = MusicTools.concatArray(triples, sound2[pitch3]);
  //System.out.println(notes[pitch] + " " + duration);
  pitchPub[counter] = pitch3;
  durationPub[counter] = duration;
  durationPlaceHolder += 2.0 * duration;
  dots[counter][0] = (double)pitch3;
  dots[counter][1] = durationPlaceHolder;
  counter+=1;

  pitchPub[counter] = pitch1;
  durationPub[counter] = duration;
  durationPlaceHolder += 2.0 * duration;
  dots[counter][0] = (double)pitch1;
  dots[counter][1] = durationPlaceHolder;
  counter+=1;

  pitchPub[counter] = pitch2;
  durationPub[counter] = duration;
  durationPlaceHolder += 2.0 * duration;
  dots[counter][0] = (double)pitch2;
  dots[counter][1] = durationPlaceHolder;
  counter+=1;

  pitchPub[counter] = pitch3;
  durationPub[counter] = duration;
  durationPlaceHolder += 2.0 * duration;
  dots[counter][0] = (double)pitch3;
  dots[counter][1] = durationPlaceHolder;
  counter+=1;

  pitchPub[counter] = pitch1;
  durationPub[counter] = duration;
  durationPlaceHolder += 2.0 * duration;
  dots[counter][0] = (double)pitch1;
  dots[counter][1] = durationPlaceHolder;
  counter+=1;

  pitchPub[counter] = pitch2;
  durationPub[counter] = duration;
  durationPlaceHolder += 2.0 * duration;
  dots[counter][0] = (double)pitch2;
  dots[counter][1] = durationPlaceHolder;
  counter+=1;

  pitchPub[counter] = pitch3;
  durationPub[counter] = duration;
  durationPlaceHolder += 2.0 * duration;
  dots[counter][0] = (double)pitch3;
  dots[counter][1] = durationPlaceHolder;
  counter+=1;

}

else if(i==2){
triples = MusicTools.concatArray(triples, sound3[randRange(0,2)]);
triples = MusicTools.concatArray(triples, sound3[randRange(0,2)]);
triples = MusicTools.concatArray(triples, sound3[randRange(0,2)]);
}

else if(i==3){
triples = MusicTools.concatArray(triples, sound4[randRange(0,2)]);
triples = MusicTools.concatArray(triples, sound4[randRange(0,2)]);
triples = MusicTools.concatArray(triples, sound4[randRange(0,2)]);
}
return triples;
}//generate triples




//Part 1 [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
public static double[] part1(int instrument){
      double[] b = {};
      double[] triples = {};
      triples = generateTriple(0.25, instrument);
      triples = MusicTools.concatArray(triples, generateTriple(0.25, instrument));
      triples = MusicTools.concatArray(triples, generateTriple(0.25,instrument));
      triples = MusicTools.concatArray(triples, generateTriple(0.25,instrument));
      clean(triples);

      double[] chords = {};
      chords = generateTripleChords(0.75);
      chords = MusicTools.concatArray(chords, generateTripleChords(0.75));
      chords = MusicTools.concatArray(chords, generateTripleChords(0.75));
      chords = MusicTools.concatArray(chords, generateTripleChords(0.75));
      chords = matchLength(triples,chords,1);

      triples = sum(triples, chords, 0.8,0.2);
      b = MusicTools.concatArray(b,changeVolume(triples,0.3));
      double[] kicks = {};
      int count = 0;
      while(count<=12){
          int i = randRange(1,2);
          if(i == 2){
            double[] kick = pitchShift(7-12*4+64, 7-12*4,0.25);
            kick = sum(kick,fade(pitchShift(7-12*2+24, 7-12*2,0.25),0.18, "OUT"),0.8,0.2);
            kicks = (MusicTools.concatArray(kicks, kick));
          }
          else{
            kicks = MusicTools.concatArray(kicks, nothing(0.25));

          }


        count++;
      }
      double[] part2 = {};
      part2 = sum(triples, kicks,0.3,0.7);
      clean(part2);
      b = MusicTools.concatArray(b,part2);
      b = MusicTools.concatArray(b,part2);
      return b;
}//part 1


//Part 2 [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
public static double[] part2(){
      double[] b = {};
      double[] triples = {};
      triples = generateTriple(0.25, 2);
      triples = MusicTools.concatArray(triples, generateTriple(0.25, 2));
      triples = MusicTools.concatArray(triples, generateTriple(0.25,2));
      triples = MusicTools.concatArray(triples, generateTriple(0.25,2));
      clean(triples);

      double[] chords = {};
      chords = generateTripleChords(0.75);
      chords = MusicTools.concatArray(chords, generateTripleChords(0.75));
      chords = MusicTools.concatArray(chords, generateTripleChords(0.75));
      chords = MusicTools.concatArray(chords, generateTripleChords(0.75));
      chords = matchLength(triples,chords,1);

      triples = sum(triples, chords, 0.8,0.2);
      b = MusicTools.concatArray(b,changeVolume(triples,0.3));


      double[] drums = {};
      int count = 0;

      double[] kick = pitchShift(7-12*4+64, 7-12*4,0.25);
      kick = sum(kick,fade(pitchShift(7-12*2+24, 7-12*2,0.25),0.18, "OUT"),0.8,0.2);

      double[] sineW = ADSR(whiteNoise(0.25),0.01,0.01,0.05,0.3,0.18);
      sineW = ADSR(sineW,0.05,0.05,0.05,0.5,0.1);
      double[] noise = ADSR(pitchShift(36, 7-24,0.25), 0.01,0.01,0.05,0.5,0.18);
      noise = sum(sineW,noise,0.3,0.7);

      while(count<3){
          double[][] patterns = {{1,0,2,0},{0,1,0,2},{1,2,1,0}};
          int i = randRange(0,patterns.length-1);
          for(int n = 0;n<4;n++){
            if(patterns[i][n] == 1){
              drums = (MusicTools.concatArray(drums, kick));
            }

            else if(patterns[i][n] == 2){
              drums = MusicTools.concatArray(drums,noise);
            }
            else{
              drums = MusicTools.concatArray(drums, nothing(0.25));
            }
          }

        count++;
      }

      double[] end = {};
      drums = matchLength(triples,drums,1);
      end = sum(triples, drums,0.3,0.7);
      b = MusicTools.concatArray(b,end);
      b = MusicTools.concatArray(b,end);
      clean(end);

      return b;
}//part 2


//playPiano [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
public static double[] playPiano(int pitch, double duration){
  double[] newN = ADSR(major(pitch,duration,"sine",pitch), duration/20,duration/20,0,0.6,duration/20*18);
  if(duration>0.75){
    newN = delay(newN,0.25,duration/20*5);
    newN = delay(newN,0.1,duration/20*10);
  }
  clean(newN);
  return newN;
  //StdAudio.play(newN);
}//playPiano


public static void splitIntoParts(double[] array, double duration){
  //double[] b = new double[(int)(duration*StdAudio.SAMPLE_RATE)];


  // int chunkLength = ((int)(duration*StdAudio.SAMPLE_RATE));
  // int index = 0;
  // int chunkNum = (int) (array.length / StdAudio.SAMPLE_RATE / duration);
  // for(int i = 0;i<chunkNum;i++){
  //   double[] b = MusicTools.cutArray(array,(i+chunkNum*chunkLength),(i+(chunkNum+1)*(chunkLength)));
  //   StdAudio.play(b);
  //   chunkNum+=1;
  // }
}

//Main [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
  // read in notes from standard input and play them on standard audio
  public static void main(String[] args) {
    double[] a = {};
    double[] b = {};

    StdDraw.setScale(-12.0, +12.0);
       StdDraw.enableDoubleBuffering();
       // double [][] dots = new double[150][2];
       // double durationPlaceHolder = 8;
       int [] pitchArray = new int[150];
       double [] durationArray = new double[150];
       double [] yPosition = new double[150];
    // read in pitch-duration pairs from standard input
    double[] piano = {};
      while (!StdIn.isEmpty()) {
          int pitch = StdIn.readInt();
          double duration = StdIn.readDouble();
          numNotes+=1;
          double doublePitch = (double) pitch;
          // pitchArray[counter] = pitch;
          // durationArray[counter] = duration;
          pitchPub[counter] = pitch;
          durationPub[counter] = duration;
          durationPlaceHolder += 2.0 * duration;
          dots[counter][0] = doublePitch;
          dots[counter][1] = durationPlaceHolder;
          counter++;
      }

      for(int z = 0;z<numNotes;z++){
          a = MusicTools.concatArray(a, playPiano(pitchPub[z],durationPub[z]));

      }


      a = MusicTools.concatArray(a, part1(2));
      a = MusicTools.concatArray(a, part1(1));
      a = MusicTools.concatArray(a, part2());
      a = MusicTools.concatArray(a, part1(3));

      for(int z = 0;z<numNotes;z++){
          a = MusicTools.concatArray(a, playPiano(pitchPub[z],durationPub[z]));

      }
      clean(a);
      MyRunnable myRunnable = new MyRunnable(10);
        Thread t = new Thread(myRunnable);
        t.start();
      StdAudio.save("audio_file.wav", a);
      StdAudio.play(a);



  }
}

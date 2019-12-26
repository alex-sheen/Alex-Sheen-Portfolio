import  java.util.concurrent.TimeUnit;
import java.awt.Font;

public class MyRunnable implements Runnable {

  private int var;

  public MyRunnable(int var){
    this.var = var;
  }

  public void run(){
    double[] b = new double[(int)2*StdAudio.SAMPLE_RATE];

    int counter = 0;
    double number = 0;
    for(int z = 0;z<GenerateMusic.numNotes;z++){
          StdDraw.clear();
          StdDraw.setPenColor(StdDraw.BLACK);
          Font font = new Font("Arial",10,10);
          StdDraw.setFont(font);
          StdDraw.textLeft(-11.8, 8.5, "Timing Line");
          StdDraw.text(-12, 11.0, "A");
          StdDraw.text(-11, 11.0, "A#");
          StdDraw.text(-10, 11.0, "B");
          StdDraw.text(-9, 11.0, "C");
          StdDraw.text(-8, 11.0, "C#");
          StdDraw.text(-7, 11.0, "D");
          StdDraw.text(-6, 11.0, "D#");
          StdDraw.text(-5, 11.0, "E");
          StdDraw.text(-4, 11.0, "F");
          StdDraw.text(-3, 11.0, "F#");
          StdDraw.text(-2, 11.0, "G");
          StdDraw.text(-1, 11.0, "G#");
          StdDraw.text(0, 11.0, "A");
          StdDraw.text(1, 11.0, "A#");
          StdDraw.text(2, 11.0, "B");
          StdDraw.text(3, 11.0, "C");
          StdDraw.text(4, 11.0, "C#");
          StdDraw.text(5, 11.0, "D");
          StdDraw.text(6, 11.0, "D#");
          StdDraw.text(7, 11.0, "E");
          StdDraw.text(8, 11.0, "F");
          StdDraw.text(9, 11.0, "F#");
          StdDraw.text(10, 11.0, "G");
          StdDraw.text(11, 11.0, "G#");
          StdDraw.text(12, 11.0, "A");

        StdDraw.line(-12,8,12,8);

        for (int i = 0; i < GenerateMusic.numNotes; i++) {
            GenerateMusic.dots[i][1] -= (2.0 * GenerateMusic.durationPub[counter]);
            StdDraw.filledCircle(GenerateMusic.dots[i][0], GenerateMusic.dots[i][1], 0.5);
        }
        StdDraw.setPenColor(StdDraw.WHITE);

        number -=(2*GenerateMusic.durationPub[counter]);
        StdDraw.filledRectangle(0.0, number, 12.0, 3.0);
        StdDraw.show();

        try
        {
            Thread.sleep((long)(1000*GenerateMusic.durationPub[counter]));
        }
        catch(InterruptedException ex)
        {
            Thread.currentThread().interrupt();
        }
        //playPiano(pitchArray[counter],durationArray[counter]);
        counter++;
    }

  }

}

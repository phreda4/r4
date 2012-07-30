import java.awt.*;

public class Repel2 extends BufferedApplet
{
    RepelThread2 rt = null;

    String[] spinButtonLabels = {"SPIN","STOP"};
    Button spinButton;

    String[] sliderLabels =
       {"TREND1","TREND2","TREND3","ENERGY","GRAVITY"};
    Slider[] slider = new Slider[sliderLabels.length];

    public void stop() {
       super.stop();
       if (rt != null)
          rt.stop();
    }

    int n=8, N[] = {4,6,8,12,20,50,70,100,140,200,280,400,560,800,1120,1600};
    double theta = 0, cos = 0, sin = 0;
    int mx = 0, px = -1, py = 0, chosen = -1;
    boolean mouseIsDown = false;

    public boolean mouseDown(Event e, int x, int y) {
       mouseIsDown = true;
       if (spinButton.down(x,y))
	  return true;
       for (int i = 0 ; i < slider.length ; i++)
          if (slider[i].down(x,y))
	     return true;
       if (x >= 50 && x < w-20)
          mx = x;
       return true;
    }
    public boolean mouseMove(Event e, int x, int y) {
       mouseIsDown = false;
       x -= w/2;
       y -= h/2;
       if (x*x + y*y < w*w/16) {
	  px = x + w/2;
	  py = y + h/2;
       }
       else
	  px = -100;
       return true;
    }
    public boolean mouseDrag(Event e, int x, int y) {
       mouseIsDown = true;
       if (spinButton.drag(x,y))
	  return true;
       for (int i = 0 ; i < slider.length ; i++)
	  if (slider[i].drag(x,y)) {
	     rt.setVar(i, slider[i].getValue());
	     return true;
          }
       if (x >= 100) {
	  if (chosen >= 0) {
	     px = x;
	     py = y;
          }
	  else {
             rotate(-.01 * (x - mx));
             mx = x;
          }
       }
       return true;
    }
    public boolean mouseUp(Event e, int x, int y) {
       mouseIsDown = false;
       px = -100;
       if (spinButton.up(x,y))
          return true;
       for (int i = 0 ; i < slider.length ; i++)
	  if (slider[i].up(x,y))
	     return true;

       if (x < 50) {
          int i = (y - 10) / 14;
	  if (i >= 0 && i < N.length) {
	     n = i;
	     P = initP();
	     rt.set(P, nColors);
          }
	  return true;
       }
       if (x >= w-20) {
	  int i = (y - 10) / 14 + 1;
	  if (i >= 1 && i <= 9)
	     rt.set(P, nColors = i);
       }
       return true;
    }

    void rotate(double t) {
       theta += t;
       cos = w/4 * Math.cos(theta);
       sin = w/4 * Math.sin(theta);
    }

    int w = 0, h;
    public void render(Graphics g) {
       int i, j, k;
       if (w == 0) {
	  w = bounds().width;
	  h = bounds().height;
	  rotate(0);

          spinButton = new Button(3, h-20, 34, 15);
	  spinButton.labels = spinButtonLabels;

	  for (i = 0 ; i < slider.length ; i++) {
             slider[i] = new Slider(w/2, h+(i-slider.length)*20, w/2-5, 15);
	     slider[i].label = sliderLabels[i];
          }
	  slider[RepelThread2.TREND1].setValue(.9);
	  slider[RepelThread2.TREND2].setValue(.1);
	  slider[RepelThread2.TREND3].setValue(.9);
	  slider[RepelThread2.ENERGY].setValue(1);

	  rt = new RepelThread2(slider.length);
	  rt.set(P, nColors);
	  for (int s = 0 ; s < slider.length ; s++)
	     rt.setVar(s,slider[s].getValue());
	  rt.start();
       }
       g.setColor(Color.white);
       g.fillRect(0,0,w,h);

       int rad = 4;//(int)(4 + 4 * slider[5].getValue());

       g.setColor(sphereColor);
       g.fillOval(w/4+rad,h/4+rad,w/2-2*rad,h/2-2*rad);

       for (i = 0 ; i < N[n] ; i++)
	  if (sin * P[i][0] - cos * P[i][2] <= -w/20) {
	     int x = w/2 + (int)(cos * P[i][0] + sin * P[i][2]);
	     int y = h/2 + (int)(h/4 * P[i][1]);
             g.setColor(backColor[colorId(i)]);
	     g.fillOval(x-rad,y-rad,2*rad,2*rad);
          }

       g.setColor(edgeColor);
       g.drawOval(w/4+rad,h/4+rad,w/2-2*rad,h/2-2*rad);

       if (mouseIsDown) {
          if (chosen >= 0) {
	     double X = (double)(px-w/2) / (w/4);
	     double Y = (double)(py-h/2) / (h/4);
	     double RR = X*X + Y*Y;
	     if (RR < 1) {
	        double Z = Math.sqrt(1 - RR);
	        P[chosen][0] = (cos * X + sin * Z) / (w/4);
	        P[chosen][1] = Y;
	        P[chosen][2] = (sin * X - cos * Z) / (w/4);
	     }
          }
       }
       else
          chosen = -1;

       for (i = 0 ; i < N[n] ; i++)
	  if (sin * P[i][0] - cos * P[i][2] > -w/20) {
	     int x = w/2 + (int)(cos * P[i][0] + sin * P[i][2]);
	     int y = h/2 + (int)(h/4 * P[i][1]);
	     if (!mouseIsDown && chosen<0 && (px-x)*(px-x)+(py-y)*(py-y) <= 16)
		chosen = i;
             g.setColor(i == chosen ? Color.red : color[colorId(i)]);
	     g.fillOval(x-rad,y-rad,2*rad,2*rad);
          }

       if (! mouseIsDown)
          rt.setChosen(chosen);
       for (i = 0 ; i < N.length ; i++) {
	  g.setColor(n==i ? Color.red : lightBrown);
	  g.drawString("" + N[i], 5, 20 + 14*i);
       }
       for (i = 0 ; i < 9 ; i++) {
	  g.setColor(nColors==i+1 ? Color.black : lightGray);
	  g.drawString("" + (i+1), w-10, 20 + 14*i);
       }

       spinButton.render(g);

       for (i = 0 ; i < slider.length ; i++)
          slider[i].render(g);

       if (spinButton.getValue() == 1)
          rotate(.025);

       g.setColor(new Color(160,160,255));
       g.drawString("" + version, w-20, h/2);
    }
    int version = 10;

    Color buttonColor = new Color(255,230,230);
    Color lightBrown = new Color(200,150,150);
    Color lightGray  = new Color(200,200,200);
    int[] srgb = {250,240,240};
    Color sphereColor = new Color(srgb[0],srgb[1],srgb[2]);
    Color edgeColor = new Color(srgb[0]/2,srgb[1]/2,srgb[2]/2);
    int[][] rgb = {
       {255,0,0},
       {240,150,0},
       {140,200,0},
       {0,140,0},
       {0,160,255},
       {0,0,255},
       {200,0,120},
       {180,120,50},
       {0,0,0},
    };
    int nColors = 8;
    int colorId(int i) { return (i % nColors) * color.length / nColors; }
    Color[] color = newColors(), backColor;
    Color[] newColors() {
       color = new Color[rgb.length];
       backColor = new Color[rgb.length];
       for (int i = 0 ; i < color.length ; i++) {
	  color[i] = new Color(rgb[i][0],rgb[i][1],rgb[i][2]);
	  backColor[i] = new Color(
	     (rgb[i][0] + 5*srgb[0])/6,
	     (rgb[i][1] + 5*srgb[1])/6,
	     (rgb[i][2] + 5*srgb[2])/6
	  );
       }
       return color;
    }

    double[][] P = initP();

    double[][] initP() {
       java.util.Random R = new java.util.Random(0);
       P = new double[N[n]][3];
       for (int i=0; i<N[n] ; i++)
	  random(R, P[i]);
       return P;
    }
    void random(java.util.Random R, double[] p) {
       double u, v, w;
       do {
          u = 2*R.nextDouble()-1;
          v = 2*R.nextDouble()-1;
          w = 2*R.nextDouble()-1;
       } while (u*u + v*v + w*w > 1);
       p[0] = u;
       p[1] = v;
       p[2] = w;
       RepelThread2.normalize(p);
    }
}

class RepelThread2 extends Thread
{
   final static int TREND1 = 0;
   final static int TREND2 = 1;
   final static int TREND3 = 2;
   final static int ENERGY    = 3;
   final static int GRAVITY   = 4;

   double[][] P = null, currentP = null;
   int chosen = -1, M = 0;
   double[] var;

   RepelThread2(int nVars) {
      var = new double[nVars];
   }

   public void set(double[][] newP, int n) {
      currentP = newP;
      this.M = n;
   }

   public void setVar(int v, double value) { var[v] = value; }

   public void setChosen(int i) {
      chosen = i;
   }
   double[] v = new double[3];
   double[] p = new double[3];
   int off = 1;
   public void run() {
      int i, j, k;
      try {
	 while (true) {
	    P = currentP;
	    int N = P.length;
            double t = .02 / Math.sqrt(N);
            double RR = 8./N/N, A, B, T;
            for (int a = 0 ; a < N ; a++)
	       if (a != chosen) {
		  for (j = 0 ; j < 3 ; j++)
		      p[j] = P[a][j];
                  for (int b = 0 ; b < N ; b++) {
                     if (b != a) {
                        for (j = 0 ; j < 3 ; j++)
                           v[j] = P[b][j] - P[a][j];
                        double rr = v[0]*v[0] + v[1]*v[1] + v[2]*v[2];
                        T = t * var[ENERGY] / rr;

			int C = ( (M*1000 + b-a) % M ) & 7;
                        if (C==1 || C==2 || C==4)        // ONE BIT SET
			   T *= 1 + 2 * var[TREND1];
                        else if (C==3 || C==5 || C==6)   // TWO BITS SET
			   T *= 1 + 2 * var[TREND2];
                        else if (C==7)                   // THREE BITS SET
			   T *= 1 + 2 * var[TREND3];

                        for (j = 0 ; j < 3 ; j++)
                           p[j] -= T * v[j];

                        if (var[GRAVITY] != 0)
                           p[1] += var[GRAVITY] / N;

                        normalize(p);
                     }
                  }
		  for (j = 0 ; j < 3 ; j++)
		     P[a][j] = p[j];
               }
	    sleep(30);
         }
      }
      catch(InterruptedException e){};
   }
   double near(double t, double r) {
      t = Math.abs(t);
      if (t > r)
	 return 0;
      return 1 - t / r;
   }
   static void normalize(double v[]) {
      double s = Math.sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
      v[0] = v[0] / s;
      v[1] = v[1] / s;
      v[2] = v[2] / s;
   }
}


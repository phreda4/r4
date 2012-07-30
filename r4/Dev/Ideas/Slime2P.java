//<!-- 2-player version of Slime Volleyball -->
// Original code: Quin Pendragon, 1999.
//  I know that this isn't exactly an ideal example of either game coding or
//  good use of java. It wasn't meant to be. :P
//  No responsibility is taken for any damage to software, hardware,
//  keyboards, or individuals' coding habits as a result of using this code.
// Mods:
// 0) fractoid: Lost the source code, and decompiled the applet on my page
//    to get it back. This is why some of the methods are in a funny
//    order, and some variables are interestingly named :P
// 1) fractoid: added SuperSlime mod.// 2) wedgey: fixed some variable names in MoveBall() and DrawSlimers()//      in November 2001 though it took over 4 years for me to put them//      on the net!
// ...

import java.applet.Applet;
import java.awt.*;

public class Slime2P extends Applet
    implements Runnable
{
    private int nWidth;
    private int nHeight;
    private final int topScore = 10;
    private int nScore;
    private int nPointsScored;
    private int p1X;
    private int p2X;
    private int p1Y;
    private int p2Y;
    private int p1Col;
    private int p2Col;
    private Color slimeColours[];
    private String slimeColText[] = {
        "Big Red Slime ", "Magic Green Slime ", "Golden Boy ", "The Great White Slime ", "The Grass Tree\251 "
    };
    private int p1OldX;
    private int p2OldX;
    private int p1OldY;
    private int p2OldY;
    private int p1XV;
    private int p2XV;
    private int p1YV;
    private int p2YV;
    private int ballX;
    private int ballY;
    private int ballVX;
    private int ballVY;
    private int ballOldX;
    private int ballOldY;
    private Graphics screen;
    private String promptMsg;
    private int replayData[][];
    private int replayPos;
    private int replayStart;
    private boolean mousePressed;
    private boolean fCanChangeCol;
    private boolean fInPlay;
    private int p1Blink;
    private int p2Blink;
    private boolean fP1Touched;
    private boolean fP2Touched;
    private Thread gameThread;
    private boolean fEndGame;
    private long startTime;
    private long gameTime;
    private int scoringRun;
    private int frenzyCol = 0;
    private final int scoringRunForSuper = 3;
    private int p1Diam = 100, p2Diam = 100, ballRad = 25;	
    public boolean handleEvent(Event event)
    {
label0:
        switch(event.id)
        {
        default:
            break;

		case Event.MOUSE_MOVE:
            showStatus("Slime Volleyball 2-Player, by Quin Pendragon: tartarus.uwa.edu.au/~fractoid");
            break;

		case Event.MOUSE_DOWN:
            mousePressed = true;
            if(!fInPlay)
            {
                fEndGame = false;
                fInPlay = true;
                nScore = 5;
                nPointsScored = 0;
                p1X = 200;
                p1Y = 0;
                p2X = 800;
                p2Y = 0;
                p1XV = 0;
                p1YV = 0;
                p2XV = 0;
                p2YV = 0;
                ballX = 200;
                ballY = 400;
                ballVX = 0;
                ballVY = 0;
                promptMsg = "";
                repaint();
                gameThread = new Thread(this);
                gameThread.start();
            }
            break;

        case Event.KEY_ACTION:
		case Event.KEY_PRESS:
            if(fEndGame)
                break;
            switch(event.key)
            {
            default:
                break;

			case 'A':
			case 'a':
                p1XV = (scoringRun <= -scoringRunForSuper) ? -16 : -8;
                break label0;

			case 'D':
			case 'd':
                p1XV = (scoringRun <= -scoringRunForSuper) ? 16 : 8;
                break label0;

			case 'W':
			case 'w':
                if(p1Y == 0)
                    p1YV = (scoringRun <= -scoringRunForSuper) ? 45 : 31;
                break label0;

            case Event.LEFT:
			case 'J':
			case 'j':
                p2XV = (scoringRun >= scoringRunForSuper) ? -16 : -8;
                break label0;

            case Event.RIGHT:
			case 'L':
			case 'l':
                p2XV = (scoringRun >= scoringRunForSuper) ? 16 : 8;
                break label0;

            case Event.UP:
			case 'I':
			case 'i':
                if(p2Y == 0)
                    p2YV = (scoringRun >= scoringRunForSuper) ? 45 : 31;
                break label0;

			case 'S':
			case 's':
                if(!fCanChangeCol)
                    break label0;
                do
                    p1Col = p1Col != 4 ? p1Col + 1 : 0;
                while(p1Col == p2Col);
                drawScores();
                break label0;

            case Event.DOWN:
			case 'K':
			case 'k':
                if(fCanChangeCol)
                {
                    do
                        p2Col = p2Col != 4 ? p2Col + 1 : 0;
                    while(p2Col == p1Col);
                    drawScores();
                    break label0;
                }
                // fall through

			case ' ':
                mousePressed = true;
                break;
            }
            break;

        case Event.KEY_ACTION_RELEASE:
		case Event.KEY_RELEASE:
            switch(event.key)
            {
            default:
                break label0;

			case 'A':
			case 'a':
                if(p1XV < 0)
                    p1XV = 0;
                break label0;

			case 'D':
			case 'd':
                if(p1XV > 0)
                    p1XV = 0;
                break label0;

            case Event.LEFT:
			case 'J':
			case 'j':
                if(p2XV < 0)
                    p2XV = 0;
                break label0;

            case Event.RIGHT:
			case 'L':
			case 'l':
                break;
            }
            if(p2XV > 0)
                p2XV = 0;
            break;
        }
        return false;
    }

    private void DrawSlimers()
    {
        // black out the old slime positions - p1
        int sWidth = nWidth*p1Diam/1000;
        int sHeight = nHeight*p1Diam/1000;
        int leftbound = p1OldX*nWidth/1000-sWidth/2;
        int topbound = 4*nHeight/5-sHeight-p1OldY*nHeight/1000;
		screen.setColor(Color.blue);
        screen.fillRect(leftbound, topbound, sWidth, sHeight);
        
        // player 2
        sWidth = nWidth*p2Diam/1000;
        sHeight = nHeight*p2Diam/1000;
        leftbound = p2OldX*nWidth/1000-sWidth/2;
        topbound = 4*nHeight/5-sHeight-p2OldY*nHeight/1000;
        screen.fillRect(leftbound, topbound, sWidth, sHeight);

        int ballXPix = ballOldX*nWidth/1000;
        int ballYPix = 4*nHeight/5-ballOldY*nHeight/1000;
		
		// draw p1
        sWidth = nWidth*p1Diam/1000;
        sHeight = nHeight*p1Diam/1000;
        leftbound = p1X*nWidth/1000-sWidth/2;
        topbound = 4*nHeight/5-sHeight-p1Y*nHeight/1000;
        screen.setColor((scoringRun <= -scoringRunForSuper) ? slimeColours[frenzyCol = ((frenzyCol + 1) % slimeColours.length)] : slimeColours[p1Col]);
        screen.fillArc(leftbound, topbound, sWidth, 2*sHeight, 0, 180);
        
        int eyeLeft = p1X+38*p1Diam/100; // coordinates, not pixels.
        int eyeTop = p1Y-60*p1Diam/100; // ditto
        leftbound = eyeLeft*nWidth/1000;
        topbound = 4*nHeight/5-sHeight-eyeTop*nHeight/1000;
        int bedx = leftbound-ballXPix; // ball-eye dx (pixels)
        int bedy = topbound-ballYPix; // ball-eye dy (pix)
        int bedist = (int)Math.sqrt(bedx*bedx+bedy*bedy); // ball-eye distance (pix)
        int eyeWidthPix = nWidth/50*p1Diam/100;
        int eyeHeightPix = nHeight/25*p1Diam/100;
        boolean flag = Math.random() < 0.01D;
        if(flag)
            p1Blink = 5;
        if(p1Blink == 0)
        {
			screen.setColor(Color.white); // eye
		    screen.fillOval(leftbound-eyeWidthPix, topbound-eyeHeightPix, eyeWidthPix, eyeHeightPix);
			screen.setColor(Color.black);
	        screen.fillOval(leftbound-4*bedx/bedist-3*eyeWidthPix/4, topbound-4*bedy/bedist-3*eyeHeightPix/4,
			    eyeWidthPix/2, eyeHeightPix/2);
		} else p1Blink--;
        
        // player 2
        sWidth = nWidth*p2Diam/1000;
        sHeight = nHeight*p2Diam/1000;
        leftbound = p2X*nWidth/1000-sWidth/2;
        topbound = 4*nHeight/5-p2Diam*nHeight/1000-p2Y*nHeight/1000;
        screen.setColor((scoringRun >= scoringRunForSuper) ? slimeColours[frenzyCol = ((frenzyCol + 1) % slimeColours.length)] : slimeColours[p2Col]);
		screen.fillArc(leftbound, topbound, sWidth, 2*sHeight, 0, 180);
        eyeLeft = p2X-18*p2Diam/100;
        eyeTop = p2Y-60*p2Diam/100;
        leftbound = eyeLeft*nWidth/1000;
        topbound = 4*nHeight/5-sHeight-eyeTop*nHeight/1000;
        bedx = leftbound-ballXPix;
        bedy = topbound-ballYPix;
        bedist = (int)Math.sqrt(bedx*bedx+bedy*bedy);
        eyeWidthPix = nWidth/50*p2Diam/100;
        eyeHeightPix = nHeight/25*p2Diam/100;
        flag = Math.random() < 0.01D;
        if(flag)
            p1Blink = 5;
        if(p1Blink == 0)
        {
			screen.setColor(Color.white); // eye
		    screen.fillOval(leftbound-eyeWidthPix, topbound-eyeHeightPix, eyeWidthPix, eyeHeightPix);
			screen.setColor(Color.black);
	        screen.fillOval(leftbound-4*bedx/bedist-3*eyeWidthPix/4, topbound-4*bedy/bedist-3*eyeHeightPix/4,
		        eyeWidthPix/2, eyeHeightPix/2);
		} else p1Blink--;
					if(nScore > 8)
        {
            int j = (p1X * nWidth) / 1000;
            int i1 = (7 * nHeight) / 10 - ((p1Y - 40) * nHeight) / 1000;
            int l1 = nWidth / 20;
            int k2 = nHeight / 20;
            int j5 = 0;
            do
            {
                screen.setColor(Color.black);
                screen.drawArc(j, i1 + j5, l1, k2, -30, -150);
            } while(++j5 < 3);
            return;
        }
        if(nScore < 2)
        {
            int i2 = nWidth / 20;
            int l2 = nHeight / 20;
            int k = (p2X * nWidth) / 1000 - i2;
            int j1 = (7 * nHeight) / 10 - ((p2Y - 40) * nHeight) / 1000;
            int k5 = 0;
            do
            {
                screen.setColor(Color.black);
                screen.drawArc(k, j1 + k5, i2, l2, -10, -150);
            } while(++k5 < 3);
        }

        // draw the new ball position
        int fudge = 5;
		int ballRadPix = (ballRad+fudge)*nHeight/1000;
		ballXPix = ballX*nWidth/1000;
        ballYPix = 4*nHeight/5-ballY*nHeight/1000;
        screen.setColor(Color.yellow);
        screen.fillOval(ballXPix-ballRadPix, ballYPix-ballRadPix, 2*ballRadPix, 2*ballRadPix);
	}

    public void paint(Graphics g)
    {
        nWidth = size().width;
        nHeight = size().height;
        g.setColor(Color.blue);
        g.fillRect(0, 0, nWidth, (4 * nHeight) / 5);
        g.setColor(Color.gray);
        g.fillRect(0, (4 * nHeight) / 5, nWidth, nHeight / 5);
        g.setColor(Color.white);
        g.fillRect(nWidth / 2 - 2, (7 * nHeight) / 10, 4, nHeight / 10 + 5);
        drawScores();
        drawPrompt();
        if(!fInPlay)
        {
            FontMetrics fontmetrics = screen.getFontMetrics();
            screen.setColor(Color.white);
            screen.drawString("Slime Volleyball!", nWidth / 2 - fontmetrics.stringWidth("Slime Volleyball!") / 2, nHeight / 2 - fontmetrics.getHeight());
            g.setColor(Color.white);
            fontmetrics = g.getFontMetrics();
            g.drawString("Written by Quin Pendragon", nWidth / 2 - fontmetrics.stringWidth("Written by Quin Pendragon") / 2, nHeight / 2 + fontmetrics.getHeight() * 2);
        }
    }

    public void destroy()
    {
        gameThread.stop();
        gameThread = null;
    }

    private void ReplayFrame(int i, int j, int k, int l, int i1, boolean flag)
    {
        if(flag)
        {
            ballX = ballOldX = 0xfd050f80;
            ballY = ballOldY = 0x186a0;
            p1OldX = p1OldY = p2OldX = p2OldY = -10000;
        } else
        {
            int j1 = i != 0 ? i - 1 : 199;
            p1OldX = replayData[j1][0];
            p1OldY = replayData[j1][1];
            p2OldX = replayData[j1][2];
            p2OldY = replayData[j1][3];
            ballOldX = replayData[j1][4];
            ballOldY = replayData[j1][5];
        }
        p1X = replayData[i][0];
        p1Y = replayData[i][1];
        p2X = replayData[i][2];
        p2Y = replayData[i][3];
        ballX = replayData[i][4];
        ballY = replayData[i][5];
        p1Col = replayData[i][6];
        p2Col = replayData[i][7];
        ballVX = 0;
        ballVY = 1;
        if((i / 10) % 2 > 0)
        {
            screen.setColor(Color.red);
            screen.drawString("Replay...", j, k);
        } else
        {
            screen.setColor(Color.blue);
            screen.fillRect(j, k - i1, l, i1 * 2);
        }
        DrawSlimers();
        try
        {
            Thread.sleep(20L);
            return;
        }
        catch(InterruptedException _ex)
        {
            return;
        }
    }

    private String MakeTime(long l)
    {
        long l1 = (l / 10L) % 100L;
        long l2 = (l / 1000L) % 60L;
        long l3 = (l / 60000L) % 60L;
        long l4 = l / 0x36ee80L;
        String s = "";
        if(l4 < 10L)
            s += "0";
        s += l4;
        s += ":";
        if(l3 < 10L)
            s += "0";
        s += l3;
        s += ":";
        if(l2 < 10L)
            s += "0";
        s += l2;
        s += ":";
        if(l1 < 10L)
            s += "0";
        s += l1;
        return s;
    }

    private void MoveSlimers()
    {
        p1X += p1XV;
        if(p1X < 50)
            p1X = 50;
        if(p1X > 445)
            p1X = 445;
        if(p1YV != 0)
        {
            p1Y += p1YV -= (scoringRun <= -scoringRunForSuper) ? 4 : 2;
            if(p1Y < 0)
            {
                p1Y = 0;
                p1YV = 0;
            }
        }
        p2X += p2XV;
        if(p2X > 950)
            p2X = 950;
        if(p2X < 555)
            p2X = 555;
        if(p2YV != 0)
        {
            p2Y += p2YV -= (scoringRun >= scoringRunForSuper) ? 4 : 2;
            if(p2Y < 0)
            {
                p2Y = 0;
                p2YV = 0;
            }
        }
    }

    public Slime2P()
    {
        p2Col = 1;
        slimeColours = (new Color[] {
            Color.red, Color.green, Color.yellow, Color.white, Color.black
        });
        replayData = new int[200][8];
    }

    private void MoveBall()
    {
        int fudge = 5; // was 5. a fudge factor.
        int maxXV = 15; // was 15
        int maxYV = 22; // was 22
        
        // move the ball
        ballY += --ballVY;
        ballX += ballVX;

        // collision detection
        if(!fEndGame) {
            int dx = 2*(ballX-p1X);
            int dy = ballY-p1Y;
            int dist = (int)Math.sqrt(dx*dx+dy*dy);
            int dvx = ballVX-p1XV;
            int dvy = ballVY-p1YV;
            if(dy > 0 && dist < p1Diam+ballRad && dist > fudge) {
                /* i have nfi what this is. i'm supposed to have done engineering
                dynamics and i can't remember any equation with x*x'+y*y' in it...
                it was a long time ago! - wedgey */
                int something = (dx*dvx+dy*dvy)/dist;
                ballX = p1X+(p1Diam+ballRad)/2*dx/dist;
                ballY = p1Y+(p1Diam+ballRad)*dy/dist;
                // cap the velocity
                if(something <= 0) {
                    ballVX += p1XV-2*dx*something/dist;
                    if(ballVX < -maxXV)
                        ballVX = -maxXV;
                    if(ballVX > maxXV)
                        ballVX = maxXV;
                    ballVY += p1YV-2*dy*something/dist;
                    if(ballVY < -maxYV)
                        ballVY = -maxYV;
                    if(ballVY > maxYV)
                        ballVY = maxYV;
                }
                fP1Touched = true;				
            }

            // that stuff all over again, but for p2.
            dx = 2*(ballX-p2X);
            dy = ballY-p2Y;
            dist = (int)Math.sqrt(dx*dx+dy*dy);
            dvx = ballVX-p2XV;
            dvy = ballVY-p2YV;
            if(dy > 0 && dist < p2Diam+ballRad && dist > fudge) {
                int something = (dx*dvx+dy*dvy)/dist;
                ballX = p2X+(p2Diam+ballRad)/2*dx/dist;
                ballY = p2Y+(p2Diam+ballRad)*dy/dist;
                if(something <= 0) {
                    ballVX += p2XV-2*dx*something/dist;
                    if(ballVX < -maxXV)
                        ballVX = -maxXV;
                    if(ballVX > maxXV)
                        ballVX = maxXV;
                    ballVY += p2YV-2*dy*something/dist;
                    if(ballVY < -maxYV)
                        ballVY = -maxYV;
                    if(ballVY > maxYV)
                        ballVY = maxYV;
                }
                fP2Touched = true;
            }
            // hits left wall
            if(ballX < 15) {
                ballX = 15;
                ballVX = -ballVX;
            }
            // hits right wall
            if(ballX > 985) {
                ballX = 985;
                ballVX = -ballVX;
            }
            // hits the post
            if(ballX > 480 && ballX < 520 && ballY < 140)
			{
                // bounces off top of net
                if(ballVY < 0 && ballY > 130) {
                    ballVY *= -1;
                    ballY = 130;
                } else if(ballX < 500) { // hits side of net
                    ballX = 480;
                    ballVX = ballVX >= 0 ? -ballVX : ballVX;
                } else {
                    ballX = 520;
                    ballVX = ballVX <= 0 ? -ballVX : ballVX;
                }
			}
        }

		// clear the ball position
		int ballXPix = ballOldX*nWidth/1000;
        int ballYPix = 4*nHeight/5-ballOldY*nHeight/1000;
		int ballRadPix = (ballRad+fudge)*nHeight/1000;
		// clear the old ball position
		screen.setColor(Color.blue);
		screen.fillRect(ballXPix-ballRadPix, ballYPix-ballRadPix, 2*ballRadPix, 2*ballRadPix);
	}

    private void DrawStatus()
    {
        Graphics g = screen;
        int i = nHeight / 20;
        g.setColor(Color.blue);
        FontMetrics fontmetrics = screen.getFontMetrics();
        int j = nWidth / 2 + ((nScore - 5) * nWidth) / 24;
        String s = "Points: " + nPointsScored + "   Elapsed: " + MakeTime(gameTime);
        int k = fontmetrics.stringWidth(s);
        g.fillRect(j - k / 2 - 5, 0, k + 10, i + 22);
        g.setColor(Color.white);
        screen.drawString(s, j - k / 2, fontmetrics.getAscent() + 20);
    }

    public void drawPrompt()
    {
        screen.setColor(Color.gray);
        screen.fillRect(0, (4 * nHeight) / 5 + 6, nWidth, nHeight / 5 - 10);
        drawPrompt(promptMsg, 0);
    }

    public void drawPrompt(String s, int i)
    {
        FontMetrics fontmetrics = screen.getFontMetrics();
        screen.setColor(Color.lightGray);
        screen.drawString(s, (nWidth - fontmetrics.stringWidth(s)) / 2, (nHeight * 4) / 5 + fontmetrics.getHeight() * (i + 1) + 10);
    }

    private void SaveReplayData()
    {
        replayData[replayPos][0] = p1X;
        replayData[replayPos][1] = p1Y;
        replayData[replayPos][2] = p2X;
        replayData[replayPos][3] = p2Y;
        replayData[replayPos][4] = ballX;
        replayData[replayPos][5] = ballY;
        replayData[replayPos][6] = p1Col;
        replayData[replayPos][7] = p2Col;
        replayPos++;
        if(replayPos >= 200)
            replayPos = 0;
        if(replayStart == replayPos)
            replayStart++;
        if(replayStart >= 200)
            replayStart = 0;
    }

    private void drawScores()
    {
        Graphics g = screen;
        int k = nHeight / 20;
        g.setColor(Color.blue);
        g.fillRect(0, 0, nWidth, k + 22);
        for(int l = 0; l < nScore; l++)
        {
            int i = ((l + 1) * nWidth) / 24;
            g.setColor(slimeColours[p1Col]);
            g.fillOval(i, 20, k, k);
            g.setColor(Color.white);
            g.drawOval(i, 20, k, k);
        }

        for(int i1 = 0; i1 < 10 - nScore; i1++)
        {
            int j = nWidth - ((i1 + 1) * nWidth) / 24 - k;
            g.setColor(slimeColours[p2Col]);
            g.fillOval(j, 20, k, k);
            g.setColor(Color.white);
            g.drawOval(j, 20, k, k);
        }

    }

    public void run()
    {
        replayPos = replayStart = 0;
        p1Col = 0;
        p2Col = 1;
        scoringRun = 0;
        fP1Touched = fP2Touched = false;
        nPointsScored = 0;
        startTime = System.currentTimeMillis();
        while(nScore != 0 && nScore != 10 && gameThread != null) 
        {
            gameTime = System.currentTimeMillis() - startTime;
            SaveReplayData();
            p1OldX = p1X;
            p1OldY = p1Y;
            p2OldX = p2X;
            p2OldY = p2Y;
            ballOldX = ballX;
            ballOldY = ballY;
            MoveSlimers();
			MoveBall();
            DrawSlimers();            DrawStatus();
            if(ballY < 35)
            {
                long l = System.currentTimeMillis();
                nPointsScored++;
                nScore += ballX <= 500 ? -1 : 1;
                if ((ballX <= 500) && (scoringRun >= 0)) scoringRun++;
                else if ((ballX > 500) && (scoringRun <= 0)) scoringRun--;
                else if ((ballX <= 500) && (scoringRun <= 0)) scoringRun = 1;
                else if ((ballX > 500) && (scoringRun >= 0)) scoringRun = -1;
                promptMsg = ballX <= 500 ? slimeColText[p2Col] : slimeColText[p1Col];
                if(!fP1Touched && !fP2Touched)
                    promptMsg = "What can I say?";
                else
                if ((scoringRun<0?-scoringRun:scoringRun) == scoringRunForSuper)
                    promptMsg += "is on fire!";
                else
                if(ballX > 500 && fP1Touched && !fP2Touched || ballX <= 500 && !fP1Touched && fP2Touched)
                    promptMsg += "aces the serve!";
                else
                if(ballX > 500 && !fP1Touched && fP2Touched || ballX <= 500 && fP1Touched && !fP2Touched)
                    promptMsg += "dies laughing! :P";
                else
                    switch(nScore)
                    {
                    case 0: // '\0'
                    case 10: // '\n'
                        if (nPointsScored == 5)
                            promptMsg += "Wins with a QUICK FIVE!!!";
                        else if (scoringRun == 8)
                            promptMsg += "Wins with a BIG NINE!!!";
                        else
                            promptMsg += "Wins!!!";
                        break;

                    case 4: // '\004'
                        promptMsg += ballX >= 500 ? "Scores!" : "takes the lead!!";
                        break;

                    case 6: // '\006'
                        promptMsg += ballX <= 500 ? "Scores!" : "takes the lead!!";
                        break;

                    case 5: // '\005'
                        promptMsg += "Equalizes!";
                        break;

                    default:
                        promptMsg += "Scores!";
                        break;
                    }
                fCanChangeCol = false;
                boolean flag = nScore != 0 && nScore != 10;
                int i = ballX;
                drawPrompt();
                if(flag)
                {
                    drawPrompt("Click mouse for replay...", 1);
                    mousePressed = false;
                    if(gameThread != null)
                        try
                        {
                            Thread.sleep(2500L);
                        }
                        catch(InterruptedException _ex) { }
                    if(mousePressed)
                    {
                        SaveReplayData();
                        DoReplay();
                    }
                } else
                if(gameThread != null)
                    try
                    {
                        Thread.sleep(2500L);
                    }
                    catch(InterruptedException _ex) { }
                promptMsg = "";
                drawPrompt();
                fCanChangeCol = true;
                if(flag)
                {
                    p1X = 200;
                    p1Y = 0;
                    p2X = 800;
                    p2Y = 0;
                    p1XV = 0;
                    p1YV = 0;
                    p2XV = 0;
                    p2YV = 0;
                    ballX = i >= 500 ? 200 : 800;
                    ballY = 400;
                    ballVX = 0;
                    ballVY = 0;
                    replayStart = replayPos = 0;
                    fP1Touched = fP2Touched = false;
                    repaint();
                }
                startTime += System.currentTimeMillis() - l;
            }
            if(gameThread != null)
                try
                {
                    Thread.sleep(20L);
                }
                catch(InterruptedException _ex) { }
        }
        fEndGame = true;
        SaveReplayData();
        DoReplay();
        fInPlay = false;
        promptMsg = "Click the mouse to play...";
        repaint();
    }

    public void init()
    {
        nWidth = size().width;
        nHeight = size().height;
        nScore = 5;
        fInPlay = fEndGame = false;
        fCanChangeCol = true;
        promptMsg = "Click the mouse to play...";
        screen = getGraphics();
        screen.setFont(new Font(screen.getFont().getName(), 1, 15));
    }

    private void DoReplay()
    {
        FontMetrics fontmetrics = screen.getFontMetrics();
        int i = fontmetrics.stringWidth("Replay...");
        int j = fontmetrics.getHeight();
        int k = nWidth / 2 - i / 2;
        int l = nHeight / 2 - j;
        promptMsg = "Click the mouse to continue...";
        mousePressed = false;
        int i1 = replayPos - 1;
        while(!mousePressed) 
        {
            if(++i1 >= 200)
                i1 = 0;
            if(i1 == replayPos)
            {
                try
                {
                    Thread.sleep(1000L);
                }
                catch(InterruptedException _ex) { }
                i1 = replayStart;
                paint(getGraphics());
            }
            ReplayFrame(i1, k, l, i, j, false);
        }
        promptMsg = "";
        paint(getGraphics());
    }

    private void DoFatality()
    {
        // PLEASE, someone put something funny/interesting here :)
    }
}

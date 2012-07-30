//<!-- 2-player version of Slime Volleyball/Cricket -->
// Original code: Quin Pendragon, 1999.
//  I know that this isn't exactly an ideal example of either game coding or
//  good use of java. It wasn't meant to be. :P
//  No responsibility is taken for any damage to software, hardware,
//  keyboards, or individuals' coding habits as a result of using this code.
// Mods:
// 0) fractoid: Lost the source code, and decompiled the applet on my page
//  to get it back. This is why some of the methods are in a funny
//  order, and some variables are interestingly named :P
// 1) fractoid: added SuperSlime mod.
// 2) danno: deobfuscated code :)
// 3) danno: cricket slime.
// 4) danno: slime cricket: world cup edition - added AI and changed physics slightly
// ...

import java.applet.Applet;
import java.awt.*;

public class SlimeCricket2 extends Applet
    implements Runnable
{
    private int p1Diam = 75; //100
    private int p2Diam = 75; //100
    private int ballRad = 13; //25

    private int nWidth, nHeight;
    private int p1X, p1Y;
    private int p2X, p2Y;
    private int p3X = 1000-p1Diam/2, p3Y;
    private int p1Col, p2Col;
    private Color slimeColours[] = {Color.yellow, new Color(0, 0, 128), new Color(164, 164, 255), Color.black,
        new Color(0, 100, 0), new Color(0, 162, 0), new Color(0, 0, 210), new Color(128, 78, 0), Color.red, Color.black};
    private Color slimeColours2[] = {new Color(0, 100, 0), Color.red, Color.yellow, Color.gray,
        Color.white, Color.yellow, Color.yellow, new Color(60,160,60), Color.yellow, Color.white};
    private String slimeColText[] = {"Australia ", "England ", "India ", "New Zealand ",
        "Pakistan ", "South Africa ","Sri Lanka ", "West Indies ", "Zimbabwe ", "Computer"};
    private String slimeColAbbr[] = {"AUS", "ENG", "IND", "NZ", "PAK", "RSA", "SL", "WI", "ZIM", "AI"};
    private Color difficultyColours[] = {Color.blue, Color.green, Color.red};
    private String difficultyText[] = {"Grade", "Domestic", "International"};
    private int difficulty = 0;

    private int p1OldX, p1OldY;
    private int p2OldX, p2OldY;
    private int p3OldY; // the wickie. note that he/it can't move horizontally.
    private int p1XV, p1YV;
    private int p2XV, p2YV;
    private int p3YV;
    private int ballX, ballY;
    private int ballVX, ballVY;
    private int ballOldX, ballOldY;
    private Graphics screen;
    private String promptMsg;
    private boolean mousePressed;
    private boolean fCanChangeCol;
    private boolean fInPlay;
    private int p1Blink, p2Blink;
    private boolean fP1Touched, fP2Touched;
    private Thread gameThread;
    private boolean fEndGame;
    private Color BALL_COL = Color.white;
    private Color COURT_COL = new Color(0, 160, 0);
    private Color DAY_COL = new Color(85, 85, 255);
    private Color NIGHT_COL = new Color(0, 0, 68); // was 128
    private Color SKY_COL = DAY_COL;
    
    // cricket specific stuff from here on
    private int bounces = 0;
    private boolean fEndOfOver;
    private boolean fHitBackWall = false;
    private int p1XMin, p2XMin, p2XMax;
    private int ballXMax;
    private int p1Touches;
    private int ballCount = 0;
    private int postPos = 1000-p1Diam-5; // where are the stumps?
    private int bowlingCrease = 450; // 300
    private int runningCrease = 450;
    private int battingCrease = postPos-p2Diam/2-20;
    private long p1Score = 0, p2Score = 0;
    private int inns = 1;
    private int wicketPenalty = 5;
    private boolean fNoBall = false;
    private int overs = 5;
    private int stillFrames = 0;
    private Image buffer;
    private int thisBall;
    private String thisOver;
    private long[] p1bxb; // player 1, ball by ball
    private long[] p2bxb;
    private boolean p1Hold = false;
    private boolean ballbowled;

    private boolean p1next, p2next; // oked by each player to move to next ball?

    private int wait; // frames to wait till the ai can bowl.
    private boolean p1ai = false, p2ai = false;
    private int balltype = -1;
    private int shottype = -1;

    private final int AI_COL = 9;

    // some commentary
    private final String[] COMM_FOUR = {
        "Along the carpet it goes for four.",
        "Back past the bowler for four.",
        "Picks the gap nicely and into the fence it goes for four.",
        "Shot!",
        "Four more added to the total.",
        "It's certainly a batsman's paradise out there today.",
        "... and the umpire waves his arm once more.",
        "Exactly not what the bowler had planned.",
        "Well it's bounced up off the rope and smacked some guy in the face!"};
    private final String[] COMM_FOURTOUCHED = {
        "Terrible fielding effort there.",
        "The bowler won't be pleased with that effort.",
        "Well that should never have been a four."};
    private final String[] COMM_SIX = {
        "He's carving them up like a Christmas cake!",
        "That's come right orf the meat of the bat.",
        "He's hit that one very hored indeed.",
        "He's smacked that one.",
        "He's gone for it... it's gone all the way!",
        "Must be playing on a road out there today.",
        "Looks like he's chasing Andrew Symonds' record here..."};
    private final String[] COMM_SIXTOUCHED = {
        "Oh no, he's done a Paul Reiffel!",
        "Well that's six more on top of the no ball, he can't be happy."};
    private final String[] COMM_STUMPED = {
        "Stumped him!",
        "A fine example of wicket keeping there. Excellent stuff.",
        "There goes the red light! What quick hands this keeper has!"};
    private final String[] COMM_RUNOUT = {
        "He's run out! What a tragedy!",
        "... and there's the red light. He's out.",
        "Allan Donald would be pleased with that effort.",
        "Well the fielder's decided to chance his arm, and it's come off!",
        "The bails were off in a flash, he never had a chance.",
        "Poor calling there, he deserved to get out.",
        "Well what else do you expect if you run like Ranatunga?"};
    private final String[] COMM_BOWLED = {
        "Bowled him neck and crop.",
        "Tremendous delivery, he really had no idea about that.",
        "What a marvellous ball!",
        "That's a ripsnorter of a ball!",
        "I think that's just knocked Joe the stumpcameraman out.",
        "Well the bowler's certainly had his weeties this morning.",
        "There's the death rattle.",
        "That's gotta be a contender for today's fastest ball.",
        "Straight through the gate. The batsman won't be pleased with that.",
        "Completely bamboozled.",
        "A wonderful spell of bowling, this."};
    private final String[] COMM_PLAYEDON = {
        "He's played on!",
        "A magnificent chop shot, oh wait, it's hit the stumps.",
        "He's done an Adam Gilchrist!"};
    private final String[] COMM_CAUGHT = {
        "He's hit it straight down his throat.",
        "A safe pair of hands, he doesn't drop those.",
        "What a magnificent shot! No, he's been caught!",
        "A marvellous catch, that.",
        "... and he takes a straightforward catch.",
        "Well, they say \"catches win matches\".",
        "Caught, yes!",
        "Well, he's picked out the only fielder in front of the bat!",
        "Can't be happy with that shot.",
        "What a shame, we can't use the snickometer on that one it's so damned obvious."};
    private final String[] COMM_CTBEHIND = {
        "... the keeper gobbles up the catch.",
        "... and the snickometer shows that that's clearly out.",
        "Excellent line and length, he's got another edge.",
        "Yes, there was some bat in that, he's gone!"};
    private final String[] COMM_OUT_GENERIC = {
        "Got him, yes!",
        "It's all happening here!",
        "A marvellous effort, that!",
        "He's out.",
        "Oh dear.",
        "Gone!",
        "What a magnificent fielding side this team is.",
        "Yes, another one! He's a hero, this man!"};

    public void init()
    {
        nWidth = size().width;
        nHeight = size().height;
        buffer = createImage(nWidth, nHeight);
        fInPlay = false;
        fEndGame = true;
        fEndOfOver = false;
        fCanChangeCol = true;
        promptMsg = "Click team names to select teams, an opponent, then choose an innings length to start!";
        screen = buffer.getGraphics();
        screen.setFont(new Font(screen.getFont().getName(), 1, 15));
        p1Col = AI_COL;
        p2Col = AI_COL;
        inns = 0;
    }

    public void paint(Graphics _g)
    {
        Graphics g = buffer.getGraphics();
        nWidth = size().width;
        nHeight = size().height;
        g.setColor(SKY_COL);
        g.fillRect(0, 0, nWidth, (4 * nHeight) / 5);
        g.setColor(COURT_COL);
        g.fillRect(0, (4 * nHeight) / 5, nWidth, nHeight / 5);
        g.setColor(Color.white); // stumps
        g.fillRect(nWidth*postPos/1000 - 2, nHeight*7/10, 3, nHeight/10);

        // the crease markings
        g.fillRect(nWidth*bowlingCrease/1000-1, nHeight*4/5, 2, 5);
        g.fillRect(nWidth*runningCrease/1000-1, nHeight*4/5, 2, 5);
        g.fillRect(nWidth*battingCrease/1000-1, nHeight*4/5, 2, 5);
        drawPrompt();
        
        // end of game - draw stuff to start another one
        if (!fInPlay && fEndGame)
        {
            // all big font...
            FontMetrics fm = screen.getFontMetrics();
            screen.setColor(Color.white);
            screen.drawString("Slime Cricket 2: World Cup Edition BETA", nWidth/2-fm.stringWidth("Slime Cricket 2: World Cup Edition BETA")/2, nHeight/2-fm.getHeight()*7);
            screen.drawString("This is not the final version of the game!", nWidth/2-fm.stringWidth("This is not the final version of the game!")/2, nHeight/2-fm.getHeight()*6);

            // draw the team selectors
            screen.setColor(slimeColours[p2Col]);
            screen.fillRect(nWidth/4-fm.stringWidth(slimeColText[p2Col])/2-10, nHeight/2-fm.getAscent()*2, fm.stringWidth(slimeColText[p2Col])+20, fm.getAscent()*2);
            screen.setColor(slimeColours2[p2Col]);
            screen.drawString(slimeColText[p2Col], nWidth/4-fm.stringWidth(slimeColText[p2Col])/2, nHeight/2-fm.getAscent()/2);

            // bowling
            screen.setColor(slimeColours[p1Col]);
            screen.fillRect(nWidth/2-fm.stringWidth(slimeColText[p1Col])/2-10, nHeight/2-fm.getAscent()*2, fm.stringWidth(slimeColText[p1Col])+20, fm.getAscent()*2);
            screen.setColor(slimeColours2[p1Col]);
            screen.drawString(slimeColText[p1Col], nWidth/2-fm.stringWidth(slimeColText[p1Col])/2, nHeight/2-fm.getAscent()/2);

            // difficulty level
            screen.setColor(difficultyColours[difficulty]);
            screen.fillRect(nWidth*3/4-fm.stringWidth(difficultyText[difficulty])/2-10, nHeight/2-fm.getAscent()*2, fm.stringWidth(difficultyText[difficulty])+20, fm.getAscent()*2);
            screen.setColor(Color.white);
            screen.drawString(difficultyText[difficulty], nWidth*3/4-fm.stringWidth(difficultyText[difficulty])/2, nHeight/2-fm.getAscent()/2);

            // and the over selectors
            g.setColor(Color.white);
            screen.setColor(SKY_COL);
            for (int i=0; i<5; i++)
            {
                g.fillRect(nWidth/4+i*nWidth/10+5, nHeight*2/3-fm.getAscent()*3/2, nWidth/10-10, 2*fm.getAscent());
                screen.drawString(""+(1*(i+1))+" overs", nWidth*3/10+i*nWidth/10-fm.stringWidth(""+(1*i+1)+" overs")/2, nHeight*2/3-fm.getAscent()*0);
            }

            // in the small font now...
            fm = g.getFontMetrics();
            g.setColor(Color.white);
            g.drawString("Written by Wedgey and Fractoid", nWidth/2-fm.stringWidth("Written by Wedgey and Fractoid")/2, nHeight/2-fm.getHeight()*6);
            g.drawString("with input from Browny, Chucky and Damo", nWidth/2-fm.stringWidth("with input from Browny, Chucky and Damo")/2, nHeight/2-fm.getHeight()*5);
            drawScores();
            
            // draw the team selectors
            g.drawString("Bowling first", nWidth/4-fm.stringWidth("Bowling first")/2, nHeight/2-fm.getAscent()*3);
            g.drawString("Batting first", nWidth/2-fm.stringWidth("Batting first")/2, nHeight/2-fm.getAscent()*3);
            g.drawString("Difficulty", nWidth*3/4-fm.stringWidth("Difficulty")/2, nHeight/2-fm.getAscent()*3);

            // draw the over selection thing.
            g.drawString("Click on innings length to start...", nWidth/2-fm.stringWidth("Click on innings length to start...")/2, nHeight*2/3-fm.getHeight()*2);
            screen.setColor(SKY_COL);
        } else if (!fInPlay && !fEndGame && !fEndOfOver)
        {
            // in between innings
            FontMetrics fm = screen.getFontMetrics();
            screen.setColor(Color.white);
            screen.drawString("Change of innings", nWidth/2-fm.stringWidth("Change of innings")/2, nHeight/2-fm.getHeight()*5);
            drawScores();
        } else if (fEndOfOver)
        {
            FontMetrics fm = screen.getFontMetrics();
            screen.setColor(Color.white);
            switch (inns)
            {
            case 2:
                drawScores();
                screen.drawString("Over", nWidth/2-fm.stringWidth("Over")/2, fm.getHeight());
                screen.drawString("Last over: "+thisOver, nWidth/2-fm.stringWidth("Last over: "+thisOver)/2, fm.getHeight()*2);
                drawWorm();
                // do the comparison
                screen.drawString("After "+ballCount/6+(ballCount/6==1?" over...":" overs..."), nWidth/2-fm.stringWidth("After "+ballCount/6+(ballCount/6==1?" over...":" overs..."))/2, fm.getHeight()*4);
                screen.drawString(slimeColText[p2Col].toUpperCase(), nWidth/3, fm.getHeight()*5);
                screen.drawString(""+p2Score, nWidth*2/3-fm.stringWidth(""+p2Score), fm.getHeight()*5);
                screen.drawString(slimeColText[p1Col]+" ("+p1Score+")", nWidth/3, fm.getHeight()*6);
                screen.drawString(""+p1bxb[ballCount-1], nWidth*2/3-fm.stringWidth(""+p1bxb[ballCount-1]), fm.getHeight()*6);
                break;

            case 1:
                drawScores();
                screen.drawString("Over", nWidth/2-fm.stringWidth("Over")/2, nHeight/2-fm.getHeight()*3);
                screen.drawString("Last over: "+thisOver, nWidth/2-fm.stringWidth("Last over: "+thisOver)/2, nHeight/2-fm.getHeight());
                break;

            default:
                break;
            }
        } else
        {
            // it's in play
            drawScores();
            drawWorm();
        }

        _g.drawImage(buffer, 0, 0, null);
    }

    public boolean handleEvent(Event event)
    {
        switch(event.id)
        {
        default:
            break;

        case 503: // Event.MOUSE_MOVE
            showStatus("Slime Cricket 2: by Wedgey: http://www.student.uwa.edu.au/~wedgey/slimec/");
            break;

        case 501: // Event.MOUSE_DOWN
            mousePressed = true;
            if (fEndOfOver)
            {
                gameThread = new Thread(this);
                gameThread.start();
                thisOver = "";
                fEndOfOver = false;
                promptMsg = "";
                repaint();
            } else if(!fInPlay)
            {
                if (fEndGame)
                {
                    FontMetrics fm = screen.getFontMetrics();
                    // was it an over selection click?
                    if (event.y > nHeight*2/3-fm.getAscent()*3/2 && event.y < nHeight*2/3+fm.getAscent()/2)
                    {
                        for (int i=0; i<5 && !fInPlay; i++)
                            if (event.x > nWidth/4+i*nWidth/10+5 && event.x < nWidth/4+(i+1)*nWidth/10-5)
                            {
                                fEndGame = false;
                                fInPlay = true;
                                p1ai = p2ai = false;
                                if (p1Col == AI_COL)
                                {
                                    p2ai = true;
                                    while ((p1Col=(int)(Math.random()*slimeColours.length)) == p2Col);
                                }
                                if (p2Col == AI_COL)
                                {
                                    p1ai = true;
                                    while ((p2Col=(int)(Math.random()*slimeColours.length)) == p1Col);
                                }
                                inns = 1;
                                p1Score = p2Score = 0;
                                int tempI = p1Col;
                                p1Col = p2Col;
                                p2Col = tempI;
                                SKY_COL = DAY_COL;
                                overs = (i+1)*1;
                                // setup the ball by ball stuff
                                p1bxb = new long[overs*6];
                                p2bxb = new long[overs*6];
                                for (int j=0; j<overs*6; j++)
                                    p1bxb[j] = p2bxb[j] = 0;
                            }
                    }
                    // or a team selection click?
                    else if (event.y > nHeight/2-fm.getAscent()*2 && event.y < nHeight/2)
                    {
                        //drawPrompt("dood", 1);
                        if (event.x > nWidth/4-fm.stringWidth(slimeColText[p2Col])/2-10 &&
                            event.x < nWidth/4+fm.stringWidth(slimeColText[p2Col])/2+10)
                        {
                            do
                                p2Col = (p2Col != slimeColours.length-1 ? p2Col+1 : 0);
                            while (p1Col == p2Col);
                            repaint();
                        } else if (event.x > nWidth/2-fm.stringWidth(slimeColText[p1Col])/2-10 &&
                            event.x < nWidth/2+fm.stringWidth(slimeColText[p1Col])/2+10)
                        {
                            do
                                p1Col = (p1Col != slimeColours.length-1 ? p1Col+1 : 0);
                            while (p1Col == p2Col);
                            repaint();
                        } else if (event.x > nWidth*3/4-fm.stringWidth(difficultyText[difficulty])/2-10 &&
                            event.x < nWidth*3/4+fm.stringWidth(difficultyText[difficulty])/2+10)
                        {
                            difficulty = (difficulty+1)%difficultyText.length;
                            repaint();
                        }
                    }
                    
                } else // in between innings
                {
                    fInPlay = true;
                    inns++;
                    // swap teams
                    int tempI;
                    tempI = p1Col;
                    p1Col = p2Col;
                    p2Col = tempI;
                    long tempL;
                    tempL = p1Score;
                    p1Score = p2Score;
                    p2Score = tempL;
                    long[] tempIA;
                    tempIA = p1bxb;
                    p1bxb = p2bxb;
                    p2bxb = tempIA;
                    // randomly choose day/night or day games
                    if (Math.random() < 0.8)
                        SKY_COL = NIGHT_COL;
                    boolean tempAI;
                    tempAI = p1ai;
                    p1ai = p2ai;
                    p2ai = tempAI;
                }
                
                // are we having fun yet?
                if (fInPlay)
                {
                    ballCount = -1;
                    thisOver = "";
                    promptMsg = "";
                    thisBall = 0;
                    nextBall();
                    gameThread = new Thread(this);
                    gameThread.start();
                }
            }
            break;

        case Event.KEY_ACTION:
        case 401: // Event.KEY_PRESS
            if(fEndGame)
                break;
            switch(event.key)
            {
            default:
                break;

            case 65: // 'A'
            case 97: // 'a'
                if (!p1ai) p1L(); // prevent human players moving the ai slimes!
                break;

            case 68: // 'D'
            case 100: // 'd'
                if (!p1ai) p1R();
                break;

            case 87: // 'W'
            case 119: // 'w'
                if (!p1ai) p1J();
                break;

            case 'S':
            case 's':
                p1next = true;
                if (!fEndOfOver && p1next && p2next)
                    nextBall();
                break;

            // wickie jump
            case 'Q':
            case 'q':
            case 'E':
            case 'e':
                if (!p1ai) p3J();
                break;

            
            case Event.LEFT:
            case 74: // 'J'
            case 106: // 'j'
                if (!p2ai) p2L();
                break;

            case Event.RIGHT:
            case 76: // 'L'
            case 108: // 'l'
                if (!p2ai) p2R();
                break;

            case Event.UP:
            case 73: // 'I'
            case 105: // 'i'
                if (!p2ai) p2J();
                break;

            case Event.DOWN:
            case 'k':
            case 'K':
                p2next = true;
                if (!fEndOfOver && p1next && p2next)
                    nextBall();
                break;

            case 32: // ' '
                mousePressed = true;
                break;

/*
            case 'B':
            case 'b': // restart - next ball
                if (!fEndOfOver)
                    nextBall();
                break;
*/
            }
            break;

        case Event.KEY_ACTION_RELEASE:
        case 402: // Event.KEY_RELEASE
            switch(event.key)
            {
            default:
                break;

            case 65: // 'A'
            case 97: // 'a'
                if (p1XV < 0 && !p1ai)
                    p1S();
                break;

            case 68: // 'D'
            case 100: // 'd'
                if (p1XV > 0 && !p1ai)
                    p1S();
                break;

            case 'S':
            case 's':
                p1Hold = false;
                break;

            case Event.LEFT:
            case 74: // 'J'
            case 106: // 'j'
                if (p2XV < 0 && !p2ai)
                    p2S();
                break;

            case Event.RIGHT:
            case 76: // 'L'
            case 108: // 'l'
                if (p2XV > 0 && !p2ai)
                    p2S();
                break;

            }
            break;
        }
        return false;
    }

    // use these to control the players - the AI can use these.
    private void p1L() {p1XV = -8;}
    private void p1R() {p1XV = 8;}
    private void p1J() {if (p1Y==0) p1YV = 31;}
    private void p1S() {p1XV = 0;}

    private void p2L() {p2XV = -8;}
    private void p2R() {p2XV = 8;}
    private void p2J() {if (p2Y==0) p2YV = 31;}
    private void p2S() {p2XV = 0;}

    private void p3J() {if (p3Y==0) p3YV = 31;}

    // reset stuff for the next ball to be bowled
    private void nextBall()
    {
        wait = 50;
        p1XMin = p1X = runningCrease-p1Diam/2;
        p2XMin = p2XMax = p2X = battingCrease+20;
        ballVX = ballVY = p1Y = p2Y = p2XV = p2YV = p3Y = p3YV = p1XV = p1YV = 0;
        ballXMax = ballX = runningCrease-p1Diam/2;
        ballY = 400;
        balltype = -1; // reset ai things.
        shottype = -1;
        p1next = p2next = false;
        ballbowled = false;
        fP1Touched = fP2Touched = false;
        bounces = 0;
        p1Touches = 0;
        if (fNoBall) // last ball was a no ball.
            thisBall += 1;

        if (ballCount >= 0)
        {
            p2bxb[ballCount] = p2Score += thisBall;
            if (fNoBall)
                thisOver = thisOver+"N";
            if (thisBall == -wicketPenalty || thisBall == -wicketPenalty+1)
                thisOver = thisOver+"W";
            else
            {
                if (thisBall == 0)
                    thisOver = thisOver+".";
                else if (!(fNoBall && (thisBall == -wicketPenalty+1 || thisBall == 0)))
                    thisOver = thisOver+(!fNoBall?thisBall:thisBall-1);
            }
            thisOver = thisOver+" ";
        }

        thisBall = 0;
        
        if (!fNoBall)
        {
            ballCount++;
            if (ballCount%6 == 0 && ballCount != 0 && ballCount != overs*6)
            {
                fEndOfOver = true;
                gameThread = null;
                promptMsg = "Click the mouse to continue...";
            }// else if (ballCount == overs*6 && inns == 2)
                //DoFatality();
        }
        fNoBall = false;
        fHitBackWall = false;
        stillFrames = 0;
        repaint();
    }

    private long getMinScore(int player)
    {
        long min = 0;
        for (int i=0; i<overs*6; i++)
            if ((player==1?p1bxb[i]:p2bxb[i]) < min)
                min = (player==1?p1bxb[i]:p2bxb[i]);
        return min;
    }

    private long getMaxScore(int player)
    {
        long max = 0;
        for (int i=0; i<overs*6; i++)
            if ((player==1?p1bxb[i]:p2bxb[i]) > max)
                max = (player==1?p1bxb[i]:p2bxb[i]);
        return max;
    }

    private void MoveSlimers()
    {
        // ai stuff
        if (p1ai) {if (!ballbowled) bowl(); else field(); }
        if (p2ai) {if (!fP2Touched && !fHitBackWall) playball(); else running(); }

        // move p1
        p1X += p1XV;
        if(p1X < p1Diam/2)
            p1X = p1Diam/2;
        if(p1X > postPos-p1Diam/2-5)
            p1X = postPos-p1Diam/2-5;
        if(p1YV != 0)
        {
            p1Y += p1YV -= 2;
            if(p1Y < 0)
            {
                p1Y = 0;
                p1YV = 0;
            }
        }

        // check for front foot overstepping
        if (ballX == 200 && ballVX == 200 && p1X < p1XMin)
            p1XMin = p1X; // incomplete...

        // move p2
        p2X += p2XV;
        if(p2X > postPos-p2Diam/2-5)
            p2X = postPos-p2Diam/2-5;
        if(p2X < p2Diam/2)
            p2X = p2Diam/2;
        if(p2YV != 0)
        {
            p2Y += p2YV -= 2;
            if(p2Y < 0)
            {
                p2Y = 0;
                p2YV = 0;
            }
        }

        // did they get a run?
        if (p2X < p2XMin && p2Y == 0)
            p2XMin = p2X;
        else if (p2X > p2XMax && p2Y == 0)
            p2XMax = p2X;

        // running to bowler's end
        if (p2X-p2Diam/2 <= runningCrease && p2XMax+p2Diam/2 >= battingCrease && (fP2Touched || fHitBackWall) && p2Y == 0)
        {
            thisBall++;
            p2XMin = p2XMax = p2X;
            drawScores();
        } // now to wickie's end
        else if (p2XMin-p2Diam/2 <= runningCrease && p2X+p2Diam/2 >= battingCrease && (fP2Touched || fHitBackWall) && p2Y == 0)
        {
            thisBall++;
            p2XMin = p2XMax = p2X;
            drawScores();
        }
        
        // move wickie
        if (p3YV != 0)
            p3Y += p3YV -= 2;
        if (p3Y < 0)
        {
            p3Y = 0;
            p3YV = 0;
        }
    }

    private void DrawSlimers() {
        int ballXPix = ballX*nWidth/1000;
        int ballYPix = 4*nHeight/5-ballY*nHeight/1000;

        // black out the old slime positions - p1
        int sWidth = nWidth*p1Diam/1000;
        int sHeight = nHeight*p1Diam/1000;
        int leftbound = p1OldX*nWidth/1000-sWidth/2;
        int topbound = 4*nHeight/5-sHeight-p1OldY*nHeight/1000;
        screen.setColor(SKY_COL);
        screen.fillRect(leftbound, topbound, sWidth, sHeight);

        // player 2
        sWidth = nWidth*p2Diam/1000;
        sHeight = nHeight*p2Diam/1000;
        leftbound = p2OldX*nWidth/1000-sWidth/2;
        topbound = 4*nHeight/5-sHeight-p2OldY*nHeight/1000;
        screen.fillRect(leftbound, topbound, sWidth, sHeight);

        // wickie
        sWidth = nWidth/10;
        sHeight = nHeight/10;
        leftbound = p3X*nWidth/1000-sWidth/2;
        topbound = 4*nHeight/5-sHeight-p3OldY*nHeight/1000;
        screen.fillRect(leftbound, topbound, sWidth, sHeight);
    
        // the ball
        int fudge = 5; // was 5. a fudge factor.
        int ballRadPix = (ballRad+fudge)*nHeight/1000;
        screen.fillOval(ballXPix-ballRadPix, ballYPix-ballRadPix, 2*ballRadPix, 2*ballRadPix);

        // draw the stumps
        screen.setColor(Color.white);
        screen.fillRect(nWidth*postPos/1000 - 2, nHeight*7/10, 3, nHeight/10);

        // draw p1
        sWidth = nWidth*p1Diam/1000;
        sHeight = nHeight*p1Diam/1000;
        leftbound = p1X*nWidth/1000-sWidth/2;
        topbound = 4*nHeight/5-sHeight-p1Y*nHeight/1000;
        screen.setColor(slimeColours2[p1Col]);
        screen.fillArc(leftbound, topbound, sWidth, 2*sHeight, 0, 180);
        // now fill in the central bit
        screen.setColor(slimeColours[p1Col]);
        screen.fillArc(leftbound, topbound, sWidth, 2*sHeight, 53, 74);
        screen.fillRect(leftbound+sWidth/5, topbound+sHeight/5,
            sWidth*3/5, sHeight*4/5);

        int eyeLeft = p1X+38*p1Diam/100; // coordinates, not pixels.
        int eyeTop = p1Y-60*p1Diam/100; // ditto
        leftbound = eyeLeft*nWidth/1000;
        topbound = 4*nHeight/5-sHeight-eyeTop*nHeight/1000;
        int bedx/*i4*/ = leftbound-ballXPix; // ball-eye dx (pixels)
        int bedy/*j4*/ = topbound-ballYPix; // ball-eye dy (pix)
        int bedist/*k4*/ = (int)Math.sqrt(bedx*bedx+bedy*bedy); // ball-eye distance (pix)
        if (bedist == 0) // avoid div/0
            bedist = 1;
        int eyeWidthPix = nWidth/50*p1Diam/100;
        int eyeHeightPix = nHeight/25*p1Diam/100;
        screen.setColor(Color.white); // eye
        screen.fillOval(leftbound-eyeWidthPix, topbound-eyeHeightPix, eyeWidthPix, eyeHeightPix);
        screen.setColor(Color.black);
        screen.fillOval(leftbound-4*bedx/bedist-3*eyeWidthPix/4, topbound-4*bedy/bedist-3*eyeHeightPix/4,
            eyeWidthPix/2, eyeHeightPix/2);

        // player 2
        sWidth = nWidth*p2Diam/1000;
        sHeight = nHeight*p2Diam/1000;
        leftbound = p2X*nWidth/1000-sWidth/2;
        topbound = 4*nHeight/5-p2Diam*nHeight/1000-p2Y*nHeight/1000;
        screen.setColor(slimeColours2[p2Col]);
        screen.fillArc(leftbound, topbound, sWidth, 2*sHeight, 0, 180);
        // now fill in the central bit
        screen.setColor(slimeColours[p2Col]);
        screen.fillArc(leftbound, topbound, sWidth, 2*sHeight, 53, 74);
        screen.fillRect(leftbound+sWidth/5, topbound+sHeight/5,
            sWidth*3/5, sHeight*4/5);

        eyeLeft = p2X-18*p2Diam/100;
        eyeTop = p2Y-60*p2Diam/100;
        leftbound = eyeLeft*nWidth/1000;
        topbound = 4*nHeight/5-sHeight-eyeTop*nHeight/1000;
        bedx = leftbound-ballXPix;
        bedy = topbound-ballYPix;
        bedist = (int)Math.sqrt(bedx*bedx+bedy*bedy);
        if (bedist == 0) // avoid div/0
            bedist = 1;
        eyeWidthPix = nWidth/50*p2Diam/100;
        eyeHeightPix = nHeight/25*p2Diam/100;
        screen.setColor(Color.white); // eye
        screen.fillOval(leftbound-eyeWidthPix, topbound-eyeHeightPix, eyeWidthPix, eyeHeightPix);
        screen.setColor(Color.black);
        screen.fillOval(leftbound-4*bedx/bedist-3*eyeWidthPix/4, topbound-4*bedy/bedist-3*eyeHeightPix/4,
            eyeWidthPix/2, eyeHeightPix/2);

        // wickie
        sWidth = nWidth*p1Diam/1000;
        sHeight = nHeight*p1Diam/1000;
        leftbound = p3X*nWidth/1000-sWidth/2;
        topbound = 4*nHeight/5-p1Diam*nHeight/1000-p3Y*nHeight/1000;
        screen.setColor(slimeColours2[p1Col]);
        screen.fillArc(leftbound, topbound, sWidth, 2*sHeight, 0, 180);
        // now fill in the central bit
        screen.setColor(slimeColours[p1Col]);
        screen.fillArc(leftbound, topbound, sWidth, 2*sHeight, 53, 74);
        screen.fillRect(leftbound+sWidth/5, topbound+sHeight/5,
            sWidth*3/5, sHeight*4/5);

        eyeLeft = p3X-18*p1Diam/100;
        eyeTop = p3Y-60*p1Diam/100;
        leftbound = eyeLeft*nWidth/1000;
        topbound = 4*nHeight/5-sHeight-eyeTop*nHeight/1000;
        bedx = leftbound-ballXPix;
        bedy = topbound-ballYPix;
        bedist = (int)Math.sqrt(bedx*bedx+bedy*bedy);
        if (bedist == 0) // avoid div/0
            bedist = 1;
        eyeWidthPix = nWidth/50*p1Diam/100;
        eyeHeightPix = nHeight/25*p1Diam/100;
        screen.setColor(Color.white); // eye
        screen.fillOval(leftbound-eyeWidthPix, topbound-eyeHeightPix, eyeWidthPix, eyeHeightPix);
        screen.setColor(Color.black);
        screen.fillOval(leftbound-4*bedx/bedist-3*eyeWidthPix/4, topbound-4*bedy/bedist-3*eyeHeightPix/4,
            eyeWidthPix/2, eyeHeightPix/2);

        // move and draw the ball.
        MoveBall();

    }

    private void MoveBall() {
/*      // the starting conditions
        ballXMax = ballX = runningCrease-p1Diam/2;
        ballY = 400;
        
        if (ballY == 400 && ballX == runningCrease-p1Diam/2)
            System.out.println("Wait="+wait);
        if (ballX == runningCrease-p1Diam/2)
            System.out.println(","+ballY);

//      System.out.println(""+ballX);
*/
        int fudge = 5; // was 5. a fudge factor.
        int maxXV = 11; // was 15
        int maxYV = 21; // was 22
        int maxXVbat = 17; // was 19

        int ballRadPix = (ballRad+fudge)*nHeight/1000;
        int ballXPix = ballOldX*nWidth/1000;
        int ballYPix = 4*nHeight/5-ballOldY*nHeight/1000;

        // move the ball
        ballY += --ballVY;
        ballX += ballVX;

        ballbowled = ballbowled || ballX > bowlingCrease;

        if (ballVX < 2 && ballVY < 2 && p1XV+p1YV+p2XV+p2YV+p3YV == 0 && ballX != 200 &&
            (p2X <= runningCrease+p2Diam/2 || p2X >= battingCrease-p2Diam/2))
        {
            if (stillFrames++ > 75)
                promptMsg = " ";
        }
        else
            stillFrames = 0;

        // make it bounce
        if (ballY < ballRad+5)
        {   
            ballY = ballRad+5;
            ballVY = -ballVY*2/3;
            ballVX = ballVX*19/20;
            // make sure it can't be caught, or count bounces for a grubber
            bounces++;
            if (!fP2Touched && bounces > 1 && !fHitBackWall)
            {
                fNoBall = true;
                drawPrompt("No ball! (grubber)", 2);
            }
        }

        // if the ball's gone past the stumps then we don't want to let the batsman hit it
        if (ballX > postPos && !fP2Touched)
        {
            fP2Touched = true;
        }

        // was it a beam ball?
        if (ballY > 300 && ballX > battingCrease-p2Diam/2 && p2X >= battingCrease-p2Diam/2 &&
            !fP2Touched && p2XMin > battingCrease-p2Diam*3/4)
        {
            fNoBall = true;
            drawPrompt("No ball! (too high)", 2);
        }

        // collision detection
        if(!fEndGame) {
            int dx = 2*(ballX-p1X);
            int dy = ballY-p1Y;
            int dist = (int)Math.sqrt(dx*dx+dy*dy);
            int dvx = ballVX-p1XV;
            int dvy = ballVY-p1YV;
            
            // collide with bowler
            // don't let the bowler do some tip serve
            if(dy > 0 && dist < p1Diam+ballRad && dist > fudge) {
                /* i have nfi what this is. i'm supposed to have done engineering
                dynamics and i can't remember any equation with x*x'+y*y' in it...
                it was a long time ago! - danno */
                int something = (dx*dvx+dy*dvy)/dist;
                ballX = p1X+(p1Diam+ballRad)/2*dx/dist;
                ballY = p1Y+(p1Diam+ballRad)*dy/dist;
                // cap the velocity
                if(something <= 0) {
                    if (!p1Hold) // is the bowler running with the ball? no
                        ballVX += p1XV-2*dx*something/dist;
                    else // or maybe they are.
                    {
                        ballVX = 0;
                        ballVY = 0;
                    }

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

                // can't hit it twice
                if (p1Touches > 0 && !fP2Touched && ballOldX == ballXMax && !fHitBackWall)
                {
                    drawPrompt("No ball! (too many touches)", 2);
                    fNoBall = true;
                }
                
                // say we've touched it
                if (fP2Touched/* || p1X != 200*/)
                    fP1Touched = true;

                if (p1X != runningCrease-p1Diam/2)
                    p1Touches++;

                // was it a catch? - have to hit the front of the slime now.
                if (fP2Touched && bounces == 0 && !fNoBall && !fHitBackWall && ballX >= p1X)
                {
                    promptMsg = COMM_CAUGHT[(int)(COMM_CAUGHT.length*Math.random())];
                    thisBall = -wicketPenalty;
                }
            }

            // collide with p2 - batsman
            if (!fP2Touched) { // only if not hit yet
                // that stuff all over again, but for p2.
                dx = 2*(ballX-p2X);
                dy = ballY-p2Y;
                dist = (int)Math.sqrt(dx*dx+dy*dy);
                dvx = ballVX-p2XV;
                dvy = ballVY-p2YV;
                if(dy > 0 && dist < p2Diam+ballRad && dist > fudge && p1Touches > 0) {
                    int something = (dx*dvx+dy*dvy)/dist;
                    ballX = p2X+(p2Diam+ballRad)/2*dx/dist;
                    ballY = p2Y+(p2Diam+ballRad)*dy/dist;
                    if(something <= 0) {
                        ballVX += p2XV-2*dx*something/dist;
                        if(ballVX < -maxXVbat)
                            ballVX = -maxXVbat;
                        if(ballVX > maxXV) // don't let him hit it behind him hard.
                            ballVX = maxXV;
                        ballVY += p2YV-2*dy*something/dist;
                        if(ballVY < -maxYV)
                            ballVY = -maxYV;
                        if(ballVY > maxYV)
                            ballVY = maxYV;
                    }
                    fP2Touched = true;
                    bounces = 0; // now bounces till the catch/whatever
                }
            }

            // collide with p3 - wickie
            dx = 2*(ballX-p3X);
            dy = ballY-p3Y;
            dist = (int)Math.sqrt(dx*dx+dy*dy);
            dvx = ballVX;
            dvy = ballVY-p3YV;
            if(dy > 0 && dist < p1Diam+ballRad && dist > fudge) {
                int something = (dx*dvx+dy*dvy)/dist*2/3;
                ballX = p3X+(p1Diam+ballRad)/2*dx/dist;
                ballY = p3Y+(p1Diam+ballRad)*dy/dist;
                if(something <= 0) {
                    ballVX += -2*dx*something/dist;
                    if(ballVX < -maxXVbat)
                        ballVX = -maxXVbat;
                    if(ballVX > maxXV) // don't let him hit it behind him hard.
                        ballVX = maxXV;
                    ballVY += p3YV-2*dy*something/dist;
                    if(ballVY < -maxYV)
                        ballVY = -maxYV;
                    if(ballVY > maxYV)
                        ballVY = maxYV;
                }
                if (!fP1Touched && fP2Touched && bounces == 0 && !fNoBall)
                {
                    promptMsg = COMM_CTBEHIND[(int)(COMM_CTBEHIND.length*Math.random())];
                    thisBall = -wicketPenalty;
                } else if ((p2X < battingCrease-p2Diam/2 && p2X > runningCrease+p2Diam/2) || p2Y != 0)
                {
                    if (p2XMin-p2Diam/2 > runningCrease && !fNoBall && !fP1Touched)
                        promptMsg = COMM_STUMPED[(int)(COMM_STUMPED.length*Math.random())];
                    else
                        promptMsg = COMM_RUNOUT[(int)(COMM_RUNOUT.length*Math.random())];
                    thisBall = -wicketPenalty;
                }
                fP1Touched = true;
            }

            // hits left wall
            if(ballX < 5) {
                ballX = 5;
                ballVX = -ballVX*2/3;
                if (fP2Touched && bounces == 0 && !fHitBackWall)
                {
                    promptMsg = COMM_SIX[(int)(COMM_SIX.length*Math.random())];
                    if (fP1Touched && Math.random() < 0.7)
                        promptMsg = COMM_SIXTOUCHED[(int)(COMM_SIXTOUCHED.length*Math.random())];
                    drawPrompt(promptMsg, 1);
                    promptMsg = "";
                    thisBall += 6;
                } else if (fP2Touched && !fHitBackWall)
                {
                    promptMsg = COMM_FOUR[(int)(COMM_FOUR.length*Math.random())];
                    if (fP1Touched && Math.random() < 0.7)
                        promptMsg = COMM_FOURTOUCHED[(int)(COMM_FOURTOUCHED.length*Math.random())];
                    drawPrompt(promptMsg, 1);
                    promptMsg = "";
                    thisBall += 4;
                } else if (!fP2Touched)
                {
                    fNoBall = true;
                    drawPrompt("No ball! (must bowl forwards)", 2);
                }
                if (fP2Touched)
                    fHitBackWall = true; // no caught off a 6!

            }
            // hits right wall
            if(ballX > 995) {
                ballX = 995;
                ballVX = -ballVX*2/3;
                fHitBackWall = true;
            }
            // hits stumps
            if(ballX > postPos-ballRad && ballX < postPos+ballRad && ballY < 105+ballRad)
            {
                // check for a wicket
                if (((p2X < battingCrease-p2Diam/2 && p2X > runningCrease+p2Diam/2) || p2Y != 0)
                    && fP1Touched && fP2Touched)
                {
                    promptMsg = COMM_RUNOUT[(int)(COMM_RUNOUT.length*Math.random())];
                    thisBall = -wicketPenalty;
                }
                else if (!fNoBall && !fHitBackWall && p1Touches == 1)
                {
                    promptMsg = COMM_BOWLED[(int)(COMM_BOWLED.length*Math.random())];
                    if (fP2Touched && Math.random() < 0.5)
                        promptMsg = COMM_PLAYEDON[(int)(COMM_PLAYEDON.length*Math.random())];
                    thisBall = -wicketPenalty;
                }
                // can't get a 4 or 6 now.
                fHitBackWall = true;
                // bounces off top of stumps
                if(ballVY < 0 && ballY > 105+ballRad) {
                    ballVY *= -1;
                    ballY = 105+ballRad;
                } else if(ballX < postPos) { // hits side of net
                    ballX = postPos-17;
                    ballVX = (ballVX >= 0 ? -ballVX : ballVX)*3/4;
                } else {
                    ballX = postPos+17;
                    ballVX = (ballVX <= 0 ? -ballVX : ballVX)*3/4;
                }
                fP2Touched = true; // so the batsman can't hit it now.
            }
        }

        if (ballX > ballXMax)
            ballXMax = ballX;

        // draw the ball
        ballXPix = (ballX*nWidth)/1000;
        ballYPix = 4*nHeight/5-ballY*nHeight/1000;
        screen.setColor(BALL_COL);
        screen.fillOval(ballXPix-ballRadPix, ballYPix-ballRadPix, 2*ballRadPix, 2*ballRadPix);

        drawScores();
        // if there's a message then there was a wicket.
        if (promptMsg.length() > 0)
        {
            if (promptMsg.length() > 1 && Math.random() < 0.3)
                promptMsg = COMM_OUT_GENERIC[(int)(COMM_OUT_GENERIC.length*Math.random())];
            drawPrompt(promptMsg, 0);
            getGraphics().drawImage(buffer, 0, 0, this);
            if (promptMsg.length() > 1)
                sleep(1500L);
            promptMsg = "";
            nextBall();
        }
    }

    private void sleep(long ms)
    {
        if (gameThread != null)
            try {
                gameThread.sleep(ms);
            } catch (InterruptedException _ex) {}
    }

    public void drawPrompt()
    {
        screen.setColor(COURT_COL);
        screen.fillRect(0, (4 * nHeight) / 5 + 6, nWidth, nHeight / 5 - 10);
        drawPrompt(promptMsg, 0);
    }

    public void drawPrompt(String s, int i)
    {
        FontMetrics fontmetrics = screen.getFontMetrics();
        screen.setColor(Color.white);
        screen.drawString(s, (nWidth - fontmetrics.stringWidth(s)) / 2, (nHeight * 4) / 5 + fontmetrics.getHeight() * (i + 1) + 10);
    }

    private void drawScores()
    {
        if (inns == 0)
            return;
        
        Graphics g = screen;
        FontMetrics fm = g.getFontMetrics();
        int lines = 1;

        g.setColor(SKY_COL);
        g.fillRect(0, 0, nWidth/2, 3*fm.getAscent()+10);
        g.setColor(Color.white);

        // batsman's score
        String s = slimeColText[p2Col]+(p2Score+thisBall);
        g.drawString(s, 10, (fm.getAscent()+3)*lines+10);
        lines++;

        if (inns != 1) // bowler's score
        { 
            s = slimeColText[p1Col]+p1Score;
            g.drawString(s, 10, (fm.getAscent()+3)*lines+10);
            lines++;
        }
        
        // overs
        if (ballCount < 6*overs-1)
        {
            s = "Over: "+(ballCount/6);
            if (ballCount%6 != 0)
                s = s+"."+(ballCount%6);
            s = s+" ("+overs+")";
        } else if (ballCount == 6*overs-1)
            s = "Last ball";
        else
            s = "Over: "+overs;

        g.drawString(s, 10, (fm.getAscent()+3)*lines+20);
        lines++;

        if (p1X != 200 || p2X != 800 || fP1Touched || fP2Touched)
            return;

/*      if (ballCount%6 > 1 && Math.random() < 0.3)
        {
            s = "This over: "+thisOver;
            g.drawString(s, 10, (fm.getAscent()+3)*lines+20);
            lines++;
        }

        if (Math.random() < 0.5 && ballCount > 1)
        {
            s = "Run rate: "+Math.abs(6*p2Score/ballCount)+"."+Math.abs(60L*p2Score/ballCount-6*p2Score/ballCount*10);
            g.drawString(s, 10, (fm.getAscent()+3)*lines+20);
            lines++;
        }
*/
    }

    private void drawWorm()
    {
        Graphics g = buffer.getGraphics();
        FontMetrics fm = g.getFontMetrics();
        // get the range of the worm first
        long min, p1min, p2min, max, p1max, p2max;
        p1min = getMinScore(1);
        p2min = getMinScore(2);
        p1max = getMaxScore(1);
        p2max = getMaxScore(2);
        min = (p1min<p2min?p1min:p2min);
        max = (p1max>p2max?p1max:p2max);
        if (min == 0 && max == 0)
            return; // don't continue, div/0s suck

        // set up the size of the graph
        int x0 = nWidth*4/5-5; // 0 mark on x axis
        int xr = nWidth/5; // x range
        int y0 = (int)(5+nHeight/5*max/(max-min));
        int yr = nHeight/5; // y range

        if (fEndOfOver) // blow up if reqd.
        {
            x0 = nWidth/10-5; // 0 mark on x axis
            xr = nWidth*4/5; // x range
            y0 = (int)(nHeight*2/5*max/(max-min)+nHeight*3/10);
            yr = nHeight*2/5; // y range
        }
        
        // draw the bowling team's worm if they've batted - only if chasing
        if (inns == 2)
        {
            // bowling team
            g.setColor(slimeColours[p1Col]);
            g.drawString(slimeColAbbr[p1Col], x0-fm.stringWidth(slimeColAbbr[p1Col])-5, y0-(int)((max+min)/2*yr/(max-min)));
            g.drawLine(x0, y0, x0+xr/(6*overs), (int)(y0-yr*p1bxb[0]/(max-min)));
            for (int i=1; i<6*overs; i++)
                g.drawLine(x0+xr*i/(6*overs), (int)(y0-yr*p1bxb[i-1]/(max-min)),
                    x0+xr*(i+1)/(6*overs), (int)(y0-yr*p1bxb[i]/(max-min)));

            // the batting team's worm
            g.setColor(slimeColours[p2Col]);
            g.drawString(slimeColAbbr[p2Col], x0-fm.stringWidth(slimeColAbbr[p2Col])-5, y0-(int)((max+min)/2*yr/(max-min))+fm.getAscent());
            g.drawLine(x0, y0, x0+xr*1/(6*overs), (int)(y0-yr*p2bxb[0]/(max-min)));
            for (int i=1; i<ballCount; i++)
                g.drawLine(x0+xr*i/(6*overs), (int)(y0-yr*p2bxb[i-1]/(max-min)),
                    x0+xr*(i+1)/(6*overs), (int)(y0-yr*p2bxb[i]/(max-min)));
            
            // the run rate line
            g.setColor(Color.white);
/*          if (p1bxb[overs*6-1] > 0)
                g.drawLine(x0, y0, x0+xr, 5);
            else
                g.drawLine(x0, y0, x0+xr, yr+5);
*/
            // the axes
            g.drawString(""+max, x0-5-fm.stringWidth(""+max), y0-(int)(max*yr/(max-min))+fm.getAscent());
            g.drawString(""+min, x0-5-fm.stringWidth(""+min), y0-(int)(min*yr/(max-min)));
            g.drawLine(x0, y0-(int)(max*yr/(max-min)), x0, y0-(int)(min*yr/(max-min)));
            g.drawLine(x0, y0, x0+xr, y0);
        }
        
    }

    public void run()
    {
        Graphics g = getGraphics();
        while (gameThread != null) 
        {
            if (wait > 0)
                wait--;
            p1OldX = p1X;
            p1OldY = p1Y;
            p2OldX = p2X;
            p2OldY = p2Y;
            p3OldY = p3Y;
            ballOldX = ballX;
            ballOldY = ballY;
            MoveSlimers();
            DrawSlimers();
            g.drawImage(buffer, 0, 0, null);

            // put end of game stuff here.
            if (ballCount == overs*6 && !fNoBall)
            {
                fInPlay = false;
                if (inns == 1)
                    promptMsg = "Click the mouse to continue...";
                else
                {
                    DoFatality();
                    promptMsg = "Click team names to select teams, then choose an innings length to start!";
                    fEndGame = true;
                    // reset the AIs
                    if (p1ai)
                        p1Col = AI_COL;
                    if (p2ai)
                        p2Col = AI_COL;
                    p1ai = p2ai = false;
                }
                gameThread = null;
            }

            // end of a normal frame
            if(gameThread != null)
                try
                {
                    gameThread.sleep(20L);
                }
                catch(InterruptedException _ex) { }
        }
        if (!fEndOfOver)
            fInPlay = false;
        repaint();
    }

    // winning slime jumps.
    private void DoFatality()
    {
//      for (int i=0; i<3; i++)
//      {
            Graphics g = getGraphics();
            if (p1Score > p2Score)
            {
                p1J();
                drawPrompt(slimeColText[p1Col]+" wins!", 1);
            } else if (p2Score > p1Score)
            {
                p2J();
                drawPrompt(slimeColText[p1Col]+" wins!", 1);
            } else
                drawPrompt("It's a tie!", 1);
            p1ai = p2ai = false;
/*
            // no replays.
            while (!(p1YV == 0 && p2YV == 0))
            {
                p1OldX = p1X;
                p1OldY = p1Y;
                p2OldX = p2X;
                p2OldY = p2Y;
                p3OldY = p3Y;
//              ballOldX = ballX;
//              ballOldY = ballY;
                ballX = ballOldX;
                ballY = ballOldY;
                MoveSlimers();
                DrawSlimers();
                g.drawImage(buffer, 0, 0, null);

                // end of a normal frame
                if(gameThread != null)
                    try
                    {
                        gameThread.sleep(20L);
                    }
                    catch(InterruptedException _ex) { }
            }
        }
*/
        //if (gameThread != null)
            //try { gameThread.sleep(1500L); } catch (InterruptedException _ex) {}
    }

    public void destroy()
    {
        gameThread.stop();
        gameThread = null;
    }

    // bowl a new ball - called until ballbowled == true
    private void bowl()
    {
        if (wait > 0)
            return;
        if (balltype == -1)
            switch (difficulty)
            {
            case 0: // beginner
                balltype = 0;
                break;
            case 1: // intermediate
                balltype = (int)(4*Math.random());
                break;
            case 2: // pro
                balltype = (int)(2*Math.random())+2;
                // if they charge you...
                break;
            }

        if (difficulty == 2 && p2X-p2Diam/2 < battingCrease - (battingCrease-runningCrease)/4)
            balltype = 1;

        //drawPrompt("balltype="+balltype, 3);
        // now bowl it.
        switch (balltype)
        {
        case 0: // a basic ball
            if (p1X > runningCrease-p1Diam*5/6) p1L();
            else if (ballY < 200 && ballVY < 0) p1J();
            else p1S();
            break;

        case 1: // a rank full toss
            if (p1X > runningCrease-p1Diam*3/4) p1L();
            else p1S();
            if (ballY < 320 && ballVY < 0) p1J();
            break;

        case 2: // a bouncer
            if (ballVY > 0 && p1X > runningCrease-p1Diam*5/6) p1L();
            else p1S();
            if (ballY > 270 && ballVY > 0) p1J();
            break;

        case 3: // flat, good length
            if (p1X > runningCrease-p1Diam*2/3) p1L();
            else p1S();
            break;
    
        }
    }

    // field the ball! wow.
    private void field()
    {
        // a catch block (!)
        if (bounces == 0)
        {
            // bowler catch it?
            if (difficulty > 1)
                if (ballX > p1X && ballVX < 0 && ballY > p1Diam/2 && 
                    Math.sqrt((ballX-p1X)*(ballX-p1X) + (ballY-p1Y)*(ballY-p1Y)) < 250) p1J();

            // caught behind
            if (difficulty == 2)
                if (ballX > postPos && 
                    Math.sqrt((ballX-p3X)*(ballX-p3X) + (ballY-p3Y)*(ballY-p3Y)) < 250) p3J();
        }
        
        // should the wickie move?
        /*if (ballX > postPos && ballY < 2*p2Diam && difficulty > 1)
            p3J();
        */

        // move towards the ball, or push it towards the stumps.
        if (difficulty < 2 && !fP2Touched && ballbowled)
            p1S(); // don't follow the ball down the pitch after it has been bowled.
        else if (p1X+p1Diam/2 > ballX) p1L();
        else if (p1X + p1Diam + ballRad*3/2 < postPos) p1R();
        else if (((p2X+p2Diam/2 < battingCrease && p2X-p2Diam/2 > runningCrease) || p2Y != 0)
            && fP1Touched) // is the batsman out of his crease?
            p1R();
        else p1S();

        // should we jump over the ball instead of pushing it for four?!
        if (ballX > p1Diam && ballY < p1Diam/2 && ballVX <= 0 && !fHitBackWall && p1X-ballX < p1Diam && p1X > ballX && bounces > 0 && difficulty == 2)
            p1J();

    }

    // called when the batsman should hit the ball
    private void playball() // no, not as in baseball. play the ball, as in hit it! damn baseball
    {
        double dist = Math.sqrt((ballX-p2X)*(ballX-p2X) + (ballY-p2Y)*(ballY-p2Y));

        // also calc where the ball will pitch
        int pitch = 0;
        int frames = 0;
        int tempY = ballY;
        int tempVY = ballVY;
        while (tempY > 0)
        {
            frames++;
            tempY += --tempVY;
        }
        pitch = ballX + ballVX*frames; // this is the X where the ball lands.
        
        // can we reach the pitch of the ball?
        boolean reach = pitch < postPos - p2Diam && pitch >= p2X - frames*8;

        switch (difficulty)
        {
        case 0: // novice
            if (dist < 400 && ballX - p2X < p2Diam*3/2 && ballX < p2X && ballY < p2Y+p2Diam*3/2)
                p2L();
            else
                p2S();

            if (dist < 350 && ballY > p2Diam*2 && ballX > p2X-p2Diam)
                p2J();
            break;

        case 1: // state
        case 2: // international
            if (ballbowled && shottype == -1) // choose a shot type
            {
                // do we need to block? block a game out! muahahahahahaha
                if (p2Score > p1Score && inns == 2 && reach)
                    shottype = 1;
                else // try to score runs now then.
                {
                    if (reach && Math.random() < 0.5) // will hit a drive or block it.
                    {
                        if (Math.random() < 0.75)
                            shottype = 4; // half volley for six.
                        else
                            shottype = 1; // block
                    } else
                    {
                        if (pitch > battingCrease || Math.random() < 0.6)
                            shottype = 3;
                        else
                            shottype = 2;
                    }
                }
            }
                
            // OK. I know I screwed up some of these, where I have some minuses
            // where the should be plusses, but they seem to work as is,
            // so it's all good :)
            switch (shottype)
            {
            case 1: // block.
                if (ballbowled && p2X - p2XV - p2Diam/2 > pitch)
                    p2L();
                else
                    p2S();
                break;

            case 2: // half volley
                if (ballbowled && p2X - p2XV - p2Diam > pitch)
                    p2L();
                else
                {
                    p2S();
                    if (ballX > p2X-p2Diam*2/3)
                        p2J();
                }
                break;

            case 3: // full toss
                if (ballbowled && p2X + p2XV + 50 > pitch)
                    p2L();
                else
                {
                    p2S();
                    if (ballX > p2X-p2Diam/2)
                        p2J();
                }
                break;

            case 4: // straight drive... just a block with some side movement.
                if (ballbowled && (p2X - p2XV - p2Diam/2 > pitch || ballX+3*ballVX > p2X-p2Diam/2))
                    p2L();
                else
                    p2S();
                break;

                default: // do nothing.
                break;
            }
        }
    }

    // called when the batsman should be running.
    private void running()
    {
        // does the fielder have control of it?
        boolean controlled = false;
        if (ballX > postPos || ballX > p1X && (p1X-ballX < 400 || (p1X-ballX < 300 && ballVX > 0)))
            controlled = true;
        
        // too far away to get a run out
        if (ballX < runningCrease || (p1X < runningCrease && ballVX < 0 && ballX < battingCrease))
            controlled = false;

        // the batsman gets a head start in the run for a run out, going to the right.
        if (ballX < postPos && p1X < p2X && ballX > p2X && p2X-p2Diam/2 <= runningCrease)
            controlled = false;

        if (ballX < postPos && ballX-p2X > battingCrease-runningCrease)
            controlled = false;

        // now run if it's not controlled, or stay in the crease if it is.
        if (controlled && (p2X+p2Diam/2 >= battingCrease || p2X-p2Diam/2 <= runningCrease))
            p2S();
        else if (controlled)
        {
            // run back to nearest crease
            if (p2X > runningCrease + (battingCrease-runningCrease)/2 || difficulty < 2)
                p2R(); // run back to the crease if we have just blcoked or whatever.
            else
                p2L();
        }
        else if (!controlled && p2X-p2Diam/2 <= runningCrease && p2X == p2XMax)
            p2R(); // run to the right
        else if (!controlled && p2X+p2Diam/2 >= battingCrease && p2X >= p2XMin)
            p2L(); // run left.

    }

}


import java.awt.event.*;
import java.util.Calendar;

public class test extends tinyptc implements KeyListener, MouseListener, MouseMotionListener {

    public void main(int width,int height) {

        int size = width * height;
        int pixel[] = new int[size];
        int seed = 0x12345;

	int cnt = 0 ;

	long now = Calendar.getInstance().getTimeInMillis();

	addKeyListener( this ) ;
	addMouseListener( this ) ;
	addMouseMotionListener( this ) ;

        while (true) {

            for (int index=0; index<size; index++) {

                int noise = seed;
                noise >>= 3;
                noise ^= seed;
                int carry = noise & 1;
                noise >>= 1;
                seed >>= 1;
                seed |= (carry << 30);
                noise &= 0xFF;

                pixel[index] = (noise<<16) | (noise<<8) | noise;

            }
            update(pixel);
	    cnt++ ;

	    if ( cnt % 100 == 0 ) {
		long dur = Calendar.getInstance().getTimeInMillis() - now ;
		System.out.println ( "fps = " + 1000.0*(100.0/dur) ) ;
		now = Calendar.getInstance().getTimeInMillis() ;
	    }
	}
    }

    public void keyTyped(KeyEvent e) {
        displayInfo(e, "KEY TYPED: ");
    }
    
    public void keyPressed(KeyEvent e) {
        displayInfo(e, "KEY PRESSED: ");
    }
    
    public void keyReleased(KeyEvent e) {
        displayInfo(e, "KEY RELEASED: ");
    }

    public void mousePressed(MouseEvent e) {
       saySomething("Mouse pressed; # of clicks: " + e.getClickCount(), e);
    }

    public void mouseReleased(MouseEvent e) {
       saySomething("Mouse released; # of clicks: " + e.getClickCount(), e);
    }

    public void mouseEntered(MouseEvent e) {
       saySomething("Mouse entered", e);
    }

    public void mouseExited(MouseEvent e) {
       saySomething("Mouse exited", e);
    }

    public void mouseClicked(MouseEvent e) {
       saySomething("Mouse clicked (# of clicks: " + e.getClickCount() + ")", e);
    }

    public void mouseMoved(MouseEvent e) {
       saySomething_move("Mouse moved", e);
    }

    public void mouseDragged(MouseEvent e) {
       saySomething_move("Mouse dragged", e);
    }

    void saySomething(String eventDescription, MouseEvent e) {
        System.out.println(eventDescription + " detected on " + e.getComponent().getClass().getName() + ".\n");
    }

    void saySomething_move(String eventDescription, MouseEvent e) {
         System.out.println(eventDescription + " (" + e.getX() + "," + e.getY() + ")" + " detected on " + e.getComponent().getClass().getName() + "\n");
    }

    private void displayInfo(KeyEvent e, String keyStatus){
        
        int id = e.getID();

        String keyString;

	keyString = keyStatus + " " ;

        if (id == KeyEvent.KEY_TYPED) {
            char c = e.getKeyChar();
            keyString += "key character = '" + c + "'";
        }
	else {
            int keyCode = e.getKeyCode();
            keyString += "key code = " + keyCode + " (" + KeyEvent.getKeyText(keyCode) + ")";
        }

	System.out.println( keyString ) ;
    }
}

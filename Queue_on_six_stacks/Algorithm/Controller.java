package Algorithm;

import java.awt.event.*;

class Controller implements ActionListener, WindowListener, MouseListener
{
    private boolean open, start;
    private String what;

    Controller()
    {
        open = true;
		start = false;
        what = new String("");
    }

	synchronized public void mouseClicked(MouseEvent event)
	{
		start = true;
	}

	public void mousePressed(MouseEvent event) {}
	public void mouseReleased(MouseEvent event) {}
	public void mouseExited(MouseEvent event) {}
	public void mouseEntered(MouseEvent event) {}

    synchronized public void actionPerformed(ActionEvent event)
    {
        what = event.getActionCommand();
    }

    public void windowClosing(WindowEvent event) 
    {
        open = false;

        System.exit(0);
    }

    public void windowOpened(WindowEvent event) {}
    public void windowClosed(WindowEvent event) {}
    public void windowIconified(WindowEvent event) {}
    public void windowDeiconified(WindowEvent event) {}
    public void windowActivated(WindowEvent event) {}
    public void windowDeactivated(WindowEvent event) {}

    boolean isOpen()
    {
        return open;
    }

    synchronized String getWhat()
    {
        return what;
    }

    synchronized void clear()
    {
        what = "";
    }

	synchronized boolean isStart()
	{
		return start;
	}
}

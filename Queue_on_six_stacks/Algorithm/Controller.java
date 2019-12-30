package Algorithm;

import java.awt.event.*;
import javax.swing.*;

class Controller implements ActionListener, WindowListener, MouseListener, ItemListener
{
    private boolean open, start, showCode;
    private String what;

    Controller()
    {
        open = true;
		start = false;
		showCode = false;

        what = new String("");
    }

	synchronized public void itemStateChanged(ItemEvent event)
	{
		showCode = showCode ? false : true;
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

    synchronized public void windowClosing(WindowEvent event) 
    {
        JFrame frame = (JFrame)event.getSource();
		String name = frame.getTitle();
		
		if (name.equals("Queue on six stacks"))
		{
			open = false;
			System.exit(0);
		}
		else if (name.equals("Pseudocode"))
		{
			showCode = false;
		}
	}

	public void windowOpened(WindowEvent event) {}
	public void windowClosed(WindowEvent event) {}
	public void windowIconified(WindowEvent event) {}
	public void windowDeiconified(WindowEvent event) {}
	public void windowActivated(WindowEvent event) {}
	public void windowDeactivated(WindowEvent event) {}

	synchronized void setShowCode(boolean show)
	{
		showCode = show;
	}

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

	synchronized boolean isShowCode()
	{
		return showCode;
	}
}

package Algorithm;

import java.awt.*;
import javax.swing.*;

@SuppressWarnings("serial")
class Menu extends JPanel
{
    private JFrame frame;
	private Pane pane;
    private Controller controller;

	private int posx, posy;
	private String header, info;

    Menu(JFrame frame, Pane pane, Controller controller)
    {
		this.frame = frame;
		this.pane = pane;
        this.controller = controller;
		
		setBounds(0, 0, 800, 600);

		addMouseListener(controller);

        init();

		pane.add(this, 10);
    }

    void init()
    {
		posx = posy = 0;
		header = new String("Queue on six stacks");
		info = new String("Click to continue");
    }

	void open()
	{
		while (posy > -600)
		{
            try
            {
                Thread.sleep(5);
            }
            catch (InterruptedException ex)
            {
                System.out.println("Error: " + ex);
            }

			posy -= 4;			
		}
	}

    public void paint(Graphics g)
    {
        g.setColor(new Color(20, 20, 20));
        g.fillRect(posx, posy, 800, 600);

        g.setColor(new Color(230, 230, 230));
        g.setFont(new Font(Font.SERIF, Font.PLAIN, 50));
        g.drawString(header, posx + 150, posy + 270);
        
		g.setColor(new Color(210, 210, 210));
        g.setFont(new Font(Font.SERIF, Font.PLAIN, 15));
        g.drawString(info, posx + 335, posy + 300);
    }
}

package Algorithm;

import java.util.*;
import java.awt.*;
import javax.swing.*;

@SuppressWarnings("serial")
class Pane extends JLayeredPane
{
    private JPanel inter, menu;

    Pane() {}
	
	void setMenu(JPanel menu)
	{
		this.menu = menu;
	}

	void setInter(JPanel inter)
	{
		this.inter = inter;
	}

    public void paint(Graphics g)
    {
		inter.paint(g);
		super.paint(g);
		menu.paint(g);
    }
}

package Algorithm;

import java.awt.*;

class DrawableStack
{
    private class Node
    {
        Element val;
        Node next;

        int posx, posy;

        Node()
        {
            val = null;
            next = null;
            posx = posy = 0;
        }

        Node(Element val, int posx, int posy)
        {
            this.posx = posx;
            this.posy = posy;

            this.val = val;
            next = null;
        }
    }

    private int amount;
    private Node head;
    private int initx, inity, emptyx, emptyy, posx, posy;
    private String name;
    private int fontSize;

    DrawableStack(String name, int posx, int posy) 
    {
        this.posx = initx = emptyx = posx;
        this.posy = inity = emptyy = posy;
        this.name = name;

        fontSize = 15;

        amount = 0;
        head = null;
    }

	void swap(DrawableStack stack)
	{
		int fromy, toy;

		fromy = posy;
		toy = stack.posy;

		int localSpeed = Element.getSpeed();
		
		float steps = (float)Math.abs(toy - posy) / (float)localSpeed;

		int deltay = toy - posy;
		float stepy = (float)deltay / steps;

		for (int i = 0; i < (int)steps; i++)
		{
			if (localSpeed != Element.getSpeed())
			{
				i = 0;
				
				steps = (float)Math.abs(toy - posy) / (float)Element.getSpeed();
				deltay = toy - posy;
				stepy = (float)deltay / steps;

				localSpeed = Element.getSpeed();
			}
            
			try
            {
                Thread.sleep(20);
            }
            catch (InterruptedException ex)
            {
                System.out.println("Error: " + ex);
            }

			posy += stepy;
			stack.posy -= stepy;
		}

		Node tmpn = stack.head;
		stack.head = head;
		head = tmpn;

		int tmpi = stack.amount;
		stack.amount = amount;
		amount = tmpi;

		posy = toy;
		stack.posy = fromy;

		tmpi = stack.emptyy;
		stack.emptyy = emptyy;
		emptyy = tmpi;
	}

	void push(Element val)
	{
		if (amount == 0)
		{
			Node node = new Node(val, posx, posy);
			head = node;
		}
		else
		{
			Node node = new Node(val, head.posx + (int)(val.getWidth() * 0.9), posy);
			node.next = head;
			head = node;
		}

		amount++;

		head.val.move(head.posx, head.posy);
		head.val.setOuterColor(new Color(13, 87, 123));
	}

	void pop()
	{
		if (amount == 0)
		{
			return;
		}

		head.val.setOuterColor(new Color(181, 73, 14));
		head.val.move(600 + head.val.getWidth(), head.posy);

		head = head.next;

		amount--;
	}

	Element top()
	{
		return head.val;
	}

	int size()
	{
		return amount;
	}

	boolean empty()
	{
		return amount == 0 ? true : false;
	}

	void clear()
	{
		amount = 0;
		head = null;

		emptyy = inity;
		posy = inity;
	}

	private void paint(Graphics g, Node node)
	{
		if (node == null)
		{
			return;
		}

		paint(g, node.next);

		node.val.paint(g);
	}

	void paint(Graphics g)
	{
		g.setColor(new Color(230, 230, 230));
		g.setFont(new Font(Font.SERIF, Font.PLAIN, fontSize));
		g.drawString(name, posx, posy - fontSize / 3);
		
		if (amount == 0)
		{
			g.setFont(new Font(Font.SERIF, Font.PLAIN, fontSize - 2));
			g.drawString("Empty", emptyx + 15, emptyy + 15 + fontSize);
		}

		paint(g, head);
	}
}

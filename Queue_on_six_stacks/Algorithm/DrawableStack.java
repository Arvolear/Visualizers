package Algorithm;

import java.awt.*;
import java.util.Vector;

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

		Node(Node other)
		{
			val = new Element(other.val);
			next = null;
			posx = other.posx;
			posy = other.posy;
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

	DrawableStack(DrawableStack other)
	{
		amount = other.amount;
		initx = other.initx;
		inity = other.inity;
		emptyx = other.emptyx;
		emptyy = other.emptyy;
		posx = other.posx;
		posy = other.posy;
		name = new String(other.name);
		fontSize = other.fontSize;
		head = null;

		Node otherCurr = other.head;

		while (otherCurr != null)
		{
			if (head != null)
			{
				Node curr = new Node(otherCurr);
				curr.next = head;
				head = curr;
			}
			else
			{
				head = new Node(otherCurr);
			}

			otherCurr = otherCurr.next;
		}
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

	void prepClear(Vector < Thread > clearer)
	{
		Node cur = head;
		
		while (cur != null)
		{
			clearer.add(new Thread(new ElementClearer(cur.val)));
			clearer.get(clearer.size() - 1).start();

			cur = cur.next;
		}
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

	Node getHead()
	{
		return head;
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

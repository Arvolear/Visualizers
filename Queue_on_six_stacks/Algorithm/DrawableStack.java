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
    private int posx, posy;
    private String name;
    private int fontSize;

    DrawableStack(String name, int posx, int posy) 
    {
        this.posx = posx;
        this.posy = posy;
        this.name = name;

        fontSize = 15;

        amount = 0;
        head = null;
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

    void paint(Graphics g)
    {
        g.setColor(new Color(230, 230, 230));
        g.setFont(new Font(Font.SERIF, Font.PLAIN, fontSize));
        g.drawString(name, posx, posy - fontSize / 3);

        Node cur = head;

        while (cur != null)
        {
            cur.val.paint(g);

            cur = cur.next;
        }
    }
}

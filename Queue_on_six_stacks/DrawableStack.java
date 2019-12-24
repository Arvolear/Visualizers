import java.util.*;
import java.awt.*;
import javax.swing.*;

class DrawableStack<T>
{
    private String name;
    private int posX, posY;
    private Color outerColor, innerColor;
    private int width, height;

    private class Cell
    {
        Rectangle outer;
        Rectangle inner;

        String number;
        int fontSize;
    }

    private Vector < Cell > cells;

    DrawableStack(String name, int x, int y, int w, int h, Color outer, Color inner)
    {
        this.name = name;
        posX = x;
        posY = y;

        width = w;
        height = h;

        outerColor = outer;
        innerColor = inner;

        cells = new Vector<Cell>();
    }

    void construct(Stack<T> stack)
    {
        cells.clear();

        Iterator<T> it = stack.iterator();
        int counter = 0;

        if (stack.empty())
        {
            Cell cell = new Cell();

            cell.outer = new Rectangle(posX, posY, width, height);
            cell.inner = new Rectangle((int)(posX + width * 0.1), posY + (int)(height * 0.1), (int)(width * 0.8), (int)(height * 0.8));
            cell.number = new String("");
            cell.fontSize = 20;

            cells.add(cell);
        }

        while (it.hasNext())
        {
            Cell cell = new Cell();

            cell.outer = new Rectangle(posX + counter * width, posY, width, height);
            cell.inner = new Rectangle((int)(posX + width * 0.1) + counter * width, posY + (int)(height * 0.1), (int)(width * 0.8), (int)(height * 0.8));
            cell.number = new String(it.next().toString());
            cell.fontSize = 20;

            cells.add(cell);

            counter++;
        }
    }

    void paint(Graphics g)
    {
        int headFont = 15;

        g.setColor(new Color(230, 230, 230));
        g.setFont(new Font(Font.SERIF, Font.PLAIN, headFont));
        g.drawString(name, (int)cells.get(0).outer.getX(), (int)cells.get(0).outer.getY() - headFont / 3);

        for (int i = 0; i < cells.size(); i++)
        {
            g.setColor(outerColor);
            g.fillRect((int)cells.get(i).outer.getX(), (int)cells.get(i).outer.getY(), (int)cells.get(i).outer.getWidth(), (int)cells.get(i).outer.getHeight());

            g.setColor(innerColor);
            g.fillRect((int)cells.get(i).inner.getX(), (int)cells.get(i).inner.getY(), (int)cells.get(i).inner.getWidth(), (int)cells.get(i).inner.getHeight());

            g.setColor(new Color(230, 230, 230));
            g.setFont(new Font(Font.SERIF, Font.PLAIN, cells.get(i).fontSize));
            g.drawString(cells.get(i).number, (int)cells.get(i).outer.getX() + (int)cells.get(i).outer.getWidth() / 2 - cells.get(i).fontSize / 3, (int)cells.get(i).outer.getY() + (int)cells.get(i).outer.getHeight() / 2 + cells.get(i).fontSize / 3);
        }
    }
}

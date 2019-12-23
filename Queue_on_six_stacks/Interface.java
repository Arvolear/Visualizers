import java.util.*;
import java.awt.*;
import javax.swing.*;

@SuppressWarnings("serial")
class Interface extends JPanel
{
    private DrawableStack<Integer> DS;
    private DrawableStack<Integer> DS1;

    Interface()
    {
        Stack<Integer> st = new Stack<Integer>();
        st.push(1);
        st.push(3);
        st.push(2);
        st.push(4);
        st.push(6);
        st.push(5);

        DS = new DrawableStack<Integer>(50, 50, 50, 50, new Color(40, 90, 199), new Color(232, 179, 44));
        DS1 = new DrawableStack<Integer>(80, 150, 50, 50, new Color(40, 90, 199), new Color(232, 179, 44));

        DS.construct(st);
        DS1.construct(st);
    }

    public void paint(Graphics g)
    {
        DS.paint(g); 
        DS1.paint(g); 
    }

    public static void play()
    {
        JFrame frame = new JFrame();
        
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setBounds(20, 20, 500, 500);
        frame.setVisible(true);

        frame.add(new Interface());
    }
}

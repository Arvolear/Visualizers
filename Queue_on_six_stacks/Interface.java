import java.util.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

@SuppressWarnings("serial")
class Interface extends JPanel
{
    private Queue6 < Integer > queue;
    private Vector < DrawableStack < Integer > > stacks;
    private JFrame frame;

    private class Info
    {
        private JPanel infoPanel;
        private JLabel copying, isCopied, toCopy;
        
        Info() 
        {
            infoPanel = new JPanel();
            copying = new JLabel();
            isCopied = new JLabel();
            toCopy = new JLabel();
        }

        void init()
        {
            if (queue.getCopying())
            {
                copying.setText("Copying: True");
            }
            else
            {
                copying.setText("Copying: False");
            }

            if (queue.getOutputIsCopied())
            {
                isCopied.setText("OutputIsCopied: True");
            }
            else
            {
                isCopied.setText("OutputIsCopied: False");
            }

            toCopy.setText("OutputToCopy: " + queue.getOutputToCopy().toString());

            infoPanel.setBounds(600, 20, 200, 100);
            infoPanel.setOpaque(false);
            
            copying.setBackground(new Color(100, 100, 100));
            copying.setForeground(new Color(230, 230, 230));
            
            isCopied.setBackground(new Color(100, 100, 100));
            isCopied.setForeground(new Color(230, 230, 230));
            
            toCopy.setBackground(new Color(100, 100, 100));
            toCopy.setForeground(new Color(230, 230, 230));

            infoPanel.add(copying);
            infoPanel.add(isCopied);
            infoPanel.add(toCopy);

            frame.add(infoPanel);
        }

        void update()
        {
            if (queue.getCopying())
            {
                copying.setText("Copying: True");
            }
            else
            {
                copying.setText("Copying: False");
            }

            if (queue.getOutputIsCopied())
            {
                isCopied.setText("OutputIsCopied: True");
            }
            else
            {
                isCopied.setText("OutputIsCopied: False");
            }

            toCopy.setText("OutputToCopy: " + queue.getOutputToCopy().toString());
        }
    }

    private class Grid implements ActionListener
    {
        private JPanel pushPanel;
        private JPanel popPanel;
        private Rectangle field;
        private Color fieldColor;
        private JButton push, pop;
        private JTextField pushText;
        private JLabel pushLabel;
        private JLabel popLabel;

        Grid(Color color)
        {
            pushPanel = new JPanel();
            popPanel = new JPanel();
            fieldColor = color;

            field = new Rectangle(600, 0, 200, 600);
            
            push = new JButton("Push");
            pop = new JButton("Pop");

            pushText = new JTextField(9);
            pushText.setActionCommand("pushText");

            pushLabel = new JLabel("Push an element");
            popLabel = new JLabel("Pop an element");
        }

        void init()
        {
            /* PUSH */

            pushPanel.setBounds(625, 100, 150, 100);
            pushPanel.setOpaque(false);

            pushText.setBackground(new Color(100, 100, 100));
            pushText.setForeground(new Color(230, 230, 230));
           
            push.addActionListener(this);
            push.setBackground(new Color(100, 100, 100));
            push.setForeground(new Color(230, 230, 230));

            pushLabel.setBackground(new Color(100, 100, 100));
            pushLabel.setForeground(new Color(230, 230, 230));
            
            pushPanel.add(pushLabel);
            pushPanel.add(pushText);
            pushPanel.add(push);
            
            frame.add(pushPanel);

            /* POP */

            popPanel.setBounds(625, 200, 150, 100);
            popPanel.setOpaque(false);

            pop.addActionListener(this);
            pop.setBackground(new Color(100, 100, 100));
            pop.setForeground(new Color(230, 230, 230));

            popLabel.setBackground(new Color(100, 100, 100));
            popLabel.setForeground(new Color(230, 230, 230));
            
            popPanel.add(popLabel);
            popPanel.add(pop);

            frame.add(popPanel);
        }

        public void actionPerformed(ActionEvent event)
        {
            String what = event.getActionCommand();

            if (what.equals("Push"))
            {
                if (pushText.getText().equals(""))
                {
                    return; 
                }
                else
                {
                    queue.push(Integer.parseInt(pushText.getText()));
                }
            }
            else if (what.equals("Pop"))
            {
                if (!queue.empty())
                {
                    queue.pop();
                }
            }

            update();
        }

        void paint(Graphics g)
        {
            g.setColor(fieldColor);
            g.fillRect((int)field.getX(), (int)field.getY(), (int)field.getWidth(), (int)field.getHeight());
        }
    }

    private Grid grid;
    private Info info;

    Interface()
    {
        queue = new Queue6 < Integer >();
        stacks = new Vector < DrawableStack < Integer > >();
        grid = new Grid(new Color(50, 50, 50));
        info = new Info();
        
        frame = new JFrame();
        
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(800, 600);
        frame.setVisible(true);

        grid.init();
        info.init();
        
        frame.add(this);
    }

    void init()
    {
        DrawableStack < Integer > output = new DrawableStack < Integer >("Output", 20, 30, 50, 50, new Color(181, 73, 14), new Color(24, 136, 191));
        output.construct(queue.getOutput());
        stacks.add(output);
        
        DrawableStack < Integer > outputCopy = new DrawableStack < Integer >("OutputCopy", 20, 125, 50, 50, new Color(181, 73, 14), new Color(24, 136, 191));
        outputCopy.construct(queue.getOutputCopy());
        stacks.add(outputCopy);
        
        DrawableStack < Integer > outputHelper = new DrawableStack < Integer >("OutputHelper", 20, 220, 50, 50, new Color(181, 73, 14), new Color(24, 136, 191));
        outputHelper.construct(queue.getOutputHelper());
        stacks.add(outputHelper);
        
        DrawableStack < Integer > tmpStorage = new DrawableStack < Integer >("TmpStorage", 20, 315, 50, 50, new Color(181, 73, 14), new Color(24, 136, 191));
        tmpStorage.construct(queue.getTmpStorage());
        stacks.add(tmpStorage);
        
        DrawableStack < Integer > input = new DrawableStack < Integer >("Input", 20, 410, 50, 50, new Color(181, 73, 14), new Color(24, 136, 191));
        input.construct(queue.getInput());
        stacks.add(input);
        
        DrawableStack < Integer > inputHelper = new DrawableStack < Integer >("InputHelper", 20, 505, 50, 50, new Color(181, 73, 14), new Color(24, 136, 191));
        inputHelper.construct(queue.getInputHelper());
        stacks.add(inputHelper);
    }

    void update()
    {
        stacks.get(0).construct(queue.getOutput());
        stacks.get(1).construct(queue.getOutputCopy());
        stacks.get(2).construct(queue.getOutputHelper());
        stacks.get(3).construct(queue.getTmpStorage());
        stacks.get(4).construct(queue.getInput());
        stacks.get(5).construct(queue.getInputHelper());

        info.update();

        SwingUtilities.updateComponentTreeUI(frame);
    }

    public void paint(Graphics g)
    {
        g.setColor(new Color(30, 30, 30));
        g.fillRect(0, 0, 800, 600);

        for (int i = 0; i < stacks.size(); i++)
        {
            stacks.get(i).paint(g);
        }

        grid.paint(g);
    }
}

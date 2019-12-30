package Algorithm;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

class Grid
{
    private Rectangle field;
    private Color fieldColor;
    
    private JPanel pushPanel;
    private JPanel popPanel;
    private JPanel infoPanel;
    private JPanel speedPanel;
     
    private JButton push, pop;
    
    private JTextField pushText;
    
    private JLabel pushLabel, popLabel;
    private JLabel copyingLabel, isCopiedLabel, toCopyLabel;

    private JSlider speedSlider;
    private JLabel speedLabel;

	private JLayeredPane pane;
	private Controller controller;
	private Sueue queue;

	Grid(JLayeredPane pane, Controller controller, Sueue queue)
	{
		this.pane = pane;
		this.controller = controller;
		this.queue = queue;

		pushPanel = new JPanel();
		popPanel = new JPanel();
		fieldColor = new Color(50, 50, 50);

		field = new Rectangle(600, 0, 200, 600);

		push = new JButton("Push");
		pop = new JButton("Pop");

		pushText = new JTextField(9);
		pushText.setActionCommand("pushText");

		pushLabel = new JLabel("Push an element");
		popLabel = new JLabel("Pop an element");

		infoPanel = new JPanel();
		copyingLabel = new JLabel();
		isCopiedLabel = new JLabel();
		toCopyLabel = new JLabel();

		speedPanel = new JPanel();
		speedLabel = new JLabel("Speed controller", SwingConstants.CENTER);
		speedSlider = new JSlider(JSlider.HORIZONTAL, 1, 15, 4);
	}

	void init()
	{
		/* PUSH */

		pushPanel.setBounds(625, 100, 150, 100);
		pushPanel.setOpaque(false);

		pushText.addKeyListener(new KeyAdapter() 
				{
					public void keyTyped(KeyEvent event) 
					{ 
						if (pushText.getText().length() >= 2)
						{
							event.consume(); 
						}
					}  
				});

		pushText.setBackground(new Color(100, 100, 100));
		pushText.setForeground(new Color(230, 230, 230));

		push.addActionListener(controller);
		push.setBackground(new Color(100, 100, 100));
		push.setForeground(new Color(230, 230, 230));

		pushLabel.setBackground(new Color(100, 100, 100));
		pushLabel.setForeground(new Color(230, 230, 230));

		pushPanel.add(pushLabel);
		pushPanel.add(pushText);
		pushPanel.add(push);

		pushPanel.setVisible(false);

		pane.add(pushPanel, 10);

		/* POP */

		popPanel.setBounds(625, 200, 150, 100);
		popPanel.setOpaque(false);

		pop.addActionListener(controller);
		pop.setBackground(new Color(100, 100, 100));
		pop.setForeground(new Color(230, 230, 230));

		popLabel.setBackground(new Color(100, 100, 100));
		popLabel.setForeground(new Color(230, 230, 230));

		popPanel.add(popLabel);
		popPanel.add(pop);
		
		popPanel.setVisible(false);

		pane.add(popPanel, 10);

		/* INFO */

		if (queue.getCopying())
		{
			copyingLabel.setText("Copying: True");
		}
		else
		{
			copyingLabel.setText("Copying: False");
		}

		if (queue.getOutputIsCopied())
		{
			isCopiedLabel.setText("OutputIsCopied: True");
		}
		else
		{
			isCopiedLabel.setText("OutputIsCopied: False");
		}

		toCopyLabel.setText("OutputToCopy: " + queue.getOutputToCopy().toString());

		infoPanel.setBounds(600, 20, 200, 100);
		infoPanel.setOpaque(false);

		copyingLabel.setBackground(new Color(100, 100, 100));
		copyingLabel.setForeground(new Color(230, 230, 230));

		isCopiedLabel.setBackground(new Color(100, 100, 100));
		isCopiedLabel.setForeground(new Color(230, 230, 230));

		toCopyLabel.setBackground(new Color(100, 100, 100));
		toCopyLabel.setForeground(new Color(230, 230, 230));

		infoPanel.add(copyingLabel);
		infoPanel.add(isCopiedLabel);
		infoPanel.add(toCopyLabel);
		
		infoPanel.setVisible(false);

		pane.add(infoPanel, 10);

		/* SPEED */

		speedPanel.setBounds(625, 500, 150, 70);
		speedPanel.setLayout(new BorderLayout());
		speedPanel.setOpaque(false);

		speedSlider.setMinorTickSpacing(1);
		speedSlider.setMajorTickSpacing(7);

		speedSlider.setBackground(new Color(50, 50, 50));
		speedSlider.setForeground(new Color(230, 230, 230));

		speedSlider.setPaintTicks(true);
		speedSlider.setPaintLabels(true);

		speedLabel.setBackground(new Color(100, 100, 100));
		speedLabel.setForeground(new Color(230, 230, 230));

		speedPanel.add(speedLabel, BorderLayout.PAGE_START);
		speedPanel.add(speedSlider);
		
		speedPanel.setVisible(false);

		pane.add(speedPanel, 10);
	}

	void update()
	{
		if (queue.getCopying())
		{
			copyingLabel.setText("Copying: True");
		}
		else
		{
			copyingLabel.setText("Copying: False");
		}

		if (queue.getOutputIsCopied())
		{
			isCopiedLabel.setText("OutputIsCopied: True");
		}
		else
		{
			isCopiedLabel.setText("OutputIsCopied: False");
		}

		toCopyLabel.setText("OutputToCopy: " + queue.getOutputToCopy().toString());
	}

	void unhide()
	{
		pushPanel.setVisible(true);
		popPanel.setVisible(true);
		infoPanel.setVisible(true);
		speedPanel.setVisible(true);
	}

	void paint(Graphics g)
	{
		g.setColor(fieldColor);
		g.fillRect((int)field.getX(), (int)field.getY(), (int)field.getWidth(), (int)field.getHeight());
	}

	String getPushText()
	{
		return pushText.getText();
	}

	Integer getSpeed()
	{
		return speedSlider.getValue();
	}
}

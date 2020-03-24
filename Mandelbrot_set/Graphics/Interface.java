package Graphics;

import Algorithm.*;

import java.awt.*;
import javax.swing.*;
import java.awt.event.*;

@SuppressWarnings("serial")
public class Interface extends JPanel implements KeyListener
{
	private static int WINDOW_WIDTH = 720;
	private static int WINDOW_HEIGHT = 509;

	private Dimension renderSize;
	private JFrame frame;

	private Fractal fractal;

	public Interface()
	{
		frame = new JFrame("Zoomer");

		renderSize = new Dimension(WINDOW_WIDTH, WINDOW_HEIGHT);

		setLayout(null);
		setFocusable(true);
		addKeyListener(this);


		fractal = new Fractal(new Mandelbrot());


		frame.setSize(renderSize);
		frame.setLocation(100, 50);
		frame.setResizable(false);
		
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

		frame.add(this);
		frame.setVisible(true);
	}

	@Override
	public void keyTyped(KeyEvent event) {}
	
	@Override
	public void keyReleased(KeyEvent event) {}
	
	@Override
	public void keyPressed(KeyEvent event) 
	{
		Point point = MouseInfo.getPointerInfo().getLocation();
		point.x -= frame.getLocationOnScreen().x;
		point.y -= frame.getLocationOnScreen().y;

		if (!fractal.isCompleted())
		{
			return;
		}

		if (point.y < 30 || point.y >= WINDOW_HEIGHT || point.x < 0 || point.y >= WINDOW_WIDTH)
		{
			return;
		}

		point.y -= 30;

		System.out.println(point.x + " " + point.y);

		if (event.getKeyCode() == KeyEvent.VK_EQUALS)
		{
			System.out.println("Zoomin");
			
			fractal.zoomIn(point);
			play();
		}

		if (event.getKeyCode() == KeyEvent.VK_MINUS)
		{
			System.out.println("Zoomout");

			fractal.zoomOut();
			play();
		}
	}

	public void play()
	{
		fractal.compute();

		Thread drawer = new Thread(new Runnable()
		{
			@Override
			public void run()
			{
				while (!fractal.isCompleted())
				{
					frame.invalidate();
					frame.repaint();
				}
			}
		});

		drawer.start();
	}

	@Override
	public void paintComponent(Graphics g)
	{
		super.paintComponent(g);
		g.drawImage(fractal.getImage(), 0, 0, this);
	}

	Dimension getRenderSize()
	{
		return renderSize;
	}

	JFrame getFrame()
	{
		return frame;
	}
}

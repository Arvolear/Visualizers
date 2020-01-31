package Algorithm;

import java.util.Vector;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

class Pseudocode extends JPanel implements MouseWheelListener
{
	private JFrame mainFrame, frame;
	private Controller controller;

	private int speed;
	private int posx, posy;
	private int fontSize;

	private JScrollBar scrollBar;

	private int curShow;
	private Vector < String > code;

	Pseudocode(JFrame mainFrame, Controller controller)
	{
		this.controller = controller;
		this.mainFrame = mainFrame;

		posx = 10;
		posy = 30;
		fontSize = 10;

		curShow = -1;

		code = new Vector < String >();
		scrollBar = new JScrollBar();

		frame = new JFrame("Pseudocode");
		frame.setSize(320, 500);
		frame.setLocation(mainFrame.getLocation().x + 800, mainFrame.getLocation().y);
		frame.addWindowListener(controller);
		frame.setResizable(false);

		addMouseWheelListener(this);
	}

	public void mouseWheelMoved(MouseWheelEvent event)
	{
		scrollBar.setValue(scrollBar.getValue() + (event.getWheelRotation() * 10));
	}

	void init()
	{
		frame.setVisible(false);
		scrollBar.setMinimum(0);
		scrollBar.setMaximum(435);
		scrollBar.setBounds(305, -2, 15, 475);
		scrollBar.setBackground(new Color(50, 50, 50));
		scrollBar.setForeground(new Color(230, 230, 230));

		code.add("Queue on six stacks pseudocode");

		code.add(" 1. void checkCopy() {");
		code.add(" 2.     copying = input.size > output.size();");
		code.add(" 3.     if (copying) {");
		code.add(" 4.         toCopy = output.size();");
		code.add(" 5.         copied = false;");
		code.add(" 6.         performCopy();");
		code.add(" 7.     }");
		code.add(" 8. }");
		code.add(" 9.");

		code.add("10. void performCopy() {");
		code.add("11.     limit = 3;");
		code.add("12.     while (!copied && limit > 0 && !output.empty()) {");
		code.add("13.         elem = output.top();");
		code.add("14.         tmpStorage.push(elem);");
		code.add("15.         output.pop();");
		code.add("16.         limit--;");
		code.add("17.     }");
		code.add("18.");
		code.add("19.     while (limit > 0 && !input.empty()) {");
		code.add("20.         copied = true;");
		code.add("21.         elem = input.top();");
		code.add("22.         output.push(elem);");
		code.add("23.         outputHelper.push(elem);");
		code.add("24.         input.pop();");
		code.add("25.         limit--;");
		code.add("26.     }");
		code.add("27.");
		code.add("28.     while (limit > 0 && !tmpStorage.empty() {");
		code.add("29.         if (toCopy > 0) {");
		code.add("30.             elem = tmpStorage.top();");
		code.add("31.             output.push(elem);");
		code.add("32.             outputHelper.push(elem);");
		code.add("33.             toCopy--;");
		code.add("34.         }");
		code.add("35.         tmpStorage.pop();");
		code.add("36.         limit--;");
		code.add("37.     }");
		code.add("38.");
		code.add("39.     if (tmpStorage.empty()) {");
		code.add("40.         swap(input, inputHelper);");
		code.add("41.         swap(outputCopy, outputHelper);");
		code.add("42.     }");
		code.add("43.     copying = !tmpStorage.empty();");
		code.add("44. }");
		code.add("45.");

		code.add("46. void push(String elem) {");
		code.add("47.     if (!copying) {");
		code.add("48.         input.push(elem);");
		code.add("49.         if (!outputHelper.empty()) {");
		code.add("50.             outputHelper.pop();");
		code.add("51.         }");
		code.add("52.         checkCopy();");
		code.add("53.     }");
		code.add("54.     else {");
		code.add("55.         inputHelper.push(elem);");
		code.add("56.         performCopy();");
		code.add("57.     }");
		code.add("58. }");
		code.add("59.");
		
		code.add("60. void pop() {");
		code.add("61.     if (!copying) {");
		code.add("62.         output.pop();");
		code.add("63.         outputCopy.pop();");
		code.add("64.         if (!outputHelper.empty()) {");
		code.add("65.             outputHelper.pop();");
		code.add("66.         }");
		code.add("67.         checkCopy();");
		code.add("68.     }");
		code.add("69.     else {");
		code.add("70.         outputCopy.pop();");
		code.add("71.         if (toCopy > 0) {");
		code.add("72.             toCopy--;");
		code.add("73.         }");
		code.add("74.         else {");
		code.add("75.             output.pop();");
		code.add("76.             outputHelper.pop();");
		code.add("77.         }");
		code.add("78.         performCopy();");
		code.add("79.     }");
		code.add("80. }");
		code.add("81.");

		code.add("82. String front() {");
		code.add("83.     if (!copying)");
		code.add("84.         return output.top();");
		code.add("85.     return outputCopy.top();");
		code.add("86. }");

		frame.add(scrollBar);
		frame.add(this);
	}

	void toggle(boolean action)
	{
		if (frame.isVisible() != action)
		{
			frame.setVisible(action);

			if (action)
			{
				frame.setLocation(mainFrame.getLocation().x + 800, mainFrame.getLocation().y);
			}
		}
	}

	void showLine(int line)
	{
		if (!frame.isVisible())
		{
			return;
		}

		curShow = line;
		
		scrollBar.setValue(line * 10 - 200);
	
		if (curShow != -1)
		{
			try
			{
				Thread.sleep(Math.min(1500, 5000 / (speed + speed)));
			}
			catch (InterruptedException ex)
			{
				System.out.println("Error: " + ex);
			}
		}
	}

	public void paint(Graphics g)
	{
		g.setColor(new Color(50, 50, 50));
		g.fillRect(0, 0, 320, 500);	

		g.setColor(new Color(230, 230, 230));
		g.setFont(new Font(Font.SERIF, Font.PLAIN, 15));
		g.drawString(code.get(0), posx + 25, posy - scrollBar.getValue() - 10);

		for (int i = 1; i < code.size(); i++)
		{
			if (i == curShow)
			{
				g.setColor(new Color(98, 155, 100));
			}
			else
			{
				g.setColor(new Color(230, 230, 230));
			}

			g.setFont(new Font(Font.SERIF, Font.PLAIN, fontSize));
			g.drawString(code.get(i), posx, posy - scrollBar.getValue() + fontSize * i - fontSize / 3 + 1);
		}
	}

	void setSpeed(int speed)
	{
		this.speed = speed;
	}

	void update()
	{
		frame.revalidate();
		frame.repaint();
	}
}

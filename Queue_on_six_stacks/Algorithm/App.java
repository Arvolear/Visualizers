package Algorithm;

import java.util.*;
import java.awt.*;
import javax.swing.*;
import java.util.ArrayList;

public class App implements Runnable
{
    private ArrayList < Sueue > queues;
    private DynamicController dynamicController;
    private Controller controller;
    private Interface inter;
	private Menu menu;
	private Pseudocode pseudocode;
    
	private JFrame frame;
	private Pane pane;

    public App()
    {
        frame = new JFrame("Queue on six stacks");
        frame.setSize(800, 600);
		frame.setLocation(100, 50);
		frame.setResizable(false);
        
		pane = new Pane();

        controller = new Controller();
		pseudocode = new Pseudocode(frame, controller);
		Sueue.pseudocode = pseudocode;
        queues = new ArrayList<>();

		Sueue sueue = new Sueue();
		queues.add(sueue);

        inter = new Interface(frame, pane, controller, queues, pseudocode);
		menu = new Menu(frame, pane, controller);
        dynamicController = new DynamicController(controller, inter.getGrid(), pseudocode);
        
		frame.addWindowListener(controller);
        frame.setVisible(true);

		pane.setInter(inter);
		pane.setMenu(menu);

        frame.add(pane);
    }

    public void run()
    {
        Thread interThread = new Thread(inter, "Interface");
        interThread.start();

        Thread dynamicThread = new Thread(dynamicController, "Dynamic");
        dynamicThread.start();
        
        while (controller.isOpen())
        {
			while (true)
			{
				try
				{
					Thread.sleep(5);
				}
				catch (InterruptedException ex)
				{
					System.out.println("Error: " + ex);
				}

				if (controller.isStart())
				{
					inter.unhide();
					pane.setStart();
					menu.open();

					break;
				}
			}

			try
			{
				Thread.sleep(5);
			}
			catch (InterruptedException ex)
			{
				System.out.println("Error: " + ex);
			}

			if (controller.getWhat().equals("Push"))
			{
				if (!inter.getGrid().getPushText().equals(""))
				{
					Sueue tmp = new Sueue(queues.get(queues.size() - 1));
					queues.add(tmp);

					queues.get(queues.size() - 1).push(inter.getGrid().getPushText());
				}
			}
			else if (controller.getWhat().equals("Pop"))
			{
				if (!queues.get(queues.size() - 1).empty())
				{
					Sueue tmp = new Sueue(queues.get(queues.size() - 1));
					queues.add(tmp);

					queues.get(queues.size() - 1).pop();
				}
			}
			else if (controller.getWhat().equals("Clear"))
			{
				if (!queues.get(queues.size() - 1).empty())
				{
					Sueue tmp = new Sueue(queues.get(queues.size() - 1));
					queues.add(tmp);

					queues.get(queues.size() - 1).clear();
				}
			}
			else if (controller.getWhat().equals("Undo"))
			{
				if (queues.size() > 1)
				{
					queues.remove(queues.size() - 1);
				}
			}

			controller.clear();
		}

		try
		{
			interThread.join();
			dynamicThread.join();
		}
		catch (InterruptedException ex)
		{
			System.out.println("Error: " + ex);
		}
	}
}

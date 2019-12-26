package Algorithm;

import java.util.*;
import java.awt.*;

public class App implements Runnable
{
    private Sueue queue;
    private SpeedController speedController;
    private Controller controller;
    private Interface inter;

    public App()
    {
        controller = new Controller();
        queue = new Sueue();
        inter = new Interface(controller, queue);

        speedController = new SpeedController(controller, inter.getGrid());
    }

    public void run()
    {
        Thread interThread = new Thread(inter, "Interface");
        interThread.start();

        Thread speedThread = new Thread(speedController, "Speed");
        speedThread.start();
        
        while (controller.isOpen())
        {
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
                if (inter.getGrid().getPushText().equals(""))
                {
                    continue;
                }

                queue.push(inter.getGrid().getPushText());
            }
            else if (controller.getWhat().equals("Pop"))
            {
                if (queue.empty())
                {
                    continue;
                }

                queue.pop();
            }

            controller.clear();
        }

        try
        {
            interThread.join();
            speedThread.join();
        }
        catch (InterruptedException ex)
        {
            System.out.println("Error: " + ex);
        }
    }
}

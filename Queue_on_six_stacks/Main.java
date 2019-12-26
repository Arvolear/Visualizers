import java.util.*;

import Algorithm.*;

class Main
{
    public static void main(String args[])
    {
        App app = new App();

        Thread appThread = new Thread(app, "App");
        appThread.start();

        try
        {
            appThread.join();
        }
        catch (InterruptedException ex)
        {
            System.out.println("Error: " + ex);
        }
    }
}

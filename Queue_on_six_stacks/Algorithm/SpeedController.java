package Algorithm;

class SpeedController implements Runnable
{
    private Controller controller;
    private Grid grid;

    SpeedController(Controller controller, Grid grid) 
    {
        this.controller = controller;
        this.grid = grid;
    }

    public void run()
    {
        while (controller.isOpen())
        {
            try
            {
                Thread.sleep(10);
            }
            catch (InterruptedException ex)
            {
                System.out.println("Error: " + ex);
            }
            
            Element.setSpeed(grid.getSpeed());
        }
    }
}

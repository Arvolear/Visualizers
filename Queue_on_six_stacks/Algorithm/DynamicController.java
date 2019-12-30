package Algorithm;

class DynamicController implements Runnable
{
    private Controller controller;
	private Pseudocode pseudocode;
    private Grid grid;

    DynamicController(Controller controller, Grid grid, Pseudocode pseudocode) 
    {
		this.pseudocode = pseudocode;
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

			boolean show = controller.isShowCode();

			pseudocode.toggle(show);
			grid.getBox().setSelected(show);

			if (controller.isShowCode() != grid.getBox().isSelected())
			{
				controller.setShowCode(false);
			}
        }
    }
}

package Algorithm;

import java.awt.*;

class Sueue
{
    private DrawableStack output;
    private DrawableStack tmpStorage;
    private DrawableStack outputCopy;
    private DrawableStack outputHelper;
    private DrawableStack input;
    private DrawableStack inputHelper;

    private int outputToCopy;
    private boolean copying, outputIsCopied;

	private boolean displayEmpty;
	private String emptyWord;

	private Pseudocode pseudocode;

    private void checkCopy()
    {
		pseudocode.showLine(1);
		pseudocode.showLine(2);

        copying = input.size() > output.size();

		pseudocode.showLine(3);
        if (copying)
        {
			pseudocode.showLine(4);
            outputToCopy = output.size();
			pseudocode.showLine(5);
            outputIsCopied = false;
			pseudocode.showLine(6);
            performCopy();
        }
    }

    private void performCopy()
    {
		pseudocode.showLine(10);
		pseudocode.showLine(11);

        int actionsLimit = 3;

        while (!outputIsCopied && actionsLimit > 0 && !output.empty())
        {
			pseudocode.showLine(12);
			pseudocode.showLine(13);

            Element elem = new Element(output.top());
            elem.setOuterColor(new Color(181, 73, 14));

			pseudocode.showLine(14);
            tmpStorage.push(elem);

			pseudocode.showLine(15);
            output.pop();

			pseudocode.showLine(16);
            actionsLimit--;
        }

        while (actionsLimit > 0 && !input.empty())
        {
			pseudocode.showLine(19);

			pseudocode.showLine(20);
            outputIsCopied = true;

			pseudocode.showLine(21);
            Element elem0 = new Element(input.top());
            elem0.setOuterColor(new Color(181, 73, 14));

            Element elem1 = new Element(input.top());
            elem1.setOuterColor(new Color(181, 73, 14));
            
			pseudocode.showLine(22);
			output.push(elem0);

			pseudocode.showLine(23);
            outputHelper.push(elem1);

			pseudocode.showLine(24);
            input.pop();

			pseudocode.showLine(25);
            actionsLimit--;
        }

        while (actionsLimit > 0 && !tmpStorage.empty())
        {
			pseudocode.showLine(28);

			pseudocode.showLine(29);
            if (outputToCopy > 0)
            {
				pseudocode.showLine(30);
                Element elem0 = new Element(tmpStorage.top());
                elem0.setOuterColor(new Color(181, 73, 14));

                Element elem1 = new Element(tmpStorage.top());
                elem1.setOuterColor(new Color(181, 73, 14));
                
				pseudocode.showLine(31);
				output.push(elem0);
				pseudocode.showLine(32);
                outputHelper.push(elem1);

				pseudocode.showLine(33);
                outputToCopy--;
            }

			pseudocode.showLine(35);
            tmpStorage.pop();
			
			pseudocode.showLine(36);
            actionsLimit--;
        }

		pseudocode.showLine(39);
        if (tmpStorage.empty())
        {
            DrawableStack tmp;

			pseudocode.showLine(40);

			input.swap(inputHelper);
            tmp = input;
            input = inputHelper;
            inputHelper = tmp;

			pseudocode.showLine(41);
			
			outputCopy.swap(outputHelper);
            tmp = outputCopy;
            outputCopy = outputHelper;
            outputHelper = tmp;
        }

		pseudocode.showLine(43);
        copying = !tmpStorage.empty();
    }

    Sueue(Pseudocode pseudocode) 
    {
		displayEmpty = true;
		emptyWord = new String("Queue is empty");
        outputToCopy = 0;
        copying = outputIsCopied = false;

        output = new DrawableStack("Output (R)", 20, 30);
        tmpStorage = new DrawableStack("TmpStorage (S)", 20, 125);
        outputCopy = new DrawableStack("OutputCopy (RC)", 20, 220);
        outputHelper = new DrawableStack("OutputHelper (RC1)", 20, 315);
        input = new DrawableStack("Input (L)", 20, 410);
        inputHelper = new DrawableStack("InputHelper (L1)", 20, 505);

		this.pseudocode = pseudocode;
    }

    boolean empty()
    {
        return !copying && output.empty();   
    }

    void push(String s)
    {
		pseudocode.showLine(46);
		
		displayEmpty = false;
		
		if (!empty())
		{
			front().setOuterColor(new Color(13, 87, 123));
		}

        Element elem = new Element(500, 300, 50, 50, s);
	
		pseudocode.showLine(47);
        if (!copying)
        {	
			pseudocode.showLine(48);
            input.push(elem);

			pseudocode.showLine(49);
            if (!outputHelper.empty())
            {
				pseudocode.showLine(50);
                outputHelper.pop();
            }

			pseudocode.showLine(52);
            checkCopy();
        }
        else
        {
			pseudocode.showLine(54);
			
			pseudocode.showLine(55);
            inputHelper.push(elem);

			pseudocode.showLine(56);
            performCopy();
        }

		front().setOuterColor(new Color(119, 55, 196));
		pseudocode.showLine(-1);
    }

    void pop()
    {
		pseudocode.showLine(60);

		pseudocode.showLine(61);
        if (!copying)
        {
			pseudocode.showLine(62);
            output.pop();
			pseudocode.showLine(63);
            outputCopy.pop();

			pseudocode.showLine(64);
            if (!outputHelper.empty())
            {
				pseudocode.showLine(65);
                outputHelper.pop();
            }

			pseudocode.showLine(67);
            checkCopy();
        }
        else
        {
			pseudocode.showLine(69);
			
			pseudocode.showLine(70);
            outputCopy.pop();

			pseudocode.showLine(71);
            if (outputToCopy > 0)
            {
				pseudocode.showLine(72);
                outputToCopy--;
            }
            else
            {
				pseudocode.showLine(74);

				pseudocode.showLine(75);
                output.pop();
				pseudocode.showLine(76);
                outputHelper.pop();
            }

			pseudocode.showLine(78);
            performCopy();
        }
		
		if (!empty())
		{
			front().setOuterColor(new Color(119, 55, 196));
		}
		else
		{
			displayEmpty = true;
		}
		
		pseudocode.showLine(-1);
    }

    Element front()
    {
        if (!copying)
        {
            return output.top();
        }

        return outputCopy.top();
    }

    Integer getOutputToCopy()
    {
        return outputToCopy;
    }

    boolean getCopying()
    {
        return copying;
    }

    boolean getOutputIsCopied()
    {
        return outputIsCopied;
    }

    void paint(Graphics g)
    {
		if (displayEmpty)
		{
			g.setColor(new Color(230, 230, 230));
			g.setFont(new Font(Font.SERIF, Font.PLAIN, 40));
			g.drawString(emptyWord, 135, 280);
		}
		else
		{
			output.paint(g);
			outputCopy.paint(g);
			outputHelper.paint(g);

			tmpStorage.paint(g);

			input.paint(g);
			inputHelper.paint(g);
		}
	}
}

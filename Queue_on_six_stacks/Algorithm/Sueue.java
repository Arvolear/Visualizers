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

    private void checkCopy()
    {
        copying = input.size() > output.size();

        if (copying)
        {
            outputToCopy = output.size();
            outputIsCopied = false;
            performCopy();
        }
    }

    private void performCopy()
    {
        int actionsLimit = 3;

        while (!outputIsCopied && actionsLimit > 0 && !output.empty())
        {
            Element elem = new Element(output.top());
            elem.setOuterColor(new Color(181, 73, 14));

            tmpStorage.push(elem);

            output.pop();

            actionsLimit--;
        }

        while (actionsLimit > 0 && !input.empty())
        {
            outputIsCopied = true;

            Element elem0 = new Element(input.top());
            elem0.setOuterColor(new Color(181, 73, 14));
            output.push(elem0);

            Element elem1 = new Element(input.top());
            elem1.setOuterColor(new Color(181, 73, 14));
            outputHelper.push(elem1);

            input.pop();

            actionsLimit--;
        }

        while (actionsLimit > 0 && !tmpStorage.empty())
        {
            if (outputToCopy > 0)
            {
                Element elem0 = new Element(tmpStorage.top());
                elem0.setOuterColor(new Color(181, 73, 14));
                output.push(elem0);

                Element elem1 = new Element(tmpStorage.top());
                elem1.setOuterColor(new Color(181, 73, 14));
                outputHelper.push(elem1);

                outputToCopy--;
            }

            tmpStorage.pop();
            actionsLimit--;
        }

        if (tmpStorage.empty())
        {
            DrawableStack tmp;

            tmp = input;
            input = inputHelper;
            inputHelper = tmp;

            tmp = outputCopy;
            outputCopy = outputHelper;
            outputHelper = tmp;
        }

        copying = !tmpStorage.empty();
    }

    Sueue() 
    {
		displayEmpty = true;
		emptyWord = new String("Queue is empty");
        outputToCopy = 0;
        copying = outputIsCopied = false;

        output = new DrawableStack("Output", 20, 30);
        tmpStorage = new DrawableStack("TmpStorage", 20, 125);
        outputCopy = new DrawableStack("OutputCopy", 20, 220);
        outputHelper = new DrawableStack("OutputHelper", 20, 315);
        input = new DrawableStack("Input", 20, 410);
        inputHelper = new DrawableStack("InputHelper", 20, 505);
    }

    boolean empty()
    {
        return !copying && output.empty();   
    }

    void push(String s)
    {
		displayEmpty = false;
		
		if (!empty())
		{
			front().setOuterColor(new Color(13, 87, 123));
		}

        Element elem = new Element(500, 300, 50, 50, s);

        if (!copying)
        {
            input.push(elem);

            if (!outputHelper.empty())
            {
                outputHelper.pop();
            }

            checkCopy();
        }
        else
        {
            inputHelper.push(elem);

            performCopy();
        }

		front().setOuterColor(new Color(119, 55, 196));
    }

    void pop()
    {
        if (!copying)
        {
            output.pop();
            outputCopy.pop();

            if (!outputHelper.empty())
            {
                outputHelper.pop();
            }

            checkCopy();
        }
        else
        {
            outputCopy.pop();

            if (outputToCopy > 0)
            {
                outputToCopy--;
            }
            else
            {
                output.pop();
                outputHelper.pop();
            }

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

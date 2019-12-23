import java.util.Stack;

class Queue6<T>
{
    private Stack<T> output;
    private Stack<T> tmpStorage;
    private Stack<T> outputCopy;
    private Stack<T> outputHelper;
    private Stack<T> input;
    private Stack<T> inputHelper;

    private int outputToCopy;
    private boolean copying, outputIsCopied;

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
            tmpStorage.push(output.peek());
            output.pop();
            
            actionsLimit--;
        }

        while (actionsLimit > 0 && !input.empty())
        {
            outputIsCopied = true;

            output.push(input.peek());
            outputHelper.push(input.peek());

            input.pop();

            actionsLimit--;
        }

        while (actionsLimit > 0 && !tmpStorage.empty())
        {
            if (outputToCopy > 0)
            {
                output.push(tmpStorage.peek());
                outputHelper.push(tmpStorage.peek());

                actionsLimit--;
            }
            
            tmpStorage.pop();
            actionsLimit--;
        }

        if (tmpStorage.empty())
        {
            Stack<T> tmp;
            
            tmp = input;
            input = inputHelper;
            inputHelper = tmp;

            tmp = outputCopy;
            outputCopy = outputHelper;
            outputHelper = tmp;
        }

        copying = !tmpStorage.empty();
    }

    Queue6() 
    {
        outputToCopy = 0;
        copying = outputIsCopied = false;

        output = new Stack<T>();
        tmpStorage = new Stack<T>();
        outputCopy = new Stack<T>();
        outputHelper = new Stack<T>();
        input = new Stack<T>();
        inputHelper = new Stack<T>();
    }

    boolean empty()
    {
        return !copying && output.empty();   
    }

    void push(T elem)
    {
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
    }

    T front()
    {
        if (!copying)
        {
            return output.peek();
        }

        return outputCopy.peek();
    }

    Stack<T> getOutput()
    {
        return output;
    }
    
    Stack<T> getOutputCopy()
    {
        return outputCopy;
    }
    
    Stack<T> getOutputHelper()
    {
        return outputHelper;
    }
    
    Stack<T> getTmpStorage()
    {
        return tmpStorage;
    }
    
    Stack<T> getInput()
    {
        return input;
    }
    
    Stack<T> getInputHelper()
    {
        return inputHelper;
    }
}

package Algorithm;

import java.math.BigDecimal;

public class Mandelbrot implements FractalComputation
{
    @Override
    public int compute(Complex num, BigDecimal maxAbsSquared, int maxIterations)
    {
        int iteration = 0;
		Complex cur = new Complex();

        while (cur.absSquared().compareTo(maxAbsSquared) <= 0 && iteration < maxIterations)
        {
            cur = cur.mul(cur).add(num);
            iteration++;
        }

        return iteration;
    }
}

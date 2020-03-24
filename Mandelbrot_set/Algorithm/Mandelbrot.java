package Algorithm;

public class Mandelbrot implements FractalComputation
{
    @Override
    public int compute(Complex number, double maxAbs, int maxIterations)
    {
        int iteration = 0;
        Complex cur = new Complex();

        while (cur.abs() <= maxAbs && iteration < maxIterations)
        {
            cur.mul(cur).add(number);
            iteration++;
        }

        return iteration;
    }
}

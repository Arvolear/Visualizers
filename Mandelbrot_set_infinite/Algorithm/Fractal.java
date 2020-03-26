package Algorithm;

import java.awt.*;
import java.awt.image.*;
import javax.imageio.*;
import java.io.File;
import java.io.IOException;
import java.math.BigDecimal;
import java.math.MathContext;

public class Fractal
{
    private static int IMAGE_WIDTH = 720;
    private static int IMAGE_HEIGHT = 480;

	private static String outputDir = "./Output/Mandelbrot/";
	private static String prefix = "out0-";

	private static String ext = "png";
	private int imageCounter = 0;

	private MathContext precision;

    private int maxIterations;
    private BigDecimal maxAbsSquared;

    private double realBeg;
    private double realEnd;
    private double imagBeg;
    private double imagEnd;

	private BigDecimal zoom;
	private BigDecimal realOffset;
	private BigDecimal imagOffset;

	private BufferedImage image;

    private int threadCompleatedCounter;

    private FractalComputation computation;

	private boolean completed;

    public Fractal(FractalComputation computation)
    {
        maxIterations = 70;
        maxAbsSquared = new BigDecimal("4");

		precision = new MathContext(10);

        realBeg = -2.0;
        realEnd = 1.0;
        imagBeg = -1.0;
        imagEnd = 1.0;

		zoom = BigDecimal.ONE;
		realOffset = BigDecimal.ZERO;
		imagOffset = BigDecimal.ZERO;
        
        this.computation = computation;
		completed = true;

		image = new BufferedImage(IMAGE_WIDTH, IMAGE_HEIGHT, BufferedImage.TYPE_INT_ARGB);
    }

    private BigDecimal getReal(int j)
    {
        return (new BigDecimal(((double)j / (double)IMAGE_WIDTH) * (realEnd - realBeg) + realBeg)).divide(zoom, precision).add(realOffset, precision);
    }

    private BigDecimal getImag(int i)
    {
        return (new BigDecimal(((double)i / (double)IMAGE_HEIGHT) * (imagEnd - imagBeg) + imagBeg)).divide(zoom, precision).add(imagOffset, precision);
    }

    private void spreadComputeToThreads(final int number)
    {
        for (int t = 0; t < number; t++)
        {
            final int threadNumber = t;

            Thread computeThread = new Thread(new Runnable()
            {
                @Override
                public void run()
                {
                    for (int i = threadNumber; i < IMAGE_HEIGHT; i += number)
                    {
                        for (int j = 0; j < IMAGE_WIDTH; j++)
                        {
                            BigDecimal real = getReal(j);
                            BigDecimal imag = getImag(i);

                            Complex point = new Complex(real, imag);

                            int iterations = computation.compute(point, maxAbsSquared, maxIterations);

                            float hue = 1.0f * iterations / maxIterations; // hue
                            float saturation = 1.0f; // saturation
                            float value = iterations < maxIterations ? 1.0f : 0.0f; // value

                            synchronized(Fractal.this)
                            {
                                image.setRGB(j, i, Color.getHSBColor(hue, saturation, value).getRGB());
                            }
                        }
                    }

                    threadCompleatedCounter++;

					if (threadCompleatedCounter == number)
					{
						saveImage();
						completed = true;
					}
				}
			});

			computeThread.start();
		}
	}

	public void compute()
	{
		completed = false;
		threadCompleatedCounter = 0;

		spreadComputeToThreads(4);
	}

	public void zoomIn(Point point)
	{
        BigDecimal realOld = (new BigDecimal(((double)point.x / (double)IMAGE_WIDTH) * (realEnd - realBeg) + realBeg)).divide(zoom, precision);
        BigDecimal imagOld = (new BigDecimal(((double)point.y / (double)IMAGE_HEIGHT) * (imagEnd - imagBeg) + imagBeg)).divide(zoom, precision);
		
		zoom = zoom.multiply(new BigDecimal("2"), precision);	
		maxIterations *= 1.15;
		setPrecision((int)(precision.getPrecision() * 1.15));
        
        BigDecimal realNew = (new BigDecimal(((double)point.x / (double)IMAGE_WIDTH) * (realEnd - realBeg) + realBeg)).divide(zoom, precision);
        BigDecimal imagNew = (new BigDecimal(((double)point.y / (double)IMAGE_HEIGHT) * (imagEnd - imagBeg) + imagBeg)).divide(zoom, precision);

		realOffset = realOffset.subtract(realNew.subtract(realOld, precision), precision);
		imagOffset = imagOffset.subtract(imagNew.subtract(imagOld, precision), precision);
	}
	
	public void zoomOut()
	{
		zoom = zoom.divide(new BigDecimal("2"), precision);
		maxIterations /= 1.15;
	}

	private void setPrecision(int precision)
	{
		this.precision = new MathContext(precision);
		Complex.setPrecision(this.precision);
	}

	public BufferedImage getImage()
	{
		return image;
	}

	public boolean isCompleted()
	{
		return completed;
	}

	private void saveImage()
	{
		try
		{
			ImageIO.write(image, ext, new File(outputDir + prefix + String.valueOf(imageCounter) + "." + ext));

			System.out.println("Name: " + imageCounter + "." + ext);
			System.out.println("maxAbsSquared = " + maxAbsSquared + ", maxIterations = " + maxIterations);
			System.out.println("Bounds: ");
			System.out.println("realBeg = " + realBeg + ", realEnd = " + realEnd);
			System.out.println("imagBeg = " + imagBeg + ", imagEnd = " + imagEnd);
			System.out.println();

			imageCounter++;
		}
		catch (Exception ex)
		{}
	}
}

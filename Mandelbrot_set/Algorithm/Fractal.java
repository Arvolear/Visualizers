package Algorithm;

import java.awt.*;
import java.awt.image.*;
import javax.imageio.*;
import java.io.File;
import java.io.IOException;

public class Fractal
{
    private static int IMAGE_WIDTH = 720;
    private static int IMAGE_HEIGHT = 480;

	private static String outputDir = "./Output/Mandelbrot/";
	private static String ext = "png";
	private int imageCounter = 0;

    private int maxIterations;
    private double maxAbs;

    private double realBeg;
    private double realEnd;
    private double imagBeg;
    private double imagEnd;

	private double zoom;
	private double realOffset;
	private double imagOffset;

	private BufferedImage image;

    private int threadCompleatedCounter;

    private FractalComputation computation;

	private boolean completed;

    public Fractal(FractalComputation computation)
    {
        maxIterations = 80;
        maxAbs = 2.0;

        realBeg = -2.0;
        realEnd = 1.0;
        imagBeg = -1.0;
        imagEnd = 1.0;

		zoom = 1.0;
		realOffset = 0.0;
		imagOffset = 0.0;
        
        this.computation = computation;
		completed = true;

		image = new BufferedImage(IMAGE_WIDTH, IMAGE_HEIGHT, BufferedImage.TYPE_INT_ARGB);
    }

    private double getReal(int j)
    {
        return (((double)j / (double)IMAGE_WIDTH) * (realEnd - realBeg) + realBeg) / zoom + realOffset;
    }

    private double getImag(int i)
    {
        return (((double)i / (double)IMAGE_HEIGHT) * (imagEnd - imagBeg) + imagBeg) / zoom + imagOffset;
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
                            double real = getReal(j);
                            double imag = getImag(i);

                            Complex point = new Complex(real, imag);

                            int iterations = computation.compute(point, maxAbs, maxIterations);

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
        double realOld = (((double)point.x / (double)IMAGE_WIDTH) * (realEnd - realBeg) + realBeg) / zoom;
        double imagOld = (((double)point.y / (double)IMAGE_HEIGHT) * (imagEnd - imagBeg) + imagBeg) / zoom;
		
		zoom *= 2;	
		maxIterations *= 1.15;
        
		double realNew = (((double)point.x / (double)IMAGE_WIDTH) * (realEnd - realBeg) + realBeg) / zoom;
        double imagNew = (((double)point.y / (double)IMAGE_HEIGHT) * (imagEnd - imagBeg) + imagBeg) / zoom;

		realOffset -= realNew - realOld;
		imagOffset -= imagNew - imagOld;
	}
	
	public void zoomOut()
	{
		zoom /= 2;	
		maxIterations /= 1.15;
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
			ImageIO.write(image, ext, new File(outputDir + String.valueOf(imageCounter) + "." + ext));

			System.out.println("Name: " + imageCounter + "." + ext);
			System.out.println("maxAbsSquared = " + maxAbs + ", maxIterations = " + maxIterations);
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

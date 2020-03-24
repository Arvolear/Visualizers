package Algorithm;

public class Complex
{
    private double real;
    private double imag;

    public Complex()
    {
        this.real = 0.0;
        this.imag = 0.0;
    }

    public Complex(double real)
    {
        this.real = real;
        this.imag = 0.0;
    }

    public Complex(double real, double imag)
    {
        this.real = real;
        this.imag = imag;
    }

    public Complex copy()
    {
        return new Complex(real, imag);
    }

    public static Complex add(Complex first, Complex second)
    {
        Complex tmp = first.copy();
        return tmp.add(second);
    }

    public Complex add(Complex other)
    {
        real += other.real;
        imag += other.imag;

        return this;
    }

    public static Complex sub(Complex first, Complex second)
    {
        Complex tmp = first.copy();
        return tmp.sub(second);
    }

    public Complex sub(Complex other)
    {
        real -= other.real;
        imag -= other.imag;

        return this;
    }

    public static Complex mul(Complex first, Complex second)
    {
        Complex tmp = first.copy();
        return tmp.mul(second);
    }

    public Complex mul(Complex other)
    {
        double newReal;

        newReal = real * other.real - imag * other.imag;
        imag = real * other.imag + imag * other.real;

        real = newReal;

        return this;
    }

    public static Complex div(Complex first, Complex second)
    {
        Complex tmp = first.copy();
        return tmp.div(second);
    }

    public Complex div(Complex other)
    {
        Complex tmp = other.copy();

        mul(other.conjugate());
        tmp.mul(tmp.conjugate());

        real /= tmp.real;
        imag /= tmp.real;

        return this;
    }

    @Override
    public boolean equals(Object obj)
    {
        if (this == obj)
        {
            return true;
        }

        if (obj instanceof Complex)
        {
            Complex other = (Complex)obj;

            return real == other.real && imag == other.imag;
        }

        return false;
    }

	@Override
	public int hashCode()
	{
		return (String.valueOf(real) + String.valueOf(imag)).hashCode();
	}

    public Complex negate()
    {
        real = -real;
        imag = -imag;

        return this;
    }

    public Complex conjugate()
    {
        imag = -imag;

        return this;
    }

    public double abs()
    {
        return Math.sqrt(real * real + imag * imag);
    }
}

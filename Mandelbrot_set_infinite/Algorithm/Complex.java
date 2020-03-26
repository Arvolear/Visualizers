package Algorithm;

import java.math.BigDecimal;
import java.math.MathContext;

class Complex
{
	private BigDecimal real;
	private BigDecimal imag;

	private static MathContext precision = new MathContext(10);
	
	public Complex()
	{
		this.real = BigDecimal.ZERO;
		this.imag = BigDecimal.ZERO;
	}

	public Complex(BigDecimal real, BigDecimal imag)
	{
		this.real = real;
		this.imag = imag;
	}

	public Complex(Complex other)
	{
		real = new BigDecimal(other.real.toString());
		imag = new BigDecimal(other.imag.toString());
	}

	public Complex mul(Complex other)
	{
		Complex res = new Complex();

		res.real = real.multiply(other.real, precision).subtract(imag.multiply(other.imag, precision), precision);
		res.imag = real.multiply(other.imag, precision).add(imag.multiply(other.real, precision), precision);

		return res;
	}

	public Complex add(Complex other)
	{
		Complex res = new Complex();

		res.real = real.add(other.real, precision);
		res.imag = imag.add(other.imag, precision);

		return res;
	}

	public BigDecimal absSquared()
	{
		return real.multiply(real, precision).add(imag.multiply(imag, precision), precision);
	}

	public void reset()
	{
		real = BigDecimal.ZERO;
		imag = BigDecimal.ZERO;
	}

	public static void setPrecision(MathContext precision)
	{
		Complex.precision = precision;
	}
}

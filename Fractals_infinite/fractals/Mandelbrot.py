import math

from interfaces.IFractal import IFractal

class Mandelbrot(IFractal):
    def __init__(self):
        self.MAX_ABS = 2.0

        self.realBeg = -2.5
        self.realEnd = 1.5
        self.imagBeg = -1.2
        self.imagEnd = 1.2

    def compute(self, num, maxIterations):
        iteration = 0
        cur = complex()

        while (abs(cur) <= self.MAX_ABS and iteration < maxIterations):
            cur = cur * cur + num
            iteration += 1

        # antialiasing
        absSq = abs(cur) * abs(cur)

        if (absSq > 0):
            log = math.log(absSq, 2)
            
            if (log > 0):
                return max(1, iteration + 1 - math.log(log))

        return iteration

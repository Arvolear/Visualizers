import math

from interfaces.IFractal import IFractal

class Julia(IFractal):
    def __init__(self):
        self.MAX_ABS = 2.0

        self.realBeg = -2.0
        self.realEnd = 2.0
        self.imagBeg = -1.2
        self.imagEnd = 1.2

    def compute(self, num, maxIterations):
        iteration = 0
        cur = num

        while (abs(cur) <= self.MAX_ABS and iteration < maxIterations):
            cur = cur * cur + complex(-0.8, 0.156)
            iteration += 1

        # antialiasing
        absSq = abs(cur) * abs(cur)

        if (absSq > 0):
            log = math.log(absSq, 2)

            if (log > 0):
                return max(1, iteration + 1 - math.log(log))

        return iteration

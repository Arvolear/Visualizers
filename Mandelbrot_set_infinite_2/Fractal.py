import pygame
import colorsys
import threading

class Fractal:
    def __init__(self, size, underlyingFractal):
        self.IMAGE_WIDTH = size[0]
        self.IMAGE_HEIGHT = size[1]
        
        self.MAX_ITERATIONS = 70
        self.MAX_MOVE = 0.1        

        self.zoom = 1.0
        self.realOffset = 0.0
        self.imagOffset = 0.0

        self.complete = True
        self.completedCounter = 0
        self.lock = threading.Lock()

        self.image = pygame.Surface((self.IMAGE_WIDTH, self.IMAGE_HEIGHT))

        self.underlyingFractal = underlyingFractal

    def _getReal(self, j):
        return (((j / self.IMAGE_WIDTH) * (self.underlyingFractal.rightBound() - self.underlyingFractal.leftBound()) + self.underlyingFractal.leftBound()) / self.zoom)

    def _getImag(self, i):
        return (((i / self.IMAGE_HEIGHT) * (self.underlyingFractal.topBound() - self.underlyingFractal.bottomBound()) + self.underlyingFractal.bottomBound()) / self.zoom)

    def _getRealWithOffset(self, i):
        return self._getReal(i) + self.realOffset

    def _getImagWithOffset(self, i):
        return self._getImag(i) + self.imagOffset

    def _drawMultithreaded(self, fromY, toY, fromX, toX, numOfThreads):
        self.complete = False
        self.completedCounter = 0

        for k in range(0, numOfThreads):
            thread = threading.Thread(target = self._drawInThread, args = (k + fromY, toY, fromX, toX, numOfThreads))
            thread.start()
    
    def _drawInThread(self, fromY, toY, fromX, toX, numOfThreads):
        for i in range(fromY, toY, numOfThreads):
            for j in range(fromX, toX):
                num = complex(self._getRealWithOffset(j), self._getImagWithOffset(i))
                iterations = self.underlyingFractal.compute(num, self.MAX_ITERATIONS)
                
                color = pygame.Color(self._hsv2rgb(
                    iterations / self.MAX_ITERATIONS % 0.5 + 0.6,
                    max(0.0, 0.7 - iterations / self.MAX_ITERATIONS),
                    1 if iterations < self.MAX_ITERATIONS else 0)
                )

                self.image.set_at((j, i), color)

        with self.lock:
            self.completedCounter += 1

            if self.completedCounter == numOfThreads:
                self.complete = True    

    def _hsv2rgb(self, h, s, v):
        return tuple(round(i * 255) for i in colorsys.hsv_to_rgb(h, s, v))

    def draw(self):
        if (not self.complete):
            return

        self._drawMultithreaded(0, self.IMAGE_HEIGHT, 0, self.IMAGE_WIDTH, 8)

    def move(self, where):
        if (not self.complete):
            return

        pixelsVertical = int(self.IMAGE_HEIGHT / (abs(self.underlyingFractal.bottomBound()) + abs(self.underlyingFractal.topBound())) * self.MAX_MOVE)
        pixelsHorizontal = int(self.IMAGE_WIDTH / (abs(self.underlyingFractal.leftBound()) + abs(self.underlyingFractal.rightBound())) * self.MAX_MOVE)

        if (where == pygame.K_UP):
            self.imagOffset -= self.MAX_MOVE / self.zoom

            for i in range(self.IMAGE_HEIGHT - 1, pixelsVertical, -1):
                for j in range(0, self.IMAGE_WIDTH):
                    color = self.image.get_at((j, i - pixelsVertical))
                    self.image.set_at((j, i), color)

            self._drawMultithreaded(0, pixelsVertical + 1, 0, self.IMAGE_WIDTH, 8)
        
        if (where == pygame.K_RIGHT):
            self.realOffset += self.MAX_MOVE / self.zoom

            for i in range(0, self.IMAGE_HEIGHT):
                for j in range(0, self.IMAGE_WIDTH - pixelsHorizontal):
                    color = self.image.get_at((j + pixelsHorizontal, i))
                    self.image.set_at((j, i), color)

            self._drawMultithreaded(0, self.IMAGE_HEIGHT, self.IMAGE_WIDTH - pixelsHorizontal, self.IMAGE_WIDTH, 8)

        if (where == pygame.K_LEFT):
            self.realOffset -= self.MAX_MOVE / self.zoom

            for i in range(0, self.IMAGE_HEIGHT):
                for j in range(self.IMAGE_WIDTH - 1, pixelsHorizontal, -1):
                    color = self.image.get_at((j - pixelsHorizontal, i))
                    self.image.set_at((j, i), color)

            self._drawMultithreaded(0, self.IMAGE_HEIGHT, 0, pixelsHorizontal + 1, 8)

        if (where == pygame.K_DOWN):
            self.imagOffset += self.MAX_MOVE / self.zoom

            for i in range(0, self.IMAGE_HEIGHT - pixelsVertical):
                for j in range(0, self.IMAGE_WIDTH):
                    color = self.image.get_at((j, i + pixelsVertical))
                    self.image.set_at((j, i), color)

            self._drawMultithreaded(self.IMAGE_HEIGHT - pixelsVertical, self.IMAGE_HEIGHT, 0, self.IMAGE_WIDTH, 8)

    def zoomIn(self, point):
        if (not self.complete):
            return

        x = point[0] * self.IMAGE_WIDTH
        y = point[1] * self.IMAGE_HEIGHT

        realOld = self._getReal(x)
        imagOld = self._getImag(y)

        self.zoom *= 2
        self.MAX_ITERATIONS *= 1.15

        realNew = self._getReal(x)
        imagNew = self._getImag(y)

        self.realOffset -= (realNew - realOld)
        self.imagOffset -= (imagNew - imagOld)

        self.draw()

    def zoomOut(self):
        if (not self.complete):
            return

        self.zoom /= 2
        self.MAX_ITERATIONS /= 1.15

        self.draw()

    def getFractal(self):
        return self.image

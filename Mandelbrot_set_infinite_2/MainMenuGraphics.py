from FractalGraphics import FractalGraphics
from Fractals.Mandelbrot import Mandelbrot
from Fractals.Julia import Julia
import sys
import pygame

class MainMenuGraphics:
    def __init__(self):        
        self.size = (1920, 1080)        
        self.centerX = self.size[0] / 2
        self.centerY = self.size[1] / 2

        self.screen = pygame.display.set_mode(self.size)        

        self._initAssets()

    def _initAssets(self):
        self.startButton = pygame.image.load('./images/start.png')          
        self.startButton = pygame.transform.scale(self.startButton, (300, 300))

    def play(self):
        while True:
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    sys.exit()

                if event.type == pygame.MOUSEBUTTONDOWN:                           
                    rect = self.startButton.get_rect().move((self.centerX - 150, self.centerY - 150))

                    if rect.collidepoint(event.pos):                        
                        if event.button == 1:
                            fractal = FractalGraphics(self.screen, Mandelbrot())
                            fractal.play()
                        
                        if event.button == 3:
                            fractal = FractalGraphics(self.screen, Julia())
                            fractal.play()         
            self.show()

    def show(self):
        self.screen.fill((163, 109, 255))
        self.screen.blit(self.startButton, (self.centerX - 150, self.centerY - 150))

        pygame.display.flip()
